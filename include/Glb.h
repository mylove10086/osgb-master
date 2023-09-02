/**
 * Created by IBM on 2022/5/8.
 */

#ifndef C_CESIUM_MASTER_GLB_H
#define C_CESIUM_MASTER_GLB_H

#include <iostream>
#include <vector>
#include <map>
#include <writer.h>
#include <document.h>
#include "Extension.h"
#include "Extras.h"
#include "Osgb.h"

namespace osg {

    class Glb {
    public:
        class ProcessPbrInfo {
        public:
            bool skinned;
            int componentType;
            bool hasVertexColors;
            bool hasMorphTargets;
            bool hasNormals;
            bool hasTangents;
            bool hasTexCoords;
            bool hasTexCoord1;
            bool hasOutline;

        };

        class Sampler {
        public:
            WebGLConstants _wrapR;
            WebGLConstants _wrapS;
            WebGLConstants _wrapT;
            WebGLConstants _magnificationFilter;
            WebGLConstants _minificationFilter;

        };

        class KHRTechniques {
        public:
            std::map<std::string, std::vector<float>> vlaue;
            int technique = 0;

            ~KHRTechniques();
        };

        class Texture {
        public:
            int sampler;
            int source;
            WebGLConstants internalFormat = WebGLConstants::NONE;
            WebGLConstants type = WebGLConstants::NONE;
            bool extensions = false;
        };

        class Primitive {
        public:
            std::map<std::string, int> attributes;
            int indices = -1;
            int material = -1;
            unsigned int mode = WebGLConstants::TRIANGLES;
            std::map<std::string, KHRTechniques *> *extensions = NULL;
            std::vector<int> targets;

            ~Primitive();
        };

        class Accessor {
        public:
            std::string name = "";
            bool normalized = false;
            int bufferView = 0;
            int byteOffset = 0;
            int componentType;
            unsigned int count;
            std::string type;
            std::vector<double> min;
            std::vector<double> max;
        };

        class Image {
        public:
            int bufferView = -1;
            std::string mimeType = "";
            Extras *extras = NULL;
            std::string uri = "";

            Image();

            ~Image();
        };

        class Asset {
        public:
            std::string generator = "CCesium";
            std::string version = "2.0";
        };

        class Buffer {
        public:
            std::string name;
            unsigned int byteLength;
            Extras *extras = NULL;

            Buffer();

            ~Buffer();
        };

        class BufferView {
        public:
            int buffer = 0;
            int byteLength = 0;
            int byteOffset = 0;
            int target = WebGLConstants::ARRAY_BUFFER;
            int byteStride = 0;
        };

        class Material {
        public:
            double alphaCutoff = 0.5;
            std::string name;
            std::map<std::string, std::vector<float>> pbrMetallicRoughness;
            //PbrMetallicRoughness *pbrMetallicRoughness = NULL;
            std::string alphaMode = "OPAQUE";
            bool doubleSided = false;
            // std::map<std::string, std::vector<float>> textureAttr;
            std::vector<double> emissiveFactor = {0.0, 0.0, 0.0};
            std::map<std::string, KHRTechniques *> extensions;

            ~Material();

            static Material *clone(Material *);
        };

        class Mesh {
        public:
            std::string name = "";
            std::vector<Primitive *> primitives;

            ~Mesh();
        };

        class Node {
        public:
            int mesh = -1;
            std::string name;
            std::vector<double> matrix = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
                                          1.0};
            std::vector<double> translation;
            std::vector<double> rotation;
            std::vector<double> scale;
            std::vector<int> children;
            //glm::dmat4 _transformToRoot;
        };

        class Scene {
        public:
            std::vector<int> nodes;
        };

        class Skin {
        public:
            int inverseBindMatrices = -1;
            std::vector<int> nodes;
        };

    public:


        unsigned int scene = 0;
        float _max[3] = {-100000, -100000, -100000};
        float _min[3] = {100000, 100000, 100000};
        std::string version = "2.0";
        Asset *asset = NULL;
        Extras *extras = NULL;
        std::map<std::string, bool> extensionsUsed;
        std::map<std::string, bool> extensionsRequired;
        std::vector<Scene *> scenes;
        // 下面两个都是访问bufferViews的索引参数
        std::vector<Glb::Accessor *> accessors;
        std::vector<Glb::Image *> images;
        std::vector<Glb::Texture *> textures;
        std::vector<Glb::Buffer *> buffers;
        std::vector<BufferView *> bufferViews;
        std::vector<Glb::Material *> materials;
        std::vector<Glb::Node *> nodes;
        std::vector<Glb::Mesh *> meshes;
        std::vector<Glb::Skin *> skins;
        std::vector<Sampler *> samplers;
        std::vector<Sampler *> animations;

        Glb();


        ~Glb();

        /**
         * 导出b3dm
         */
        void writeB3dm(std::string output, std::string outname);

        void writeGlb(std::string output, std::string outname);

        static Glb *parse(Osgb *osgb);

        static void writeJSON(Glb *glo, rapidjson::Writer<rapidjson::StringBuffer> *jsonWriter);

    };
}


#endif //C_CESIUM_MASTER_GLB_H
