#include<stdio.h>
#include<GL/glut.h>
#include<Windows.h>
#include<MMSystem.h>
#include<iostream>

GLint flag = 0;
//GLfloat red = 0.196078, green = 0.6, blue = 0.8 ;
GLfloat red = 0, blue = 0.8, green = .1;
GLint a1 = 300, a2 = 300, b1 = -500, b2 = -500, upX1=70,upY1 = -500, upX2 = -70, upY2 = -500;
//a1=passenger bus; b1=schoolbus; b2=car1; a2=car2; upX,upY=busup
GLint am=-300,downX = 865, downY = 1000, manX1 = 170,manY1 = 410, manX2 = 170, manY2 = 410; // for cardown
GLint initial_regulator = 1, amb = 0, traffic_number, control_key=0, control_keyr, traffic_regulator[4];
GLfloat p[4], q[4], r[4],m[4],n[4];
GLint light=0;//lights
GLfloat c1 = 1, c2 = 0, c3 = 0,t1=0.2,t2=0.0,t3=0.4,sx=2.0 , sy=6.0, s2=4.0;
void *currentfont;
void myinit();
void mydisplay();
void display();
void road();
//void tree();
void grass();
void man();
void trafficsignal1();
void trafficsignal2();
void trafficsignal3();
void trafficsignal4();
void passengerbus();
void schoolbus();
void car1();
void car2();
void busup();
void busup1();
void cardown();
void cardown1();
void ambulance();
void update(int);
void myKeyboard(unsigned char key, int x, int y);
void myMouse(int button, int state, int x, int y);
void menu(int id);
void redraw();
void setFont(void * font);
void drawstring(float x, float y, float z, char * string);
//void display0(void);
void mainscreen(void);
void controlscreen();
void control();




void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1400, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TRAFFIC INTERSECTION CONTROL SYSTEM");

	/*call back functions*/
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	
	PlaySound("song.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		

	glutCreateMenu(menu);
	glutAddMenuEntry("Main Screen", 1);
	glutAddMenuEntry("Control Screen", 2);
	glutAddMenuEntry("Pause", 3);
	glutAddMenuEntry("Play", 4);
	glutAddMenuEntry("Restart", 5);
	glutAddMenuEntry("Quit", 6);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	menu(GLUT_LEFT_BUTTON);
	myinit();
	glutTimerFunc(50, update, 0); 
	glutMainLoop();
}

void myinit()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1400.0, 0.0, 700.0);
}

void mydisplay(void)  //display function
{
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (flag == 0)
			mainscreen();
		if (flag == 1)
			controlscreen();
		if (flag == 2)  //flag==2
			display();
	
		glutSwapBuffers();
	}
}

void display(void)  //main simulation
{
	if (initial_regulator);
		glutTimerFunc(50, update, 0);
		glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 0);/*back ground for sky*/
//	glClear(GL_COLOR_BUFFER_BIT);

	grass();
	road();
	
	glPushMatrix();
	glTranslated(manX1, manY1, 0); //manX=170manY = 410;
	man();
	glPopMatrix();

	glPushMatrix();
	glTranslated(manX2+550, manY2, 0); //manX=170manY = 410;
	man();
	glPopMatrix();
	ambulance();
	cardown();
	cardown1();
	trafficsignal1();
	trafficsignal2();
	ambulance(); 
	car1();
	schoolbus();
	 
	car2();
	passengerbus();

	trafficsignal3();
	trafficsignal4();
	busup();
	busup1();

	glFlush();
}



void update(int value)
{
	if(amb==1)
{
	am = am + 9;
	for (int i = 1; i <= 4; i++)
	{
		p[i] = 1; q[i] = 0; r[i] = 0; //red
		m[i] = 1; n[i] = 0;
	}
	if (am > 1400)
	{
		amb = 0;
		control_key = 3;
		traffic_regulator[traffic_number] = 0;
	}
}
	if (control_key == 1)
	{
		a1 = a1 - s2;
		a2 = a2 - s2;
		b1 = b1 + s2;
		b2 = b2 + s2;
	}
	
	if (control_key == 2)
	{
		upX1 = upX1 + sx;//down to up
		upY1 = upY1 + sy;
		upX2 = upX2 + sx;//down to up
		upY2 = upY2 + sy;
		downX = downX - sx; //up to down
		downY = downY - sy;

	}
	

	a1 = a1 - s2; //right to left
	a2 = a2 - s2;
	b1 = b1 + s2; //left to right
	b2 = b2 + s2;
	upX1 = upX1 + sx;//down to up
	upY1 = upY1 + sy; 
	upX2 = upX2 + sx;//down to up
	upY2 = upY2 + sy;
	downX = downX - sx; //up to down
	downY = downY - sy;
	control();
	
	/*making day to night*/
	if (blue != 0 && green != 0)
	{
		blue -= .004; green -= .004;
	}

	
	glutPostRedisplay();
}

void control()
{	
	if (traffic_regulator[traffic_number] == 2) //stop when z pressed
	{
		for (int i = 1; i <= 4; i++)
		{

			m[i] = 1; //red line
			n[i] = 0;
		}
		a1 = a1 + s2;
		a2 = a2 + s2;
		b1 = b1 - s2;
		b2 = b2 - s2;
		upX1 = upX1 - sx;//down to up
		upY1 = upY1 - sy;
		upX2 = upX2 - sx;//down to up
		upY2 = upY2 - sy;
		downX = downX + sx; //up to down
		downY = downY + sy;

	}
	if (traffic_regulator[traffic_number] == 0) //start x pressed
	{
		a1 = a1 - s2;
		a2 = a2 - s2;
		b1 = b1 + s2;
		b2 = b2 + s2;
		upX1 = upX1 + sx;//down to up
		upY1 = upY1 + sy;
		upX2 = upX2 + sx;//down to up
		upY2 = upY2 + sy;
		downX = downX - sx; //up to down
		downY = downY -sy;

	}
	if(control_key==1) //for key L
	{
		p[1] = 0; q[1] = 0; r[1] = 1;//green
		p[3] = 0; q[3] = 0; r[3] = 1;
		p[2] = 1; q[2] = 0; r[2] = 0; //red
		p[4] = 1; q[4] = 0; r[4] = 0;
		m[1] = 0; n[1] = 1; //green
		m[3] = 0; n[3] = 1;
	}
	if (control_key == 2)  //for key k
	{
		p[2] = 0; q[2] = 0; r[2] = 1;//green
		p[4] = 0; q[4] = 0; r[4] = 1;

		p[1] = 1; q[1] = 0; r[1] = 0; //red
		p[3] = 1; q[3] = 0; r[3] = 0;
		m[2] = 0; n[2] = 1;//green
		m[4] = 0; n[4] = 1;
		//light = 0;
	}
	if (control_key == 3)//everything green on q
	{
		for (int i = 1; i <= 4; i ++)
		{
			p[i] = 0; q[i] = 0; r[i] = 1;
			m[i] = 0; n[i] = 1;
		}
	}
	if (control_key == 4) //everything red on w
	{
		for (int i = 1; i <= 4; i++)
		{
			p[i] = 1; q[i] = 0; r[i] = 0; //red
			m[i] = 1; n[i] = 0;
		}
	}

	if (amb == 1) //when ambulance enters evrything red
	{
		for (int i = 1; i <= 4; i++)
		{
			p[i] = 1; q[i] = 0; r[i] = 0; //red
			m[i] = 1; n[i] = 0;
		}
	}

	switch (traffic_number) //one way traffic control
	{
	case 1:
		if (traffic_regulator[1] == 1) //Allow left to right
		{
			a1 = a1 + s2;
			a2 = a2 + s2;
			upX1 = upX1 -sx;//down to up
			upY1 = upY1 - sy;
			upX2 = upX2 - sx;//down to up
			upY2 = upY2 - sy;
			downX = downX + sx; //up to down
			downY = downY + sy;
		}
		break;

	case 2:
		if (traffic_regulator[2] == 1) //Allow top to down
		{
			a1 = a1 + s2;
			a2 = a2 + s2;
			b1 = b1 - s2;
			b2 = b2 - s2;
			upX1 = upX1 - sx;//down to up
			upY1 = upY1 - sy;
			upX2 = upX2 - sx;//down to up
			upY2 = upY2 - sy;

		}
		break;

	case 3:
		if (traffic_regulator[3] == 1) //Allow left to right
		{
			b1 = b1 - s2;
			b2 = b2 - s2;
			upX1 = upX1 - sx;//down to up
			upY1 = upY1 - sy;
			upX2 = upX2 - sx;//down to up
			upY2 = upY2 - sy;
			downX = downX + sx; //up to down
			downY = downY + sy;
		}
		break;
	case 4:
		if (traffic_regulator[4] == 1) //Allow dont to up
		{
			b1 = b1 - s2;
			b2 = b2 - s2;
			a1 = a1 + s2;
			a2 = a2 + s2;
			downX = downX + sx; //up to down
			downY = downY + sy;
			
			m[4] = 0;
			n[4] = 1;
		}
		break;

default:break;
	} 
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 13:
		
		if (flag == 1) //Ascii of 'enter' key is 13
		{
			flag = 2; 
			mydisplay();
		}
		if (flag == 0) //Ascii of 'enter' key is 13
		{
			flag = 1;
			mydisplay();
		}

		break;
	case 'l':control_key = 1;
		traffic_regulator[traffic_number] = 2; //only horizontal vehicles
		
		
		break;
	case 'k':control_key = 2;
		traffic_regulator[traffic_number] = 2; //only vertical vehicles
	case 's':
		s2 += s2;
		break;
	case 'd':
		s2 = s2-1;
		break;
	case 'h':
		flag = 1; 
		mydisplay();
		break;
	case 'o':
		light = 1;
		break;
	case 'f':
		light = 0;
		break;
	case 'z':control_key = 4; //zebra crossing
		traffic_regulator[traffic_number] = 2; //stop vehicles
		p[traffic_number] = 1;
		q[traffic_number] = 0;
		r[traffic_number] = 0;
		
		manX1 = manX1 - 1;
		manY1 = manY1 - 3;
		manX2 = manX2 + 1;
		manY2 = manY2 - 3;
		break;
	case 'x': //start vehicles
		control_key = 3;
		traffic_regulator[traffic_number] = 0;
		amb = 0;
		break;
	case 'a':
		traffic_regulator[traffic_number] = 2; //stop vehicles
		amb = 1;		
		break;

	case '1':
		c1 = 0.0;
		c2 = 1.0;
		c3 = 0.4;
		break;

	case '2':
		c1 = 1.0;
		c2 = 0.5;
		c3 = 0.0;
		break;
	case '3':
		c1 = 1;
		c2 = 1;
		c3 = 0;
		break;
	case '4':
		c1 = 0.0;
		c2 = 1;
		c3 = 0.5;
		break;
	case '5':
		c1 = 1.0;
		c2 = 0.0;
		c3 = 0.0;
		break;
	case '6':
		t1 = 0.3;
		t2 = 0.0;
		t3 = 0.1;
		break;
	case '7':
		t1 = 0.5;
		t2 = 0.5;
		t3 = 0.5;
		break;
	case '8':
		t1 = 0.2;
		t2 = 0.0;
		t3 = 0.4;
		break;

	case 27:
		exit(0);
		break;

	default:break;
	}

}


void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			//origin=left top corner
			if (x<600 && y<200) 
			traffic_number = 1; //left to right
			else if (x > 900 && y < 200)
			traffic_number = 2;	 //right to left
			else if (x > 850 && y > 450)
			traffic_number = 3;
			else if (x < 550 && y>450)
			traffic_number = 4;

			traffic_regulator[traffic_number] = 2; //yellow
			p[traffic_number] = 0;
			q[traffic_number] = 1;
			r[traffic_number] = 0;

	}

	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)  //green
	{

			traffic_regulator[traffic_number] = 1;
			p[traffic_number] = 0;
			q[traffic_number] = 0;
			r[traffic_number] = 1;

			m[traffic_number] = 0;//for line
			n[traffic_number] = 1;

			for (int i = 1; i <= 4; i++)
			{
				if (i == traffic_number)
					continue;
				p[i] = 1;
				q[i] = 0;
				r[i] = 0;
			
				m[i] = 1;
				n[i] = 0;

			}

	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)  //red
	{
		traffic_regulator[traffic_number] = 0;
		p[traffic_number] = 1;
		q[traffic_number] = 0;
		r[traffic_number] = 0;

		m[traffic_number] = 1;//for line
		n[traffic_number] = 0;

	}
	glutPostRedisplay();

}

void menu(int id)
{

	switch (id)
	{
	case 1:flag = 0;
		mydisplay();
		break;
	case 2:
		flag = 1;
		mydisplay();
		break;
	case 3:control_key = 4;
		traffic_regulator[traffic_number] = 2;
		break;
	case 4:	control_key = 3;
		traffic_regulator[traffic_number] = 0;
		amb = 0;
		break;
	case 5:redraw();
		break;
	case 6:exit(0);
		break;
	default: break;
	}
}

void redraw()
{
	flag = 0;
	red = 0; blue = 0.8; green = .1;
	a1 = 300; a2 = 300; b1 = -500; b2 = -500; upX1 = 70; upY1 = -500; upX2 = -70; upY2 = -500;
	am = -300; downX = 865; downY = 1000; manX1 = 170; manY1 = 410; manX2 = 170; manY2 = 410; // for cardown
	initial_regulator = 1; amb = 0; control_key = 0;

light = 0;
c1 = 1; c2 = 0; c3 = 0; t1 = 0.2; t2 = 0.0; t3 = 0.4; sx = 2.0; sy = 6.0; s2 = 4.0;
mydisplay();
}

void setFont(void *font)
{
	currentfont = font;
}

void drawstring(float x, float y, float z, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, *c);
	}
}

void mainscreen(void)
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0.6, 0.8, 1.0, 0);/*background for cover page*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	drawstring(450.0, 620.0, 0.0, "RAJIV GANDHI INSTITUTE OF TECHNOLOGY ");
	glColor3f(0.7, 0, 1);
	drawstring(330, 570, 0.0, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1, 0.5, 0);
	drawstring(530, 480, 0.0, "A MINI PROJECT ON");
	glColor3f(1, 0, 0);
	drawstring(360, 440, 0.0, "TRAFFIC INTERSECTION CONTROL SYSTEM");
	glColor3f(1, 0.5, 0);
	drawstring(200, 310, 0.0, "BY:");
	glColor3f(0, 0, 0);
	drawstring(100, 250, 0.0, "NAME:SURENDRA AYER");
	//glColor3f(1, 1, 1);
	//drawstring(100, 240, 0.0, "name");
	glColor3f(1, 0.5, 0);
	drawstring(980, 310, 0.0, "GUIDES:");
	glColor3f(0, 0, 0);
	drawstring(930, 250, 0.0, "NAME: Mrs.SUNITA.T N");
	glColor3f(0, 0, 0);
	drawstring(930, 210, 0.0, "NAME: Mrs.PAMELA VINITHA ");
	glColor3f(1, 0.1, 1);
	drawstring(543, 50, 0.0, "PRESS ENTER TO START");

	glLineWidth(3.0);  //table border
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(40, 100, 0);
	glVertex3f(1360, 100, 0);
	glVertex3f(1360, 670, 0);
	glVertex3f(40, 670, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(30, 90, 0);
	glVertex3f(1370, 90, 0);
	glVertex3f(1370, 680, 0);
	glVertex3f(30, 680, 0);
	glEnd();
	glFlush();
}

void controlscreen()
{

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0.6, 1, 0.7, 0);/*background for cover page*/
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 0, 0);
	drawstring(450.0, 680.0, 0.0, "MOUSE   /   KEBOARD CONTROLS:");
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.8, 0.2, 0.1); 
	drawstring(150.0, 650.0, 0.0, "KEY  /  BUTTON");
	glColor3f(0.8, 0.2, 0.1);
	drawstring(600.0, 650.0, 0.0, "FUNCTION");

	//CONTROLS
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 620.0, 0.0, "MOUSE LEFT CLICK DOWN / HOLD");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 580.0, 0.0, "MOUSE LEFT CLICK UP / RELEASE");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 540.0, 0.0, "MOUSE RIGHT BUTTON");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0,500.0, 0.0, "PRESS        L");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 460.0, 0.0, "PRESS        K");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 420.0, 0.0, "PRESS        O");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 380.0, 0.0, "PRESS        F");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 340.0, 0.0, "PRESS        A");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 300.0, 0.0, "PRESS        Z");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 260.0, 0.0, "PRESS        X");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 220.0, 0.0, "PRESS        S");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 180.0, 0.0, "PRESS        D");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 140.0, 0.0, "PRESS        H");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 100.0, 0.0, "PRESS        1,  2,  3,  4,  5");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 60.0, 0.0, "PRESS        6,  7,  8");
	glColor3f(0.6, 0.3, 0.0);
	drawstring(50.0, 20.0, 0.0, "PRESS        ESCAPE");

	//FUNCTIONS
	glColor3f(0.4, 0.2, 1);
	drawstring(450.0, 620.0, 0.0, "SELECT TRAFFIC POLE   //   TURN ON YELLOW LIGHT   //   VEHICLES GET READY ");
	glColor3f(0.4, 0.2, 1);
	drawstring(450.0, 580.0, 0.0, "TURN ON GREEN LIGHT   ///   ALLOW VEHICLES TO MOVE");
	glColor3f(0.4, 0.2, 1);
	drawstring(450.0, 540.0, 0.0, "TURN ON RED LIGHT   ///   STOP VEHICLES");
	glColor3f(0.4, 0.2, 1);
	drawstring(450.0, 500.0, 0.0, "BLOCK VERTICAL ROAD   ///   ALLOW ONLY HORIZONTAL ROAD");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 460.0, 0.0, "BLOCK HORIZONTAL ROAD   ///   ALLOW ONLY VERTICAL ROAD");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 420.0, 0.0, "TURN ON VEHICLE LIGHTS");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 380.0, 0.0, "TURN OFF VEHICLE LIGHTS");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 340.0, 0.0, "EMERGENCY TRAFFIC  //  ALLOW ONLY AMBULANCE");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 300.0, 0.0, "ALLOW ZEBRA CROSSING   //   ALL VEHICLES STOP");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 260.0, 0.0, "ALLOW ALL VEHICLES MOVEMENT");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 220.0, 0.0, "INCREASE VEHICLES SPEED");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 180.0, 0.0, "DECREASE VEHICLES SPEED");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 140.0, 0.0, "GOTO CONTROL SCREEN");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 100.0, 0.0, "CHANGE COLOR OF VEHICLES");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 60.0, 0.0, "CHANGE COLOR OF TRAFFIC POLES");
	glColor3f(0.4, 0.2, 1); 
	drawstring(450.0, 20.0, 0.0, "EXIT SIMULATION");


	
	glColor3f(1, 0.1, 1);
	drawstring(1000, 20, 0.0, "[ PRESS ENTER TO START SIMULATION ]");

	glLineWidth(3.0);  //table border
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(20, 10, 0);
	glVertex3f(1380, 10, 0);
	glVertex3f(1380, 670, 0);
	glVertex3f(20, 670, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(20, 640, 0);
	glVertex3f(1380, 640, 0);
	glVertex3f(400, 670, 0);
	glVertex3f(400, 10, 0);
	glVertex3f(20, 520, 0);
	glVertex3f(1380, 520, 0);
	glEnd();

	glLineWidth(1.0); //middle lines
	glBegin(GL_LINES);
	glVertex3f(20, 610, 0);
	glVertex3f(1380, 610, 0);
	glVertex3f(20, 560, 0);
	glVertex3f(1380, 560, 0);
	glVertex3f(20, 490, 0);
	glVertex3f(1380, 490, 0);
	glVertex3f(20, 450, 0);
	glVertex3f(1380, 450, 0);
	glVertex3f(20, 410, 0);
	glVertex3f(1380, 410, 0);
	glVertex3f(20, 370, 0);
	glVertex3f(1380, 370, 0);
	glVertex3f(20, 330, 0);
	glVertex3f(1380, 330, 0);
	glVertex3f(20, 290, 0);
	glVertex3f(1380, 290, 0);
	glVertex3f(20, 250, 0);
	glVertex3f(1380, 250, 0);
	glVertex3f(20, 210, 0);
	glVertex3f(1380, 210, 0);
	glVertex3f(20, 170, 0);
	glVertex3f(1380, 170, 0);
	glVertex3f(20, 130, 0);
	glVertex3f(1380, 130, 0);
	glVertex3f(20, 90, 0);
	glVertex3f(1380, 90, 0);
	glVertex3f(20, 50, 0);
	glVertex3f(1380, 50, 0);
	glEnd();
	glFlush();
}



void road()
{
	glPushMatrix();
	//glScaled(40.0, 40.0, 0.0);
	
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	//horizontal straight road
	glVertex2f(0, 200);
	glVertex2f(1400, 200);
	glVertex2f(1400, 425);
	glVertex2f(0, 425);
	glEnd();
	
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	//vertical straight road
	glVertex2f(450, 0);
	glVertex2f(750, 0);
	glVertex2f(950, 700);
	glVertex2f(650, 700);
	glEnd();

	//white edge start
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	//horizontal
	glVertex2f(0, 200);  //left lower
	glVertex2f(515, 200);
	glVertex2f(515, 210);
	glVertex2f(0, 210);
	
	glVertex2f(0, 415); //left upper
	glVertex2f(575, 415);
	glVertex2f(575, 425);
	glVertex2f(0, 425);
	
	glVertex2f(800, 200); //right lower
	glVertex2f(1400, 200);
	glVertex2f(1400, 210);
	glVertex2f(800, 210);
	
	glVertex2f(865, 415); //right upper
	glVertex2f(1400, 415);
	glVertex2f(1400, 425);
	glVertex2f(865, 425);
	
	//vertical
	glVertex2f(450, 0); //left lower
	glVertex2f(460, 0);
	glVertex2f(520, 210);
	glVertex2f(510, 210);
	
	glVertex2f(750, 0); //right lower
	glVertex2f(760, 0);
	glVertex2f(810, 210);
	glVertex2f(800, 210);
	
	glVertex2f(565, 415); //left upper
	glVertex2f(575, 415);
	glVertex2f(660, 700);
	glVertex2f(650, 700);
	
	glVertex2f(860, 415); //right upper
	glVertex2f(870, 415);
	glVertex2f(960, 700);
	glVertex2f(950, 700);
	

	//middle strips
	//horizontal
	glVertex2f(10, 309);  
	glVertex2f(10, 315);
	glVertex2f(40, 315);
	glVertex2f(40, 309);

	glVertex2f(90, 309);
	glVertex2f(90, 315);
	glVertex2f(120, 315);
	glVertex2f(120, 309);

	glVertex2f(170, 309);
	glVertex2f(170, 315);
	glVertex2f(200, 315);
	glVertex2f(200, 309);

	glVertex2f(250, 309);
	glVertex2f(250, 315);
	glVertex2f(280, 315);
	glVertex2f(280, 309);
	
	glVertex2f(310, 309);
	glVertex2f(310, 315);
	glVertex2f(340, 315);
	glVertex2f(340, 309);
	
	glVertex2f(440, 309);
	glVertex2f(440, 315);
	glVertex2f(480, 315);
	glVertex2f(480, 309);
	
	glVertex2f(500, 309);
	glVertex2f(500, 315);
	glVertex2f(530, 315);
	glVertex2f(530, 309);
	
	glVertex2f(875, 309);//right
	glVertex2f(875, 315);
	glVertex2f(900, 315);
	glVertex2f(900, 309);

	glVertex2f(950, 309);
	glVertex2f(950, 315);
	glVertex2f(980, 315);
	glVertex2f(980, 309);

	glVertex2f(1030, 309);
	glVertex2f(1030, 315);
	glVertex2f(1060, 315);
	glVertex2f(1060, 309);

	glVertex2f(1110, 309);
	glVertex2f(1110, 315);
	glVertex2f(1140, 315);
	glVertex2f(1140, 309);

	glVertex2f(1190, 309);
	glVertex2f(1190, 315);
	glVertex2f(1220, 315);
	glVertex2f(1220, 309);

	glVertex2f(1270, 309);
	glVertex2f(1270, 315);
	glVertex2f(1300, 315);
	glVertex2f(1300, 309);
	
	glVertex2f(1350, 309);
	glVertex2f(1350, 315);
	glVertex2f(1380, 315);
	glVertex2f(1380, 309);

	//vertical
	glVertex2f(597, 0);
	glVertex2f(603, 0);
	glVertex2f(609, 30);
	glVertex2f(603, 30);

	glVertex2f(617, 80);
	glVertex2f(623, 80);
	glVertex2f(629,110);
	glVertex2f(623, 110);

	glVertex2f(637, 160);
	glVertex2f(643, 160);
	glVertex2f(649, 190);
	glVertex2f(643, 190);

	glVertex2f(702, 400);
	glVertex2f(708, 400);
	glVertex2f(714, 430);
	glVertex2f(708, 430);

	glVertex2f(722, 480);
	glVertex2f(728, 480);
	glVertex2f(734, 510);
	glVertex2f(728, 510);

	glVertex2f(742, 560);
	glVertex2f(748, 560);
	glVertex2f(754, 590);
	glVertex2f(748, 590);

	glVertex2f(762, 640);
	glVertex2f(768, 640);
	glVertex2f(774, 670);
	glVertex2f(768, 670);

	glEnd();

	//Zebra Crossing
	glBegin(GL_QUADS); //left
	
	glVertex2f(380, 400);
	glVertex2f(380, 406);
	glVertex2f(460, 406);
	glVertex2f(460, 400);

	glVertex2f(370, 370);
	glVertex2f(370, 376);
	glVertex2f(450, 376);
	glVertex2f(450, 370);
	
	glVertex2f(360, 340);
	glVertex2f(360, 346);
	glVertex2f(440, 346);
	glVertex2f(440, 340);
	
	glVertex2f(350, 310);
	glVertex2f(350, 316);
	glVertex2f(430, 316);
	glVertex2f(430, 310);
	
	glVertex2f(340, 280);
	glVertex2f(340, 286);
	glVertex2f(420, 286);
	glVertex2f(420, 280);
	
	glVertex2f(330, 250);
	glVertex2f(330, 256);
	glVertex2f(410, 256);
	glVertex2f(410, 250);
	
	glVertex2f(320, 220);
	glVertex2f(320, 226);
	glVertex2f(400, 226);
	glVertex2f(400, 220);

//right
	
	glVertex2f(970, 400);
	glVertex2f(970, 406);
	glVertex2f(1050, 406);
	glVertex2f(1050, 400);

	glVertex2f(980, 370);
	glVertex2f(980, 376);
	glVertex2f(1060, 376);
	glVertex2f(1060, 370);
	
	glVertex2f(990, 340);
	glVertex2f(990, 346);
	glVertex2f(1070, 346);
	glVertex2f(1070, 340);
	
	glVertex2f(1000, 309);
	glVertex2f(1000, 315);
	glVertex2f(1080, 315);
	glVertex2f(1080, 309);
	
	glVertex2f(1010, 280);
	glVertex2f(1010, 286);
	glVertex2f(1090, 286);
	glVertex2f(1090, 280);
	
	glVertex2f(1020, 250);
	glVertex2f(1020, 256);
	glVertex2f(1100, 256);
	glVertex2f(1100, 250);
	
	glVertex2f(1030, 220);
	glVertex2f(1030, 226);
	glVertex2f(1110, 226);
	glVertex2f(1110, 220);
	glEnd();

	//front lines
	//left 1
	glColor3f(m[1], n[1], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(540, 315);
	glVertex2f(545, 315);
	glVertex2f(570, 415);
	glVertex2f(565, 415);
	glEnd();

	//top 2
	glColor3f(m[2], n[2], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(855, 425);
	glVertex2f(855, 430);
	glVertex2f(715, 430);
	glVertex2f(715, 425);
	glEnd();

	//right 3
	glColor3f(m[3], n[3], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(830, 210);
	glVertex2f(835, 210);
	glVertex2f(860, 310);
	glVertex2f(855, 310);
	glEnd();
	//down 4
	glColor3f(m[4], n[4], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(640, 195);
	glVertex2f(640, 200);
	glVertex2f(525, 200);
	glVertex2f(525, 195);
	glEnd();
	glPopMatrix();
}



void trafficsignal1()
{
	glPushMatrix();
	glTranslated(200.0, 290.0,0.0);
	glScaled(20.0, 20.0, 0.0);
	//stand
	glColor3f(t1,t2,t3);
	glBegin(GL_POLYGON);
	glVertex2f(15.5, 7);
	glVertex2f(15.5, 8);
	glVertex2f(17, 8);
	glVertex2f(17, 7);
	glEnd(); 
	//pole
	glBegin(GL_POLYGON);
	glVertex2f(16, 7);
	glVertex2f(16.5,7 );
	glVertex2f(16.5, 16);
	glVertex2f(16, 16);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(400.0, 150.0, 0.0);
	glRotated(30.0, 0.0, 0.0, 1.0);
	glScaled(20.0, 20.0, 0.0);
	//board
	glBegin(GL_POLYGON);
	glVertex2f(15.3, 17);
	glVertex2f(17.3, 17);
	glVertex2f(17.3, 13);
	glVertex2f(15.3, 13);
	glEnd();
	//red
	glColor3f(p[1], 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 16.5);
	glVertex2f(16.8, 16.5);
	glVertex2f(16.8, 16);
	glVertex2f(15.8, 16);
	glEnd();
	//yellow
	glColor3f(q[1], q[1], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 15.5);
	glVertex2f(16.8, 15.5);
	glVertex2f(16.8, 15);
	glVertex2f(15.8, 15);
	glEnd();
	//green
	glColor3f(0.0, r[1], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 14.5);
	glVertex2f(16.8, 14.5);
	glVertex2f(16.8, 14);
	glVertex2f(15.8, 14);
	glEnd();
	glPopMatrix();

}

void trafficsignal2()
{
	glPushMatrix();
	glTranslated(600.0, 285.0, 0.0);
	glScaled(20.0, 20.0, 0.0);
	//stand
	glColor3f(t1, t2, t3);
	glBegin(GL_POLYGON);
	glVertex2f(15.5, 7);
	glVertex2f(15.5, 8);
	glVertex2f(17, 8);
	glVertex2f(17, 7);
	glEnd();
	//pole
	glBegin(GL_POLYGON);
	glVertex2f(16, 7);
	glVertex2f(16.5, 7);
	glVertex2f(16.5, 16);
	glVertex2f(16, 16);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(580.0, 925.0, 0.0);
	glRotated(270.0, 0.0, 0.0, 1.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(t1, t2, t3);
	//board
	glBegin(GL_POLYGON);
	glVertex2f(15.3, 17);
	glVertex2f(17.3, 17);
	glVertex2f(17.3, 13);
	glVertex2f(15.3, 13);
	glEnd();
	//red
	glColor3f(p[2], 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 16.5);
	glVertex2f(16.8, 16.5);
	glVertex2f(16.8, 16);
	glVertex2f(15.8, 16);
	glEnd();
	//yellow
	glColor3f(q[2], q[2], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 15.5);
	glVertex2f(16.8, 15.5);
	glVertex2f(16.8, 15);
	glVertex2f(15.8, 15);
	glEnd();
	//green
	glColor3f(0.0, r[2], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 14.5);
	glVertex2f(16.8, 14.5);
	glVertex2f(16.8, 14);
	glVertex2f(15.8, 14);
	glEnd();
	glPopMatrix();

}

void trafficsignal3()
{
	glPushMatrix();
	glTranslated(540.0, 40.0, 0.0);
	glScaled(20.0, 20.0, 0.0);
	//stand
	glColor3f(t1, t2, t3);
	glBegin(GL_POLYGON);
	glVertex2f(15.5, 7);
	glVertex2f(15.5, 8);
	glVertex2f(17, 8);
	glVertex2f(17, 7);
	glEnd();
	//pole
	glBegin(GL_POLYGON);
	glVertex2f(16, 7);
	glVertex2f(16.5, 7);
	glVertex2f(16.5, 16);
	glVertex2f(16, 16);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(840.0, -90.0, 0.0);
	glRotated(40.0, 0.0, 0.0, 1.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(t1, t2, t3);
	//board
	glBegin(GL_POLYGON);
	glVertex2f(15.3, 17);
	glVertex2f(17.3, 17);
	glVertex2f(17.3, 13);
	glVertex2f(15.3, 13);
	glEnd();
	//red
	glColor3f(p[3], 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 16.5);
	glVertex2f(16.8, 16.5);
	glVertex2f(16.8, 16);
	glVertex2f(15.8, 16);
	glEnd();
	//yellow
	glColor3f(q[3], q[3], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 15.5);
	glVertex2f(16.8, 15.5);
	glVertex2f(16.8, 15);
	glVertex2f(15.8, 15);
	glEnd();
	//green
	glColor3f(0.0, r[3], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 14.5);
	glVertex2f(16.8, 14.5);
	glVertex2f(16.8, 14);
	glVertex2f(15.8, 14);
	glEnd();
	glPopMatrix();
}

void trafficsignal4()
{
	glPushMatrix();
	glTranslated(130.0, 40.0, 0.0);
	glScaled(20.0, 20.0, 0.0);
	//stand
	glColor3f(t1, t2, t3);
	glBegin(GL_POLYGON);
	glVertex2f(15.5, 7);
	glVertex2f(15.5, 8);
	glVertex2f(17, 8);
	glVertex2f(17, 7);
	glEnd();
	//pole
	glBegin(GL_POLYGON);
	glVertex2f(16, 7);
	glVertex2f(16.5, 7);
	glVertex2f(16.5, 16);
	glVertex2f(16, 16);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(800.0, 35.0, 0.0);
	glRotated(90.0, 0.0, 0.0, 1.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(t1, t2, t3);
	//board
	glBegin(GL_POLYGON);
	glVertex2f(15.3, 17);
	glVertex2f(17.3, 17);
	glVertex2f(17.3, 13);
	glVertex2f(15.3, 13);
	glEnd();
	//red
	glColor3f(p[4], 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 16.5);
	glVertex2f(16.8, 16.5);
	glVertex2f(16.8, 16);
	glVertex2f(15.8, 16);
	glEnd();
	//yellow
	glColor3f(q[4], q[4], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 15.5);
	glVertex2f(16.8, 15.5);
	glVertex2f(16.8, 15);
	glVertex2f(15.8, 15);
	glEnd();
	//green
	glColor3f(0.0, r[4], 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15.8, 14.5);
	glVertex2f(16.8, 14.5);
	glVertex2f(16.8, 14);
	glVertex2f(15.8, 14);
	glEnd();
	glPopMatrix();
}


void passengerbus()
{
	glPushMatrix();
	glTranslated(a1, -40.0, 0.0);
	glScaled(40.0, 40.0, 0.0);
	//glRotated(90.0, 0.0, 0.0, 0.0);
	glColor3f(c2, c1, c3);
	//bus out line
	glBegin(GL_POLYGON);
	glVertex2f(25, 8);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(32, 11);
	glVertex2f(32, 8);
	glEnd();
	//light
	glColor3f(light, light, light);
	glBegin(GL_POLYGON); //front
	glVertex2f(25, 8.7);
	glVertex2f(25, 9);
	glVertex2f(25.5,9);
	glVertex2f(25.5, 8.7);
	glEnd();
	glBegin(GL_POLYGON); //back
	glVertex2f(31.5, 8.7);
	glVertex2f(31.5, 9);
	glVertex2f(32, 9);
	glVertex2f(32, 8.7);
	glEnd();

	//window frame
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(26.1, 9.5);
	glVertex2f(26.1, 10.5);
	glVertex2f(31.8, 10.5);
	glVertex2f(31.8, 9.5);
	glEnd();
	//Doors
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(26.2, 9);
	glVertex2f(26.2, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 9);
	glEnd();


	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8.4);
	glVertex2f(27, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 8.4);
	glEnd();
	//small windows
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(27.8, 9.6);
	glVertex2f(27.8, 10.4);
	glVertex2f(29, 10.4);
	glVertex2f(29, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(29.1, 9.6);
	glVertex2f(29.1, 10.4);
	glVertex2f(30.2, 10.4);
	glVertex2f(30.2, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(30.3, 9.6);
	glVertex2f(30.3, 10.4);
	glVertex2f(31.7, 10.4);
	glVertex2f(31.7, 9.6);
	glEnd();


	//driver window
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(26, 9.5);
	glEnd();
	glPopMatrix();
	
	//tyre
	glPushMatrix();//front tyre
	glTranslated(a1 + 970, 230, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//back tyre
	glTranslated(a1 + 1140, 230, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();
}

void schoolbus()
{
	glPushMatrix();
	glTranslated(b1+500, 40.0, 0.0);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScaled(40.0, 40.0, 0.0);
	//glRotated(90.0, 0.0, 0.0, 0.0);
	glColor3f(c1, c1, c2);
	//bus out line
	glBegin(GL_POLYGON);
	glVertex2f(25, 8);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(32, 11);
	glVertex2f(32, 8);
	glEnd();
	//light
	glColor3f(light, light, light);
	glBegin(GL_POLYGON); //front
	glVertex2f(25, 8.7);
	glVertex2f(25, 9);
	glVertex2f(25.5, 9);
	glVertex2f(25.5, 8.7);
	glEnd();
	glBegin(GL_POLYGON); //back
	glVertex2f(31.5, 8.7);
	glVertex2f(31.5, 9);
	glVertex2f(32, 9);
	glVertex2f(32, 8.7);
	glEnd();

	//window frame
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(26.1, 9.5);
	glVertex2f(26.1, 10.5);
	glVertex2f(31.8, 10.5);
	glVertex2f(31.8, 9.5);
	glEnd();
	//Doors
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(26.2, 9);
	glVertex2f(26.2, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 9);
	glEnd();

	//second door
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8.4);
	glVertex2f(27, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 8.4);
	glEnd();
	//small windows
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(27.8, 9.6);
	glVertex2f(27.8, 10.4);
	glVertex2f(29, 10.4);
	glVertex2f(29, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(29.1, 9.6);
	glVertex2f(29.1, 10.4);
	glVertex2f(30.2, 10.4);
	glVertex2f(30.2, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(30.3, 9.6);
	glVertex2f(30.3, 10.4);
	glVertex2f(31.7, 10.4);
	glVertex2f(31.7, 9.6);
	glEnd();


	//driver window
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(26, 9.5);
	glEnd();
	glPopMatrix();

	//tyre
	glPushMatrix();//front tyre
	glTranslated(b1+500-970, 310, 0.0);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//back tyre
	glTranslated(b1+500-1140, 310, 0.0);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(b1-450, 200.0, 0.0);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(9, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glRasterPos2i(10, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glRasterPos2i(12, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glRasterPos2i(14, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	/*glRasterPos2i(10, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glRasterPos2i(110, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glRasterPos2i(130, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glRasterPos2i(140, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'F');
	glRasterPos2i(150, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'F');
	glRasterPos2i(160, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glRasterPos2i(165, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glRasterPos2i(175, 170);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	*/
	glPopMatrix();
}


void car1()
{
	glPushMatrix(); //making color for outer line
	glTranslated(b2, 320.0, 0.0);

	glScaled(20.0, 20.0, 0.0);
	glColor3f(c1, c2, c3);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //color for outer window
	glBegin(GL_POLYGON);
	glVertex2f(5.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //making outer line for car
	glBegin(GL_LINE_LOOP);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP); //outer line for design a car
	glVertex2f(8.0, 3.0);
	glVertex2f(16.0, 3.0);
	glVertex2f(16.5, 3.5);
	glVertex2f(17.0, 4.0);
	glVertex2f(16.5, 4.25);
	glVertex2f(16.0, 4.5);
	glVertex2f(15.0, 4.5);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glVertex2f(5.0, 5.0);
	glVertex2f(7.0, 5.0);
	glVertex2f(6.5, 4.5);
	glEnd();


	
	glBegin(GL_LINES); //connecting outer line
	glVertex2d(7.0, 5.0);
	glVertex2d(15.0, 5.0);
	glEnd();


	glColor3f(0.0, 0.0, 0.0); //connecting outer line 
	glBegin(GL_LINES);
	glVertex2d(15.0, 4.0);
	glVertex2d(17.0, 4.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(15.0, 3.5);
	glVertex2d(16.5, 3.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(15.0, 5.0);
	glVertex2d(14.0, 3.0);
	glEnd();

	glColor3f(0.5, 0.5, 0.5); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(12.0, 5.0);
	glVertex2d(12.0, 6.2);
	glEnd();

	glColor3f(.5, 0.5, 0.5); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(7.0, 5.0);
	glVertex2d(7.0, 6.7);
	glEnd();

	glColor3f(light, light, light); //light
	glBegin(GL_POLYGON); //front
	glVertex2f(19.75, 4.0);
	glVertex2f(19.75, 4.5);
	glVertex2f(20.75, 4.5);
	glVertex2f(20.75, 4.0);
	glEnd();
	glBegin(GL_POLYGON); //back
	glVertex2f(1.0, 4.0);
	glVertex2f(1.0, 4.5);
	glVertex2f(2.0, 4.5);
	glVertex2f(2.0, 4.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //drawing a back tyre
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();


	glBegin(GL_POLYGON); //drawing front tyre
	glVertex2f(17.0, 2.5);
	glVertex2f(17.0, 2.6);
	glVertex2f(17.15, 3.1);
	glVertex2f(17.2, 3.2);
	glVertex2f(17.3, 3.35);
	glVertex2f(17.4, 3.4);
	glVertex2f(17.5, 3.45);
	glVertex2f(17.6, 3.55);
	glVertex2f(17.7, 3.6);
	glVertex2f(17.8, 3.63);
	glVertex2f(18.0, 3.65);
	glVertex2f(18.2, 3.7);
	glVertex2f(18.4, 3.7);
	glVertex2f(18.6, 3.65);
	glVertex2f(18.8, 3.55);
	glVertex2f(19.0, 3.45);
	glVertex2f(19.1, 3.4);
	glVertex2f(19.2, 3.25);
	glVertex2f(19.3, 3.2);
	glVertex2f(19.4, 3.0);

	glVertex2f(19.5, 2.5);
	glVertex2f(19.45, 2.15);
	glVertex2f(19.4, 1.9);
	glVertex2f(19.35, 1.8);
	glVertex2f(19.2, 1.6);
	glVertex2f(19.0, 1.5);
	glVertex2f(18.9, 1.4);
	glVertex2f(18.7, 1.3);
	glVertex2f(18.6, 1.27);
	glVertex2f(18.4, 1.25);
	glVertex2f(18.0, 1.25);
	glVertex2f(17.9, 1.3);
	glVertex2f(17.75, 1.35);
	glVertex2f(17.6, 1.4);
	glVertex2f(17.45, 1.55);
	glVertex2f(17.3, 1.7);
	glVertex2f(17.2, 1.8);
	glVertex2f(17.1, 2.2);
	glEnd();
	glPopMatrix();
}

void car2()
{
	glPushMatrix(); //making color for outer line
	glTranslated(a2 + 2300, 220.0, 0.0);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(c3, c1, c2);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //color for outer window
	glBegin(GL_POLYGON);
	glVertex2f(5.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //making outer line for car
	glBegin(GL_LINE_LOOP);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP); //outer line for design a car
	glVertex2f(8.0, 3.0);
	glVertex2f(16.0, 3.0);
	glVertex2f(16.5, 3.5);
	glVertex2f(17.0, 4.0);
	glVertex2f(16.5, 4.25);
	glVertex2f(16.0, 4.5);
	glVertex2f(15.0, 4.5);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glVertex2f(5.0, 5.0);
	glVertex2f(7.0, 5.0);
	glVertex2f(6.5, 4.5);
	glEnd();


	glBegin(GL_LINES); //connecting outer line
	glVertex2d(7.0, 5.0);
	glVertex2d(15.0, 5.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line 
	glBegin(GL_LINES);
	glVertex2d(15.0, 4.0);
	glVertex2d(17.0, 4.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(15.0, 3.5);
	glVertex2d(16.5, 3.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(15.0, 5.0);
	glVertex2d(14.0, 3.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(12.0, 5.0);
	glVertex2d(12.0, 6.2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //connecting outer line
	glBegin(GL_LINES);
	glVertex2d(7.0, 5.0);
	glVertex2d(7.0, 6.7);
	glEnd();

	glColor3f(light, light, light); //light
	glBegin(GL_POLYGON); //front
	glVertex2f(19.75, 4.0);
	glVertex2f(19.75, 4.5);
	glVertex2f(20.75, 4.5);
	glVertex2f(20.75, 4.0);
	glEnd();
	glBegin(GL_POLYGON); //back
	glVertex2f(1.0, 4.0);
	glVertex2f(1.0, 4.5);
	glVertex2f(2.0, 4.5);
	glVertex2f(2.0, 4.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //drawing a back tyre
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();


	glBegin(GL_POLYGON); //drawing front tyre
	glVertex2f(17.0, 2.5);
	glVertex2f(17.0, 2.6);
	glVertex2f(17.15, 3.1);
	glVertex2f(17.2, 3.2);
	glVertex2f(17.3, 3.35);
	glVertex2f(17.4, 3.4);
	glVertex2f(17.5, 3.45);
	glVertex2f(17.6, 3.55);
	glVertex2f(17.7, 3.6);
	glVertex2f(17.8, 3.63);
	glVertex2f(18.0, 3.65);
	glVertex2f(18.2, 3.7);
	glVertex2f(18.4, 3.7);
	glVertex2f(18.6, 3.65);
	glVertex2f(18.8, 3.55);
	glVertex2f(19.0, 3.45);
	glVertex2f(19.1, 3.4);
	glVertex2f(19.2, 3.25);
	glVertex2f(19.3, 3.2);
	glVertex2f(19.4, 3.0);

	glVertex2f(19.5, 2.5);
	glVertex2f(19.45, 2.15);
	glVertex2f(19.4, 1.9);
	glVertex2f(19.35, 1.8);
	glVertex2f(19.2, 1.6);
	glVertex2f(19.0, 1.5);
	glVertex2f(18.9, 1.4);
	glVertex2f(18.7, 1.3);
	glVertex2f(18.6, 1.27);
	glVertex2f(18.4, 1.25);
	glVertex2f(18.0, 1.25);
	glVertex2f(17.9, 1.3);
	glVertex2f(17.75, 1.35);
	glVertex2f(17.6, 1.4);
	glVertex2f(17.45, 1.55);
	glVertex2f(17.3, 1.7);
	glVertex2f(17.2, 1.8);
	glVertex2f(17.1, 2.2);
	glEnd();
	glPopMatrix();
}

void busup()
{
	glPushMatrix();
	glTranslated(upX1-80-10, upY1, 0.0);  //upX=320,upY=-180
	glScaled(60.0, 60.0, 0.0);
	//glRotated(10.0, 0.0, 0.0, 1.0);
	glColor3f(c1, c2, c1);
	//bus out line
	glBegin(GL_POLYGON);
	glVertex2f(5.9, 5);
	glVertex2f(6.9, 8);
	glVertex2f(8, 8);
	glVertex2f(7, 5);
	glEnd();
	//top window
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(6.7, 7.1);
	glVertex2f(6.8, 7.5);
	glVertex2f(7.7, 7.4);
	glVertex2f(7.5, 7);
	glEnd();
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(6.3, 5.8);
	glVertex2f(6.4, 6.2);
	glVertex2f(7.2, 6.1);
	glVertex2f(7.1, 5.7);
	glEnd();
	//front window
	glColor3f(0.0, 0.0, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(6.9, 8);
	glVertex2f(7.4, 8.2);
	glVertex2f(8.4, 8.2);
	glVertex2f(8, 8);
	glEnd();
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(8.4, 8.2);
	glVertex2f(8.7, 8); 
	glEnd();
	//back
	glColor3f(c2, c1, c3);
	glBegin(GL_POLYGON);
	glVertex2f(5.9, 5);
	glVertex2f(6.4, 4.4);
	glVertex2f(7.7, 4.2);
	glVertex2f(7, 5);
	glEnd();
	//back window
	glColor3f(0.0, 0.5, 1.0); 
	glBegin(GL_POLYGON);
	glVertex2f(6.1, 4.8);
	glVertex2f(7, 4.8);
	glVertex2f(7.2, 4.6);
	glVertex2f(6.3, 4.6);
	glEnd();

	glColor3f(c3, c1, c3);//side
	glBegin(GL_POLYGON);
	glVertex2f(7, 5);
	glVertex2f(7.7, 4.2);
	glVertex2f(8.7, 8);
	glVertex2f(8.4, 8.2);
	glVertex2f(8, 8);
	glEnd();
	
	//back light
	glColor3f(light, light, light);//right
	glBegin(GL_POLYGON);
	glVertex2f(7.1, 4.4);
	glVertex2f(7.05, 4.5);
	glVertex2f(7.4, 4.45);
	glVertex2f(7.4, 4.35);
	glEnd();
	
	glBegin(GL_POLYGON); //left
	glVertex2f(6.4, 4.45);
	glVertex2f(6.35, 4.55);
	glVertex2f(6.7, 4.5);
	glVertex2f(6.75, 4.4);
	glEnd();
	//window
	
	glColor3f(0.0, 0.0, 0.7); //driver
	glBegin(GL_POLYGON);
	glVertex2f(8, 8);
	glVertex2f(8.4, 8.2);
	glVertex2f(8.3, 7.8);
	glEnd();

	glColor3f(0.0, 0.0, 0.7); //side
	glBegin(GL_POLYGON);
	glVertex2f(7.1, 5.1);
	glVertex2f(7.5, 5);
	glVertex2f(8.3, 7.6);
	glVertex2f(8, 7.8);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //lines
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(7.1, 5.1);
	glVertex2f(7.5, 5);
	glVertex2f(8.3, 7.6);
	glVertex2f(8, 7.8);
	glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(8, 8);
	glVertex2f(8.4, 8.2);
	glVertex2f(8.3, 7.8);
	glEnd();

	glBegin(GL_LINES); //side window outline
	glVertex2f(7.25, 5.6);
	glVertex2f(7.65, 5.5);
	glVertex2f(7.4, 6);
	glVertex2f(7.8, 5.9);
	glVertex2f(7.6, 6.5);
	glVertex2f(7.95, 6.4);
	glVertex2f(7.7, 6.9);
	glVertex2f(8.05, 6.8);
	glVertex2f(7.85, 7.4);
	glVertex2f(8.2, 7.2);
	glEnd();

	glPopMatrix();

//tyre
	glPushMatrix();//front tyre
	glTranslated(upX1+475-10, upY1+380, 0.0); //x=70 y=-500
	glRotated(90, 0, 0, 1);
		glScaled(15.0, 15.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//back tyre
	glTranslated(upX1+435-10, upY1+250, 0.0);
	glRotated(90, 0, 0, 1);
	glScaled(15.0, 15.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();
	
	}

	void busup1()
	{
		glPushMatrix();
		glTranslated(upX1 - 80-200 - 120, upY1-900, 0.0);  //upX=320,upY=-180
		glScaled(60.0, 60.0, 0.0);
		//glRotated(10.0, 0.0, 0.0, 1.0);
		glColor3f(c3, c1, c2);
		//bus out line
		glBegin(GL_POLYGON);
		glVertex2f(5.9, 5);
		glVertex2f(6.9, 8);
		glVertex2f(8, 8);
		glVertex2f(7, 5);
		glEnd();
		//top window
		glColor3f(0.0, 0.5, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(6.7, 7.1);
		glVertex2f(6.8, 7.5);
		glVertex2f(7.7, 7.4);
		glVertex2f(7.5, 7);
		glEnd();
		glColor3f(0.0, 0.5, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(6.3, 5.8);
		glVertex2f(6.4, 6.2);
		glVertex2f(7.2, 6.1);
		glVertex2f(7.1, 5.7);
		glEnd();
		//front window
		glColor3f(0.0, 0.0, 0.8);
		glBegin(GL_POLYGON);
		glVertex2f(6.9, 8);
		glVertex2f(7.4, 8.2);
		glVertex2f(8.4, 8.2);
		glVertex2f(8, 8);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(8.4, 8.2);
		glVertex2f(8.7, 8);
		glEnd();
		//back
		glColor3f(c2, c3, c1);
		glBegin(GL_POLYGON);
		glVertex2f(5.9, 5);
		glVertex2f(6.4, 4.4);
		glVertex2f(7.7, 4.2);
		glVertex2f(7, 5);
		glEnd();
		//back window
		glColor3f(0.0, 0.5, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(6.1, 4.8);
		glVertex2f(7, 4.8);
		glVertex2f(7.2, 4.6);
		glVertex2f(6.3, 4.6);
		glEnd();

		glColor3f(c3, c1, c3);//side
		glBegin(GL_POLYGON);
		glVertex2f(7, 5);
		glVertex2f(7.7, 4.2);
		glVertex2f(8.7, 8);
		glVertex2f(8.4, 8.2);
		glVertex2f(8, 8);
		glEnd();

		//back light
		glColor3f(light, light, light);//right
		glBegin(GL_POLYGON);
		glVertex2f(7.1, 4.4);
		glVertex2f(7.05, 4.5);
		glVertex2f(7.4, 4.45);
		glVertex2f(7.4, 4.35);
		glEnd();

		glBegin(GL_POLYGON); //left
		glVertex2f(6.4, 4.45);
		glVertex2f(6.35, 4.55);
		glVertex2f(6.7, 4.5);
		glVertex2f(6.75, 4.4);
		glEnd();
		//window

		glColor3f(0.0, 0.0, 0.7); //driver
		glBegin(GL_POLYGON);
		glVertex2f(8, 8);
		glVertex2f(8.4, 8.2);
		glVertex2f(8.3, 7.8);
		glEnd();

		glColor3f(0.0, 0.0, 0.7); //side
		glBegin(GL_POLYGON);
		glVertex2f(7.1, 5.1);
		glVertex2f(7.5, 5);
		glVertex2f(8.3, 7.6);
		glVertex2f(8, 7.8);
		glEnd();

		glColor3f(0.0, 0.0, 0.0); //lines
		glLineWidth(3.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(7.1, 5.1);
		glVertex2f(7.5, 5);
		glVertex2f(8.3, 7.6);
		glVertex2f(8, 7.8);
		glEnd();
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(8, 8);
		glVertex2f(8.4, 8.2);
		glVertex2f(8.3, 7.8);
		glEnd();

		glBegin(GL_LINES); //side window outline
		glVertex2f(7.25, 5.6);
		glVertex2f(7.65, 5.5);
		glVertex2f(7.4, 6);
		glVertex2f(7.8, 5.9);
		glVertex2f(7.6, 6.5);
		glVertex2f(7.95, 6.4);
		glVertex2f(7.7, 6.9);
		glVertex2f(8.05, 6.8);
		glVertex2f(7.85, 7.4);
		glVertex2f(8.2, 7.2);
		glEnd();

		glPopMatrix();

		//tyre
		glPushMatrix();//front tyre
		glTranslated(upX1 + 475-200- 120, upY1 + 380-900, 0.0); //x=70 y=-500
		glRotated(90, 0, 0, 1);
		glScaled(15.0, 15.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(3.0, 2.5);
		glVertex2f(3.0, 2.6);
		glVertex2f(3.15, 3.1);
		glVertex2f(3.2, 3.2);
		glVertex2f(3.3, 3.35);
		glVertex2f(3.4, 3.4);
		glVertex2f(3.5, 3.45);
		glVertex2f(3.6, 3.55);
		glVertex2f(3.7, 3.6);
		glVertex2f(3.8, 3.63);
		glVertex2f(4.0, 3.65);
		glVertex2f(4.2, 3.7);
		glVertex2f(4.4, 3.7);
		glVertex2f(4.6, 3.65);
		glVertex2f(4.8, 3.55);
		glVertex2f(5.0, 3.45);
		glVertex2f(5.1, 3.4);
		glVertex2f(5.2, 3.25);
		glVertex2f(5.3, 3.2);
		glVertex2f(5.4, 3.0);
		glVertex2f(5.5, 2.5);

		glVertex2f(5.45, 2.15);
		glVertex2f(5.4, 1.9);
		glVertex2f(5.35, 1.8);
		glVertex2f(5.2, 1.6);
		glVertex2f(5.0, 1.5);
		glVertex2f(4.9, 1.4);
		glVertex2f(4.7, 1.3);
		glVertex2f(4.6, 1.27);
		glVertex2f(4.4, 1.25);
		glVertex2f(4.0, 1.25);
		glVertex2f(3.9, 1.3);
		glVertex2f(3.75, 1.35);
		glVertex2f(3.6, 1.4);
		glVertex2f(3.45, 1.55);
		glVertex2f(3.3, 1.7);
		glVertex2f(3.2, 1.8);
		glVertex2f(3.1, 2.2);
		glEnd();
		glPopMatrix();

		glPushMatrix();//back tyre
		glTranslated(upX1 + 435-200-120, upY1 + 250-900, 0.0);
		glRotated(90, 0, 0, 1);
		glScaled(15.0, 15.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(3.0, 2.5);
		glVertex2f(3.0, 2.6);
		glVertex2f(3.15, 3.1);
		glVertex2f(3.2, 3.2);
		glVertex2f(3.3, 3.35);
		glVertex2f(3.4, 3.4);
		glVertex2f(3.5, 3.45);
		glVertex2f(3.6, 3.55);
		glVertex2f(3.7, 3.6);
		glVertex2f(3.8, 3.63);
		glVertex2f(4.0, 3.65);
		glVertex2f(4.2, 3.7);
		glVertex2f(4.4, 3.7);
		glVertex2f(4.6, 3.65);
		glVertex2f(4.8, 3.55);
		glVertex2f(5.0, 3.45);
		glVertex2f(5.1, 3.4);
		glVertex2f(5.2, 3.25);
		glVertex2f(5.3, 3.2);
		glVertex2f(5.4, 3.0);
		glVertex2f(5.5, 2.5);

		glVertex2f(5.45, 2.15);
		glVertex2f(5.4, 1.9);
		glVertex2f(5.35, 1.8);
		glVertex2f(5.2, 1.6);
		glVertex2f(5.0, 1.5);
		glVertex2f(4.9, 1.4);
		glVertex2f(4.7, 1.3);
		glVertex2f(4.6, 1.27);
		glVertex2f(4.4, 1.25);
		glVertex2f(4.0, 1.25);
		glVertex2f(3.9, 1.3);
		glVertex2f(3.75, 1.35);
		glVertex2f(3.6, 1.4);
		glVertex2f(3.45, 1.55);
		glVertex2f(3.3, 1.7);
		glVertex2f(3.2, 1.8);
		glVertex2f(3.1, 2.2);
		glEnd();
		glPopMatrix();

	}




	void cardown()
	{
	glPushMatrix();

	glTranslated(downX - 50, downY - 400, 0.0);  //X=750,Y=400

	glScaled(30.0, 30.0, 0.0);
	glRotated(5.0, 0.0, 0.0, 1.0);

	//car outline 
	glColor3f(c1, c2, c3);
	glBegin(GL_POLYGON); //lower
	glVertex2f(0.2, 0.5);
	glVertex2f(0, 0.7);
	glVertex2f(0.8, 2.8);
	glVertex2f(2.8, 6.4);
	glVertex2f(3.2, 7);
	glVertex2f(4.9, 7);
	glVertex2f(5.4, 6.6);
	glVertex2f(2.4, 0);
	glEnd();
	glBegin(GL_POLYGON); //top
	glVertex2f(0.8, 2.8);
	glVertex2f(0.9, 4.3);
	glVertex2f(2.1, 6.2);
	glVertex2f(2.8, 6.4);
	glEnd();
	//side outline
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0.7);
	glVertex2f(1.8, 0.3);
	glVertex2f(2.8, 2.4);
	glVertex2f(3, 4.2);
	glVertex2f(4.1, 6.2);
	glVertex2f(4.5, 6.3);
	glVertex2f(4.9, 7);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(2.4, 0);
	glVertex2f(1.8, 0.3);
	glVertex2f(4.1, 6.2);
	glVertex2f(2.8, 6.4);
	glEnd();

	//front window
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(0.8, 2.8);
	glVertex2f(0.9, 4.3);
	glVertex2f(3, 4.2);
	glVertex2f(2.8, 2.4);
	glEnd();

	//side window
	glBegin(GL_POLYGON);
	glVertex2f(3, 2.9);
	glVertex2f(3.2, 4.4);
	glVertex2f(4.1, 6.1);
	glVertex2f(4.5, 6.3);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(3.6, 4.2);
	glVertex2f(3.3, 4.6);
	glVertex2f(4.2, 5.6);
	glVertex2f(3.8, 5.5);
	glEnd();

	//light
	glColor3f(light, light, light);
	glBegin(GL_POLYGON);  //rigth
	glVertex2f(1.5, 0.21);
	glVertex2f(1.5, 0.3);
	glVertex2f(1.7, 0.3);
	glVertex2f(1.7, 0.2);
	glEnd();
	glBegin(GL_POLYGON); //left
	glVertex2f(0.2, 0.48);
	glVertex2f(0.2, 0.55);
	glVertex2f(0.5, 0.52);
	glVertex2f(0.5, 0.48);
	glEnd();
	glPopMatrix();

	//front tyre
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslated(downX + 45, downY - 330, 0.0);
	glScaled(30.0, 30.0, 0.0);
	glutSolidSphere(0.5, 360, 360);
	glPopMatrix();
	//back tyre
	glPushMatrix();
	glTranslated(downX + 80, downY - 230, 0.0);
	glScaled(30.0, 30.0, 0.0);
	glutSolidSphere(0.5, 360, 360);
	glPopMatrix();
	}


	void cardown1()
	{
		glPushMatrix();
		
		glTranslated(downX-50+250 + 60, downY-400+700+200, 0.0);  //X=750,Y=400
		
		glScaled(30.0, 30.0, 0.0);
	glRotated(5.0,0.0, 0.0, 1.0);
		
		//car outline 
		glColor3f(c1, c2, 1);
		glBegin(GL_POLYGON); //lower
		glVertex2f(0.2,0.5);
		glVertex2f(0,0.7);
		glVertex2f(0.8,2.8);
		glVertex2f(2.8,6.4);
		glVertex2f(3.2,7);
		glVertex2f(4.9,7);
		glVertex2f(5.4,6.6);
		glVertex2f(2.4, 0);
		glEnd();
		glBegin(GL_POLYGON); //top
		glVertex2f(0.8, 2.8);
		glVertex2f(0.9, 4.3);
		glVertex2f(2.1, 6.2);
		glVertex2f(2.8, 6.4);
		glEnd();
		//side outline
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(0, 0.7);
		glVertex2f(1.8,0.3);
		glVertex2f(2.8,2.4);
		glVertex2f(3, 4.2);
		glVertex2f(4.1,6.2);
		glVertex2f(4.5, 6.3);
		glVertex2f(4.9, 7);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(2.4, 0);
		glVertex2f(1.8, 0.3);
		glVertex2f(4.1, 6.2);
		glVertex2f(2.8, 6.4);
		glEnd();
	
		 //front window
		glColor3f(0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex2f(0.8, 2.8);
		glVertex2f(0.9, 4.3); 
		glVertex2f(3, 4.2);
		glVertex2f(2.8, 2.4);		
		glEnd();

			//side window
		glBegin(GL_POLYGON);
		glVertex2f(3,2.9);
		glVertex2f(3.2, 4.4);
		glVertex2f(4.1, 6.1);
		glVertex2f(4.5, 6.3);
		glEnd();
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(3.6, 4.2);
		glVertex2f(3.3, 4.6);
		glVertex2f(4.2, 5.6);
		glVertex2f(3.8, 5.5);
		glEnd();

		//light
		glColor3f(light, light, light);
		glBegin(GL_POLYGON);  //rigth
		glVertex2f(1.5, 0.21);
		glVertex2f(1.5, 0.3);
		glVertex2f(1.7, 0.3);
		glVertex2f(1.7, 0.2);
		glEnd();
		glBegin(GL_POLYGON); //left
		glVertex2f(0.2, 0.48);
		glVertex2f(0.2, 0.55);
		glVertex2f(0.5, 0.52);
		glVertex2f(0.5, 0.48);
		glEnd();
	glPopMatrix();

		//front tyre
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslated(downX+45+250 + 60, downY-330+700+200, 0.0);
		glScaled(30.0, 30.0, 0.0);
		glutSolidSphere(0.5, 360, 360);
		glPopMatrix();
		//back tyre
		glPushMatrix();
		glTranslated(downX+80+250+60, downY-230+700+200, 0.0);
		glScaled(30.0, 30.0, 0.0);
		glutSolidSphere(0.5, 360, 360);
		glPopMatrix();
	}
/*
	void tree()
	{
		glPushMatrix();
		glTranslated(200.0, 520.0, 0.0);
		glScaled(40.0, 40.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidSphere(1.6, 500, 500);
		glPopMatrix();

		glPushMatrix();
		glTranslated(340.0, 520.0, 0.0);
		glScaled(40.0, 40.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidSphere(1.6, 500, 500);
glPopMatrix();
glColor3f(0.0, 1.0, 0.0);
glBegin(GL_QUADS);
glVertex2f(0, 425);
glVertex2f(0, 550);
glVertex2f(610, 550);
glVertex2f(570, 425);

	}
	*/
	void grass()
	{
		//left lower
		glBegin(GL_POLYGON);//blue
		glColor3f(0.3, 0.5, 0.9);
		glVertex2f(0, 120);
		glVertex2f(0, 250);
		glVertex2f(515, 300);
		glVertex2f(500, 120);
		glEnd();

		glBegin(GL_POLYGON); //green
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(0, 140);
		glVertex2i(515, 140);
		glVertex2i(500, 0);
		glVertex2i(0, 0);
		glEnd();
	
		//right lower
		glBegin(GL_POLYGON);//blue
		glColor3f(0.3, 0.5, 0.9);
		glVertex2f(780, 120);
		glVertex2f(800, 250);
		glVertex2f(1400, 300);
		glVertex2f(1400, 120);
		glEnd();

		glBegin(GL_POLYGON); //green
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(780, 140);
		glVertex2i(1400, 140);
		glVertex2i(1400, 0);
		glVertex2i(700, 0);
		glEnd();
	
		//left upper
		glBegin(GL_POLYGON);//blue
		glColor3f(0.3, 0.5, 0.9);
		glVertex2f(0, 420);
		glVertex2f(0, 480);
		glVertex2f(585, 480);
		glVertex2f(570, 420);
		glEnd();

		glBegin(GL_POLYGON); //green
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(0, 470);
		glVertex2i(700, 470);
		glVertex2i(700, 550);
		glVertex2i(0, 550);
		glEnd();

		//right upper
		glBegin(GL_POLYGON);//blue
		glColor3f(0.3, 0.5, 0.9);
		glVertex2f(850, 420);
		glVertex2f(890, 480);
		glVertex2f(1400, 480);
		glVertex2f(1400, 420);
		glEnd();

		glBegin(GL_POLYGON); //green
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(850, 470);
		glVertex2i(1400, 470);
		glVertex2i(1400, 550);
		glVertex2i(900, 550);
		glEnd();

	}

	void man()
	{
		glColor3ub(0, 0, 0);  //head
		glPushMatrix();
		glTranslatef(270, 105, 0);
		glutSolidTorus(1, 15, 100, 90);
		glPopMatrix();


		glColor3ub(0, 0, 0); //eyebrows
		glBegin(GL_LINES);
		glVertex2i(270, 107);
		glVertex2i(270, 100);
		glVertex2i(261, 113);
		glVertex2i(267, 113);
		glVertex2i(273, 113);
		glVertex2i(279, 113);
		glEnd();

		glBegin(GL_POLYGON);//eyes
		glVertex2i(263, 111);
		glVertex2i(265, 111);
		glVertex2i(265, 109);
		glVertex2i(263, 109);
		glEnd();

		glBegin(GL_POLYGON); 
		glVertex2i(275, 111);
		glVertex2i(277, 111);
		glVertex2i(277, 109);
		glVertex2i(275, 109);
		glEnd();

		glBegin(GL_POLYGON); //mouth
		glVertex2i(266, 97);
		glVertex2i(270, 95);
		glVertex2i(274, 97);
		glVertex2i(270, 95);
		glEnd();

		glBegin(GL_POLYGON); //body
		glColor3f(0.9, 0.3, 0.7);
		glVertex2i(259, 90);
		glVertex2i(281, 90);
		glVertex2i(296, 79);
		glVertex2i(291, 71);
		glVertex2i(286, 75);
		glVertex2i(286, 55);
		glVertex2i(254, 55);
		glVertex2i(254, 75);
		glVertex2i(249, 70);
		glVertex2i(244, 79);
		glEnd();

		glBegin(GL_POLYGON);  //belt
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(286, 55);
		glVertex2i(254, 55);
		glVertex2i(254, 50);
		glVertex2i(286, 50);
		glEnd();


		glBegin(GL_POLYGON); //right hand
		glColor3ub(255, 191, 128);
		glVertex2i(295, 78);
		glVertex2i(302, 53);
		glVertex2i(297, 54);
		glVertex2i(292, 72);
		glEnd();
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2i(302, 53);
		glVertex2i(297, 54);
		glVertex2i(302, 50);
		glVertex2i(297, 51);
		glEnd();
		
		glBegin(GL_POLYGON); //left hand
		glColor3ub(255, 191, 128);
		glVertex2i(245, 78);
		glVertex2i(238, 53);
		glVertex2i(243, 54);
		glVertex2i(248, 72);
		glEnd();
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2i(238, 53);
		glVertex2i(243, 54);
		glVertex2i(243, 51);
		glVertex2i(238, 50);
		glEnd();
		

		glBegin(GL_POLYGON);
		glColor3ub(200, 140, 110);
		glVertex2i(259, 90);
		glVertex2i(281, 90);
		glVertex2i(276, 80);
		glVertex2i(264, 80);
		glEnd();
		
		
		glBegin(GL_POLYGON); //leg
		glColor3f(0.3, 0.0, 0.0);
		glVertex2i(285, 50);
		glVertex2i(254, 50);
		glVertex2i(250, 15);
		glVertex2i(260, 15);
		glVertex2i(263, 48);
		glVertex2i(280, 15);
		glVertex2i(290, 15);
		glEnd();

		glBegin(GL_QUADS); //leg
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(245, 15);
		glVertex2i(260, 15);
		glVertex2i(260, 8);
		glVertex2i(245, 8);

		glVertex2i(280, 15);
		glVertex2i(295, 15);
		glVertex2i(295, 8);
		glVertex2i(280, 8); 
		glEnd();
	}

	void ambulance()
	{
		glPushMatrix();
		glTranslated(am, 350.0, 0.0); //b1
		glScaled(25.0, 25.0, 0.0);
		//glRotated(90.0, 0.0, 0.0, 0.0);
		glColor3f(1, 1, 1);
		//bus out line
		glBegin(GL_POLYGON);
		glVertex2f(1, 2);
		glVertex2f(1, 7);
		glVertex2f(8, 7);
		glVertex2f(8, 2);
		glEnd();
		
		glBegin(GL_POLYGON);
		glVertex2f(8, 2);
		glVertex2f(8, 6);
		glVertex2f(9.5, 6);
		glVertex2f(10.5, 4);
		glVertex2f(10.5, 2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(10.5, 4);
		glVertex2f(10.5, 2);
		glVertex2f(12, 2);
		glVertex2f(12, 3.5);
		glEnd();

		glColor3f(0.5, 0.5, 0.5); //outline
		glBegin(GL_LINE_LOOP);
		glVertex2f(1, 2);
		glVertex2f(1, 7);
		glVertex2f(8, 7);
		glVertex2f(8, 2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(8, 2);
		glVertex2f(8, 6);
		glVertex2f(9.5, 6);
		glVertex2f(10.5, 4);
		glVertex2f(10.5, 2);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(10.5, 4);
		glVertex2f(10.5, 2);
		glVertex2f(12, 2);
		glVertex2f(12, 3.5);
		glEnd();
		
		
		glColor3f(0, 0, 0.7);
		//window
		glBegin(GL_POLYGON);
		glVertex2f(8.2, 4.2);
		glVertex2f(8.2, 5.8);
		glVertex2f(9.5, 5.8);
		glVertex2f(10.2, 4.2);
		glEnd();
		
		glColor3f(1, 0, 0);
		//red strip
		glBegin(GL_POLYGON);
		glVertex2f(10.5, 4);
		glVertex2f(12, 3.5);
		glVertex2f(12, 3.1);
		glVertex2f(1, 3.1);
		glVertex2f(1, 4);
		glEnd();
		
		glBegin(GL_QUADS); //cross
		glVertex2f(3.25, 5.5);
		glVertex2f(3.25, 6);
		glVertex2f(5.75, 6);
		glVertex2f(5.75, 5.5);
		
		glVertex2f(4.25, 4.5);
		glVertex2f(4.75, 4.5);
		glVertex2f(4.75, 6.75);
		glVertex2f(4.25, 6.75);

		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_QUADS); //front and back black
		glVertex2f(11, 2);
		glVertex2f(12, 2);
		glVertex2f(12, 2.5);
		glVertex2f(11, 2.5);

		glVertex2f(1, 2);
		glVertex2f(2, 2);
		glVertex2f(2, 2.5);
		glVertex2f(1, 2.5);
		glEnd();

		glColor3f(1-light, 1-light, 1-light);
		glBegin(GL_QUADS); //light
		glVertex2f(12, 3.1);
		glVertex2f(12, 2.7);
		glVertex2f(11.5, 2.7);
		glVertex2f(11.5, 3.1);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP); 
		glVertex2f(12, 3.1);
		glVertex2f(12, 2.7);
		glVertex2f(11.5, 2.7);
		glVertex2f(11.5, 3.1);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_QUADS); //top light
		glVertex2f(8.3, 3.6);
		glVertex2f(8.3, 3.8);
		glVertex2f(8.8, 3.8);
		glVertex2f(8.8, 3.6);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_QUADS); //top light
		glVertex2f(8.5, 6);
		glVertex2f(8.5, 6.5);
		glVertex2f(9, 6.5);
		glVertex2f(9, 6);
		glEnd();

		glLineWidth(0.5); //door
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINE_LOOP);
		glVertex2f(6, 2);
		glVertex2f(7.5, 2);
		glVertex2f(7.5, 6);
		glVertex2f(6, 6);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(8.1, 3);
		glVertex2f(8.1, 5.9);
		glVertex2f(9.6, 5.9);
		glVertex2f(10.3, 4.2);
		glVertex2f(10.3, 3);
		glEnd();

		glLineWidth(2); 
		glColor3f(10, 1, 1);
		glBegin(GL_LINES);
		glVertex2f(8, 2);
		glVertex2f(8, 3.1);
		glVertex2f(10.5, 2);
		glVertex2f(10.5,3.1);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);//back tyre
		glTranslated(am+90, 400, 0.0);
		glScaled(40.0, 40.0, 0.0);
		glutSolidSphere(0.5, 360, 360);
		glPopMatrix();
		//front tyre
		glPushMatrix();
		glTranslated(am+245, 400, 0.0);
		glScaled(40.0, 40.0, 0.0);
		glutSolidSphere(0.5, 360, 360);
		glPopMatrix();
	}