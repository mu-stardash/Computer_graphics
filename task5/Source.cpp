#include <iostream>
#include <glut.h>
#include <math.h>

float angleRight = 0, angleUp = 0, angleLeft = 0, angleDown = 0;
// ���� �������� (��������) ��� ������ � ��������
float planet = 0.0;
float satellite = 0.0f;


const float light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f}; // ������������� �������� �����
const float light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f}; // ������������� ��������� ���� ����� (���������� ����)
const float light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f}; // ������������� ����������� ����� (0-�����)
const float light_position[] = { 0.0f, 0.75f, 0.0f, 1.0f}; // ������������� ��������� ��������� (w = 1) ��������� �����

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	gluLookAt(2, 4, 60, 0, 0, 0, 0, 1, 0);    //1,2,3-���������� ��������� ����� �����������
											 //4,5,6-��������� �����, ���� ��������� ��� ������
											 //7,8,9-��������� ����������� ��������� ����� ���� �����������

	glRotatef(angleRight, 0.0f, 1.0f, 0.0f);
	glRotatef(angleUp, 1.0f, 0.0f, 0.0f);
	glRotatef(angleLeft, 0.0f, -1.0f, 0.0f);
	glRotatef(angleDown, -1.0f, 0.0f, 0.0f);


	glEnable(GL_LIGHT0); // ������������� ��������� �����
	glEnable(GL_LIGHTING); // ���. ������ ���������
	glEnable(GL_COLOR_MATERIAL); //����� �������� ������� glColor3f

	/* ������������� ��������� ����� ��������� */
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Draw Sun : color yellow	
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(3.0f, 100, 100);

	glEnable(GL_LIGHTING); // ������������� ��������� �����
	glRotatef(planet, 0.0f, 1.0f, 0.0f);
	
	//Venus : drak yellow	
	glColor3f(0.9f, 0.7f, 0.0f);	
	glTranslatef(-14.0f, 0.60, 0.0f);
	glutSolidSphere(0.75f, 60, 60);

	//Mercury : Red
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(7.0f, 0.0f, 4.0f);
	glutSolidSphere(0.60f, 40, 40);

	//Earth : blue	
	glPushMatrix();
	glColor3f(0.0f, 0.7f, 1.0f);
	glTranslatef(17.0f, 0.0f, 8.0f);
	glutSolidSphere(1.5f, 40, 40);	

	//Moon : gray
	glRotatef(satellite, 0.0f, 1.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(2.0, 0.0f, 2.0f);
	glutSolidSphere(0.5f, 40, 40);
	satellite += 1.0f;
	glPopMatrix();

	//Mars : pink
	glColor3f(1.0f, 0.5f, 0.5f);
	glTranslatef(12.0f, 0.0f, -15.0f);
	glutSolidSphere(0.75f, 40, 40);

	//Jupiter: drak yellow
	glColor3f(0.9f, 0.5f, 0.0f);
	glTranslatef(12.0f, 0.0f, 5.0f);
	glutSolidSphere(1.9f, 40, 40);

	//Saturn: brown
	glColor3f(0.7f, 0.6f, 0.2f);
	glTranslatef(5.0f, 0.0f, -10.0f);
	glutSolidSphere(1.5f, 60, 60);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	GLUquadric* q = gluNewQuadric(); // ���� ������ �������
	glColor3f(0.9f, 0.6f, 0.2f);
	gluDisk(q, 2, 3, 60, 60);
	glPopMatrix();

	planet += 0.2f;

	glutSwapBuffers();
}


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

void processSpecialKeys(int key, int xx, int yy) {
	//float fraction = 0.1f;
	switch (key) {
	case GLUT_KEY_LEFT :
		angleLeft += 5.0f;
		break;
	case GLUT_KEY_RIGHT :
		angleRight += 5.1f;
		break;
	case GLUT_KEY_UP :
		angleUp += 5.1f;
		break;
	case GLUT_KEY_DOWN :
		angleDown += 5.1f;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // ������������� glut (1-����� ����������, 2-�� ��������)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
															  // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
															  // 3-�������� �������� ����
	glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
	glutInitWindowSize(1000, 600);                            // ������� ����

	glutCreateWindow("Solar System");						  // ������� ���� � ������

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����
	glutIdleFunc(renderScene);								  // �������� �� ��������
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();											  // ���� � ������� ����
	return 0;
}
