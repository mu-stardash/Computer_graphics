#include <iostream>
#include <glut.h>

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	gluLookAt(-15, -15, -15, 0, 0, 0, 0, 1, 0); //1,2,3-���������� ��������� ����� �����������
											 //4,5,6-��������� �����, ���� ��������� ��� ������
											 //7,8,9-��������� ����������� ��������� ����� ���� �����������
	

	//glRotatef(-85, 1, 0, 0);

	glBegin(GL_QUADS); // left
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 1, 0);
	glEnd();

	glBegin(GL_QUADS); // right
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(1, 0, 0);
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 0);
	glEnd();

	glBegin(GL_QUADS); // down
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 0, 1);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS); // up
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(1, 0, 1);
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 0, 1);
	glEnd();

	glBegin(GL_QUADS); // front
	glVertex3f(1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(-1.0*4, 1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(-1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glVertex3f(1.0*4, -1.0*4, 1.0*4);
	glColor3f(1, 1, 0);
	glEnd();

	glBegin(GL_QUADS); // back
	glVertex3f(1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(-1.0*4, -1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glVertex3f(-1.0*4, 1.0*4, -1.0*4);
	glColor3f(0, 1, 1);
	glEnd();
	
	glutSwapBuffers(); // ���������� ������, ��������� ���� �������, ����� ���� ��� ��� �������-��
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