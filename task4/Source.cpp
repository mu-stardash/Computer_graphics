//#include <iostream>
//#include <glut.h>
//#include <math.h>                                  // ��� ������� Sin()
//
//float points[45][45][3]; // ������ ����� ����� ����� "�����"
//
//int wiggle_count = 0;        // ������� ��� �������� �������� ���������� �����
//GLfloat hold;                // �������� �������� ����� � ��������� �������
//
//void Volna() {
//	// ��������� �� ��� X
//	for (int x = 0; x < 45; x++)
//	{
//		// ��������� �� ��� Y
//		for (int y = 0; y < 45; y++)
//		{
//			// �������� ����� � ����� �����
//			points[x][y][0] = float((x / 5.0f) - 4.5f);
//			points[x][y][1] = float((y / 5.0f) - 4.5f);
//			points[x][y][2] = float(sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.141592654 * 2.0f));
//		}
//	}
//}
//
//void renderScene() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������. 1-������� ������
//	glLoadIdentity();									// �������� ���.������� �������� ��������� (� ������ �����)
//
//	gluLookAt(4, 4, 4, 0, 0, 0, 0, 1, 0);    //1,2,3-���������� ��������� ����� �����������
//											 //4,5,6-��������� �����, ���� ��������� ��� ������
//											 //7,8,9-��������� ����������� ��������� ����� ���� �����������

//	GLfloat	xrot=0;			// �������� X
//	GLfloat	yrot=0;			// Y
//	GLfloat	zrot=0;			// Z
//
//	int x, y;  // ���������� ������
//	 // ��� ��������� ����� �� ��������� ��������
//	float float_x, float_y, float_xb, float_yb;
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �������� ����� � ����� �������
//
////	glLoadIdentity();                                   // ����� ������� �������
////	glTranslatef(0.0f, 0.0f, -12.0f);                     // ��������� 17 ������ � ����� ������
//
//	glRotatef(xrot, 1.0f, 0.0f, 0.0f);                     // �������� �� ��� X
//	glRotatef(yrot, 0.0f, 1.0f, 0.0f);                     // �������� �� ��� Y 
//	glRotatef(zrot, 0.0f, 0.0f, 1.0f);                     // �������� �� ��� Z
//
//	//glPolygonMode(GL_BACK, GL_FILL);       // ������ (������) ������� ���������
//	//glPolygonMode(GL_FRONT, GL_LINE);      // ������� (��������) ������� ����������� �������
//
//	//Volna();
//
//	glBegin(GL_QUADS);              // �������� �������� ��������
//	
//			glVertex3f(0, 0, 0);
//			glVertex3f(0, 1, 0);
//			glVertex3f(1, 1, -1);
//			glVertex3f(1, 0, -1);
//		glEnd();       
//		xrot += 0.3f;             // ��������� �������� ���������� �������� �� X
//		yrot += 0.2f;             // ��������� �������� ���������� �������� �� Y
//		zrot += 0.4f;             // ��������� �������� ���������� �������� �� Z

//		glutSwapBuffers();
//}
//
//void ChangeSize(int w, int h) {
//	if (h == 0)
//		h = 1;
//
//	float ratio = w * 1.0 / h;   // ��������� ������ ���� � ������
//	glMatrixMode(GL_PROJECTION); // ������� �������� (������������� 3� � 2�)
//	glLoadIdentity();            // �������� ���.������� �������� ��������� (� ������ �����)
//	glViewport(0, 0, w, h);      // ������� ����, � ������� ������������ ��� ������
//	gluPerspective(45.0f, ratio, 0.1f, 100.0f); // ������������� �������������� (��� ������������ 3� �������)
//												//3-���������� �� ������ ������������� �� ��������� ����� ���������
//												//4- ���������� �� ������ ����� �� ������ ��������� ���������
//	glMatrixMode(GL_MODELVIEW);  // ������� �������� ������. ������ ��� ��������� �������� �������� �����
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);                                    // ������������� glut (1-����� ����������, 2-�� ��������)
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
//															  // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
//															  // 3-�������� �������� ����
//	glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
//	glutInitWindowSize(1000, 600);                             // ������� ����
//
//	glutCreateWindow("OpenGL");								  // ������� ���� � ������
//
//	glEnable(GL_DEPTH_TEST);
//	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
//	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����
//
//	glutMainLoop();											  // ���� � ������� ����
//	return 0;
//}


#include <iostream>
#include <glut.h>
#include <math.h> 

const double PI = 3.14159265358979323846;

//������������� ��� ��������� �������� ����
void ChangeSize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

double p = 0;

void renderScene(void) {

    p += 0.01;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(20, -20/2, 60/2, 7.5, 6.5, 0, 0, 1, 0);


    const double z = 0.0;
    const double STEP_X = 0.1; // ��� �� ��� X � �������������� ������� �������������.
    double HEIGHT = 13; // ������ ������ (�������� �� Y).

    for (double x = 0; x <= 15; x += STEP_X) {
        double y1 = sin(x + p) * 0.4;           // �������� y ��� x.
        double y2 = sin(x + p + STEP_X) * 0.4; // �������� y ��� (x + STEP_X).

        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.2, 0.0);
        glVertex3d(x, y1, z);
        glVertex3d(x, y1 + HEIGHT , z);
        glVertex3d(x + STEP_X, y2 + HEIGHT, z);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.2, 0.0);
        glVertex3d(x - 0.5, y1 - 0.5, z);
        glVertex3d(x + STEP_X, y2, z);
        glVertex3d(x + STEP_X, y2 + HEIGHT, z);
        glEnd();
    }

    glutSwapBuffers();
    // �� ����� ������������
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(ChangeSize);
    glEnable(GL_DEPTH_TEST); 
    glutMainLoop();
    return 0;
}