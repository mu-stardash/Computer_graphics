#include <iostream>
#include <glut.h>

#define PI 3.1415927 // ��
#define ANGLE 5     // ���� �������� � �������� 

/* ��� �������� �������� � �������� */
double Cos(double alpha) {
	alpha = cos(PI / 180 * (alpha));
	return alpha;
}

/* ��� ������� ������ � �������� */
double Sin(double alpha) {
	alpha = sin(PI / 180 * (alpha));
	return alpha;
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	gluLookAt(5, 1, 5, 0, 0, 0, 0, 1, 0);    //1,2,3-���������� ��������� ����� �����������
											 //4,5,6-��������� �����, ���� ��������� ��� ������
											 //7,8,9-��������� ����������� ��������� ����� ���� �����������
	glRotatef(90, 0, 0, 1);
	/* ������� ��� ������������ ����������, �������������� �� �.(0, 0, 0) �� OY */
	for (int i = 1; i >= -1; i -= 2) {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 0.1, 0.0);
		glVertex3f(0, i, 0); // �����
		for (double k = 0; k <= 360; k += ANGLE) {
			glColor3f(0.5, 0.0, 0.5);
			glVertex3f(Cos(k), i,  Sin(k));
		}
		glEnd();
	}
	    
	glBegin(GL_TRIANGLE_STRIP); // ������� ������� 
	for (int j = 0; j <= 360; j += ANGLE) {
		glColor3f(1.0, 0.1, 0.0);
		glVertex3f(Cos(j), 1, Sin(j));
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(Cos(j), -1, Sin(j));
	}
	glEnd(); 

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

int main(int argc, char** argv) {
	glutInit(&argc, argv);                                    // ������������� glut (1-����� ����������, 2-�� ��������)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
															  // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
															  // 3-�������� �������� ����
	glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
	glutInitWindowSize(1000, 600);                             // ������� ����

	glutCreateWindow("OpenGL");								  // ������� ���� � ������

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����

	glutMainLoop();											  // ���� � ������� ����
	return 0;
}