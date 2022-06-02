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

#define STB_IMAGE_IMPLEMENTATION
#include "./Graphics/stb_image.h"

#include "./Game.h"
#include "./Input/InputManager.h"

/* Main Game Object */
std::unique_ptr<Game> game;

/* InputManager */
std::unique_ptr<InputManager> inputManager;
double time_of_previous_frame = 0;

/* SKYBOX STUFF ---------------------------------------*/
GLuint sky_top;
uint32_t load_texture(const char* filename)
{
	int width, height, components;
	unsigned char* data = stbi_load(filename, &width, &height, &components, STBI_rgb);

	unsigned int id;
	glPushAttrib(GL_TEXTURE_BIT);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glPopAttrib();
	return id;
}

void skybox() {

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sky_top);

	glPushMatrix();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-70, -70, -50);

	glTexCoord2f(1, 0);
	glVertex3f(70, -70, -50);

	glTexCoord2f(1, 1);
	glVertex3f(70, 70, -50);

	glTexCoord2f(0, 1);
	glVertex3f(-70, 70, -50);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

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
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float light_position[] = { 1.0, 1,0, 1.0f, 0.0f };
void init_lighting()                             // *** EXERCISE 3 ...
{
	
	float light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	float mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	
	glEnable(GL_LIGHT0);
}

/* Display Callback */
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	skybox();
	glLoadIdentity();
	
	init_lighting();
	// Set the camera
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
	glutWarpPointer(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
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

	/* loading textures */
	sky_top = load_texture("../assets/textures/sky/front.png");
	if (!sky_top) {
		printf("No texture created; exiting.\n");
		return EXIT_FAILURE;
	}

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