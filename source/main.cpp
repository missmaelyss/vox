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

#include <SceneOpenGL.hpp>

int main(int argc, char **argv)
{
    // Création de la sène
	
    SceneOpenGL scene("Chapitre 3", 800, 600);
	
	
    // Initialisation de la scène
	
    if(scene.initialiserFenetre() == false)
	    return -1;
	
    if(scene.initGL() == false)
	    return -1;
	
	
    // Boucle Principale
	
    scene.bouclePrincipale();
	
	
    // Fin du programme
	
    return 0;
}