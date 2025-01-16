#pragma once
#include<glad.h>
#include<glm.hpp>
#include<string>
#include<vector>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"Shader.h"
#define MAX_BONE 4
namespace _3D{


    struct Vertex {
        glm::vec3 Position;//顶点
        glm::vec3 Normal;//法线
        glm::vec2 TexCoords;//纹理
        glm::vec3 Tangent;//切线
        glm::vec3 Bitangent;//副切线
        int m_BoneIDs[MAX_BONE];//骨头
        float m_Weights[MAX_BONE];
    };
    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };
    class Mesh {
    public:
        std::vector<Vertex>       vertices;//顶点数组
        std::vector<unsigned int> indices;//索引数组
        std::vector<Texture>      textures;//纹理数组
        unsigned int VAO;//顶点绑定
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader& shader);
    private:
        unsigned int VBO, EBO;
        void setupMesh();
    };
    class Model
    {
    public:
        // model data
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh>    meshes;
        std::string directory;
        bool gammaCorrection;
        Model(std::string const& path, bool gamma = false);
        void Draw(Shader& shader);
    private:
        void loadModel(std::string const& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };
    class skybox {
    public:
        std::vector<float> cubeVertices = {

            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f

        };
        std::vector<std::string> faces{
            "./data/model/sky/right.jpg",
            "./data/model/sky/left.jpg",
            "./data/model/sky/top.jpg",
            "./data/model/sky/bottom.jpg",
            "./data/model/sky/front.jpg",
            "./data/model/sky/back.jpg"
        };
        Shader shader;
        unsigned int skyboxVAO;
        unsigned int cubemapID;
        skybox();
        void skyboxload();
        void loadcubemap();
        void Draw(glm::mat4 x, glm::mat4 y);
    };
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

}
namespace _2D {
    class Texture2D
    {
    public:   
        GLuint ID; 
        GLuint Width, Height;
        GLuint Internal_Format; 
        GLuint Image_Format; 
        GLuint Wrap_S; 
        GLuint Wrap_T; 
        GLuint Filter_Min; 
        GLuint Filter_Max; 
        
        Texture2D();
        
        void Generate(GLuint width, GLuint height, unsigned char* data);
        
        void Bind() const;
    };
}



