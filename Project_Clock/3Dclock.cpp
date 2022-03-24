/* �������� ������ �� ������������ �������
 * ��������: "3� ����"
 * ���������: �������� ������ 22205
 * ������� ����� ��������� � ����� ����� ��������
 * 24.12.2020
 */

#include <glut.h>
#include <iostream>
#include <time.h>

using namespace std;

struct tm* curr_time;       // �����
int old_sec;                // ����������� (������) ����� � ��������
time_t local_time;          // ��������� ����� 

// ������ ������� ����� �� 1 �� 12
string num1[12] = { "I", "II", "III", "IV", "V", "VI",
					"VII", "VIII", "IX", "X", "XI", "XII" };

// ������ �������� ����� �� 1 �� 12
string num2[12] = { "1","2","3","4","5","6",
					"7","8","9", "10", "11","12" };
string* num = num1;			 // �� ��������� ������������ ������� �����

double eyepos[3] = { 0, 0, 15 };		 // ��������� ������� ������������
float arrow_angle[3] = { 90, 90, 90 };   // ��������� ���� ������� �� �����
GLfloat light1[] = { (GLfloat)250 / 255, (GLfloat)12 / 255, (GLfloat)12 / 255, 1.0f, 1.0f }; // ���� ����� �����
float angleR = 0.0, angleL = 0.0, angleU = 0.0, angleD = 0.0; // ��� �������� ��������


/* ������ n ����� � �������� r, ���������� ����� ������ ����� d*/
void drawBalls(GLfloat r, GLfloat d, int n) {
	GLfloat m = r * 2 + d; // ��������� ������� ����� ��� �� �����������
	glPushMatrix();
	for (int k = 0; k < n; k++) {
		glutSolidSphere(r, 15, 15);
		glTranslated(m, 0.0, 0.0);
	}
	glPopMatrix();
}

/* ������ �����, ��������� �� ������� */
void drawDigit(int i, GLfloat r, GLfloat d) {
	GLfloat m = 2 * r + d; // ��������� ������� ����� ��� �� �����������
	switch (i) {
	case 0: // ������������ ����������� ����� �� 0 �� 9
		glPushMatrix();
		drawBalls(r, d, 4);
		glRotated(-90.0, 0, 0, 1);
		glTranslated(m, 0.0, 0.0);
		drawBalls(r, d, 6);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, -6.0 * m, 0.0);
		drawBalls(r, d, 3);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -2.0 * m, 0);
		drawBalls(r, d, 6);
		glPopMatrix();
		break;
	case 1:
		glPushMatrix();
		glTranslated(3.0 * m, 0.0, 0.0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, -3.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, 0, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslated(3.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 3);
		glTranslated(3.0 * m, 0, 0);
		glRotated(90, 0, 0, 1);
		drawBalls(r, d, 3);
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 4);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, -m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 2);
		glTranslated(3.0 * m, 3.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -6.0 * m, 0);
		drawBalls(r, d, 3);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, 0, 0);
		drawBalls(r, d, 3);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 3);
		glTranslated(2.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 3);
		glPopMatrix();
		break;
	case 7:
		glPushMatrix();
		drawBalls(r, d, 3);
		glTranslated(3.0 * m, 0.0, 0.0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 8:
		glPushMatrix();
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glRotated(90, 0, 0, 1);
		glTranslated(m, -6.0 * m, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		glPushMatrix();
		glTranslated(m, 0, 0);
		drawBalls(r, d, 2);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 2);
		glTranslated(2.0 * m, 3.0 * m, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	case 9:
		glPushMatrix();
		drawBalls(r, d, 3);
		glTranslated(0, -3.0 * m, 0);
		drawBalls(r, d, 3);
		glRotated(90, 0, 0, 1);
		glTranslated(m, 0, 0);
		drawBalls(r, d, 2);
		glPopMatrix();
		glPushMatrix();
		glTranslated(3.0 * m, 0, 0);
		glRotated(-90, 0, 0, 1);
		drawBalls(r, d, 7);
		glPopMatrix();
		break;
	}
}

/* ��������� �������� ������� */
void drawDigitalTime(int h, int m, int s, GLfloat r, GLfloat d) {
	GLfloat l = r * 2 + d;
	if (h >= 10) // ���� ������ ������ 10 �����
		drawDigit(h / 10, r, d); // ������ ������ ����� �����
	glPushMatrix();
	glTranslated(1.8, 0, 0);
	drawDigit(h % 10, r, d); // ��������� ������ ����� �����
	glTranslated(2, 0, 0);
	glPushMatrix();
	glRotated(-90, 0, 0, 1); // ������������ ��� ����������� �� ���������
	glTranslated(l, 0, 0);
	drawBalls(r, 3 * l, 2); //  ��������� ������ ���������
	glPopMatrix();

	glTranslated(1, 0, 0);
	drawDigit(m / 10, r, d); // ������������ ������ ����� �����
	glTranslated(1.8, 0, 0);
	drawDigit(m % 10, r, d); // ������
	glTranslated(2, 0, 0);
	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	glTranslated(l, 0, 0);
	drawBalls(r, 3 * l, 2); // ��������� ������ ���������
	glPopMatrix();

	glTranslated(1, 0, 0);
	drawDigit(s / 10, r, d); // ��������� ������ ����� ������
	glTranslated(1.8, 0, 0);
	drawDigit(s % 10, r, d); // ��������� ������ ����� ������
	glPopMatrix();
}

/* ����������� ������������� �������� ����� � GLfloat */
inline GLfloat doColor(int n) {
	return (GLfloat)n / 255.0;
}

/* ��������� ��������� �������������� (�������) */
void drawArrow(int n, GLfloat poly[][3])
{
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++) {
		glVertex3f(poly[i][0], poly[i][1], poly[i][2]);
	}
	glEnd();
}

/* ������� ��������� ����� */
void drawString(GLfloat fSize, char* str)
{
	char* p;
	glPushMatrix();
	glScalef(fSize / 500, fSize / 500, fSize / 500); // ������������� ������ ������
	for (p = str; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); // ����� ����
	glPopMatrix();
}

void renderScene() {
	// �������� ����� ���� � �������
	static GLfloat light2[] = { doColor(348), doColor(91), doColor(86), 1.0f, 1.0f };
	static GLfloat light3[] = { doColor(255), doColor(206), doColor(133), 1.0f, 1.0f };

	static GLfloat r = 0.15f, d = 0.05f; // ������ ���� � ����������
	static int k;

	/* ��������, �������. ��� ��������� ������� � ����� ����� */
	GLfloat arrowSec[4][3] = { {-1,0,0},{0,0.2f,0},{10,0,0}, {0,-0.2f,0} }; // ���������� ��������� �������
	GLfloat arrowMin[4][3] = { {-1,0,0},{0,0.6f,0},{8,0,0},{0,-0.6f,0} };   // ���������� �������� �������
	GLfloat arrowHour[4][3] = { {-1,0,0},{0,0.8f,0},{5,0,0},{0,-0.8f,0} };   // ���������� ������� �������
	GLfloat scaleHour[4][3] = { {-2,0.5f,0}, {2,0.5f,0}, {2,-0.5f,0},{-2,-0.5f,0} }; // ����� �������

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������� ������
	glLoadIdentity();
	gluLookAt(eyepos[0], eyepos[1], eyepos[2],    // �������������� ���������
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	/* ������������ ���� ��� ������� �� ������� */
	glRotatef(angleR, 0.0f, 1.0f, 0.0f);
	glRotatef(angleU, 1.0f, 0.0f, 0.0f);
	glRotatef(angleL, 0.0f, -1.0f, 0.0f);
	glRotatef(angleD, -1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);    // ������������� ��������� ����� (����. ����)
	glEnable(GL_LIGHTING);						 // ���. ������ ���������
	glEnable(GL_LIGHT0);						 // ������������� ��������� �����

	glutSolidTorus(0.3, 14, 128, 128);           // ������ ����� �����
	glDisable(GL_LIGHT1);						 // ��������� ���������
	glDisable(GL_LIGHTING);

	glPushMatrix();				// �������� � �������, ����� ��������� ������ �������
	glRotatef(180, 0, 1, 0);    // ������������� ���� ��� ����������� �����������
	glPushMatrix();
	glRotatef(arrow_angle[0], 0, 0, 1);           // ������������ ������ (���������� 90 ��������)
	glColor3f(doColor(255), doColor(153), doColor(0));       // ������������� ���� ��� ��������
	drawArrow(4, arrowSec);                         // ������ ������� (���. �������) �� �������� �����������
	glPopMatrix();

	/* ��������� �������� ������� */
	glPushMatrix();
	glRotatef(arrow_angle[1], 0, 0, 1);
	glColor3f(doColor(220), doColor(20), doColor(60));
	drawArrow(4, arrowMin);
	glPopMatrix();

	/* ��������� ������� �������*/
	glPushMatrix();
	glRotatef(arrow_angle[2], 0, 0, 1);
	glColor3f(doColor(148), doColor(0), doColor(211));
	drawArrow(4, arrowHour);
	glPopMatrix();
	glPopMatrix();

	/* ������ ������� ����� */
	glColor3f(0.82f, 0.72f, 0.32f);
	for (k = 0; k < 12; k++) {
		glPushMatrix();
		glRotatef(k * 30, 0, 0, 1); // ������ 30 ��������
		glTranslatef(13, 0, 0);
		glScalef(0.2f, 0.1f, 1);    // ������� ����� ������ ��������
		glColor3f(1, (GLfloat)169 / 255, (GLfloat)112 / 255);
		drawArrow(4, scaleHour);
		glPopMatrix();
	}

	/* ������ �������� ����� */
	for (k = 0; k < 60; k++) {
		glPushMatrix();
		glRotatef(k * 6, 0, 0, 1);
		glTranslatef(13, 0, 0);
		glScalef(0.2f, 1, 1);
		glColor3f(1, (GLfloat)169 / 255, (GLfloat)112 / 255);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
		glEnd();
		glPopMatrix();
	}

	/* ����������� ����� �� ������� ����� */
	glColor3f(doColor(198), doColor(255), doColor(217));
	for (k = 0; k < 12; k++) {
		glPushMatrix();
		glRotatef(60 - k * 30, 0, 0, 1);
		glTranslatef(11, 0, 0);
		glRotatef(-60 + k * 30, 0, 0, 1);
		drawString(6, (char*)num[k].c_str());
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);						// ��� ���������
	glEnable(GL_LIGHT0);					    // ��� �������� �����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light2);   // ������ ���������� ���������

	/* ������ ����� (������ ������� � ������ �����) */
	glutSolidSphere(0.3, 32, 32);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light3);	// ������ ���� �����

	/* ������ �������� ���� ���� ������ */
	glTranslatef(-6.5f, 7, 0);
	drawDigitalTime(curr_time->tm_hour, curr_time->tm_min, curr_time->tm_sec, r, d);

	glutSwapBuffers();
}

/* ��� ��������� ���� */
void ChangeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;   // ��������� ������ ���� � ������
	glMatrixMode(GL_PROJECTION); // ������� �������� (������������� 3� � 2�)
	glLoadIdentity();            // �������� ���.������� �������� ��������� (� ������ �����)
	glViewport(0, 0, w, h);      // ������� ����, � ������� ������������ ��� ������
	gluPerspective(90.0, ratio, 1.0, 256.0); // ������������� �������������� (��� ������������ 3� �������)
												//3-���������� �� ������ ������������� �� ��������� ����� ���������
												//4- ���������� �� ������ ����� �� ������ ��������� ���������
	glMatrixMode(GL_MODELVIEW);  // ������� �������� ������. ������ ��� ��������� �������� �������� �����
}

void getting_time(void) {
	time(&local_time);						// �������� ������� ����������� ����� � �������� (�������� ����� �������� ��� ��������)
	curr_time = localtime(&local_time);		// �������������� �����. ������������ ������� � ��������� 

	/* ������������ ����������� ���� ��� ������� ����� */
	if (curr_time->tm_sec != old_sec) {		// ���� ����� ����������
		old_sec = curr_time->tm_sec;	    // ������ ����� = ������
		arrow_angle[0] = 90 + curr_time->tm_sec * 6; // ����� �������� �������� �������
		arrow_angle[1] = 90 + curr_time->tm_min * 6 + curr_time->tm_sec / 10;  // ��������
		arrow_angle[2] = 90 + curr_time->tm_hour * 30 + curr_time->tm_min / 2; // �������
		renderScene(); // ������� ��� �����������
	}
}

/* ��������� ������� ������ */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x': // ���������
	{
		eyepos[2] += 2; break;
		light1[2] += 0.01f; break;
	} break;
	case 'z': // �����������
	{
		eyepos[2] -= 2; break;
		light1[2] -= 0.01f; break;
	} break;
	case 't': // ����� ���� �� �����
		if (num == num1) {
			num = num2;
		}
		else {
			num = num1;
		} break;
	case 'a': angleL += 5.0; // ������� �����
		break;
	case 'd': angleR += 5.1; // ������
		break;
	case 'w': angleU += 5.1; // �����
		break;
	case 's': angleD += 5.1; // ����
	}
	getting_time(); // ����� ��������� �����
}

/* ������������� ����� ��������� � ��������� */
void init() {
	GLfloat light_position[] = { 50, 50, 50.0, 0.0 };    // ��������� �����
	GLfloat mat_specular[] = { 0.8f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   // �������� ����� �������� ����
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // ������� ����������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);   // ������������� ��������� ��������� �����

	glEnable(GL_DEPTH_TEST);    // ����� ������� ���
	glViewport(0, 0, 600, 600); // glViewport � ��������� �������� ������
	glShadeModel(GL_SMOOTH);    // �����������
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);									  // ������������� glut (1-����� ����������, 2-�� ��������)
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// ���������� ����� �����������
															  // 1-����� �������, 2-����� ������� �����������(�������� ��� ��������)
															  // 3-�������� �������� ����
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);                         // (������ ��������� ����) ������������� ���� ���������� (�-����� ���� �� ����� ����� ������, �-�� �������
	glutCreateWindow("3D CLOCK (Dasha & Denis)");             // ������� ���� � ������
	init();													  // ������������� ���������
	glutReshapeFunc(ChangeSize);							  // �������� �� ��������� ����
	glutKeyboardFunc(keyboard);								  // ��������� ������
	glutDisplayFunc(renderScene);							  // ���������� ������� ������ ��� ��� ����������� ����
	glutIdleFunc(getting_time);							      // �������� �� ��������
	glutMainLoop();										      // ���� � ������� ����
	return 0;
}