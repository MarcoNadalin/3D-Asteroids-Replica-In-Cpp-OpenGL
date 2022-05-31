#include <stdlib.h>
#include <stdio.h>
#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include "./Game.h"
#include "./Input/InputManager.h"

/* Main Game Object */
std::unique_ptr<Game> game;

/* InputManager */
std::unique_ptr<InputManager> inputManager;

double time_of_previous_frame = 0;

int window_w, window_h;

/* Display callback */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    /* Render the game */
    game->Render();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));

    glutSwapBuffers();
}

/* Idle callback and game loop */
void update() {

    double current = glutGet(GLUT_ELAPSED_TIME);

    if ((current - time_of_previous_frame) > 0.001) {

        /* Convert delta time to seconds */
        double dt = (current - time_of_previous_frame) / 1000;
        time_of_previous_frame = current;

        /* Update game for current frame */
        game->Update((float)dt);

        /* Re-Render for current frame */
        glutPostRedisplay();
    }
}

/* Keyboard callback */
void keyDown(unsigned char key, int x, int y)
{
    inputManager->OnKeyDown(key);
}

void keyUp(unsigned char key, int x, int y) {
    inputManager->OnKeyUp(key);
}

void init()
{
    /* In this simple program these OpenGL calls only need to be done once, */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    time_of_previous_frame = glutGet(GLUT_ELAPSED_TIME);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutIdleFunc(update);

    /* set rand seed */
    srand(time(NULL));
    /* Initialising objects for the game and input manager */
    inputManager = std::make_unique<InputManager>();
    game = std::make_unique<Game>(inputManager.get());
}

void on_reshape(int w, int h)
{
    fprintf(stderr, "on_reshape(%d, %d)\n", w, h);
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Astroids - Assignment 1 - s3782230");
    glutFullScreen();

    /* Display callback */
    glutDisplayFunc(display);
    glutReshapeFunc(on_reshape);

    /* Setting up keyboard input and callbacks */
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    init();

    /* Start glut main application loop */
    glutMainLoop();
}