#include <SceneOpenGL.hpp>

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre), 
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0)
{

}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL
	
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        return false;
    }
	
    // Double Buffer
	
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	
    // Création de la fenêtre
	
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Tout s'est bien passé, on retourne true

    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    // Variables
	
    bool terminer(false);
    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};
	
	
    // Boucle principale
	
    while(!terminer)
    {
        // Gestion des évènements
		
        SDL_WaitEvent(&m_evenements);
		
        if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = 1;
		
		
        // Nettoyage de l'écran
		
        glClear(GL_COLOR_BUFFER_BIT);
		
		
        // On remplie puis on active le tableau Vertex Attrib 0
		
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);
	  	
		
        // On affiche le triangle
		
        glDrawArrays(GL_TRIANGLES, 0, 3);
		
		
        // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
		
        glDisableVertexAttribArray(0);
		
		
        // Actualisation de la fenêtre
		
        SDL_GL_SwapWindow(m_fenetre); 
    }
}