#include <iostream>
#include <glut.h>

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������, 2-������� ������ �������
	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)

	gluLookAt(4, 4, 4, 0, 0, 0, 0, 1, 0);    //1,2,3-���������� ��������� ����� �����������
											 //4,5,6-��������� �����, ���� ��������� ��� ������
											 //7,8,9-��������� ����������� ��������� ����� ���� �����������

	
	glTranslatef(-1.0f, 0.0f, 1.0f);         // ������������ ������� ����� 
	
	/* ������ ��������� */
	glBegin(GL_TRIANGLES);  // front
	glColor3f(0.3, 0.0, 0.6);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1.0, 0.25, 0.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.3, 0.0, 0.6); // right
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.3, 0.0, 0.6); // left
    glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	glColor3f(1.0, 0.25, 0.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.25, 0.0); // down
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();

	/* ������. ������� ������ � ������� ���� */
	glTranslatef(2.0f, 0.0f, -2.0f);
	glRotatef(-20, 0, 1, 0);
	/* ������ ��� */
	glBegin(GL_QUADS); // left
	glVertex3f(-1.0, 1.0, 1.0);
	glColor3f(0, 1, 0);

	glVertex3f(-1.0, 1.0, -1.0);
	glColor3f(0, 1, 0);

	glVertex3f(-1.0, -1.0, -1.0);
	glColor3f(0, 1, 0);

	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(0, 1, 0);
	glEnd();

	glBegin(GL_QUADS); // right
	glVertex3f(1.0, 1.0, 1.0);
	glColor3f(1, 0, 0);

	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(1, 0, 0);

	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(1, 0, 0);

	glVertex3f(1.0, 1.0, -1.0);
	glColor3f(1, 0, 0);
	glEnd();

	glBegin(GL_QUADS); // down
	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(0, 0, 1);

	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(0, 0, 1);

	glVertex3f(-1.0, -1.0, -1.0);
	glColor3f(0, 0, 1);

	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON); // up
	glVertex3f(1.0, 1.0, 1.0);
	glColor3f(1, 0, 1);

	glVertex3f(1.0, 1.0, -1.0);
	glColor3f(1, 0, 1);

	glVertex3f(-1.0, 1.0, -1.0);
	glColor3f(1, 0, 1);

	glVertex3f(-1.0, 1.0, 1.0);
	glColor3f(1, 0, 1);
	glEnd();

	glBegin(GL_POLYGON); // front
	glVertex3f(1.0, 1.0, 1.0);
	glColor3f(1, 1, 0);

	glVertex3f(-1.0, 1.0, 1.0);
	glColor3f(1, 1, 0);

	glVertex3f(-1.0, -1.0, 1.0);
	glColor3f(1, 1, 0);

	glVertex3f(1.0, -1.0, 1.0);
	glColor3f(1, 1, 0);
	glEnd();

	glBegin(GL_POLYGON); // back
	glVertex3f(1.0, 1.0, -1.0);
	glColor3f(0, 1, 1);

	glVertex3f(1.0, -1.0, -1.0);
	glColor3f(0, 1, 1);

	glVertex3f(-1.0, -1.0, -1.0);
	glColor3f(0, 1, 1);

	glVertex3f(-1.0, 1.0, -1.0);
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
	glutInitWindowSize(900, 600);                             // ������� ����
							  
	glutCreateWindow("OpenGL");								  // ������� ���� � ������
	glEnable(GL_DEPTH_TEST);				 // ����� ������� �������

	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����

	glutMainLoop();											  // ���� � ������� ����
	return 0;
}