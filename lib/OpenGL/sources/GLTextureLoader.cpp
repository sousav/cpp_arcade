//
// GLTextureLoader.cpp for  in /Users/vicostudio/Documents/Shared Folder/TEK2/CPP/cpp_arcade/lib/OpenGL/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Mar 26 01:33:55 2017 Sousa Victor
// Last update Sun Apr  9 21:08:58 2017 Sousa Victor
//

#include "GLTextureLoader.hpp"

std::map<std::string, GLuint> GLTextureLoader::_textureMap;

GLuint GLTextureLoader::load(std::string const & filename, bool useMipMap) {
    if (filename != "") {
        std::map<std::string,GLuint>::iterator it = GLTextureLoader::_textureMap.find(filename);
        if (it != GLTextureLoader::_textureMap.end()) {
            return it->second;
        } else {
            std::cout << "loading: " << filename << std::endl;
            GLTextureLoader::_textureMap[filename] = GLTextureLoader::loadTexture(filename.data(), useMipMap);
            return GLTextureLoader::_textureMap[filename];
        }
    }
    return 0;
}

void GLTextureLoader::clean() {
    GLTextureLoader::_textureMap.clear();
}

GLuint GLTextureLoader::loadTexture(const char * filename, bool useMipMap) {
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        return 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    SDL_PixelFormat format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;
    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);
    gl_fliped_surface = flipSurface(gl_surface);
    glGenTextures(1, &glID);
    glBindTexture(GL_TEXTURE_2D, glID);
    if (useMipMap) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, gl_fliped_surface->w,
                          gl_fliped_surface->h, GL_RGBA,GL_UNSIGNED_BYTE,
                          gl_fliped_surface->pixels);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                     gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                     gl_fliped_surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);
    return glID;
}

SDL_Surface *GLTextureLoader::flipSurface(SDL_Surface * surface){
    int current_line,pitch;
    SDL_Surface * fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   surface->w,surface->h,
                                   surface->format->BitsPerPixel,
                                   surface->format->Rmask,
                                   surface->format->Gmask,
                                   surface->format->Bmask,
                                   surface->format->Amask);
    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);
    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line ++) {
        memcpy(&((unsigned char* )fliped_surface->pixels)[current_line*pitch],
               &((unsigned char* )surface->pixels)[(surface->h - 1  -
                                                    current_line)*pitch], pitch);
    }
    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}
