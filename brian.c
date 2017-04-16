#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int n=0;
struct arrow
{
	GLint x=250,y=110,r=10;
};

struct arrow a[100];

//int x=250,r=10;
//int y=110;

bool move=false;
void glow_pixel(GLint m,GLint n)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(m,n);
	glEnd();
	glFlush();
}	

void symmetry(GLint h, GLint k, GLint x, GLint y)
{
	glow_pixel(x+h,y+k);
	glow_pixel(-x+h,y+k);
	glow_pixel(x+h,-y+k);
	glow_pixel(-x+h,-y+k);
	glow_pixel(y+h,x+k);
	glow_pixel(-y+h,x+k);
	glow_pixel(y+h,-x+k);
	glow_pixel(-y+h,-x+k);
}								

void circle1(GLint h, GLint k, GLint r)
{
	
	GLint x=0;
	GLint y=r;
	GLint d=1-r;
	

	symmetry(h,k,x,y);
	while(y>x)
	{
		if(d<0)
		{
			d=d+2*x+3;
			++x;
		}
		else
		{
			d=d+2*(x-y)+5;
			++x;
			--y;
		}
		symmetry(h,k,x,y);
	}
} 

void arrow(GLint x, GLint y, GLint x1, GLint y1, GLint r)
{
		y1=y1+70;
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
	    glVertex2f(x,y);
	    glVertex2f(x1,y1);
		glEnd();
		glFlush();
	
	
		GLint h=x,k=y-10;
		GLint x2=0;
		GLint y2=r;
		GLint d=1-r;
	
		symmetry(h,k,x2,y2);	//Symmetric Property.
		while(y2>x2)
		{
			if(d<0)
			{
				d=d+2*x2+3;
				++x2;
			}
			else
			{
				d=d+2*(x2-y2)+5;
				++x2;
				--y2;
			}
			symmetry(h,k,x2,y2);
		}
		
}

void Sprint( int x, int y, char *st)
{
	int l,i;
	l=strlen(st); // see how many characters are in text string.
	glRasterPos2i(x,y); // location to start printing text
	for( i=0; i < l; i++) // loop until i is greater then l
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
	}
}

/*void rotate()
{
	glPushMatrix();
    glTranslatef ( 250,350, 75);  // Moves rotated circle to desired location.
    glRotatef    (10, 0,0,1);
    glTranslatef (-250, -350, 75);  // Centers circle at origin.
    circle1(x, y, r);
	glPopMatrix();
}*/

//static GLfloat theta[] = {0.0, 0.0, 0.0};
//static GLint axis = 2;
void display()
{
	int i = 0;
		
	char str1[]={"Brian Darts"};
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	Sprint(50,450,str1); // Print text to screen
	circle1(250,400,75);				// Function call to draw first Circle.
	//circle2();      		// Function call to draw second Circle.
	//line(250,y,250,y); 	// Function call to draw a line.
	for(i=0;i<2;i++)	arrow(a[i].x,a[i].y,a[i].x,a[i].y,a[i].r);
	//rotate();
	glutPostRedisplay();
	glutSwapBuffers();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);	// Zoom in & Zoom out.
	//glLoadIdentity();
}

void update()
{
	int speed = 1;
	int i=0;
	int j;
	i=n;
		for(j=0;j<(325-71);j++)
		if(a[i].y<325-71)
		{
			if(move == true)
			{
				a[i].y = a[i].y + speed;
			}
		}
	++i;
	n=i;
	move = false;
	
	//arrow(250,110,250,110,10);
	
}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		move = true;
		update();
	}
	
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500,500);			// To initialise the Size of the Window.
	glutInitWindowPosition(0,0);			// To set the position of the Window.
	glutCreateWindow("Brain Darts");				// Function call for Displaying.
	//glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    //glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
	//glutIdleFunc(update);
	myinit();
    //glEnable(GL_DEPTH_TEST);
    //glRotatef(0.0, 1.0, 0.0, 1.0);
	glutMainLoop();
}


