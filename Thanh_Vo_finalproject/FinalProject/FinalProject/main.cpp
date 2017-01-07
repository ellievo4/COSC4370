/*	Thanh Vo _ 1148524
	COSC 4377
	Final Project
	main.cpp
	References: 
		GLUT setup:		http://aschultz.us/blog/archives/176
		GLUT tutorials: http://www.videotutorialsrock.com/
		Obj loader:		https://www.youtube.com/watch?v=XIVUxywOyjE&t=190s
		SOIL usage:		http://www.lonesock.net/soil.html
*/

// ----------------------------------------------------------
// include libraries
// ----------------------------------------------------------
#include "glut\glut.h"
#include <Windows.h>
#include "ObjLoader.h"
#include "src\SOIL.h"

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void init();							//some enables and load obj files 
void display();							//display the scene
void specialKeys();						//set up controlling keys for rotating around
void handleResize(int w, int h);		//function for handling window resizes
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, GLint tt);	//draw a cube
void DrawSphere(GLfloat transX, GLfloat transY, GLfloat transZ);	//draw a sphere
void _timer(int value);					//client function for timer event

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double ROTATE_Y = 0;			//initial user rotation around x
double ROTATE_X = 0;			//initial user rotation around y
#define SCREEN_WIDTH 640		//width
#define SCREEN_HEIGHT 480		//height
GLuint _TEXTUREID;				//The OpenGL id of the texture
GLdouble LOOKFROMX = 0;			//eye position X
GLdouble LOOKFROMY = 0;			//eye position Y
GLdouble LOOKFROMZ = 0;			//eye position Z
GLdouble LOOKATX = 0;			//reference point position X
GLdouble LOOKATY = 0;			//reference point position Y
GLdouble LOOKATZ = -1;			//reference point position Z
GLdouble UPX = 0;				//up vector X
GLdouble UPY = 1;				//up vector Y
GLdouble UPZ = 0;				//up vector Z
GLfloat AMBIENTLIGHT[] = { 0.3f, 0.3f, 0.3f, 1.0f };	//Color(0.3, 0.3, 0.3)
GLfloat LIGHTCOLOR[] = { 0.7f, 0.7f, 0.7f, 1.0f };		//Color (0.7, 0.7, 0.7)
GLfloat LIGHTSPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };	//Color (1.0, 1.0, 1.0)
GLfloat LIGHTSHININESS[] = { 15.0f };					//RGBA specular (15.0)
GLfloat LIGHTPOS[] = { -100.0f, 50.0f, 200.0f, 1.0f }; //Positioned at (-100, 50, 200)
int MODEL[30];	//store all animations got from obj files
ObjLoader OBJ;	//create an instance of the ObjLoader
int CURRENT_FRAME_NUMBER = 0;	//number of current frame loaded
const double TIME_PER_FRAME = 1000.0 / 30.0;	//time for each frame to be loaded

// -----------------------------------------------------------
// My function for handling window resizes. take in width w and height h
// ------------------------------------------------------------
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (float)w / (float)h, 1.0, 5000.0);
}

// -----------------------------------------------------------
// My function for enabling server-side GL capabilities and loading obj files
// ------------------------------------------------------------
void init()
{
	//compare depth and update depth buffer
	glEnable(GL_DEPTH_TEST);

	//load obj files store in 
	MODEL[0] = OBJ.load("character_walkingupstairs/character1.0001.obj");	//load it
	MODEL[1] = OBJ.load("character_walkingupstairs/character1.0003.obj");	//load it
	MODEL[2] = OBJ.load("character_walkingupstairs/character1.0005.obj");	//load it
	MODEL[3] = OBJ.load("character_walkingupstairs/character1.0007.obj");	//load it
	MODEL[4] = OBJ.load("character_walkingupstairs/character1.0009.obj");	//load it
	MODEL[5] = OBJ.load("character_walkingupstairs/character1.0011.obj");	//load it
	MODEL[6] = OBJ.load("character_walkingupstairs/character1.0013.obj");	//load it
	MODEL[7] = OBJ.load("character_walkingupstairs/character1.0015.obj");	//load it
	MODEL[8] = OBJ.load("character_walkingupstairs/character1.0017.obj");	//load it
	MODEL[9] = OBJ.load("character_walkingupstairs/character1.0019.obj");	//load it
	MODEL[10] = OBJ.load("character_walkingupstairs/character1.0021.obj");	//load it
	MODEL[11] = OBJ.load("character_walkingupstairs/character1.0023.obj");	//load it
	MODEL[12] = OBJ.load("character_walkingupstairs/character1.0026.obj");	//load it
	MODEL[13] = OBJ.load("character_walkingupstairs/character1.0027.obj");	//load it
	MODEL[14] = OBJ.load("character_walkingupstairs/character1.0029.obj");	//load it
	MODEL[15] = OBJ.load("character_pickup/character1.0001.obj");	//load it
	MODEL[16] = OBJ.load("character_pickup/character1.0003.obj");	//load it
	MODEL[17] = OBJ.load("character_pickup/character1.0005.obj");	//load it
	MODEL[18] = OBJ.load("character_pickup/character1.0007.obj");	//load it
	MODEL[19] = OBJ.load("character_pickup/character1.0009.obj");	//load it
	MODEL[20] = OBJ.load("character_pickup/character1.0011.obj");	//load it
	MODEL[21] = OBJ.load("character_pickup/character1.0013.obj");	//load it
	MODEL[22] = OBJ.load("character_pickup/character1.0015.obj");	//load it
	MODEL[23] = OBJ.load("character_pickup/character1.0017.obj");	//load it
	MODEL[24] = OBJ.load("character_pickup/character1.0019.obj");	//load it
	MODEL[25] = OBJ.load("character_pickup/character1.0021.obj");	//load it
	MODEL[26] = OBJ.load("character_pickup/character1.0023.obj");	//load it
	MODEL[27] = OBJ.load("character_pickup/character1.0025.obj");	//load it
	MODEL[28] = OBJ.load("character_pickup/character1.0027.obj");	//load it
	MODEL[29] = OBJ.load("character_pickup/character1.0029.obj");	//load it

	//enable light, normalizing normal vectors, material tracking color
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	//initial setting of light source
	float col[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);

	//initial viewing transformation
	gluLookAt(LOOKFROMX, LOOKFROMY, LOOKFROMZ, LOOKATX, LOOKATY, LOOKATZ, UPX, UPY, UPZ);
}

// -----------------------------------------------------------
// My function for display callback
// ------------------------------------------------------------
void display()
{
	//clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	// projection matrix defines the properties of the camera that views the objects in the world coordinate frame. 
	glMatrixMode(GL_PROJECTION);	
	// replace the current matrix with the identity matrix and starts a fresh because matrix transforms such as 
	//glOrpho and glRotate cumulate, basically puts at (0, 0, 0)
	glLoadIdentity(); 
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
	// (default matrix mode) modelview matrix defines how objects are transformed 
	//(meaning translation, rotation and scaling) in the world
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); // same as above comment

	//divide screen width and height by half
	GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
	GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

	//half frames are loaded with the ball and the cubes
	if (CURRENT_FRAME_NUMBER > 14)
	{
		glTranslatef(halfScreenWidth + 50, halfScreenHeight - 10, -500);	//translation
		glRotated(90, 0, 1, 0);												//rotate 90deg along y-axis

		//allow rotating around model by using keyboard
		glRotatef(ROTATE_X, 1.0, 0.0, 0.0);
		glRotatef(ROTATE_Y, 0.0, 1.0, 0.0);

		//draw 2 cubes and a ball
		DrawCube(halfScreenWidth - 320, halfScreenHeight - 280, 3, 40, 1);
		DrawCube(halfScreenWidth - 320, halfScreenHeight - 262, 24, 40, 2);
		DrawSphere(halfScreenWidth - 300, halfScreenHeight - 68, 36);
	}
	//other half frames are loaded with the ball and the cubes
	else
	{
		glTranslatef(halfScreenWidth, halfScreenHeight - 50, -500);		//translation
		glRotated(90, 0, 1, 0);											//rotate 90deg along y-axis

		//allow rotating around model by using keyboard
		glRotatef(ROTATE_X, 1.0, 0.0, 0.0);
		glRotatef(ROTATE_Y, 0.0, 1.0, 0.0);

		//draw 2 cubes and a ball
		DrawCube(halfScreenWidth - 320, halfScreenHeight - 240, 53, 40, 1);
		DrawCube(halfScreenWidth - 320, halfScreenHeight - 222, 74, 40, 2);
		DrawSphere(halfScreenWidth - 300, halfScreenHeight - 30, 87);
	}


	//Add ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AMBIENTLIGHT);

	//Add positioned light, specular light, shininess, diffuse light 
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHTSPECULAR);
	glLightfv(GL_LIGHT0, GL_SHININESS, LIGHTSHININESS);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHTCOLOR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS);

	//display the frames
	glCallList(MODEL[CURRENT_FRAME_NUMBER]);

	//swaps the buffers of the current window if double buffered
	glutSwapBuffers();		

}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//Right arrow - increase rotation around y by 5 degree
	if (key == GLUT_KEY_RIGHT)
		ROTATE_Y += 5;

	//Left arrow - decrease rotation around y by 5 degree
	else if (key == GLUT_KEY_LEFT)
		ROTATE_Y -= 5;

	//Up arrow - increase rotation around x by 5 degree
	else if (key == GLUT_KEY_UP)
		ROTATE_X += 5;

	//Down arrow - decrease rotation around x by 5 degree
	else if (key == GLUT_KEY_DOWN)
		ROTATE_X -= 5;

	//Request display update
	glutPostRedisplay();

}

// ----------------------------------------------------------
// draw cube function given center point (x,y,z) and edge length
// ----------------------------------------------------------
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength, GLint tt)
{
	//half edgelength
	GLfloat halfSideLength = edgeLength * 0.5f;

	//enable OpenGL to apply textures to subsequent polygons. 
	glEnable(GL_TEXTURE_2D);

	int width, height;
	unsigned char* image;

	//apply the texture with id _TEXTUREID
	glBindTexture(GL_TEXTURE_2D, _TEXTUREID);

	//using png files as texture for the cube, specify 2d texture and then free the data image 
	if (tt == 1)
		image = SOIL_load_image("brick.png", &width, &height, 0, SOIL_LOAD_RGB);	
	else 
		image = SOIL_load_image("red.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); 
	SOIL_free_image_data(image);

	//have OpenGL use blurry texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//OpenGL won't try to change the color of texture
	glColor3f(1.0f, 1.0f, 1.0f);

	//fetch 4 vertices for each of 6 faces, set texture coordinates and set current normal vector for each face
	//FRONT
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glEnd();

	//BACK
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glEnd();

	//RIGHT
	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glEnd();

	//LEFT
	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glEnd();

	//TOP
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength);
	glEnd();

	//BOTTOM
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

// -----------------------------------------------------------
// draw sphere function given (x,y,z) for translation
// ------------------------------------------------------------
void DrawSphere(GLfloat transX, GLfloat transY, GLfloat transZ) {
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(transX, transY, transZ);
	glColor3f(0.5f, 0.0f, 1.0f);
	glutSolidSphere(10, 10, 10);
	glPopAttrib();
	glPopMatrix();
}

// -----------------------------------------------------------
// My function for timer callback
// ------------------------------------------------------------
void _timer(int value) {


	/* send redisplay event */
	glutPostRedisplay();

	//if there's still frame, continue loading, else turn back to the first frame
	if (CURRENT_FRAME_NUMBER < 30) {
		CURRENT_FRAME_NUMBER++;
	}
	else
		CURRENT_FRAME_NUMBER = 0;


	/* call this function again in (TIME_PER_FRAME) milliseconds */
	glutTimerFunc(TIME_PER_FRAME, _timer, 0);

}

// -----------------------------------------------------------
// My main function
// ------------------------------------------------------------
int main(int argc, char** argv)
{
	//set up window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Final Project");

	//initial capabilities
	init();

	//callback functions
	glutDisplayFunc(display);					//display
	glutSpecialFunc(specialKeys);				//sets the special keyboard callback for the current window
	glutReshapeFunc(handleResize);				//resize window
	glutTimerFunc(TIME_PER_FRAME, _timer, 0);	//timer

	//enters the GLUT event processing loop
	glutMainLoop();

	return 0;
}