#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <gl/glut.h>
#define pi (2*acos(0.0))
#define GL_SILENCE_DEPRECATION
#include<stdlib.h>
#include<stdio.h>

double incx=0, incy;
int state;

struct point
{
	double x,y,z;
};

struct point pos,l,u;
double X=0,Z=0;
int Y=-1;
int check=0;
struct point arra[100];
float objx=0,objy=1.8,basx=0,basy=-1.95,dropx=0,dropy=1.94;
float ran,p=0.00,speed=0.0001;

int score=0,level=1;

float s1x=1.05,s1y=-2.1,s2x=1.84,s2y=-2.1;
float l1x=-1.95,l1y=-2.1,l2x=-1.55,l2y=-2.1;

float sty=-1,f=0,q=0.00,z=1;

void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2.2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}
void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f(1,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void just_line() // create the basket
{
     //BLUE LINE 3f=3



    glLineWidth(6);

    glBegin(GL_LINES); // It can be any type Gl_POINT,_LINE
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2d(-0.30,0.5); //d=double
        glVertex2d(-0.30,0.0);

        glVertex2d(-0.30,0.0);
        glVertex2d(0.30,0.0);

        glVertex2d(0.30,0.0);
        glVertex2d(0.30,0.5); //d=double


    glEnd();

}
 void higest_score() // update higest score
{

   FILE *fptr1; //file pointer
   int num;


   fptr1 = fopen("Higest_score.txt","r"); // read from text and store in num
   fscanf(fptr1,"%d", &num);
   fclose(fptr1); // closed

  // printf("%d",num);


   FILE *fp;

   if ((fp= fopen("Higest_score.txt","r")) == NULL)  // create a text file
   {

       FILE *fptr;
       fptr = fopen("Higest_score.txt","w");
       fprintf(fptr,"%d",0);  // write zero
       fclose(fptr);
   }

   fclose(fp);

   if(score > num) //
   {
       FILE *fptr;
       fptr = fopen("Higest_score.txt","w");
       fprintf(fptr,"%d",score);
       fclose(fptr);
   }

   // print in the game over screen
     char msg1[]="Higest Score ";
      glColor3f(1,1,0); //yellow
    glRasterPos3f(-.55,0.0,0);
    for(int k=0;k<strlen(msg1);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[k]);
    }

    char str[10];
    sprintf(str, "%d", num); // store score in the array
    glColor3f(1,0,0); //red
    glRasterPos3f(0.35,0.0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[0]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[1]);





}

void s_quad()
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(1.0f, 0.0f, 0.0f);
         glVertex2d(-0.30,p); //p= box full
        //glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2d(-0.30,0.0);
        //glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2d(0.30,0.0);
        //glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2d(0.30,p);
    glEnd();

}
void s_quad1() // menu box
{
    glBegin(GL_QUADS); // DRAWING 4 SIDED QUADRILATERAL
        glColor3f(1.0f, 0.0f, 0.0f);
         glVertex2d(-0.30,q);
        //glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2d(-0.30,0.0);
        //glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2d(0.30,0.0);
        //glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2d(0.30,q);
    glEnd();

}


void showscore()
{
    glColor3f(1,1,0); //yellow
    glRasterPos3f(s1x,s1y,0);

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'M');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'y');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'S');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'c');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'o');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'r');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'=');

    char str[10];
    sprintf(str, "%d", score);

    glColor3f(1,0,0);
    glRasterPos3f(s2x,s2y,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[0]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[1]);


}

void showlevel()
{
    glColor3f(1,1,0);
    glRasterPos3f(l1x,l1y,0);

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'L');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'v');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'l');


    char str[10];
    sprintf(str, "%d", level);

    glColor3f(1,0,0);
    glRasterPos3f(l2x,l2y,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[0]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[1]);



}

void restart_msg_show()
{
    char msg4[]="press      to restart the game ";
     glColor3f(0,1,0);
    glRasterPos3f(-.9,0.9,0);
    for(int k=0;k<strlen(msg4);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg4[k]);
    }

    char msg5[]="R";
     glColor3f(1,0.1,0);
    glRasterPos3f(-0.5,.9,0);
    for(int k=0;k<strlen(msg5);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg5[k]);
    }
}

void all_msg()
{
     char msg1[]="press     to start the game ";
     glColor3f(0,1,0);
    glRasterPos3f(-.8,0.1,0);
    for(int k=0;k<strlen(msg1);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg1[k]);
    }

    char msg2[]="S";
     glColor3f(1,0.1,0);
    glRasterPos3f(-0.4,0.1,0);
    for(int k=0;k<strlen(msg2);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,msg2[k]);
    }


    char title[]="Catch The Ball";
     glColor3f(1,1,0);
    glRasterPos3f(-0.55,-1.7,0);
    for(int k=0;k<strlen(title);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,title[k]);
    }

    char title1[]="-----------";
     glColor3f(1,1,0);
    glRasterPos3f(-0.55,-1.8,0);
    for(int k=0;k<strlen(title1);k++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,title1[k]);
    }


}

void starting_menu()
{
     // create new display

    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2,2,-2.2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);

    // for animation
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();



    all_msg();

     if(sty>=-1 && f==0)
    {
         if(sty>=-1 && sty<=-.3)
         {
             sty+=.0005;
             f=0;

         }
         else
         {
            z=z+1;
            if(z==5.00)
            {
                z=0;
               q=.0;
            }

            f=1;
         }

    }
    if(f == 1)
    {
       if(sty <= -1)
       {
           q += .1;
           f = 0;
       }
       else
        {

           sty-=.0005;
        }
    }



    glPushMatrix();
    glTranslatef(0, sty, 0);
    glColor3f(1, 0, 0);
    drawSphere(0.2, 25, 25);  // ball
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, -1.3, 0);
    just_line();
    s_quad1();
    glPopMatrix();




    glutSwapBuffers();
    glutPostRedisplay();
}

void Game()
{


//printf("\n\n");


    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // for animation

    showscore();
    showlevel();
   // glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[1]);



    if (objy<-1.8 && (objx<basx-0.3 || objx>basx+0.3))  // check game over
    {
       check=1;
       //printf("final score=%d",score);
       //p=0.03;
       // speed=0.02;
       s1x = -.5,s1y=.5,s2x=.28,s2y=.5;
       l1x=-.3,l1y=.3,l2x=.09,l2y=.3;
       higest_score();
       restart_msg_show();

    }

    if (check==0)
    {
      objy-=speed;
    }


    if(objy<-1.85)
    {
       ran=((float(rand()) / float(RAND_MAX)) * (1.8 - (-1.8))) + (-1.8);
       objy=1.8;
       objx=ran;
       dropx=ran;
       p+=.1;
       score+=1;
       //printf("score=%d",score);
       if(score==5)
       {
         level+=1;
         p=0.0;
         speed=speed+0.001;
       }
       if(score==10)
       {
         level+=1;
         p=0.0;
         speed=speed+0.001;
       }
       if(score==15)
       {
         level+=1;
         p=0.0;
         speed=speed+0.001;
       }
       if(score==20)
       {
         level+=1;
         p=0.0;
         speed=speed+0.002;
       }
       if(score==25)
       {
         level+=1;
         p=0.0;
         speed=speed+0.002;
       }
       if(score==30)
       {
         level+=1;
         p=0.0;
         speed=speed+0.002;
       }
       if(score==35)
       {
         level+=1;
         p=0.0;
         speed=speed+0.002;
       }
    }



    glPushMatrix();
    glTranslatef(objx,objy, 0);
    glColor3f(1, 0, 0);
    drawSphere(0.2, 25, 25);  // main ball
    glPopMatrix();


    glPushMatrix();
    glTranslatef(dropx,dropy, 0);
    glScalef(1.5, 0.4, 1);
    drawSphere(0.2, 50, 25);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(basx, basy, 0);
    just_line();
    s_quad();
    glPopMatrix();


    glutSwapBuffers();
    glutPostRedisplay();


}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			break;
		case GLUT_KEY_UP:
		    	//glutDisplayFunc(display);	// up arrow key
			break;

		case GLUT_KEY_RIGHT:
		    if(check != 1)
            {
               if (basx < 1.6)
		       basx += 0.2;
            }

		   // printf("%f",basx);
			break;
		case GLUT_KEY_LEFT:
             if(check != 1)
            {
		    if (basx >- 1.41)
		    basx -= 0.2;
            }

			break;


		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		     if(check == 1)
            {
		   // glutDisplayFunc(starting_menu);
            }


			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':
        // code animating
        break;
    case 'r':
        check=0;

        objx = 0,objy = 1.8, basx = 0, basy = -1.95,dropx = 0,dropy = 1.94;
        ran,p=0.00,speed=0.002;

        score=0,level=1;

        s1x=1.05,s1y=-2.1,s2x=1.8,s2y=-2.1;
        l1x=-1.95,l1y=-2.1,l2x=-1.55,l2y=-2.1;

        break;
    case 's':
        check=0;

        objx=0,objy=1.8,basx=0,basy=-1.95,dropx=0,dropy=1.94;
        ran,p=0.00,speed=0.002;

        score=0,level=1;

        s1x=1.05,s1y=-2.1,s2x=1.8,s2y=-2.1;
        l1x=-1.95,l1y=-2.1,l2x=-1.55,l2y=-2.1;
        glutDisplayFunc(Game);

        break;
    case 'g':

        break;
    case 'w':

        break;

    default:
        break;
    }
}


int main(int argc,char **argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(600, 550);
    glutCreateWindow("Catch the ball");
    init();
    //glutDisplayFunc(display);
    glutDisplayFunc(starting_menu);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(keyboardListener);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
