#include <iostream>
#include <glut.h>
#include "FreeImage.h"
#include <string>

#define PI 3.1415927 // ��
#define ANGLE 15     // ���� �������� � �������� 
#define RADIUS 1.0f  // ������ �����������
#define H 6			 // ������ ��������


float angleRight = 0, angleUp = 0, angleLeft = 0, angleDown = 0; // ��� �������� ��� ������� �� �������
const float light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };		 // ������������� �������� ����� (���� �����)
const float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		 // ������������� ��������� ���� ����� (���������� ����) (���������� ���� �� �������)
const float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		 // ������������� ����������� ����� (0-�����)
const float light_position[] = { 2.0f, 0.0f, 2.0f, 1.0f};		 // ������������� ��������� ��������� (w = 1 - ��������, 0 -������ (�����������))) ��������� �����

GLuint Texture1; // �������� ����� ������
GLuint Texture2; // �������� ������ � ����������
GLuint Texture3; // �������� ��� (�������)
GLuint texture; // ��������

/* �������� ����������� */
FIBITMAP* loadImage(const char* filename)
{
	FIBITMAP* dib = nullptr;
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);// ���������� ��� ������������ ����� ������ �� ��� ����������

	dib = FreeImage_Load(fif, filename, JPEG_DEFAULT); // ��������� � ������ ����������� ���� � �����.
	/* ���������, ������� �� ������ �������� */
	if (!dib)
	{
		std::cerr << "Image loading ERROR" << std::endl;
		exit(0);
	}
	std::cerr << "Success" << std::endl;
	return dib;
}

GLuint loadTexture(FIBITMAP* dib)
{
	GLuint tex = 0;    // ������������� ��������
	int x, y;		   // �������
	int height, width; // ������, ������

	RGBQUAD rgbquad;
	FREE_IMAGE_TYPE type;
	//BITMAPINFOHEADER* header;
	BYTE* bits = nullptr;
	bits = FreeImage_GetBits(dib);		// ����������� ���� �����������

	type = FreeImage_GetImageType(dib); // ���
	height = FreeImage_GetHeight(dib);  // ������
	width = FreeImage_GetWidth(dib);    // ������

	//header = FreeImage_GetInfoHeader(dib); // ��� ��������� �������� ���������� � �������� � �������� ������� ������������ �� ���������� ���������� ����������� (DIB)

	/* �������� ������� �����������  � ���������� � texels */
	int scanLineWidh = ((3 * width) % 4 == 0) ? 3 * width : ((3 * width) / 4) * 4 + 4;
	unsigned char* texels = (GLubyte*)calloc(height * scanLineWidh, sizeof(GLubyte)); // ����������� ������ �����������
	for (x = 0; x < width; x++)
		for (y = 0; y < height; y++)
		{
			FreeImage_GetPixelColor(dib, x, y, &rgbquad);
			texels[(y * scanLineWidh + 3 * x) + 0] = ((GLubyte*)&rgbquad)[2]; // RED
			texels[(y * scanLineWidh + 3 * x) + 1] = ((GLubyte*)&rgbquad)[1]; // BLUE
			texels[(y * scanLineWidh + 3 * x) + 2] = ((GLubyte*)&rgbquad)[0]; // GREEN
		}
	glGenTextures(1, &tex);			   // ��������� ����� �������� (1 -����������, &tex - ���� ��������� ��������)
	glBindTexture(GL_TEXTURE_2D, tex); // ���������

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // ��������� ���������� �����������, ���� ����� �� �������� ������ �� ��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // �� �Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ����������, ����� ��������������� ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ����� ���������������� �����

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, // ��������� �������� 
				 width, height, 0, GL_RGB,
			     GL_UNSIGNED_BYTE, texels);

	free(texels); // ����������� ���������� ������
	return tex;
}

GLuint LoadTextureAUTO(std::string filename)
{
	GLuint tex;								     // ������������� ��������
	FIBITMAP* dib = loadImage(filename.c_str()); // ��������� ����������� (����� �������)
	tex = loadTexture(dib);					     // ��������� �������� (����� �������)
	FreeImage_Unload(dib);						 // ���������
	return tex;
}


void renderScene() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
	//glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	//gluLookAt(-8, 1, 5, 0, 0, 0, 0, 1, 0);    //1,2,3-���������� ��������� ����� �����������
	//										  //4,5,6-��������� �����, ���� ��������� ��� ������
	//										  //7,8,9-��������� ����������� ��������� ����� ���� �����������

	//glEnable(GL_LIGHT0); // ������������� ��������� �����
	//glEnable(GL_LIGHTING);	

	///* ������������� ��������� ����� ��������� */
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	///* ������ ����� ��������� */
	//glRotatef(90, 0, 0, 1);

	///* ������� ��� ������������ ����������, �������������� �� �.(0, 0, 0) �� OY */	
	//glPushMatrix();
	//glRotatef(-180, 1, 0, 1);
	//glTranslatef(0, 0, H / 2); // ������� ����������
	//float angle, radian, x1, y1, xcos, ysin, tx, ty;

	//glEnable(GL_TEXTURE_2D); 
	//glBindTexture(GL_TEXTURE_2D, Texture2); // ��������� �������� ������

	//glBegin(GL_POLYGON);
	//for (angle = 0.0; angle < 360.0; angle += 2.0)
	//{
	//	radian = angle * (PI / 180.0f);

	//	xcos = (float)cos(radian);				 ysin = (float)sin(radian);
	//	x1 = xcos * RADIUS;					     y1 = ysin * RADIUS;
	//	tx = (x1 / RADIUS + 1) * 0.5;			 ty = (y1 / RADIUS + 1) * 0.5;

	//	glTexCoord2f(tx, ty);
	//	glVertex2f(x1, y1);
	//}
	//glEnd();
	//glDisable(GL_TEXTURE_2D);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, Texture3); // ��������� �������� ���
	//glTranslatef(0, 0, -H);

	//glBegin(GL_POLYGON);
	//for (angle = 0.0; angle < 360.0; angle += 2.0)
	//{
	//	radian = angle * (PI / 180.0f);

	//	xcos = (float)cos(radian);				 ysin = (float)sin(radian);
	//	x1 = xcos * RADIUS;					     y1 = ysin * RADIUS;
	//	tx = (x1 / RADIUS + 1) * 0.5;			 ty = (y1 / RADIUS + 1) * 0.5;

	//	glTexCoord2f(tx, ty);
	//	glVertex2f(x1, y1);
	//}

	//glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

	///* ������ ��� ������� */
	//glPushMatrix();
	//glRotatef(-90, 0, 1, 0);
	//const int n = 360 / ANGLE; // ���-�� �����, �� ������� �������� �������
	//double x[n], y[n];
	//for (int k = 0; k < n; k++) {
	//	x[k] = cos((double)2 * PI * k / n);
	//	y[k] = sin((double)2 * PI * k / n);
	//}
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, Texture1);

	//for (int k = 0; k < n; k++) {
	//	int m = (k + 1) % n;

	//	glBegin(GL_POLYGON);
	//	glTexCoord2f(0.99 / n * (k), 0.0);					 glVertex3f(x[k], y[k], H / 2);
	//	glTexCoord2f(0.99 / n * (k), 1.0);					 glVertex3f(x[k], y[k], -H / 2);
	//	glTexCoord2f(0.99 / n * ((double)k + 1), 1.0);		 glVertex3f(x[m], y[m], -H / 2);
	//	glTexCoord2f(0.99 / n * ((double)k + 1), 0.0);		 glVertex3f(x[m], y[m], H / 2);
	//	glEnd();
	//}
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

	//glutSwapBuffers();






	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	gluLookAt(40, 3, 7, 0, 0, 0, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* ������������ ��� ������� �� ������� */
	glRotatef(angleRight, 0.0f, 1.0f, 0.0f);
	glRotatef(angleUp, 1.0f, 0.0f, 0.0f);
	glRotatef(angleLeft, 0.0f, -1.0f, 0.0f);
	glRotatef(angleDown, -1.0f, 0.0f, 0.0f);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	double r = 10;
	int nx = 30;
	int ny = 30;
	int i, ix, iy;
	double x, y, z;
	glBegin(GL_QUAD_STRIP);
	for (ix = 0; ix <= nx; ++ix)
	{
		for (iy = 0; iy <= ny; ++iy)
		{
			x = r * sin(iy * PI / ny);
			y = r * sin(iy * PI / ny) * cos(2 * ix * PI / nx);
			z = r * sin(iy * PI / ny)* sin(2 * ix * PI / nx);
			//������� ���������� �� ������
			glNormal3f(x, y, z);
			glTexCoord2f((double)ix / (double)nx, (double)iy / (double)ny);
			glVertex3f(x, y, z);
			x = r * sin((iy + 1) * PI / ny) *
				cos(2 * ix * PI / nx);
			y = r * sin((iy + 1) * PI / ny) *
				sin(2 * ix * PI / nx);
			z = r * cos((iy + 1) * PI / ny);
			glNormal3f(x, y, z);
			glTexCoord2f((double)ix / (double)nx, (double)(iy + 1) / (double)ny);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
	glutSwapBuffers();
}

/* ��������� ������� ������� �� ���������� */
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		angleLeft += 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleRight += 5.1f;
		break;
	case GLUT_KEY_UP:
		angleUp += 5.1f;
		break;
	case GLUT_KEY_DOWN:
		angleDown += 5.1f;
		break;
	}
}

/* ��� ��������� ������� ���� */
void ChangeSize(int w, int h) {
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;   // ��������� ������ ���� � ������
	glMatrixMode(GL_PROJECTION); // ������� �������� (������������� 3� � 2�)
	glLoadIdentity();            // �������� ���.������� �������� ��������� (� ������ �����)
	glViewport(0, 0, w, h);      // ������� ����, � ������� ������������ ��� ������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // ������������� �������������� (��� ������������ 3� �������)
												//3-���������� �� ������ ������������� �� ��������� ����� ���������
												//4- ���������� �� ������ ����� �� ������ ��������� ���������
	glMatrixMode(GL_MODELVIEW);  // ������� �������� ������. ������ ��� ��������� �������� �������� �����
}

/* ������� ������� */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // ������������� glut (1-����� ����������, 2-�� ��������)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
															  // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
															  // 3-�������� �������� ����
	glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
	glutInitWindowSize(1000, 600);                            // ������� ����

	glutCreateWindow("����� ������ � ����");			      // ������� ���� � ������

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����
	glutIdleFunc(renderScene);								  // �������� �� ��������
	glutSpecialFunc(processSpecialKeys);					  // �������� �� ������� ����. �������� (�������)

   // Texture1 = LoadTextureAUTO("pringlesNEW.jpeg");
	//Texture2 = LoadTextureAUTO("krishkaNEW.jpg");
	//Texture3 = LoadTextureAUTO("Gelezo.jpg");
	texture = LoadTextureAUTO("earth.jpg");

	glutMainLoop();											  // ���� � ������� ����
	return 0;
}