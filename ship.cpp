/*
 * TragicCruise.c
 *
 *  Created on: 14 November 2016
 *      Author: Pushkar, Abhinav and Rydel
 *    compile using  g++ ship.cpp -lGL -lGLU -lglut
 */

#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<GL/freeglut.h>
#include<time.h>
#include<bits/stdc++.h>
#define WIDTH 768
#define HEIGHT 1024
using namespace std;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3f;

const vec3f _FONT_SIZE_NORMAL = {0.5f, 0.5f, 1.0f};
const vec3f _FONT_SIZE_BIG = {1.0f, 1.0f, 1.0f};
const vec3f _FONT_SIZE_SMALL = {0.25f, 0.25f, 1.0f};

const vec3f *FONT_SIZE_NORMAL = &_FONT_SIZE_NORMAL;
const vec3f *FONT_SIZE_BIG = &_FONT_SIZE_BIG;
const vec3f *FONT_SIZE_SMALL = &_FONT_SIZE_SMALL;

 struct timespec tim, tim2;
void sun();
void ice();
void sky();
void display();
void display0();
void display1();
void display2();
void display3();
void display4();
void ship(int, double);
void rescueShip(int, double);
void drawStickMan();
void water();

vector<pair<int, int> > starpoints;
bool KEY_PRESSED = false;
GLint a=0,b=0,c=120,d=0, z = 1200,e=0,f=0,g=500,h=600,x=0,i=0;
float p = 0, q=0, r=0;
//a = initial ship position
//b = second screen ship position
//c  = crash position

GLfloat theta=0.0;

void initVariables()
{
    a=0,b=0,c=120,d=0, p = 0,q = 0, r=0,z = 1200,e=0,f=0,g=500,h=600,x=0,i=0;
}
void normalKeys(unsigned char key, int x, int y) {
    switch (key) {
       case 27:    // ESC key
               exit(EXIT_SUCCESS);
        case 13:    // Enter key
            {
                initVariables();
                KEY_PRESSED = true;
            }
            break;

        default:
            break;
    }
}

void drawStrokeText(std::string text, int x, int y, int z, const vec3f *fontSize) {

    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(fontSize->x, fontSize->y, fontSize->z);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char const *) text.c_str());

    glPopMatrix();
}

void update(int value)
{
    a+=20.0;
    e-=10;
    p-=0.01;
    q-=0.01;
    glutPostRedisplay();
    glutTimerFunc(200,update,0);                //speed of ship 200
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    display0();
    if(KEY_PRESSED == true)
    display1();         //DRAW SHIP IN INITIAL POSITION AND WATER


    if(a>950 && KEY_PRESSED == true)            //SHIFT TO NEW SCREEN
    {
        b+=20;
        display2();
    }
    if(b==180 && KEY_PRESSED == true)
    {
        tim.tv_sec = 1.5;                            //crash pause time
        tim.tv_nsec = 500000000L;
//        nanosleep(&tim , &tim2);
    }
    if(b>180 && KEY_PRESSED == true)
    {
        c+=10;
        display3();

    }
    if(c>700 && KEY_PRESSED == true)
    {
        z-=20;
        display4();
    }
    if(z <-100 && KEY_PRESSED == true)
        exit(EXIT_SUCCESS);

    glFlush();
    glutSwapBuffers();
}
void display0() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glLineWidth(3);
    glColor3f(0.0,0.0,1.0);
    drawStrokeText("The Last Cruise", WIDTH/3, HEIGHT/2, 0, FONT_SIZE_NORMAL);

    glLineWidth(1);
    drawStrokeText("PRESS ENTER TO START", WIDTH/2.5, HEIGHT/2.5, 0, FONT_SIZE_SMALL);
    drawStrokeText("Press Esc to Quit", WIDTH/2.5, HEIGHT/3.4, 0, FONT_SIZE_SMALL);
    drawStrokeText("By:\n\tRYDEL DCOSTA - IIT2014047\n\tPUSHKAR JAIN - IIT2014039 \n\tABHINAV PRAKASH - IIT2014046\n\t",
     WIDTH/2, HEIGHT/7, 0, FONT_SIZE_SMALL);

}
void display4()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f,0.18f,0.2f,1.0f);
    sky();

    glPushMatrix();
    glTranslated(z,75,0.0);
    rescueShip(1, 1);                                //1 = night
    glPopMatrix();
    water();
}
void display1()
{


    glClearColor(1.0f + q,0.6f + p,0.0f,1.0f);
    //startScreen();
    glPushMatrix();
    glTranslated(0,e,0.0);
    sun();
    glPopMatrix();
    glPushMatrix();
    glTranslated(a,75,0.0);
    ship(0, 2);                        //0 = day
    glPopMatrix();
    water();
}

void display2()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f,0.18f,0.2f,1.0f);
    sky();

    ice();
    glPushMatrix();
    glTranslated(b,75,0.0);
    ship(1, 2);                                //1 = night
    glPopMatrix();
    water();

}

void display3()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f,0.18f,0.2f,1.0f);
    x-=1;                    //slope of sinking ship

    //stars();
    sky();
    ice();
    glPushMatrix();
    glTranslated(c,100+x*5,0.0);        //sinking ship axis
    glRotated(-15,0,0,1);
    ship(1,2);
    glPopMatrix();
    water();


}

/* DRAW WATER */
void water()
{

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(1000,0);
        glVertex2f(1000,100);
        glVertex2f(0,100);
    glEnd();
}

void drawRailing(vector<double> xx, vector<double> yy, double inc, double col)
{
    glColor3f(col, col, col);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<6;i++)
        {
            glVertex2f(xx[i] + inc, yy[i]);
        }

    glEnd();
}

void drawStickMan()
{
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f( 0.0f,  0.0f, 0.0f);
            int cx1 = 6, cy1 = 11, r1 = 1, num_segments=1000;
            for (int ii = 0; ii < num_segments; ii++)
            {
                float alpha = 2.0f * 3.1415926f * float(ii) / float(num_segments); ///get the current angle
                float x = r1 * cosf(alpha); ///calculate the x component
                float y = r1 * sinf(alpha); ///calculate the y component
                glVertex2f(x + cx1, y + cy1); ///output vertex
            }
            glEnd();
            /// Player's Face Boundary
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_POLYGON);
            glColor3f( 0.96f,  0.80f, 0.69f);
            cx1 = 6, cy1 = 11, r1 = 1, num_segments=1000;
            for (int ii = 0; ii < num_segments; ii++)
            {
                float alpha = 2.0f * 3.1415926f * float(ii) / float(num_segments); ///get the current angle
                float x = (r1-0.1) * cosf(alpha); ///calculate the x component
                float y = (r1-0.1) * sinf(alpha); ///calculate the y component
                glVertex2f(x + cx1, y + cy1); ///output vertex
            }
            glEnd();

        glColor3f(0.0,0.0,0.0);
            /// Player's Hand
            glBegin(GL_LINES);
            glVertex2f(5,8);
                    glVertex2f(6,10);
            glEnd();

                       glBegin(GL_LINES);
                    glVertex2f(6,10);
                        glVertex2f(7,8);
            glEnd();
            //playerbody
            glBegin(GL_LINES);
            glVertex2f(6,10);
            glVertex2f(6,6.5);
            glEnd();

            //playerrightleg
            glBegin(GL_LINES);
            glVertex2f(5,5.5);
            glVertex2f(6,6.5);
            glEnd();

            glBegin(GL_LINES);
            glVertex2f(6,6.5);
            glVertex2f(7,5.5);
            glEnd();

}
void drawWindows(vector<double> xx, vector<double> yy, double inc, int flag)
{
    if(flag == 0)
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0,1.0,1.0);
    }
    else
    {
        glColor3f(1,1,0);
            glBegin(GL_POLYGON);
    }
        for(int i=0;i<4;i++)
        {
            glVertex2f(xx[i] + inc, yy[i]);
        }

    glEnd();
}

void drawDeck(double x, double y)
{
    glColor3f(0.69,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+1.5);
        glVertex2f(x+14,y+1.5);
        glVertex2f(x+14,y);
    glEnd();
}
void drawChimney(double x, double y)
{
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x,y);
        glVertex2f(x,y+3);
        glVertex2f(x+1.5,y+3);
        glVertex2f(x + 1.5, y);
    glEnd();
    glColor3f(0.545, 0.271, 0.075);                //brown
    glBegin(GL_POLYGON);
        glVertex2f(x,y+3);
        glVertex2f(x,y+3.5);
        glVertex2f(x+1.5,y+3.5);
        glVertex2f(x+1.5,y+3);
    glEnd();
}
//rescue ship
void rescueShip(int flag, double scale)
{


    glScaled(10*scale,10*scale, 0);
    //ship base
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(1,5.5);
        glVertex2f(4,1);
        glVertex2f(19,1);
        glVertex2f(21.5,5.5);
    glEnd();
    //door
    glColor3f(0.545, 0.271, 0.075);
    glBegin(GL_POLYGON);
        glVertex2f(4,5.5);
        glVertex2f(4,8);
        glVertex2f(5,8);
        glVertex2f(5,5.5);
    glEnd();
    //light
    glColor4f(1, 1, 0.0, 0.5);
    glBegin(GL_POLYGON);
        glVertex2f(4,7.5);
        glVertex2f(4,8);
        glVertex2f(-7,1);
        glVertex2f(-3,1);
    glEnd();

    drawStickMan();
    //railing down
    vector<double> xx,yy;
    xx.push_back(1.5);
    xx.push_back(1.5);
    xx.push_back(2);
    xx.push_back(3);
    xx.push_back(3.5);
    xx.push_back(3.5);

    yy.push_back(5.5);
    yy.push_back(6.5);
    yy.push_back(6.2);
    yy.push_back(6.2);
    yy.push_back(6.5);
    yy.push_back(5.5);
    for(int i=0;i<10; i++)
    {
        drawRailing(xx, yy, i*2, 0);
    }
}
/* TO DRAW SHIP */
void ship(int flag, double scale)
{


    glScaled(10*scale,10*scale, 0);
    //ship mid
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
        glVertex2f(3.5,5.5);
        glVertex2f(3.5,8.5);
        glVertex2f(19.5,8.5);
        glVertex2f(19.5,5.5);
    glEnd();
    //ship base
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(1,5.5);
        glVertex2f(4,1);
        glVertex2f(19,1);
        glVertex2f(21.5,5.5);
    glEnd();
    //door
    glColor3f(0.545, 0.271, 0.075);
    glBegin(GL_POLYGON);
        glVertex2f(4,5.5);
        glVertex2f(4,8);
        glVertex2f(5,8);
        glVertex2f(5,5.5);
    glEnd();
    //upper windows
    if(flag == 0)
        glColor3f(0.9,0.9,0.9);
    else
        glColor3f(1, 1, 0);

    glBegin(GL_POLYGON);
        glVertex2f(7,7.5);
        glVertex2f(7,8);
        glVertex2f(10,8);
        glVertex2f(10,7.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(11.5,7.5);
        glVertex2f(11.5,8);
        glVertex2f(15,8);
        glVertex2f(15,7.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(16,7.5);
        glVertex2f(16,8);
        glVertex2f(19,8);
        glVertex2f(19,7.5);
    glEnd();
//upper deck

    drawDeck(4.5, 8.5);

    double x = 5.5,y=10;

    for(int i=0; i<4; i++)
    {
        drawChimney(x + i*3, y);
    }

    //railing down
    vector<double> xx,yy;
    xx.push_back(1.5);
    xx.push_back(1.5);
    xx.push_back(2);
    xx.push_back(3);
    xx.push_back(3.5);
    xx.push_back(3.5);

    yy.push_back(5.5);
    yy.push_back(6.5);
    yy.push_back(6.2);
    yy.push_back(6.2);
    yy.push_back(6.5);
    yy.push_back(5.5);
    for(int i=0;i<10; i++)
    {
        drawRailing(xx, yy, i*2, 0);
    }
    //window coordinates
    xx.clear();
    yy.clear();
    xx.push_back(4.5);
    xx.push_back(4.5);
    xx.push_back(5.5);
    xx.push_back(5.5);

    yy.push_back(3.5);
    yy.push_back(4.5);
    yy.push_back(4.5);
    yy.push_back(3.5);

    for(int i=0;i<6; i++)
    {

        drawWindows(xx, yy, i*2.5, flag);
    }
    //upper railing
    xx.clear();
    yy.clear();
    xx.push_back(5);
    xx.push_back(5);
    xx.push_back(5.5);
    xx.push_back(6.5);
    xx.push_back(7);
    xx.push_back(7);

    yy.push_back(10);
    yy.push_back(11);
    yy.push_back(10.8);
    yy.push_back(10.8);
    yy.push_back(11);
    yy.push_back(10);
    for(int i=0;i<6; i++)
    {
        drawRailing(xx, yy, i*2, 0.1);
    }

}
void sun()
{
    glPushMatrix();
    glTranslated(700, 500,0.0);
    float cx = 100, cy = 100, r = 50;

int num_segments = 100;

glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0, 1.0, 0);

glBegin(GL_TRIANGLE_FAN);

for(int ii = 0; ii < num_segments; ii++)

{

float theta = 2.0f * 3.1415926f * float(ii) /

float(num_segments);//get the current angle

float x = r * cosf(theta);//calculate the x

float y = r * sinf(theta);//calculate the y
glVertex2f(x + cx, y + cy);//output vertex

}
glEnd();

glPopMatrix();

}
void sky()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //moon
    glPushMatrix();
    glTranslated(700, 500,0.0);
    float cx = 100, cy = 100, r = 50;

int num_segments = 100;

//glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0, 1.0, 1.0);

glBegin(GL_TRIANGLE_FAN);

for(int ii = 0; ii < num_segments; ii++)

{

float theta = 2.0f * 3.1415926f * float(ii) /

float(num_segments);//get the current angle

float x = r * cosf(theta);//calculate the x

float y = r * sinf(theta);//calculate the y
glVertex2f(x + cx, y + cy);//output vertex

}
glEnd();

glPopMatrix();



//stars
for(int i=0;i<10;i++) {

    float tx = (rand()%950) + 10, ty = 450 + rand()%400, R = 2;

glColor3f(1.0, 1.0, 1.0);

glBegin(GL_TRIANGLE_FAN);

for(int ii = 0; ii < num_segments; ii++)

{

float theta2 = 2.0f * 3.1415926f * float(ii) /

float(num_segments);//get the current angle

float x = R * cosf(theta2);//calculate the x

float y = R * sinf(theta2);//calculate the y
glVertex2f(x + tx, y + ty);//output vertex


}
glEnd();
//glPopMatrix();

}


}

/* TO DRAW ICEBERG */
void ice()
{
    glPushMatrix();
    glTranslated(450,50,0.0);
    glScaled(10,10,0);
    glColor3f(0.0,1.0,1.0);
    if(c>120)
    {
        //ice after crash
        glPushMatrix();
        glTranslated(0,x,0);            //sinking iceberg

        glPushMatrix();
        glTranslated(7,2,0.0);             //translate + rotate - translate about base of iceberg
        glRotated(-x,0,0,1);
        glTranslated(-7,-2,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(7,2);
        glVertex2f(8,3);
        glVertex2f(11,18);
        glVertex2f(12,19);
        glVertex2f(12,3);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(12,3,0.0);
        glRotated(x,0,0,1);
        glTranslated(-12,-3,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(12,3);
        glVertex2f(12,19);
        glVertex2f(17,18);
        glVertex2f(18,3);
        glVertex2f(19,3);
        glEnd();
        glPopMatrix();

        glPopMatrix();
    }
    else
    {
        //iceberg before crash
        glBegin(GL_POLYGON);
            glVertex2f(7,2);
            glVertex2f(8,3);
            glVertex2f(11,18);
            glVertex2f(12,19);
            glVertex2f(12,3);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(12,3);
            glVertex2f(12,19);
            glVertex2f(17,18);
            glVertex2f(18,3);
            glVertex2f(19,3);
            glEnd();
    }


    glPopMatrix();

}



void myinit()
{
    glClearColor(1,1,1,1);                //background    night = glClearColor(0.2f,0.18f,0.2f,1.0f);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glutKeyboardFunc(normalKeys);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,999.0,0.0,799.0);
}

int main(int argc, char* argv[])

{
    int key=0;

    printf("project by\n\t Pushkar, Rydel and Abhinav \n");
    printf("press 1 to start\npress 0 to quit\n");
    scanf("%d",&key);
    if(key==0) return 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024.0,768.0);

    glutInitWindowPosition(0,0);
    glutCreateWindow("The Last Cruise");
    glutDisplayFunc(display);
    myinit();
    glutTimerFunc(100,update,0);
    glutMainLoop();
    return 0;
}

