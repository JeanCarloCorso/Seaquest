#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

#define BUF_SIZE 255

#define PI 3.14159265358979323846  
#define janela_altura 600
#define janela_largura 1000


float corRGsub = 1;
float corBsub = 0;
float corRGsub2 = 0;
float corBsub2 = 0.56;

float InimigoCorRGsub = 0.82;
float InimigoCorBsub = 0.82;
float InimigoCorRGsub2 = 0;
float InimigoCorBsub2 = 0.56;


int tubaroesesquerda[100];
int mergulhadoresesquerda[100];
int submarinosadversarioesquerda[100];

int tubaroes[100];
int mergulhadores[100];
int submarinosadversario[100];
float mergul_salv = 0;

int ramdom = 0;
float andarX = -560;
float andarXesquerda = 530;
BOOLEAN fim = false;
int pontos = 0;
char placar[30];
float oxigenio = 150;
BOOLEAN perdeu = false;
int tentativas = 3;
int direcaotiro = 1;
BOOLEAN disparado = false;
BOOLEAN disparo = false;
BOOLEAN comeco = false;
BOOLEAN passo = false;
float tiroX = 0;
float tiroY = 0;
int direcao = 1;
float velocidade = 7;
float submarioY = 69;
float submarinoX = 0;
BOOLEAN barco = false;
float andardebarco = 450;

//void animaPas(int valor){
//	if (InimigoCorRGsub == 0)
//	{
//		InimigoCorRGsub = 0.82;
//		InimigoCorBsub = 0.82;
//		InimigoCorRGsub2 = 0;
//		InimigoCorBsub2 = 0.56;
//	}
//	else
//	{
//		InimigoCorRGsub = 0;
//		InimigoCorBsub = 0.56;
//		InimigoCorRGsub2 = 0.82;
//		InimigoCorBsub2 = 0;
//	}
//
//	glutPostRedisplay();
//	glutTimerFunc(1, animaPas, 1);
//}
void SubInimigo(int submarinoX, int submarioY, int direcaoSub);
void submarino(int submarinoX, int submarioY, int direcaoSub);
void detonado();
void vidas(float submarinoX, float submarioY);
void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anima(int valor);
const int font = (int)GLUT_BITMAP_TIMES_ROMAN_24;

void barquinho(float x, float y){
	glPushMatrix();
	glTranslated(x, y, 0);
	glBegin(GL_POLYGON);
	glColor3f(0.3, 1, 0);
	glVertex2f(0, 110);
	glVertex2f(45, 110);
	glVertex2f(45, 125);
	glVertex2f(40, 120);
	glVertex2f(20, 120);
	glVertex2f(15, 125);
	glVertex2f(10, 120);
	glVertex2f(0, 120);
	glVertex2f(-5, 115);
	glEnd();
	glPopMatrix();
}

void tubarao(float x, float y){
	glPushMatrix();
	glTranslated(x + 35, y + 110, 0);
	glColor3f(0, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2f(50, 10);
	glVertex2f(50, -10);
	glVertex2f(-50, -10);
	glVertex2f(-50, 10);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(50, -5);
	glVertex2f(25, -5);
	glVertex2f(50, 0);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(6.0);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0.5);
	glVertex2i(25, 4);
	glEnd();

	glColor3f(0, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2f(-50, 10);
	glVertex2f(-70, 20);
	glVertex2f(-70, 10);
	glVertex2f(-50, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-50, -10);
	glVertex2f(-70, -20);
	glVertex2f(-70, -10);
	glVertex2f(-50, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-10, 10);
	glVertex2f(-10, 25);
	glVertex2f(10, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-10, -10);
	glVertex2f(-10, -25);
	glVertex2f(10, -10);
	glEnd();
	glPopMatrix();
}

void mergulhador(float x, float y, float R, float B){
	//cabeça 
	glPushMatrix();
	glTranslated(x, y, 1);
	glPointSize(10.0);
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(R, 0, B);
	glVertex2i(0, 100);
	glEnd();

	//tronco 
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3f(R, 0, B);
	glVertex2f(0, 100);
	glVertex2f(35, 90);
	glVertex2f(15, 106);
	glVertex2f(-5, 90);
	glVertex2f(15, 106);
	glVertex2f(20, 96);
	glVertex2f(25, 90);
	glVertex2f(35, 80);
	glEnd();
	glPopMatrix();
}

void inicializa(){
	int contador = 0;
	BOOLEAN divide = false;
	for (int i = -50; i <= 0; i++){
		tubaroesesquerda[i] = rand() % 5;
		submarinosadversarioesquerda[i] = rand() % 5;
		if (divide){
			submarinosadversarioesquerda[i] = 50;
			divide = false;
		}
		else
		{
			tubaroesesquerda[i] = 50;
			divide = true;
		}
		if (contador >= 0 && contador <= 10)
		{
			tubaroesesquerda[i] = 50;
			submarinosadversarioesquerda[i] = 50;
			//printf("Contador: %d --> ", contador);
		}
		else if (contador >= 20)
		{
			contador = 0;
		}
		contador++;
	}
	contador = 0;
	for (int i = 0; i<100; i++){
		mergulhadores[i] = rand() % 4;
		submarinosadversario[i] = rand() % 5;

		if (contador > 8 && contador < 20)
		{
			mergulhadores[i] = 50;
			submarinosadversario[i] = 50;
		}
		else if (contador >= 20)
		{
			contador = 0;
		}
		if (mergulhadores[i] == submarinosadversario[i+2]){
			mergulhadores[i] = 50;
		}
		printf("[%d]: %d\n", i, submarinosadversario[i]);
		contador++;
	}
	mergulhadores[0] = 0;
}


void renderBitmapString(float x, float y, void *font, const char *string){
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela

	glutInitWindowPosition(60, 60); // posicao inicial da janela

	glutCreateWindow("Animação Casa");   /// cria a janela

	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(150, anima, 1);

	if (ramdom == 0){
		inicializa();
		ramdom = 1;
	}

	glutMainLoop(); //redesenhar
	return(0);
}

void anima(int valor){
	valor++;
	if (valor >= 20000)
	{
		barco = true;
		printf("\n\n\n\n\AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\n\n\n");
		valor = 0;
	}

	if (barco){
		andardebarco -= 0.3;
		printf("\nandardebarco = %f\n",andardebarco);
		if (andardebarco <= -350){
			andardebarco = 450;
			barco = false;
		}
	}

	if (andarX <= 13000)
	{
		andarX += 0.3;
	}
	else
	{
		andarX = 530;
	}


	if (andarXesquerda >= -15000)
	{
		andarXesquerda -= 0.3;
	}
	else
	{
		andarXesquerda = +530;
	}
	//fim = false;
	if (tentativas <= 0){
		fim = true;
	}

	if (perdeu)
	{
		perdeu = false;
		tentativas--;
		comeco = false;
		Sleep(500);
		submarinoX = 0;
		submarioY = 69;
		oxigenio = 150;
	}

	if (disparo){
		if (disparado && direcaotiro == 1){
			tiroX -= 1;
		}
		else if (disparado == true && direcaotiro == 2){
			tiroX += 1;
		}
		if (tiroX >= 425 || tiroX <= -425)
		{
			disparado = false;
			disparo = false;
			direcaotiro = 0;
		}
	}
	else
	{
		tiroX = submarinoX;
		tiroY = submarioY;
	}

	if (oxigenio > -150 && submarioY != 69)
	{
		oxigenio -= 0.008;
		if (oxigenio <= -150)
		{
			perdeu = true;
		}
	}
	else if (submarioY == 69 && passo == false)
	{
		if (oxigenio < 150)
		{
			oxigenio += 0.3;
		}
		else
		{
			oxigenio = 150;
		}
	}

	if (mergul_salv < 7 && submarioY == 69 && comeco){
		if (mergul_salv > 0)
		{
			mergul_salv--;
			comeco = false;
		}
		else
		{
			perdeu = true;
			comeco = false;
		}
	}
	
	if (mergul_salv == 7 && submarioY == 69 && comeco){
		passo = true;
	}

	glutPostRedisplay();
	glutTimerFunc(1, anima, valor);
}

void keyboard(unsigned char key, int x, int y)
{
	BOOLEAN pas = false;
	if (perdeu == false)
	{
		if (fim)
		{
			goto ignora;
		}
		switch (key)
		{
		case 'X':
			exit(EXIT_SUCCESS);
			break;
		case 'w':
			submarioY += velocidade;
			if (submarioY >= 69)
			{
				submarioY = 69;
			}
			pas = true;
			break;
		case 's':
			submarioY -= velocidade;
			comeco = true;
			if (submarioY <= -225)
			{
				submarioY = -225;
			}
			pas = true;
			break;
		case 'a':
			direcao = 1;
			submarinoX -= velocidade;
			if (submarinoX <= -379)
			{
				submarinoX = -379;
			}
			pas = true;
			break;
		case 'q':
			direcao = 1;
			submarinoX -= velocidade;
			submarioY += velocidade;
			pas = true;
			if (submarinoX <= -379)
			{
				submarinoX = -379;
			}
			if (submarioY >= 69)
			{
				submarioY = 69;
			}
			break;
		case 'e':
			direcao = 2;
			submarinoX += velocidade;
			submarioY += velocidade;
			pas = true;
			if (submarinoX >= 345)
			{
				submarinoX = 345;
			}
			if (submarioY >= 69)
			{
				submarioY = 69;
			}
			break;
		case 'z':
			direcao = 1;
			submarinoX -= velocidade;
			submarioY -= velocidade;
			pas = true;
			if (submarinoX <= -379)
			{
				submarinoX = -379;
			}
			if (submarioY <= -225)
			{
				submarioY = -225;
			}
			break;
		case 'x':
			direcao = 2;
			submarinoX += velocidade;
			submarioY -= velocidade;
			pas = true;
			if (submarinoX >= 345)
			{
				submarinoX = 345;
			}
			if (submarioY <= -225)
			{
				submarioY = -225;
			}
			break;
		case 'd':
			direcao = 2;
			submarinoX += velocidade;
			if (submarinoX >= 345)
			{
				submarinoX = 345;
			}
			pas = true;
			break;
		case ' ':
			disparo = true;
			if (disparado == false)
			{
				direcaotiro = direcao;
			}
			disparado = true;
			break;
		case 'F':
			if (perdeu){
				perdeu = false;
			}
			else{
				perdeu = true;
			}
		}
	}

	if (pas)
	{
		if (corRGsub == 0)
		{
			corRGsub = 1;
			corBsub = 0;
			corRGsub2 = 0;
			corBsub2 = 0.56;
		}
		else
		{
			corRGsub = 0;
			corBsub = 0.56;
			corRGsub2 = 1;
			corBsub2 = 0;
		}
	}
	else
	{
		corRGsub = 1;
		corBsub = 0;
		corRGsub2 = 0;
		corBsub2 = 0.56;
	}
	printf("\nSubmarinoY: %f", submarioY);
	printf("\nSubmarinoX: %f", submarinoX);
ignora:;
}

void desenhar()
{
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef((janela_largura) / 2, (janela_altura) / 2, 0);

	for (int i = 0; i < 30; i++)
	{
		glPushMatrix();
	}

	//cenario
	glColor3f(0.0f, 0.0f, 0.56f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, 260);
	glVertex2d(430, 260);
	glVertex2d(430, -260);
	glVertex2d(-430, -260);
	glEnd();
	glPopMatrix();

	//superficie do oceano cel
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, 260);
	glVertex2d(430, 260);
	glVertex2d(430, 200);
	glVertex2d(-430, 200);
	glEnd();
	glPopMatrix();

	//superficie do oceano orizonte
	glColor3f(0.54f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, 200);
	glVertex2d(430, 200);
	glVertex2d(430, 196);
	glVertex2d(-430, 196);
	glEnd();
	glPopMatrix();
	//superficie do oceano orizonte
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, 203);
	glVertex2d(430, 203);
	glVertex2d(430, 200);
	glVertex2d(-430, 200);
	glEnd();
	glPopMatrix();
	//superficie do oceano orizonte
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(-430, 203);
	glVertex2d(430, 203);
	glEnd();

	for (int i = 0; i < 30; i += 5)
	{
		//superficie do oceano agua
		glColor3f(0.1f, 0.1f, 0.75f);
		glLineWidth(4);
		glBegin(GL_LINES);
		glVertex2d(-430, 191 - i);
		glVertex2d(430, 191 - i);
		glEnd();
	}

	//fundo do mar
	glColor3f(0.0f, 0.399f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, -130);
	glVertex2d(430, -130);
	glVertex2d(430, -260);
	glVertex2d(-430, -260);
	glEnd();
	glPopMatrix();
	int i = -490;
	for (int b = 0; b < 13; b++)
	{
		i += 70;
		//suavização do fundo do mar
		glPushMatrix();
		glTranslated(i, 15, 0);
		glColor3f(0.663f, 0.663f, 0.663f);
		glBegin(GL_POLYGON);
		glVertex2d(30, -170);
		glVertex2d(0, -170);
		glVertex2d(0, -175);
		glVertex2d(30, -175);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//suavização do fundo do mar
		glTranslated(i, 15, 0);
		glColor3f(0.663f, 0.663f, 0.663f);
		glBegin(GL_POLYGON);
		glVertex2d(35, -175);
		glVertex2d(-5, -175);
		glVertex2d(-5, -180);
		glVertex2d(35, -180);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//suavização do fundo do mar
		glTranslated(i, 15, 0);
		glColor3f(0.663f, 0.663f, 0.663f);
		glBegin(GL_POLYGON);
		glVertex2d(40, -180);
		glVertex2d(-10, -180);
		glVertex2d(-10, -185);
		glVertex2d(40, -185);
		glEnd();
		glPopMatrix();

	}

	//ajuste da suavização
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(470, -130);
	glVertex2d(430, -130);
	glVertex2d(430, -260);
	glVertex2d(470, -260);
	glEnd();
	glPopMatrix();

	//abaicho do fundo do mar
	glColor3f(0.663f, 0.663f, 0.663f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, -170);
	glVertex2d(430, -170);
	glVertex2d(430, -260);
	glVertex2d(-430, -260);
	glEnd();

	//indicador mergulhadores resgatados
	int cont = 0;
	for (int i = 1; i <= mergul_salv; i++)
	{
		if (mergul_salv < 7)
		{
			mergulhador(-410 + cont, -335, 0, 0.97);
			cont += 50;
		}
		else
		{
			mergulhador(-410 + cont, -335, 1, 0);
			cont += 50;
		}
		
	}
	//conta pontos passo de fase
	if (oxigenio > -150 && passo)
	{
		Sleep(100);
		oxigenio -= 10;
		pontos += 10;
		if (oxigenio < -150)
		{
			oxigenio = -150;
		}
	}
	if (passo && mergul_salv > 0 && oxigenio <= -150){
		mergul_salv--;
		pontos += 100;
		Sleep(500);
	}
	else if (mergul_salv == 0)
	{
		passo = false;
	}

	//barra oxigenio vazia
	glLineWidth(2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2d(-150, -200);
	glVertex2d(150, -200);
	glVertex2d(150, -214);
	glVertex2d(-150, -214);
	glEnd();

	//barra oxigenio cheia
	glLineWidth(2);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2d(-150, -200);
	glVertex2d(oxigenio, -200);
	glVertex2d(oxigenio, -214);
	glVertex2d(-150, -214);
	glEnd();

	int t = 130;
	for (int i = 0; i < tentativas; i++)
	{
		vidas(-500 + t, 118);
		t += 130;
	}

	/*vidas(-370, 118);
	vidas(-240, 118);
	vidas(-110, 118);*/

	glColor3f(0.0f, 0.0f, 0.0f);
	renderBitmapString(-250, -210, (void *)font, "OXIGEN");
	sprintf(placar, "%2d", pontos);
	renderBitmapString(-20, 230, (void *)font, placar);

	if (fim){
		renderBitmapString(-20, 0, (void *)font, "GAME OVER");
	}

	//inimigos vem da direita
	for (int j = 0; j < 100; j++)
	{
		SubInimigo(j * 300 - andarX, submarinosadversario[j] * -50, 1);
		//batida submarino
		if (submarinosadversario[j] * -50 + 40 >= submarioY  && submarinosadversario[j] * -50 - 40 <= submarioY &&
			(j * 300 - andarX) >= submarinoX - 125 && j * 300 - andarX <= submarinoX + 100)
		{
			InimigoCorBsub2 = 0;
			perdeu = true;
			detonado();
			submarinosadversario[j] = 50;
		}
		else
		{
			InimigoCorBsub2 = 0.56;
		}
		//bala de prata
		if (submarinosadversario[j] * -50 + 40 >= tiroY  && submarinosadversario[j] * -50 - 40 <= tiroY &&
			(j * 300 - andarX) >= tiroX - 125 && j * 300 - andarX <= tiroX + 100)
		{
			InimigoCorBsub2 = 0;
			disparado = false;
			disparo = false;
			direcaotiro = 0;
			submarinosadversario[j] = 50;
			pontos += 20;
		}
		else
		{
			InimigoCorBsub2 = 0.56;
		}

	}

	//inimigos vem da esquerda
	for (int j = -50; j <= 0; j++)
	{
		SubInimigo(j * 300 - andarXesquerda, submarinosadversarioesquerda[j] * -50, 2);
		//batida submarino
		if (submarinosadversarioesquerda[j] * -50 + 40 >= submarioY  && submarinosadversarioesquerda[j] * -50 - 40 <= submarioY &&
			(j * 300 - andarXesquerda) >= submarinoX - 125 && j * 300 - andarXesquerda <= submarinoX + 100)
		{
			InimigoCorBsub2 = 0;
			perdeu = true;
			detonado();
			submarinosadversarioesquerda[j] = 50;
		}
		else
		{
			InimigoCorBsub2 = 0.56;
		}
		//bala de prata
		if (submarinosadversarioesquerda[j] * -50 + 40 >= tiroY  && submarinosadversarioesquerda[j] * -50 - 40 <= tiroY &&
			(j * 300 - andarXesquerda) >= tiroX - 125 && j * 300 - andarXesquerda <= tiroX + 100)
		{
			InimigoCorBsub2 = 0;
			disparado = false;
			disparo = false;
			direcaotiro = 0;
			submarinosadversarioesquerda[j] = 50;
			pontos += 20;
		}

	}


	//inimigos tubarão vem da esquerda
	for (int j = -50; j <= 0; j++)
	{
		tubarao(j * 300 - andarXesquerda, tubaroesesquerda[j] * -50);
		//batida submarino com tubarão (pense num tubarão que detona submarinos)
		if (tubaroesesquerda[j] * -50 + 40 >= submarioY  && tubaroesesquerda[j] * -50 - 40 <= submarioY &&
			(j * 300 - andarXesquerda) >= submarinoX - 125 && j * 300 - andarXesquerda <= submarinoX + 100)
		{
			InimigoCorBsub2 = 0;
			perdeu = true;
			detonado();
			tubaroesesquerda[j] = 50;
		}
		//bala de prata
		if (tubaroesesquerda[j] * -50 + 40 >= tiroY  && tubaroesesquerda[j] * -50 - 40 <= tiroY &&
			(j * 300 - andarXesquerda) >= tiroX - 125 && j * 300 - andarXesquerda <= tiroX + 100)
		{
			InimigoCorBsub2 = 0;
			disparado = false;
			disparo = false;
			direcaotiro = 0;
			tubaroesesquerda[j] = 50;
			pontos += 20;
		}

	}
	

	//mergulhadores vem da direita
	for (int j = 0; j < 50; j++)
	{
		mergulhador(j * 600 - andarX, mergulhadores[j] * -50, 0, 0.97);
		//resgate mergulhador
		if (mergulhadores[j] * -50 + 40 >= submarioY  && mergulhadores[j] * -50 - 40 <= submarioY &&
			(j * 600 - andarX) >= submarinoX - 125 && j * 600 - andarX <= submarinoX + 70)
		{
			if (mergul_salv < 7){
				mergul_salv++;
			}
			mergulhadores[j] = 50;
		}
	}

	if (perdeu == false)
	{

		//tiro
		glTranslated(tiroX, tiroY, 1);
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(4);
		glBegin(GL_LINES);
		glVertex2d(-30, 110);
		glVertex2d(0, 110);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		submarino(submarinoX, submarioY, direcao);
	}
	else
	{
		detonado();
	}

	//barco filho da fruta
	barquinho(andardebarco, 60);
	if (andardebarco + 70 >= submarinoX && andardebarco - 80 < submarinoX && submarioY >= 30)
	{
		perdeu = true;
		andardebarco = 450;
		barco = false;
		detonado();
	}

	//fim do cenario
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-530, 260);
	glVertex2d(-430, 260);
	glVertex2d(-430, -260);
	glVertex2d(-530, -260);
	glEnd();
	glPopMatrix();

	//fim do cenario
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(430, 260);
	glVertex2d(530, 260);
	glVertex2d(530, -260);
	glVertex2d(430, -260);
	glEnd();
	glPopMatrix();

	glutSwapBuffers(); // executa o desenho
}

void display(){
	glMatrixMode(GL_MODELVIEW); //COORDENADAS DO DESENHO
	glLoadIdentity();
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush();
}

void tela(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}

void submarino(int submarinoX, int submarioY, int direcaoSub){

	if (direcaoSub == 1){
		//Submarino do jogador andando para a esquerda
		//retangulo principal
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 115);
		glVertex2d(65, 115);
		glVertex2d(65, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//escotilha
		glColor3f(0.0f, 0.399f, 0.0f);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-30, 110);
		glVertex2d(0, 110);
		glVertex2d(0, 105);
		glVertex2d(-30, 105);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo superior
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 120);
		glVertex2d(55, 120);
		glVertex2d(55, 115);
		glVertex2d(-35, 115);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo inferior
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-10, 100);
		glVertex2d(85, 100);
		glVertex2d(85, 95);
		glVertex2d(-10, 95);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo entrada
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-10, 135);
		glVertex2d(15, 135);
		glVertex2d(15, 120);
		glVertex2d(-10, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//pas do submarino
		glColor3f(corRGsub, corRGsub, corBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 130);
		glVertex2d(85, 130);
		glVertex2d(85, 120);
		glVertex2d(65, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(corRGsub2, corRGsub2, corBsub2);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 120);
		glVertex2d(85, 120);
		glVertex2d(85, 110);
		glVertex2d(65, 110);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(corRGsub, corRGsub, corBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 110);
		glVertex2d(85, 110);
		glVertex2d(85, 100);
		glVertex2d(65, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
	}
	else if (direcaoSub == 2){
		//Submarino do jogador andando para a esquerda
		//retangulo principal
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 115);
		glVertex2d(65, 115);
		glVertex2d(65, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//escotilha
		glColor3f(0.0f, 0.399f, 0.0f);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(30, 110);
		glVertex2d(60, 110);
		glVertex2d(60, 105);
		glVertex2d(30, 105);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo superior
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 120);
		glVertex2d(-25, 120);
		glVertex2d(-25, 115);
		glVertex2d(65, 115);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo inferior
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(45, 100);
		glVertex2d(-55, 100);
		glVertex2d(-55, 95);
		glVertex2d(45, 95);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo entrada
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(45, 135);
		glVertex2d(25, 135);
		glVertex2d(25, 120);
		glVertex2d(45, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//pas do submarino
		glColor3f(corRGsub, corRGsub, corBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 130);
		glVertex2d(-55, 130);
		glVertex2d(-55, 120);
		glVertex2d(-35, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(corRGsub2, corRGsub2, corBsub2);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 120);
		glVertex2d(-55, 120);
		glVertex2d(-55, 110);
		glVertex2d(-35, 110);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(corRGsub, corRGsub, corBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 110);
		glVertex2d(-55, 110);
		glVertex2d(-55, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
	}
}


void SubInimigo(int submarinoX, int submarioY, int direcaoSub){

	if (direcaoSub == 1){
		//Submarino do jogador andando para a esquerda
		//retangulo principal
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 115);
		glVertex2d(65, 115);
		glVertex2d(65, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//escotilha
		glColor3f(0.0f, 0.399f, 0.0f);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-30, 110);
		glVertex2d(0, 110);
		glVertex2d(0, 105);
		glVertex2d(-30, 105);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo superior
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 120);
		glVertex2d(55, 120);
		glVertex2d(55, 115);
		glVertex2d(-35, 115);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo inferior
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-10, 100);
		glVertex2d(85, 100);
		glVertex2d(85, 95);
		glVertex2d(-10, 95);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo entrada
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-10, 135);
		glVertex2d(15, 135);
		glVertex2d(15, 120);
		glVertex2d(-10, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//pas do submarino
		glColor3f(InimigoCorRGsub, InimigoCorRGsub, InimigoCorBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 130);
		glVertex2d(85, 130);
		glVertex2d(85, 120);
		glVertex2d(65, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(InimigoCorRGsub2, InimigoCorRGsub2, InimigoCorBsub2);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 120);
		glVertex2d(85, 120);
		glVertex2d(85, 110);
		glVertex2d(65, 110);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(InimigoCorRGsub, InimigoCorRGsub, InimigoCorBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 110);
		glVertex2d(85, 110);
		glVertex2d(85, 100);
		glVertex2d(65, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
	}
	else if (direcaoSub == 2){
		//Submarino do jogador andando para a esquerda
		//retangulo principal
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 115);
		glVertex2d(65, 115);
		glVertex2d(65, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//escotilha
		glColor3f(0.0f, 0.399f, 0.0f);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(30, 110);
		glVertex2d(60, 110);
		glVertex2d(60, 105);
		glVertex2d(30, 105);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo superior
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(65, 120);
		glVertex2d(-25, 120);
		glVertex2d(-25, 115);
		glVertex2d(65, 115);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo inferior
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(45, 100);
		glVertex2d(-55, 100);
		glVertex2d(-55, 95);
		glVertex2d(45, 95);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//retangulo entrada
		glColor3f(0.82, 0.82, 0.82);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(45, 135);
		glVertex2d(25, 135);
		glVertex2d(25, 120);
		glVertex2d(45, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		//pas do submarino
		glColor3f(InimigoCorRGsub, InimigoCorRGsub, InimigoCorBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 130);
		glVertex2d(-55, 130);
		glVertex2d(-55, 120);
		glVertex2d(-35, 120);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(InimigoCorRGsub2, InimigoCorRGsub2, InimigoCorBsub2);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 120);
		glVertex2d(-55, 120);
		glVertex2d(-55, 110);
		glVertex2d(-35, 110);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glColor3f(InimigoCorRGsub, InimigoCorRGsub, InimigoCorBsub);
		glPushMatrix();
		glTranslated(submarinoX, submarioY, 1);
		glBegin(GL_POLYGON);
		glVertex2d(-35, 110);
		glVertex2d(-55, 110);
		glVertex2d(-55, 100);
		glVertex2d(-35, 100);
		glEnd();
		glPopMatrix();
		glPushMatrix();
	}
}


void detonado(){
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glColor3f(0, 0, 1);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2i(0, 110);
	glVertex2i(20, 110);
	glVertex2i(-20, 110);
	glVertex2i(0, 130);
	glVertex2i(0, 90);

	glVertex2i(30, 135);
	glVertex2i(-30, 135);
	glVertex2i(30, 85);
	glVertex2i(-30, 85);
	glEnd();
	glPopMatrix();

}

void vidas(float submarinoX, float submarioY){
	//retangulo principal
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-35, 115);
	glVertex2d(65, 115);
	glVertex2d(65, 100);
	glVertex2d(-35, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//escotilha
	glColor3f(0.0f, 0.399f, 0.0f);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(30, 110);
	glVertex2d(60, 110);
	glVertex2d(60, 105);
	glVertex2d(30, 105);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//retangulo superior
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(65, 120);
	glVertex2d(-25, 120);
	glVertex2d(-25, 115);
	glVertex2d(65, 115);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//retangulo inferior
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(45, 100);
	glVertex2d(-55, 100);
	glVertex2d(-55, 95);
	glVertex2d(45, 95);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//retangulo entrada
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(45, 135);
	glVertex2d(25, 135);
	glVertex2d(25, 120);
	glVertex2d(45, 120);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//pas do submarino
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-35, 130);
	glVertex2d(-55, 130);
	glVertex2d(-55, 120);
	glVertex2d(-35, 120);
	glEnd();
	glPopMatrix();
	glPushMatrix();

	glColor3f(0, 0, 0.56);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-35, 120);
	glVertex2d(-55, 120);
	glVertex2d(-55, 110);
	glVertex2d(-35, 110);
	glEnd();
	glPopMatrix();
	glPushMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslated(submarinoX, submarioY, 1);
	glBegin(GL_POLYGON);
	glVertex2d(-35, 110);
	glVertex2d(-55, 110);
	glVertex2d(-55, 100);
	glVertex2d(-35, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
}
