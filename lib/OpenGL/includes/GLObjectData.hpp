//
// GLObjectData.hpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Apr  1 01:07:03 2017 Sousa Victor
// Last update Thu Apr  6 19:41:18 2017 Sousa Victor
//

#ifndef GLOBJECTDATA_HPP_
#define GLOBJECTDATA_HPP_

#ifdef __APPLE__
# include <GL/glew.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# ifdef _WIN32
   #include <windows.h>
# endif
# include <GL/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>
#endif
#include <IL/il.h>
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <iostream>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class GLObjectData {
public:
    GLObjectData();
    GLObjectData(const std::string& filename);
    ~GLObjectData();
    GLObjectData &operator=(const GLObjectData &obj);
    GLObjectData(GLObjectData const &obj);

    void move(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z);
    void setOffset(float x, float y, float z);
    void draw();

private:
    int loadasset(const char* path);
    int loadGLTextures(const aiScene* scene, std::string const & path);
    std::string getBasePath(const std::string& path);
    void get_bounding_box(aiVector3D* min, aiVector3D* max) const;
    void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo) const;
    void recursive_render(const aiScene *sc, const aiNode* nd);
    void color4_to_float4(const aiColor4D *c, float f[4]) const;
    void set_float4(float f[4], float a, float b, float c, float d) const;
    void apply_material(const aiMaterial *mtl);

    const aiScene* _scene;
    GLuint _scene_list;
    aiVector3D _scene_min, _scene_max, _scene_center;
    std::map<std::string, GLuint*> _textureIdMap;
    GLuint *_textureIds;

    float _angle;
    float _posX;
    float _posY;
    float _posZ;
    float _scaleX;
    float _scaleY;
    float _scaleZ;
    float _rotX;
    float _rotY;
    float _rotZ;
    float _offX;
    float _offY;
    float _offZ;

};

#else

class GLObjectData;

#endif /*GLOBJECTDATA_HPP_*/
