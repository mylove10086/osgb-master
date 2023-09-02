#include <iostream>
#include <fstream>
#include <vector>
#include <Geometry.h>
#include <Osgb.h>
#include "Drawable.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

GLFWwindow *m_pWindow = NULL;
typedef struct {
    GLenum type;
    const char *shaderSource;
    GLuint shader;
} ShaderInfos;
using namespace osg;

void initialize(const char *title, int width, int height) {

    glfwInit();

    //配置GLFW,第一个参数代表选项的名称,第二个参数接受一个整型，用来设置这个选项的值
    //此处设置表示使用的OpenGL版本号3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint作为窗口创建的一种提示，可以设置窗口的多种属性，包括透明度等等，感兴趣的可以在glfw文档中查询
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //使用流水线配置模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    m_pWindow = glfwCreateWindow(width, height, title ? title : "CESIUM Application", nullptr, nullptr);
    //glfwSetWindowUserPointer(window, this);

    //glfwSetKeyCallback(m_pWindow, key_callback);//按键的回调
    //glfwSetMouseButtonCallback(this->m_pWindow, WindowEventHandler::handleMouseDownUp);//鼠标左右中建按下抬起事件
    //glfwSetCursorPosCallback(this->m_pWindow, WindowEventHandler::handleMouseMove);//鼠标移动
    //glfwSetScrollCallback(this->m_pWindow, WindowEventHandler::handleWheel);//滚轮
    //glfwSetFramebufferSizeCallback(this->m_pWindow, Windows::resizeEvent);

    // //将该窗口作为当前线程的主上下文
    glfwMakeContextCurrent(m_pWindow);
    //交换间隔表示交换缓冲区之前等待的帧数，通常称为vsync。
    //默认情况下，交换间隔为0，但因为屏幕每秒只更新60-75次，所以大部分的画面不会被显示。
    //而且，缓冲区有可能在屏幕更新的中间交换，出现屏幕撕裂的情况。
    //所以，可以将该间隔设为1，即每帧更新一次。它可以设置为更高的值，但这可能导致输入延迟。
    glfwSwapInterval(1);//1使帧数等于显示器帧数

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

}

int createAndLinkProgram(std::string vsSource, std::string fsSource) {
    //std::string vsSource = shader->_vertexShaderText;
    //std::string fsSource = shader->_fragmentShaderText;

    ShaderInfos shaders[] = {
            {GL_VERTEX_SHADER,   vsSource.c_str()},
            {GL_FRAGMENT_SHADER, fsSource.c_str()},
            {GL_NONE, NULL}

    };
    if (shaders == NULL) { return 0; }

    GLuint program = glCreateProgram();

    ShaderInfos *entry = shaders;
    while (entry->type != GL_NONE) {
        // glCreateShader - 创建一个着色器对象
        GLuint shader = glCreateShader(entry->type);//
        entry->shader = shader;
        const GLchar *source = entry->shaderSource;
        if (source == NULL) {
            for (entry = shaders; entry->type != GL_NONE; ++entry) {
                glDeleteShader(entry->shader);
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource(shader, 1, &source, NULL);
        //delete[] source;

        glCompileShader(shader);//指定要编译的 shader 对象

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);// 指定要查询的着色器对象。
        if (!compiled) {
//#ifdef _DEBUG
            GLsizei len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

            GLchar *log = new GLchar[len + 1];
            glGetShaderInfoLog(shader, len, &len, log);
            std::cerr << "Shader compilation failed: " << log << std::endl;
            delete[] log;
//#endif /* DEBUG */

            return 0;
        }

        glAttachShader(program, shader);//将着色器对象附加到program对象
        glDeleteShader(shader);

        ++entry;
    }

    //指定要链接的program对象的句柄
    glLinkProgram(program);

    GLint linked;
    //判断着色器的连接是否成功
    glGetProgramiv(program, GL_LINK_STATUS, &linked);//指定要查询的program对象
    if (!linked) {
//#ifdef _DEBUG
        GLsizei len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

        GLchar *log = new GLchar[len + 1];
        glGetProgramInfoLog(program, len, &len, log);
        std::cerr << "Shader linking failed: " << log << std::endl;
        delete[] log;
//#endif /* DEBUG */

        for (entry = shaders; entry->type != GL_NONE; ++entry) {
            glDeleteShader(entry->shader);
            entry->shader = 0;
        }

        return 0;
    }

    return program;
}


class Canvas {
public:
    GLuint shaderProgram;
    Osgb osgb;
    Canvas() {
        std::string fileurl = "../data/1536.terrain";
        fileurl = "../data/Tile_11_L24_00100000.osgb";

        osgb.read(fileurl);
        osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data;
        size_t size = osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data.size();
        FILE *file = fopen("../data/test.jpeg", "wb");
        fwrite(&(osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data)[0],
               sizeof(unsigned char), size, file);
        fclose(file);
        init();
    }

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    GLuint _texture;
    GLuint projection;


    void init() {

        std::string render_vs = "#version 330 core\n"
                                "layout (location = 0) in vec3 position;\n"
                                //"layout (location = 1) in vec2 texCoord;\n"//接收纹理坐标
                                "uniform mat4 projection;\n"
                                //"out vec2 v_textureCoordinates;\n"
                                "void main()\n"
                                "{\n"
                                "    gl_Position =projection* vec4(position.x, position.y, position.z, 1.0);\n"
                                //"    v_textureCoordinates=texCoord;\n"
                                "}";
        std::string render_fs = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                //"in vec2 v_textureCoordinates;\n"
                                //"uniform sampler2D u_texture;\n"
                                //"uniform samplerCube czm_environmentMap;\n"
                                "void main()\n"
                                "{\n"
                                //"     vec3 r=vec3(1.0);\n"
                                //"     vec4 sceneSkyBox = texture(czm_environmentMap, r).rgba;\n"

                                "     FragColor = vec4(1.0, 1.0f, 0.0f, 1.0f);\n"
                                //"    gl_FragColor = texture2D(u_texture, v_textureCoordinates);\n"//只使用纹理
                                "}";
        shaderProgram = createAndLinkProgram(render_vs, render_fs);
        GLuint indices[6] = { // 注意索引从0开始!
                0, 1, 3, // 第一个三角形
                1, 2, 3}; // 第二个三角形
        std::vector<float> *vertices = new std::vector<float>();
        vertices->push_back(0.5f);
        vertices->push_back(0.5f);
        vertices->push_back(0.0f);

        vertices->push_back(0.5f);
        vertices->push_back(-0.5f);
        vertices->push_back(0.0f);

        vertices->push_back(-0.5f);
        vertices->push_back(-0.5);
        vertices->push_back(0.0f);

        vertices->push_back(-0.5f);
        vertices->push_back(0.5f);
        vertices->push_back(0.0f);


        glGenBuffers(1, &this->VBO);

        int bufferTarget = GL_ARRAY_BUFFER;
        glBindBuffer(bufferTarget, this->VBO);

        int usage = GL_STATIC_DRAW;
        int size = 4 * vertices->size();
        glBufferData(bufferTarget, size, &vertices->at(0), usage);
        glBindBuffer(bufferTarget, 0);


        //1,生成顶点数组对象名称
        glGenBuffers(1, &this->EBO);
        int bufferTargetindex = GL_ELEMENT_ARRAY_BUFFER;
        glBindBuffer(bufferTargetindex, this->EBO);
        int usageindex = GL_STATIC_DRAW;
        glBufferData(bufferTargetindex, 24, indices, usageindex);
        glBindBuffer(bufferTargetindex, 0);


        GLint linked;
        glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &linked);
        GLint length;
        glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
        projection = glGetUniformLocation(shaderProgram, "projection");

        setUnform();


        buildVertexArray();

    };

    void setUnform() {
        GLfloat projection_matrix[16] = {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };
        glUniformMatrix4fv(projection, 1, false, projection_matrix);//投影矩阵

    }

    void buildVertexArray() {

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //顶点location
        int index = 0;
        int componentsPerAttribute = 3;
        GLenum componentDatatype = GL_FLOAT;
        bool normalize = false;
        int strideInBytes = 3 * 4;
        int offsetInBytes = 0;
        glVertexAttribPointer(index, componentsPerAttribute, componentDatatype, normalize, strideInBytes,
                              (GLvoid *) (offsetInBytes));
        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }

    void render() {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        glClearColor(0.2f, 0.3f, 0.3f, 0.50f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        setUnform();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        int primitiveType = GL_TRIANGLES;
        int count = 6;
        int indexDatatype = GL_UNSIGNED_INT;
        int offset = 0;
        glDrawElements(primitiveType, count, indexDatatype, (void *) offset);

        glBindVertexArray(0);

    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    initialize("123", 500, 400);
    if (!m_pWindow) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    Canvas *canvas = new Canvas();


    /* Main loop */
    do {
        /* Draw one frame */
        canvas->render();
        /* Swap buffers */
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();


    } while (!glfwWindowShouldClose(m_pWindow));




    //saveJpeg("../data/test.jpeg",);
    return 0;
}
