#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL


// Includes 

#ifdef WIN32
#include <GL/glew.h>

#elif __APPLE__
#include <Opengl/gl.h>

#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>

#endif

#include <SDL2/SDL.h>
#include <iostream>


// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();


    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;	
    SDL_Event m_evenements;
};

#endif