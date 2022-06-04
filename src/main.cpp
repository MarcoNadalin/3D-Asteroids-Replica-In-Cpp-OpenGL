#include "./Game.h"
#include "./Assets/AssetLoader.h"
#include "./Input/InputManager.h"
#include "Graphics/Cubemap.h"



/* Main Game Object */
std::unique_ptr<Game> game;

/* InputManager */
std::unique_ptr<InputManager> inputManager;
double time_of_previous_frame = 0;

/* SKYBOX STUFF ---------------------------------------*/
GLuint sky_top;
GLuint sky_front;
GLuint sky_left;
GLuint sky_right;
GLuint sky_bottom;
GLuint sky_back;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

/* Display Callback */
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->Render();

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

void pressKey(int key, int xx, int yy) {

	inputManager->OnKeyDown(key);

}

void releaseKey(int key, int x, int y) {

	inputManager->OnKeyUp(key);

}

void mouseMove(int x, int y) {
	inputManager->MouseMotion(x, y);
	/* Send the cursor back to the middle of the screen */
	glutWarpPointer((int) (glutGet(GLUT_SCREEN_WIDTH) / 2), (int) (glutGet(GLUT_SCREEN_HEIGHT) / 2));
}




int main(int argc, char** argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Assignment 2");
	glutFullScreen();
	glutWarpPointer(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);

	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(update);
	

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutPassiveMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	/* Initialising objects for the game and input manager */
	inputManager = std::make_unique<InputManager>();
	game = std::make_unique<Game>(inputManager.get());

	
	// enter GLUT event processing cycle
	glutMainLoop();	

	return 1;
}