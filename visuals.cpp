#include <stdio.h>    
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "GLUT/glut.h"   
#include "visuals.h"   

bool one = false;
static float tx = 0.0;
static float rotx = 0.0;
static float worldX = 15.0;
static float worldY = 0.0;
static float scaleFactor = 0.6;
static bool animate = false;
static float first = 1;
static float second = 1;
point stars[500];
GLuint texture1;

int globalW, globalH;

using namespace std;

void naslov(const char *str, float size)
{

	glPushMatrix();
	glScalef(size, size, size);

	for (int i = 0; i<strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();

}

GLuint LoadTexture(const char* filename, int width, int height){
       GLuint texture;
       unsigned char* data;
       FILE* file;
       file=fopen(filename, "rb");
       if(file==NULL)return 0;
       data=(unsigned char*)malloc(width * height * 3);
       fread(data,width * height * 3,1,file);
       fclose(file);
       glGenTextures(1,&texture);
       glBindTexture(GL_TEXTURE_2D,texture);
       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);       
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
       glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
       free(data);
       return texture;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
														 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    texture1 = LoadTexture("textures/2k_mars.jpg",256, 256);

	glTranslatef(0, 0, -100);
	
	if (!animate) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glTranslatef(-8, 50, 0.0);
		naslov("Stopirano", 0.05f);
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);



	glScalef(scaleFactor, scaleFactor, scaleFactor);

	glRotatef(worldX, 1, 0, 0);
	glRotatef(worldY, 0, 1, 0);

	glDisable(GL_LIGHTING);
 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture1); 
	glColor3f(0.8, 0.498039, 0.196078);
	gluSphere(quadric, 15, 36, 18); 
	glColor3f(1, 1, 0); 
	glEnable(GL_BLEND);
	glBlendFunc(first, second);
	gluSphere(quadric, 20, 36, 18);
	gluQuadricTexture(quadric, GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 0.0, 0.0, 0.0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);


	
	glPushMatrix(); //1 planeta
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(40, 0, -10.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(1, 0, 1);                            
	gluSphere(quadric, 5, 36, 18);
	glPopMatrix();

	glPushMatrix();// 2 planeta
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(-20, 0.0, -70);
	glRotatef(rotx, 0, 0, 1);
	glColor3f(0, 1, 0);                            
	gluSphere(quadric, 10, 36, 18);
	glPopMatrix();

	glPushMatrix();// 3 planeta 
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(-60, 0, 0.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(0, 0, 1);                            
	gluSphere(quadric, 17, 36, 18);
	glPopMatrix();


	glPushMatrix();// 4 planeta
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(20, 0, 44.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(0, 1, 1);                            
	gluSphere(quadric, 11, 36, 18);
	glPopMatrix();

	glPushMatrix();// 5 planeta
	glRotatef(rotx, 0, 1, 0);
	glTranslatef(-60, 0, -70.0);
	glRotatef(rotx, 1, 0, 0);
	glColor3f(1, 0, 0);                            
	gluSphere(quadric, 13, 36, 18);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	DrawStars();


	glutSwapBuffers();             
}



//-----------------------------------------------------------

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	globalH = h;
	globalW = w;

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 1000.0);
}

void Idle()
{
	if (animate)
		rotx += 1.1;

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': exit(0);
		break;
	case '1': if (animate) worldX -= 1.0f;
		break;
	case '2': if (animate) worldX += 1.0f;
		break;
	case '3': if (animate) worldY -= 1.0f;
		break;
	case '4': if (animate)  worldY += 1.0f;
		break;
	case ' ': animate = !animate;;
		break;
	default: break;
	}
	glutPostRedisplay();

}

void MouseWheel(int button, int dir, int x, int y)
{
	if (animate) {
		if (dir > 0) {
			scaleFactor += 0.01;
			glutPostRedisplay();
		}
		else {
			if (scaleFactor > 0.08) {
				scaleFactor -= 0.01;
				glutPostRedisplay();
			}
		}
	}
}


void Setup() 
{

	for (int i = 0; i < 500; i++)
		RandomCoordinates(&stars[i]);
	srand(time(0));
	//Parametri
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon renderovanje
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Crna pozadina
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RandomCoordinates(point *star)
{

	int lowest = -1000, highest = 1000;
	int range = (highest - lowest) + 1;
	star->x = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->y = lowest + int(range*rand() / (RAND_MAX + 1.0));
	star->z = lowest + int(range*rand() / (RAND_MAX + 1.0));
	
}

void DrawStars()
{
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);
	for ( int i = 0; i < 500; i ++ ) {
		glPushMatrix();
		glTranslatef(stars[i].x, stars[i].y, stars[i].z);
		glColor3f(1, 1, 1);
		gluSphere(quadric, 1, 36, 18);
		glPopMatrix();
	}
}
