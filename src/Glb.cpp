/**
 * Created by IBM on 2022/5/8.
 */
#include <fstream>

#include "Glb.h"

using namespace osg;

Glb::KHRTechniques::~KHRTechniques() {
    vlaue.clear();
}

Glb::Primitive::~Primitive() {
    if (extensions != NULL) {
        std::map<std::string, KHRTechniques *>::iterator iter = extensions->begin();
        while (iter != extensions->end()) {
            delete iter->second;
            iter++;
        }
        extensions->clear();
        delete extensions;
    }
    extensions = NULL;
}

Glb::Material::~Material() {
    pbrMetallicRoughness.clear();
    std::map<std::string, KHRTechniques *>::iterator iter = extensions.begin();
    while (iter != extensions.end()) {
        delete iter->second;
        iter++;

    }
    extensions.clear();
}


Glb::Mesh::~Mesh() {
    int length = primitives.size();
    for (int i = 0; i < length; i++) {
        delete primitives[i];
    }
    primitives.clear();
}

Glb::Image::Image() {
    this->extras = new Extras();
}

Glb::Image::~Image() {
    delete this->extras;
}

Glb::Buffer::Buffer() {
    this->extras = new Extras();
}

Glb::Buffer::~Buffer() {
    delete this->extras;
}

Glb::Material *Glb::Material::clone(Glb::Material *material) {
    Glb::Material *result = new Glb::Material();
    result->alphaCutoff = material->alphaCutoff;
    result->name = material->name;
    result->alphaMode = material->alphaMode;
    result->alphaMode = material->alphaMode;
    result->doubleSided = material->doubleSided;
    result->emissiveFactor[0] = material->emissiveFactor[0];
    result->emissiveFactor[1] = material->emissiveFactor[1];
    result->emissiveFactor[2] = material->emissiveFactor[2];

    return result;
    std::cout << "Gltf::Material::clone" << std::endl;

}

Glb::Glb() {

    this->extras = new Extras();

}

Glb::~Glb() {
    delete asset;
    delete extras;

    int length = scenes.size();
    for (int i = 0; i < length; i++) {
        delete scenes[i];
    }
    scenes.clear();
    length = accessors.size();
    for (int i = 0; i < length; i++) {
        delete accessors[i];
    }
    accessors.clear();

    length = images.size();
    for (int i = 0; i < length; i++) {
        delete images[i];
    }
    images.clear();

    length = textures.size();
    for (int i = 0; i < length; i++) {
        delete textures[i];
    }
    textures.clear();

    length = buffers.size();
    for (int i = 0; i < length; i++) {
        delete buffers[i];
    }
    buffers.clear();

    length = bufferViews.size();
    for (int i = 0; i < length; i++) {
        delete bufferViews[i];
    }
    bufferViews.clear();
    length = materials.size();
    for (int i = 0; i < length; i++) {
        delete materials[i];
    }
    materials.clear();

    length = nodes.size();
    for (int i = 0; i < length; i++) {
        delete nodes[i];
    }
    nodes.clear();

    length = meshes.size();
    for (int i = 0; i < length; i++) {
        delete meshes[i];
    }
    meshes.clear();

    length = skins.size();
    for (int i = 0; i < length; i++) {
        delete skins[i];
    }
    skins.clear();


}


void Glb::writeB3dm(std::string output, std::string outname) {
    //output=output+"/tileset.json";

    std::cout << "Glb" << std::endl;
    Glb::Buffer *buffer = this->buffers[0];

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriter = rapidjson::Writer<rapidjson::StringBuffer>(s);

    writeJSON(this, &jsonWriter);
    std::string jsonString = s.GetString();
    std::cout << "gltfLing: " << jsonString.length() << std::endl;
    //glb
    int jsonPadding = (4 - (jsonString.length() & 3)) & 3;
    int binPadding = (4 - (buffer->byteLength & 3)) & 3;
    int glbLength = 12 + (8 + jsonString.length() + jsonPadding + 8 + buffer->byteLength + binPadding); // length

    output = output + "/" + outname + ".b3dm";
    FILE *file = fopen(output.c_str(), "wb");                    //b3dm
    rapidjson::StringBuffer featureTables;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriterFeatureTables = rapidjson::Writer<rapidjson::StringBuffer>(
            featureTables);

    jsonWriterFeatureTables.StartObject();
    jsonWriterFeatureTables.Key("BATCH_LENGTH");
    jsonWriterFeatureTables.Int(0);
    jsonWriterFeatureTables.EndObject();

    std::string featureTableJson = featureTables.GetString();
    int remainder = (featureTableJson.length() + 28) % 8;
    int featureTableJsonPadding = (remainder == 0) ? 0 : 8 - remainder;

    int featureTableJsonByteLength = featureTableJson.length() + featureTableJsonPadding;


    //头长度
    int headerByteLength = 28;
    //b3dm的总长度=gltf的长度 + 28字节头长度 + BATCH_LENGTH的长度 + 属性的长度
    unsigned int byteLength = headerByteLength + featureTableJsonByteLength + glbLength;
    fwrite("b3dm", sizeof(char), 4, file); // magic
    uint32_t writeHeader[6];//version:1,
    writeHeader[0] = 1;//version
    writeHeader[1] = byteLength;//总长度
    writeHeader[2] = featureTableJsonByteLength;//要素表长度
    writeHeader[3] = 0;//要素表二进制的长度
    writeHeader[4] = 0;//批量表的长度
    writeHeader[5] = 0;//批量表二进制的长度
    fwrite(writeHeader, sizeof(uint32_t), 6, file); // b3dm header
    //要素表 // featureTable json
    fwrite(featureTableJson.c_str(), sizeof(char), featureTableJson.length(), file);
    for (int i = 0; i < featureTableJsonPadding; i++) {
        fwrite(" ", sizeof(char), 1, file);
    }

    fwrite("glTF", sizeof(char), 4, file); // magic
    writeHeader[0] = 2; // 版本
    writeHeader[1] = glbLength; //长度
    fwrite(writeHeader, sizeof(uint32_t), 2, file); // GLB header
    writeHeader[0] = jsonString.length() + jsonPadding; // 2.0 - chunkLength / 1.0 - contentLength
    writeHeader[1] = 0x4E4F534A; // 2.0 - chunkType JSON
    fwrite(writeHeader, sizeof(uint32_t), 2, file);
    fwrite(jsonString.c_str(), sizeof(char), jsonString.length(), file);//输出json串
    //输出四字节对齐
    for (int i = 0; i < jsonPadding; i++) {
        fwrite(" ", sizeof(char), 1, file);
    }
    writeHeader[0] = buffer->byteLength + binPadding; // chunkLength
    writeHeader[1] = 0x004E4942; // chunkType BIN
    fwrite(writeHeader, sizeof(uint32_t), 2, file);
    fwrite(&buffer->extras->_pipeline->source[0], sizeof(unsigned char), buffer->byteLength, file);
    for (int i = 0; i < binPadding; i++) {
        fwrite("\0", sizeof(char), 1, file);
    }

    fclose(file);
}

void Glb::writeGlb(std::string output, std::string outname) {
    //output=output+"/tileset.json";

    std::cout << "Glb" << std::endl;
    Glb::Buffer *buffer = this->buffers[0];

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriter = rapidjson::Writer<rapidjson::StringBuffer>(s);

    writeJSON(this, &jsonWriter);
    std::string jsonString = s.GetString();

    std::cout << "gltfLing: " << jsonString.length() << std::endl;
    int jsonPadding = (4 - (jsonString.length() & 3)) & 3;
    int binPadding = (4 - (buffer->byteLength & 3)) & 3;
    int glbLength = 12 + (8 + jsonString.length() + jsonPadding + 8 + buffer->byteLength + binPadding); // length

    output = output + "/" + outname + ".glb";
    FILE *file = fopen(output.c_str(), "wb");                    //b3dm
    //glb
    glbLength = 12 + (8 + jsonString.length() + jsonPadding + 8 + buffer->byteLength); // length
    glbLength += binPadding;

    uint32_t writeHeader[2];//version:1,

    fwrite("glTF", sizeof(char), 4, file); // magic
    writeHeader[0] = 2; // 版本
    writeHeader[1] = glbLength; //长度
    fwrite(writeHeader, sizeof(uint32_t), 2, file); // GLB header

    writeHeader[0] = jsonString.length() + jsonPadding; // 2.0 - chunkLength / 1.0 - contentLength
    writeHeader[1] = 0x4E4F534A; // 2.0 - chunkType JSON
    fwrite(writeHeader, sizeof(uint32_t), 2, file);
    fwrite(jsonString.c_str(), sizeof(char), jsonString.length(), file);//输出json串

    //输出四字节对齐
    for (int i = 0; i < jsonPadding; i++) {
        fwrite(" ", sizeof(char), 1, file);
    }

    writeHeader[0] = buffer->byteLength + binPadding; // chunkLength
    writeHeader[1] = 0x004E4942; // chunkType BIN
    fwrite(writeHeader, sizeof(uint32_t), 2, file);
    fwrite(&buffer->extras->_pipeline->source[0], sizeof(unsigned char), buffer->byteLength, file);
    for (int i = 0; i < binPadding; i++) {
        fwrite("\0", sizeof(char), 1, file);
    }

    fclose(file);
}


Glb *Glb::parse(Osgb *osgb) {
    Glb *gltf = NULL;
    Geometry *geometry = NULL;

    if (osgb->pagedLod.size() > 0) {
        geometry = osgb->pagedLod[0]->geode[0]->geometry;
    }
    if (osgb->geode.size() > 0) {
        geometry = osgb->geode[0]->geometry;
    }
    if (geometry != NULL) {
        gltf = new Glb();

        gltf->asset = new Glb::Asset();

        gltf->scene = 0;

        // Scene
        Glb::Scene *scene = new Glb::Scene();
        gltf->scenes.push_back(scene);
        scene->nodes.push_back(0);
        // Node
        Glb::Node *node = new Glb::Node();
        gltf->nodes.push_back(node);
        node->mesh = 0;

        // Mesh
        Glb::Mesh *meshe = new Glb::Mesh();
        gltf->meshes.push_back(meshe);
        Glb::Primitive *primitive = new Glb::Primitive();
        meshe->primitives.push_back(primitive);
        primitive->attributes["POSITION"] = 0;
        //primitive->attributes["NORMAL"] = 1;
        primitive->attributes["TEXCOORD_0"] = 1;
        primitive->indices = 2;
        primitive->material = 0;
        primitive->mode = 4;

        // Material
        Glb::Material *material = new Glb::Material();
        gltf->materials.push_back(material);
        //material->alphaMode = "OPAQUE";
        material->doubleSided = false;
        material->emissiveFactor[0] = 0;
        material->emissiveFactor[1] = 0;
        material->emissiveFactor[2] = 0;
        material->pbrMetallicRoughness["baseColorTexture"].push_back(0);
        material->pbrMetallicRoughness["baseColorFactor"].push_back(1.0);
        material->pbrMetallicRoughness["baseColorFactor"].push_back(1.0);
        material->pbrMetallicRoughness["baseColorFactor"].push_back(1.0);
        material->pbrMetallicRoughness["baseColorFactor"].push_back(1.0);
        material->pbrMetallicRoughness["metallicFactor"].push_back(0.0);
        material->pbrMetallicRoughness["roughnessFactor"].push_back(0.5);

        // Texture
        Glb::Texture *texture = new Glb::Texture();
        gltf->textures.push_back(texture);
        texture->sampler = 0;
        texture->source = 0;
        Glb::Image *image = new Glb::Image();
        gltf->images.push_back(image);
        image->mimeType = "image/jpeg";
        image->bufferView = 3;

        // Sampler
        Sampler *sampler = new Sampler();
        sampler->_wrapR = WebGLConstants::REPEAT;
        sampler->_wrapS = WebGLConstants::REPEAT;
        sampler->_wrapT = WebGLConstants::REPEAT;
        sampler->_magnificationFilter = WebGLConstants::LINEAR;
        sampler->_minificationFilter = WebGLConstants::LINEAR;
        gltf->samplers.push_back(sampler);

        //Accessor
        // 5120 BYTE
        // 5121 UNSIGNED_BYTE
        // 5122 SHORT
        // 5123 UNSIGNED_SHORT
        // 5125 UNSIGNED_INT
        Glb::Accessor *accessor = new Glb::Accessor();
        gltf->accessors.push_back(accessor);

        // 顶点
        std::vector<float> *vertex = (std::vector<float> *) &geometry->vertex;
        //vertex->resize(3 * 2);
        /*vertex->clear();*/
        /*vertex->at(0)=0;
        vertex->at(0)=0;
        vertex->at(0)=0;*/

        /*vertex->push_back(yo);
        vertex->push_back(yo);
        vertex->push_back(zo);

        vertex->push_back(0);
        vertex->push_back(1);
        vertex->push_back(-20);*/

        //vertex->push_back(0);
        //vertex->push_back(1);
        //vertex->push_back(0);

        /* vertex->push_back(20);
         vertex->push_back(1);
         vertex->push_back(-20);*/

        float maxs[3] = {-100000, -100000, -100000};
        float mins[3] = {100000, 100000, 100000};
        int lv = vertex->size();
        float x, y, z;
        for (int i = 0; i < lv;) {
            x = vertex->at(i);
            y = vertex->at(i + 1);
            z = vertex->at(i + 2);

            maxs[0]=std::max(x, maxs[0]);
            maxs[1]=std::max(y, maxs[1]);
            maxs[2]=std::max(z, maxs[2]);
            mins[0]=std::min(x, mins[0]);
            mins[1]=std::min(y, mins[1]);
            mins[2]=std::min(z, mins[2]);
            i = i + 3;
        }
        gltf->_max[0] = maxs[0];
        gltf->_max[1] = maxs[1];
        gltf->_max[2] = maxs[2];
        gltf->_min[0] = mins[0];
        gltf->_min[1] = mins[1];
        gltf->_min[2] = mins[2];
        /*for (int i = 0; i < lv;) {
            x = vertex->at(i);
            y = vertex->at(i + 1);
            z = vertex->at(i + 2);
            vertex->at(i + 1) = z;
            vertex->at(i + 2) = y;

            if (maxs[0] < x)
                maxs[0] = x;
            if (maxs[1] < z)
                maxs[1] = z;
            if (maxs[2] < y)
                maxs[2] = y;
            if (mins[0] > x)
                mins[0] = x;
            if (mins[1] > z)
                mins[1] = z;
            if (mins[2] > y)
                mins[2] = y;
            i = i + 3;
        }*/

        int vnum = geometry->vertex.size() / 4;
        accessor->bufferView = 0;
        accessor->byteOffset = 0;
        accessor->componentType = 5126;//float
        accessor->count = vnum / 3;
        accessor->type = "VEC3";
        accessor->min.push_back(mins[0]);
        accessor->min.push_back(mins[1]);
        accessor->min.push_back(mins[2]);
        accessor->max.push_back(maxs[0]);
        accessor->max.push_back(maxs[1]);
        accessor->max.push_back(maxs[2]);
        // 法线 没有法线
        /*
         accessor = new Glb::Accessor();
        gltf->accessors.push_back(accessor);
         count = osgb->pagedLod[0]->geode[0]->geometry->vertex.size() / 3;
        accessor->bufferView = 0;
        accessor->byteOffset = 0;
        accessor->componentType = 5126;//float
        accessor->count = count;
        accessor->type = "VEC3";
        accessor->min.push_back(vv.GetDouble());
        accessor->max.push_back(vv.GetDouble());*/
        // 纹理坐标
        std::vector<float> *vt = (std::vector<float> *) &geometry->vt;
        //vt->resize(3 * 2);

        /*vt->clear();
        vt->push_back(0.0);
        vt->push_back(0);

        vt->push_back(0.7);
        vt->push_back(1);

        vt->push_back(0);
        vt->push_back(1);

        vt->push_back(0.7);
        vt->push_back(0);*/

        //float maxvt[2] = {-100000, -100000};
        //float minvt[2] = {100000, 100000};
        lv = vt->size();
        for (int i = 0; i < lv;) {
            //x = vt->at(i);
            y = vt->at(i + 1);
            vt->at(i + 1) = (1 - y);
            i = i + 2;
        }
        accessor = new Glb::Accessor();
        gltf->accessors.push_back(accessor);
        int vtnum = geometry->vt.size() / 4;
        accessor->bufferView = 1;
        accessor->byteOffset = 0;
        accessor->componentType = 5126;//float
        accessor->count = vtnum / 2;
        accessor->type = "VEC2";
        /*accessor->min.push_back(minvt[0]);
        accessor->min.push_back(minvt[1]);
        accessor->max.push_back(maxvt[0]);
        accessor->max.push_back(maxvt[1]);*/
        // 索引
        //std::vector<unsigned int> *vertexIndex = (std::vector<unsigned int> *) &geometry->vertexIndex;
        //vertexIndex->resize(3);
        /*vertexIndex->clear();
        vertexIndex->push_back(0);
        vertexIndex->push_back(1);
        vertexIndex->push_back(2);

        vertexIndex->push_back(0);
        vertexIndex->push_back(3);
        vertexIndex->push_back(1);*/

        accessor = new Glb::Accessor();
        gltf->accessors.push_back(accessor);
        int vi = geometry->vertexIndex.size() / 4;
        accessor->bufferView = 2;
        accessor->byteOffset = 0;
        accessor->componentType = 5125;//UNSIGNED_INT
        accessor->count = vi;
        accessor->type = "SCALAR";
        //accessor->min.push_back(0);
        //accessor->max.push_back(vertex->size() / 3 - 1);

        // Buffer
        Glb::Buffer *buffer = new Glb::Buffer();
        gltf->buffers.push_back(buffer);
        // BufferView
        // 顶点
        size_t byteLength = geometry->vertex.size();
        size_t byteOffset = 0;

        Glb::BufferView *view = new Glb::BufferView();
        gltf->bufferViews.push_back(view);
        view->buffer = 0;
        view->byteLength = byteLength;
        view->byteOffset = byteOffset;
        view->byteStride = 12;
        view->target = (int) WebGLConstants::ARRAY_BUFFER;

        buffer->extras->_pipeline->source.resize(byteOffset + byteLength);
        memmove(&buffer->extras->_pipeline->source[byteOffset], &geometry->vertex[0], byteLength);

        // 纹理坐标
        byteOffset += byteLength;
        byteLength = geometry->vt.size();
        view = new Glb::BufferView();
        gltf->bufferViews.push_back(view);
        view->buffer = 0;
        view->byteLength = byteLength;
        view->byteOffset = byteOffset;
        view->target = (int) WebGLConstants::ARRAY_BUFFER;
        view->byteStride = 8;

        buffer->extras->_pipeline->source.resize(byteOffset + byteLength);
        memmove(&buffer->extras->_pipeline->source[byteOffset], &geometry->vt[0], byteLength);

        // 索引
        byteOffset += byteLength;
        byteLength = geometry->vertexIndex.size();
        view = new Glb::BufferView();
        gltf->bufferViews.push_back(view);
        view->buffer = 0;
        view->byteLength = byteLength;
        view->byteOffset = byteOffset;
        view->target = (int) WebGLConstants::ELEMENT_ARRAY_BUFFER;
        view->byteStride = 4;

        buffer->extras->_pipeline->source.resize(byteOffset + byteLength);
        memmove(&buffer->extras->_pipeline->source[byteOffset], &geometry->vertexIndex[0], byteLength);

        // 图片
        byteOffset += byteLength;

        /*std::ifstream ifstream;
        std::string json = "";
        ifstream.open( "../data/img/timg.jpg", std::ios::in);
        if (ifstream.is_open()) {
            json.append((std::istreambuf_iterator<char>(ifstream)), std::istreambuf_iterator<char>());
            ifstream.close();
        }*/
        byteLength = geometry->_drawable->_stateSet->_texture[0]->_image->data.size();
        //byteLength = json.size();

        view = new Glb::BufferView();
        gltf->bufferViews.push_back(view);
        view->buffer = 0;
        view->byteLength = byteLength;
        view->byteOffset = byteOffset;
        buffer->extras->_pipeline->source.resize(byteOffset + byteLength);
        memmove(&buffer->extras->_pipeline->source[byteOffset],
                &geometry->_drawable->_stateSet->_texture[0]->_image->data[0], byteLength);
        //memmove(&buffer->extras->_pipeline->source[byteOffset],&json[0], byteLength);
        byteOffset += byteLength;

        buffer->byteLength = byteOffset;
    }

    return gltf;
}


void Glb::writeJSON(Glb *glb, rapidjson::Writer<rapidjson::StringBuffer> *jsonWriter) {
    jsonWriter->StartObject();

    //写资产元数据
    if (glb->asset != NULL) {
        jsonWriter->Key("asset");
        jsonWriter->StartObject();
        jsonWriter->Key("version");
        jsonWriter->String(glb->asset->version.c_str());
        jsonWriter->Key("generator");
        jsonWriter->String(glb->asset->generator.c_str());
        jsonWriter->EndObject();
    }
    jsonWriter->Key("extensionsRequired");
    jsonWriter->StartArray();
    jsonWriter->String("KHR_materials_unlit");
    jsonWriter->EndArray();
    jsonWriter->Key("extensionsUsed");
    jsonWriter->StartArray();
    jsonWriter->String("KHR_materials_unlit");
    jsonWriter->EndArray();
    // 场景（注意单数）是一个附加属性，用于标识在加载时要显示阵列中的哪个场景
    if (glb->scene >= 0) {
        jsonWriter->Key("scene");
        jsonWriter->Int(glb->scene);
    }
    //编写场景并构建节点数组
    if (glb->scenes.size() > 0) {
        jsonWriter->Key("scenes");
        jsonWriter->StartArray();
        int sceneId = 0;
        //获取场景中的每一个节点并构建节点中的索引 nodes向量的位置
        for (Glb::Scene *scene : glb->scenes) {
            jsonWriter->StartObject();
            jsonWriter->Key("nodes");
            jsonWriter->StartArray();
            for (int node : scene->nodes) {
                jsonWriter->Int(node);
            }
            jsonWriter->EndArray();
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写入节点
    if (glb->nodes.size() > 0) {
        jsonWriter->Key("nodes");
        jsonWriter->StartArray();
        for (int i = 0; i < glb->nodes.size(); i++) {
            jsonWriter->StartObject();
            jsonWriter->Key("mesh");
            jsonWriter->Int(i);
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写入格网
    if (glb->meshes.size() > 0) {
        jsonWriter->Key("meshes");
        jsonWriter->StartArray();
        for (Mesh *mesh:glb->meshes) {
            jsonWriter->StartObject();
            jsonWriter->Key("primitives");
            jsonWriter->StartArray();
            for (Primitive *primitive:mesh->primitives) {
                jsonWriter->StartObject();

                jsonWriter->Key("attributes");
                jsonWriter->StartObject();
                for (const auto &attribute : primitive->attributes) {
                    jsonWriter->Key(attribute.first.c_str());
                    jsonWriter->Int(attribute.second);
                }
                jsonWriter->EndObject();
                if (primitive->indices >= 0) {
                    jsonWriter->Key("indices");
                    jsonWriter->Int(primitive->indices);
                }
                jsonWriter->Key("mode");
                jsonWriter->Int(primitive->mode);//static_cast<int >将一个指向基类的指针转换为指向子类的指针
                if (primitive->material >= 0) {
                    jsonWriter->Key("material");
                    jsonWriter->Int(primitive->material);
                }
                jsonWriter->EndObject();
            }
            jsonWriter->EndArray();
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写入访问器
    if (glb->accessors.size() > 0) {
        jsonWriter->Key("accessors");
        jsonWriter->StartArray();
        for (Accessor *accessor:glb->accessors) {
            jsonWriter->StartObject();
            //写入缓冲区视图
            //写入字节偏移
            jsonWriter->Key("byteOffset");
            jsonWriter->Int(accessor->byteOffset);
            //写入缓冲区视图
            jsonWriter->Key("bufferView");
            jsonWriter->Int(accessor->bufferView);

            //写入元素个数
            jsonWriter->Key("count");
            jsonWriter->Int(accessor->count);

            //写入类型
            jsonWriter->Key("type");
            jsonWriter->String(accessor->type.c_str());

            //写入字节类型
            jsonWriter->Key("componentType");
            jsonWriter->Int(accessor->componentType);

            //写入最大最小值
            if (accessor->max.size() > 0) {
                jsonWriter->Key("max");
                jsonWriter->StartArray();
                for (int i = 0; i < accessor->max.size(); i++) {
                    //if (this->componentType == GLTF::Constants::WebGL::FLOAT) {
                    if (accessor->type != "SCALAR") {
                        jsonWriter->Double(accessor->max[i]);
                    } else {
                        jsonWriter->Int((int) accessor->max[i]);
                    }
                }
                jsonWriter->EndArray();
            }
            if (accessor->min.size() > 0) {
                jsonWriter->Key("min");
                jsonWriter->StartArray();
                for (int i = 0; i < accessor->min.size(); i++) {
                    if (accessor->type != "SCALAR") {
                        jsonWriter->Double(accessor->min[i]);
                    } else {
                        jsonWriter->Int((int) accessor->min[i]);
                    }
                }
                jsonWriter->EndArray();
            }

            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //编写材料并构建技术和纹理数组
    if (glb->materials.size() > 0) {
        jsonWriter->Key("materials");
        jsonWriter->StartArray();
        for (Material *material:glb->materials) {
            jsonWriter->StartObject();

            jsonWriter->Key("pbrMetallicRoughness");
            jsonWriter->StartObject();

            //写入金属粗糙度
            std::map<std::string, std::vector<float>>::iterator iter = material->pbrMetallicRoughness.begin();
            while (iter != material->pbrMetallicRoughness.end()) {
                jsonWriter->Key(iter->first.c_str());
                if ("baseColorTexture" == iter->first) {
                    jsonWriter->StartObject();
                    jsonWriter->Key("index");
                    jsonWriter->Double(iter->second[0]);
                    jsonWriter->EndObject();
                } else {
                    if (iter->second.size() > 1) {
                        jsonWriter->StartArray();
                        for (int i = 0; i < iter->second.size(); i++) {
                            jsonWriter->Double(iter->second[i]);
                        }
                        jsonWriter->EndArray();
                    } else {
                        for (int i = 0; i < iter->second.size(); i++) {
                            jsonWriter->Double(iter->second[i]);
                        }
                    }
                }

                iter++;
            }

            jsonWriter->EndObject();

            //发射贴图控制材质发射的光的颜色和强度。
            /*jsonWriter->Key("emissiveFactor");
            jsonWriter->StartArray();
            for (int i = 0; i < 3; i++) {
                jsonWriter->Double(material->emissiveFactor[i]);
            }
            jsonWriter->EndArray();*/

            /*if (!material->alphaMode.empty()) {
                jsonWriter->Key("alphaMode");
                jsonWriter->String(material->alphaMode.c_str());

            }*/
            if (material->doubleSided) {
                jsonWriter->Key("doubleSided");
                jsonWriter->Bool(material->doubleSided);
            }
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    if (glb->textures.size() > 0) {
        jsonWriter->Key("textures");
        jsonWriter->StartArray();
        for (Glb::Texture *texture : glb->textures) {
            jsonWriter->StartObject();
            jsonWriter->Key("sampler");
            jsonWriter->Int(texture->sampler);
            jsonWriter->Key("source");
            jsonWriter->Int(texture->source);
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //如果有的话，写下图像并添加bufferViews
    if (glb->images.size() > 0) {
        //unsigned char *cs = images[0]->data;
        //std::cout << cs << std::endl;
        jsonWriter->Key("images");
        jsonWriter->StartArray();
        for (Glb::Image *image:glb->images) {
            jsonWriter->StartObject();
            jsonWriter->Key("bufferView");
            jsonWriter->Int(image->bufferView);
            jsonWriter->Key("mimeType");
            jsonWriter->String(image->mimeType.c_str());
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写入采样器
    if (glb->samplers.size() > 0) {
        jsonWriter->Key("samplers");
        jsonWriter->StartArray();
        for (Sampler *sampler :glb->samplers) {
            jsonWriter->StartObject();
            jsonWriter->Key("magFilter");
            jsonWriter->Int((int) sampler->_magnificationFilter);
            jsonWriter->Key("minFilter");
            jsonWriter->Int((int) sampler->_minificationFilter);
            jsonWriter->Key("wrapR");
            jsonWriter->Int((int) sampler->_wrapR);
            jsonWriter->Key("wrapS");
            jsonWriter->Int((int) sampler->_wrapS);
            jsonWriter->Key("wrapT");
            jsonWriter->Int((int) sampler->_wrapT);
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写入bufferViews并将缓冲区添加到缓冲区数组中
    if (glb->bufferViews.size() > 0) {
        jsonWriter->Key("bufferViews");
        jsonWriter->StartArray();
        for (BufferView *bufferView:glb->bufferViews) {
            jsonWriter->StartObject();
            jsonWriter->Key("buffer");
            jsonWriter->Int(bufferView->buffer);

            jsonWriter->Key("byteLength");
            jsonWriter->Int(bufferView->byteLength);
            jsonWriter->Key("byteOffset");
            jsonWriter->Int(bufferView->byteOffset);
            //步
            if (bufferView->byteStride >= 0) {
                jsonWriter->Key("byteStride");
                jsonWriter->Int(bufferView->byteStride);
            }
            if (bufferView->target > 0) {
                jsonWriter->Key("target");
                jsonWriter->Int(bufferView->target);
            }
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }
    //写缓冲区
    if (glb->buffers.size() > 0) {
        jsonWriter->Key("buffers");
        jsonWriter->StartArray();
        for (Buffer *buffer:glb->buffers) {
            jsonWriter->StartObject();
            jsonWriter->Key("byteLength");
            jsonWriter->Int(buffer->byteLength);
            jsonWriter->EndObject();
        }
        jsonWriter->EndArray();
    }

    jsonWriter->EndObject();

}


