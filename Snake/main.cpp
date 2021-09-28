#define GLUT_DISABLE_ATEXIT_HACK
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <gl/glut.h>

int level = 1;
int points = 0;
int score = 0;
int size = 0;

bool Game_Over = true;
bool finished = false;


// snake all variable
int bodypos[2][100] = {{}};
int x = 5;
int z = 10;
int oldx[2] = {};
int oldz [2] = {};

int direction = 0;

// food varialbes
int fx = 0;
int fz = 0;

// Screen variables
int   width       = 850;
int   height      = 600;
int   iw     = 0;
int   ih     = 0;
int   fw     = 150;
int   fh     = 150;

//Variables for the Camera Angle
static float view_rotation_x = 0.0;
static float view_rotation_y = 0.0;
static float view_rotation_z = 0.0;

static float headRotation = 90.0;
static float zoom = -400.0;

void Write(char *string){  //This function will write the string
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}

// Initialize
void init(void){
    glClearColor(1,0.6,0.3,0);
    glEnable(GL_DEPTH_TEST);
}

//Rotate the object according to the Angles
void ManipulateViewAngle() {
    glRotatef(view_rotation_x, 1.0, 0.0, 0.0); //Rotate with X axis
    glRotatef(view_rotation_y, 0.0, 1.0, 0.0); //Rotate with Y axis
    glRotatef(view_rotation_z, 0.0, 0.0, 1.0); //Rotate with Z axis
}

//Configure window resize
void resize (int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1, 800.0);
}

void Reset(){
    x = 5;
    z = 10;
    direction = 0;
    level = 1;
    points = 0;
    size = 0;
    Game_Over = false;
    finished = false;
    view_rotation_x = 45.0;
    view_rotation_y = 0.0;
    view_rotation_z = 0.0;
    headRotation = 90.0;
}

void DrawSnake(){
    glPushMatrix();
        ManipulateViewAngle();
        glPushMatrix();
            glColor3f(0, 0, 0);
            glTranslatef(75.0, -16.0, 75.0);
            glScalef(155, 5.0, 155);
            glutSolidCube(1);
        glPopMatrix();
        //draw the Head of the snake
        glColor3f(0, 0, 1); //Color it red
        glTranslatef(x, -10.0, z);//Give it the location according to _x & _z
        glScalef(0.5,0.5,0.5);
        glutSolidSphere(12,23,21);//Draw the head as a sphere a litle bit bigger than the body spheres
        glRotatef(headRotation, 0.0, 1.0, 0.0);
        glColor3f(0, 0, 1);
        glTranslatef(0,0.0,6.0);
        glScalef(0.8,1.0,1.0);
        glutSolidCone(10,10,20,20);
        glColor3f(1,1,1);
        glTranslatef(-4.0,10.0,0.0);
        glScalef(0.3,0.3,0.3);
        glutSolidSphere(12,23,21);
        glTranslatef(26.0,0.0,0.0);
        glutSolidSphere(10,20,20);
    glPopMatrix();

    //Draw the body
    for(int i = 0; i < size; i++){
        glPushMatrix();
            ManipulateViewAngle();
            glTranslatef(bodypos[0][i], -12.0, bodypos[1][i]); //locate the spheres
            glColor3f(0, 0, 1);//Color Red
            glScalef(0.5, 0.5, 0.5);
            glutSolidSphere(7, 20, 20);
        glPopMatrix();
    }

}

void DrawFood(){
    glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(fx, -12.0, fz);
        glColor3f(0, 1, 0); // Green food
        glScalef(0.5,0.5,0.5);
        glutSolidSphere(7,20,20);
    glPopMatrix();
}

//Home screen
void HomeScreen(){
    char str[40];
    glRasterPos2f(-20, 20);
    Write(" ~~~~~~ Teserract 4D ~~~~~~ ");
    glRasterPos2f(-65, 3);
    Write(" ~~~~~~~~~~~~ Play Snake Game ~~~~~~~~~~~~ ");
    glRasterPos2f(-60, -15);
    Write(" ~~~~~~ Press 'S' or 's' to Start Playing ~~~~~~ ");

}

void End_Game(){
    char str[40];
    glRasterPos2f(-20, 20);
    Write(" ~~~~~~ Teserract 4D ~~~~~~ ");
    glRasterPos2f(-65, 3);
    Write(" ~~~~~~~~~~~~ End Game ~~~~~~~~~~~~ ");
    glRasterPos2f(-80, -15);
    Write(" ~~~~~~ You Have Finished the game! Congrats ~~~~~~ ");
}

// Highest Score Shows
void highest_Score(){
   FILE *fp;
   int score;


   fp = fopen("highest_Score.txt", "r");
   fscanf(fp, "%d", &score);
   fclose(fp);

   FILE *fp1;

   if ((fp1 = fopen("highest_Score.txt", "r")) == NULL){
        FILE *fp;
        fp = fopen("highest_Score.txt","w");
        fprintf(fp, "%d", 0);
        fclose(fp);
   }

   fclose(fp1);

   if(points > score){
       FILE *fp;
       fp = fopen("highest_Score.txt","w");
       fprintf(fp, "%d", points);
       fclose(fp);
   }

   // print in the Game status Screen
    glColor3f(0.4, 0.2, 0.7); //red
    glRasterPos2f(5, 0);

    char str[10];
    sprintf(str, "Highest Score: %d", score); // store score in the array
    Write(str);
}

void Game_Status(){
    char str[20];
    // Print the status of the game on the screen
    glColor3f(0, 1, 0);
    glRasterPos2f(5, 15);
    sprintf(str, "Level: %d Points: %d", level, points);
    Write(str);
    highest_Score();
}

//Generates random numbers for the food
int Random_Gen(int h, int l){
    return (rand() % (h - l)) + l;
}

//Generate the new food
void Generate_new_Food(){
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    fx = Random_Gen(fw - iw, iw + 10);
    fz = Random_Gen(fh - ih, ih + 10);
}

void Display(void){
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef (-50.0, 50.0, zoom);

    if(finished){
        End_Game();
    }
    else if(!Game_Over){
        Game_Status();
        DrawFood();
        DrawSnake();
    }
    else
        HomeScreen();
    // Updates the screen
    glutPostRedisplay();
    glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'S':
            Reset();
            glutPostRedisplay();
            break;
        case 's'    :
            Reset() ;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

bool collision(){
    for(int i = 0; i < size; i++){
        if((bodypos[0][i] == x && bodypos[1][i] == z) || ((bodypos[0][i] >= x) && (bodypos[0][i] <= x + 5) && (bodypos[1][i] <= z) && (bodypos[1][i] >= z - 5)))
            return true;
    }
   return false;
}

void Run(int value){
    int i;
    oldx[1] = x;
    oldz[1] = z;
    switch(direction){
        case '1':
            headRotation = 0;
            z += 6;
            if(z > fh - 2)
                z = ih - 1;//This will check if the snake is going into the border so it will appear on the other side
            break;

        case '2':
            headRotation = 180;
            z -= 6;
            if(z < 2)
                z = fh - 2;//This will check if the snake is going into the border so it will appear on the other side
            break;

        case '3':
            headRotation = -90;
            x -= 6;
            if(x < 0)
                x = fw - 2;//This will check if the snake is going into the border so it will appear on the other side
            break;

        case '4':
            headRotation = 90;
            x += 6;
            if(x > fw - 2)
                x = iw - 1;//This will check if the snake is going into the border so it will appear on the other side
            break;

    }
    //Checks for Collisoin if yes Game Over
    if(collision())
        Game_Over = true;

    //Checks if the snake ate the food (check the X and Y)
    // If yes it will increase the points & the size of the snake & create a new food
    if((x == fx && z == fz) ||
    ((x >= fx) && (x <= fx + 4) && (z >= fz) && (z <= fz + 4)) ||
    ((x <= fx) && (x >= fx - 4) && (z <= fz) && (z >= fz - 4)) ||
    ((x <= fx) && (x >= fx - 4) && (z >= fz) && (z <= fz + 4)) ||
    ((x >= fx) && (x <= fx + 4) && (z <= fz) && (z >= fz - 4))){
        points++;
        if(points < 100)
            size++;
        if(points > 99){
            finished = true;
        }
        if(points % 5 == 0 && level < 15)
            level++;
        Generate_new_Food();
    }

    for(i = 0; i < size; i++){// Save the positions of the body parts
        oldx[0] = oldx[1];
        oldz[0] = oldz[1];
        oldx[1] = bodypos[0][i];
        oldz[1] = bodypos[1][i];
        bodypos[0][i] = oldx[0];
        bodypos[1][i] = oldz[0];
    }

    //Set the timer
    glutTimerFunc(500, Run, 0);
}

void Special(int key, int x, int y){
    switch(key){
        case GLUT_KEY_RIGHT:
            if(direction != '3')
                direction = '4';
            break;
        case GLUT_KEY_LEFT      :
            if(direction != '4')
                direction = '3';
            break;
        case GLUT_KEY_UP        :
            if(direction != '1')
                direction = '2';
            break;
        case GLUT_KEY_DOWN      :
            if(direction != '2')
                direction = '1';
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(80, 80);
    glutCreateWindow("Snake Game");
    init();
    glutSpecialFunc(Special);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutReshapeFunc(resize);
    Generate_new_Food();
    Run(0);
    glutMainLoop();
}
