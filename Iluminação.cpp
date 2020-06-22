#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 480
#define janela_largura 640
int on = 1;
int cobre = 0;
float x = 0.0f;
float y = 0.0f;
float z = 0.0f;

float ambiente[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float posicao[] = { 0.0f, 1.0f, 2.0f, 0.0f };

void conf_luz(float ambiente[4], float diffuse[4], float specular[4], float posicao[4]){
	
 	float lmodel_ambiente[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	float local_view[] = { 8.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void reshape(GLsizei largura, GLsizei altura) {

	if (altura == 0) altura = 1; // previne a divisão por zero
	GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;


	glViewport(0, 0, largura, altura);

	glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção
	glLoadIdentity(); // zerando a matriz
	gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia
	glEnable(GL_DEPTH_TEST); // alunos devem testar
	glShadeModel(GL_SMOOTH); // acabamento com suavização
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}

void cubo(float raio) {
	glPushMatrix();
		glTranslatef(1.5f, 0.0f, -6.0f); 
		glRotatef(30.0f, 0, 0, 1);
		glutSolidCube(raio);
	glPopMatrix();
}

void esfera(float raio, int f) {
	glPushMatrix();
		glTranslatef(-1.5f, 0.0f, -6.0f);
		glutSolidSphere(raio, f, f);
	glPopMatrix();
}

void display() {
	
	float padrao[] = { 0.0, 0.0, 0.0, 1.0 };
	float mat_ambiente[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	float mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float alto_brilho[] = { 25.0 };


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos
	glLoadIdentity();
	
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, alto_brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, padrao);

	
	esfera(1.0f, 60);
	cubo(1.5f);
	
	glutSwapBuffers(); // trocar a matriz da tela por esta aqui.
}

void keyboard(unsigned char key, int a, int b) {

	if (key == 'o') {
		if (on) {
			glDisable(GL_LIGHT0);
			on = 0;
		}
		else {
			glEnable(GL_LIGHT0);
			on = 1;
		}
	}
	else {

		float spec_nova[4] = { 0.74f, 0.76f, 0.78f, 1.0f };
		float dif_nova[4] = { 0.86f, 0.86f, 0.88f, 1.0f };

		if (key == 'x') {
			x += 10.0f;
		}
		else if(key == 'c') {

			if (cobre) {
				cobre = 0;
			}
			else {
				cobre = 1;
			}
		}

		if (cobre) {
			spec_nova[0], dif_nova[0] = 0.94f;
			spec_nova[1], dif_nova[1] = 0.57f;
			spec_nova[2], dif_nova[2] = 0.16f;
			spec_nova[3], dif_nova[3] = 1.0f;
		}

		float pos_nova[4] = { 1.5f + sin(x * 2.0f * 3.14f / 360.0f), 1.0f, 2.0f + sin(x * 2.0f * 3.14f / 360.0f),  0.0f };

		conf_luz(ambiente, dif_nova, spec_nova, pos_nova);	
	}

	glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc, argv); // Ligar GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("iluminacao"); // Criar Janela

	conf_luz(ambiente, diffuse, specular, posicao);

	glutDisplayFunc(display); // imagem
	glutReshapeFunc(reshape); // config telas
	glutKeyboardFunc(keyboard); // funcoes de teclado
	glutMainLoop(); // loop
	return 0;
}
