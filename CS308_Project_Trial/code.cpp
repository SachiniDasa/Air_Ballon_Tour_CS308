#include <gl\glut.h>
#include <math.h>
#include <SOIL2.h>
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------Camera movement--
//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;
//-----------------------------------------------------------------------------------------------------------------------------
constexpr float pi = 3.14159265358979323846;
int animationFactor = 0;
const int numPoints = 100;
//For the texture image

int width;
int height;
unsigned char* image;
unsigned char* image1;
unsigned char* image2;
unsigned char* image3;
unsigned char* image4;
unsigned char* image5;
unsigned char* image6;
unsigned char* image7;
unsigned char* image8;
unsigned char* image9;

GLuint tex, tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8,tex9;


GLuint textureID1;
GLuint textureID2;
GLuint textureID3;
GLuint textureID4;
GLuint textureID5;

float vertices[][3] = { {1.0,1.0,-1.0},{-1.0,1.0,-1.0},{-1.0,1.0, 1.0},
    {1.0,1.0,1.0},{1.0,-1.0,-1.0},{1.0,-1.0,1.0},
    {-1.0,-1.0,1.0},{-1.0,-1.0,-1.0} ,{0.0,1.0,0.0} };

float roofV[][3] = { {-0.75,0.0,0.75},{0.75,0.0,0.75},{0.75,0.0,-0.75},{-0.75,0.0,-0.75},
                        {0.0,0.5,0.0} };

void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;

    glBegin(GL_LINES);
    for (line = -20; line <= 20; line += step) {
        glVertex3f(line, -0.4, 20);
        glVertex3f(line, -0.4, -20);

        glVertex3f(20, -0.4, line);
        glVertex3f(-20, -0.4, line);
    }
    glEnd();
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);

    glEnd();
}

void Timer(int x) {
    animationFactor++;
    glutPostRedisplay();
    glutTimerFunc(60, Timer, 1);
}
//used  to add texture to grass tile
void loadTexture1() {
    textureID1 = SOIL_load_OGL_texture(
        "grass_tile1.bmp",  // Replace with the path to your texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!textureID1) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
}
//not used
void loadTexture2() {
    textureID2 = SOIL_load_OGL_texture(
        "wooden_Wall2.bmp",  // Replace with the path to your texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!textureID2) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
}
//use to add Texture for water
void loadTexture3() {
    textureID3 = SOIL_load_OGL_texture(
        "river.bmp",  // Replace with the path to your texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!textureID3) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
}

//used to add texture for river
void loadTexture4() {
    textureID4 = SOIL_load_OGL_texture(
        "pond.bmp",  // Replace with the path to your texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!textureID4) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
}
//uesd to add texture for the lamp posts
void loadTexture5() {
    textureID5 = SOIL_load_OGL_texture(
        "lamp_pole.bmp",  // Replace with the path to your texture file
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (!textureID5) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
}
//used to add texture for floor ,wall,ballon,house,
void loadTextures() {
    image = SOIL_load_image("road_floor.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image1 = SOIL_load_image("wooden_wall2.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    image2 = SOIL_load_image("ballon.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    image3 = SOIL_load_image("wooden_wall4.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex3);
    glBindTexture(GL_TEXTURE_2D, tex3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image4 = SOIL_load_image("leaves2.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex4);
    glBindTexture(GL_TEXTURE_2D, tex4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image5 = SOIL_load_image("wooden_wall3.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex5);
    glBindTexture(GL_TEXTURE_2D, tex5);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image6 = SOIL_load_image("river.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex6);
    glBindTexture(GL_TEXTURE_2D, tex6);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image7 = SOIL_load_image("redwood.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex7);
    glBindTexture(GL_TEXTURE_2D, tex7);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image8 = SOIL_load_image("wooden_wall5.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex8);
    glBindTexture(GL_TEXTURE_2D, tex8);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    image9 = SOIL_load_image("ballon1.bmp", &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL) {
        printf("Error : %s", SOIL_last_result());
    }

    glGenTextures(1, &tex9);
    glBindTexture(GL_TEXTURE_2D, tex9);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}

//grid with filled texture
void drawGrid1(int ext1, int ext2) {
    //GLfloat ext=ext;
    GLfloat step = 1.0f;
    GLfloat yGrid = -0.4f;
    GLint line;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_POLYGON);
    for (line = ext1; line <= ext2; line += 5) {
        glTexCoord2f(0, 1); glVertex3f(line, yGrid, ext2);
        glTexCoord2f(1, 1); glVertex3f(line, yGrid, ext1);

        glTexCoord2f(1, 0); glVertex3f(ext2, yGrid, line);
        glTexCoord2f(0, 0); glVertex3f(ext1, yGrid, line);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------------------------------------------------------
//Texture added roof
void triangle(int a, int b, int c)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex1);

    glBegin(GL_POLYGON);
    (0, 0);
    glVertex3fv(roofV[a]);

    glTexCoord2f(1.0, 0);
    glVertex3fv(roofV[b]);

    glTexCoord2f(0.5, 1.0);
    glVertex3fv(roofV[c]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void square(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(roofV[a]);
    glVertex3fv(roofV[b]);
    glVertex3fv(roofV[c]);
    glVertex3fv(roofV[d]);
    glEnd();
}

//Draw a cylinder
void drawCylinder(float radius, float height) {
    float x = 0.0f;
    float z = 0.0f;
    float angle = 0.0;
    float stepSize = 0.1;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBegin(GL_QUAD_STRIP);
    while (angle < 2 * pi) {
        x = radius * cos(angle);
        z = radius * sin(angle);
        glVertex3f(x, 0, z);
        glVertex3f(x, height, z);
        angle += stepSize;
    }
    glVertex3f(radius, 0, 0);
    glVertex3f(radius, height, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
//for ballon
void drawCyl() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);

    gluCylinder(quad, 0.3f, 0.3f, 2.0f, 32, 32);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}
//for the red bridge
void drawCyl1(){
     GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex7);

    gluCylinder(quadric, 0.3f, 0.3f, 2.0f, 32, 32);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadric);
}



//To draw surface of cube
void surface4(int v1, int v2, int v3, int v4) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1); glVertex3fv(vertices[v1]);
    glTexCoord2f(1, 1); glVertex3fv(vertices[v2]);
    glTexCoord2f(1, 0); glVertex3fv(vertices[v3]);
    glTexCoord2f(0, 0); glVertex3fv(vertices[v4]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void surfac4(int v1, int v2, int v3, int v4) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex5);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0); glVertex3fv(vertices[v1]);
    glTexCoord2f(1, 0); glVertex3fv(vertices[v2]);
    glTexCoord2f(1, 1); glVertex3fv(vertices[v3]);
    glTexCoord2f(1, 0); glVertex3fv(vertices[v4]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
//3D Cube  -----corret-without upper surface--
void cube3D() {
    //surface4(0, 1, 2, 3);
    surface4(4, 7, 6, 5);
    surface4(3, 2, 6, 5);
    surface4(0, 1, 7, 4);
    surface4(1, 2, 6, 7);
    surface4(0, 3, 5, 4);
}
//cube -------- correct-with upper surface----
void cube() {
    surfac4(0, 1, 2, 3);
    surfac4(4, 7, 6, 5);
    surfac4(3, 2, 6, 5);
    surfac4(0, 1, 7, 4);
    surfac4(1, 2, 6, 7);
    surfac4(0, 3, 5, 4);
}
//Drawing air ballon
void ballonpart1(double radius1, double radius2, double height) {
    float x1, y = 0.0, z1, x2, z2;
    float angle = 0.0;
    float stepSize = 0.1;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glBegin(GL_QUAD_STRIP);
    while (angle < 2 * pi) {
        x1 = radius1 * cos(angle);
        x2 = radius2 * cos(angle);
        z1 = radius1 * sin(angle);
        z2 = radius2 * sin(angle);

        // Calculate texture coordinates based on the angle
        float s1 = angle / (2 * pi);
        float s2 = s1;
        // Assign texture coordinates to the vertices
        glTexCoord2f(s1, 1.0);
        glVertex3f(x1, y, z1);

        glTexCoord2f(s2, 0.0);
        glVertex3f(x2, y + height, z2);

        angle += stepSize;
    }
    // Last two points
    glTexCoord2f(1.0, 0.0);
    glVertex3f(radius1, 0, 0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(radius2, height, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void drawTexturedSphere(float radius, int slices, int stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    gluSphere(quadric, radius, slices, stacks);

    gluDeleteQuadric(quadric);
}
void drawBallon() {
    glPushMatrix();
    glTranslatef(0.0, 6, 0.0);

    // Draw the textured sphere
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex2);
    drawTexturedSphere(6, 20, 20); // Assuming drawTexturedSphere is a function to draw a textured sphere
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    // Draw other parts of the balloon
    glPushMatrix();
    glTranslatef(0, 0, -animationFactor / 20);
    glTranslatef(0.0, 13, 0.0);
    glScalef(0.48, 0.48, 0.48);
    ballonpart1(3, 5, 4);
    glPopMatrix();
}


void getAirBallonLines() {
    glPushMatrix();
    glTranslatef(14, 15,-8);
    glRotatef(90, 1, 0, 0);
    glScalef(0.1, 9, 0.1);
    drawCyl();
    glTranslatef(-29, 0, 0);
    drawCyl();
    glTranslatef(0, -29, 0);
    drawCyl();
    glTranslatef(29, 0, 0);
    drawCyl();
    glPopMatrix();
}

void drawAirBallon() {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0, 0, -animationFactor / 20);
    glTranslatef(0, 14, 0);
    glScalef(0.5, 0.5, 0.5);
    drawBallon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -animationFactor / 20);
    glTranslatef(0, 10, 0);
    glScalef(1.5, 1.5, 1.5);
    cube3D();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -animationFactor / 20);
    glTranslatef(1.25, 13, -1.25);
    glRotatef(90, 0, 1, 0);
    glScalef(0.1, 9, 0.1);
    drawCyl();
    glTranslatef(-29, 0, 0);
    drawCyl();
    glTranslatef(0, 0, -29);
    drawCyl();
    glTranslatef(29, 0, 0);
    drawCyl();
    glPopMatrix();
    glPopMatrix();
}
//Draw tree
void Circle(float radius1) {
    //glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 64; i++) {
        float theta = 2.0f * pi * float(i) / float(64);
        float x = radius1 * cos(theta);
        float y = radius1 * sin(theta);
        glVertex2f(x, y);
    }
}

//texture for trunck for cone
void drawTrunk() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex3);

    gluCylinder(quad, 0.3f, 0.3f, 2.0f, 32, 32);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

void getFullCylinder(float radius, float height) {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glPushMatrix();
    drawCylinder(radius, height);
    glDisable(GL_TEXTURE_2D);
    glRotated(90, 1, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);
    Circle(radius);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    Circle(radius);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

//texture for leaves for cone
void drawleaves() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex4);

    gluCylinder(quad, 0.7f, 0.0f, 3.0f, 32, 32);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

//draw one tree
void trees() {
    //glPushMatrix();
    glPushMatrix();
    glTranslatef(-10, 3, 0);
    glRotatef(90, -1, 0, 0);
    drawleaves();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-10, 3,0);
    glRotatef(90, 1, 0, 0);
    drawTrunk();
    glPopMatrix();
    //glPopMatrix();
}

//draw bunch of trees
void moreTrees() {

    glPushMatrix();
    glScalef(1.5, 1.5, 1.5);
    //glTranslatef(0,0, 0);
    trees();
    glScalef(2, 2, 2);
    glTranslatef(2, 0, 2);
    trees();
    glPushMatrix();
    glTranslatef(-2, 0, 0);
    trees();
    glScalef(1, 1, 1);
    glTranslatef(-2, 0, 0);
    trees();
    glTranslatef(0, 0, -2);
    trees();
    glTranslatef(1, 0, -2);
    trees();
    glPopMatrix();
    glPopMatrix();

}

//--------------------------------------------------------------------------------------------------

//draw the floor of the building
void buildingFloor() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex8);
    glPushMatrix();
    glScaled(3.0, 0.2, 3.0);
    cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void drawHouse() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex8);
    glPushMatrix();
    glTranslatef(1, 1.7, 0);
    glScaled(2.0, 2, 2.0);
    cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void roof()
{
    square(0, 1, 2, 3);
    triangle(0, 1, 4);
    triangle(1, 2, 4);
    triangle(2, 4, 3);
    triangle(0, 3, 4);
}

void roofScaled() {
    glPushMatrix();
    glTranslatef(1, 3.0, 0);
    glScalef(4, 4, 4);
    roof();
    glPopMatrix();
}
void housepills() {
    glPushMatrix();
    glTranslatef(2, 3, 2.7);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.5, 2);
    drawCyl();
    glPushMatrix();
    glTranslatef(-7, 0, 0);
    drawCyl();
    glTranslatef(0, -4, 0);
    drawCyl();
    glTranslatef(0, -4, 0);
    drawCyl();

    glPopMatrix();
    glPopMatrix();

}
void groundHouse() {
    buildingFloor();
    drawHouse();
    roofScaled();
    housepills();
}
//-------------------------------------Not ok--------------

void twostorehouse() {
    glPushMatrix();
    //glScalef(0, 1, 0);
    buildingFloor();
    drawHouse();
    housepills();
    glTranslatef(0, 4, 0);
    groundHouse();
    glPopMatrix();

}

//---------------------------------------------------------------------Checked -Ok-------------
//draw grass on the floor
void drawGrass() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID1);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, -10.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
//MORE grass
void moreGrass() {
    glPushMatrix();
    glTranslated(10, 0, 0);
    drawGrass();
    glTranslated(0, 0, 20);
    drawGrass();
    glTranslated(10, 0, 0);
    drawGrass();
    glTranslated(10, 0, 0);
    drawGrass();
    glTranslated(0, 0, 20);
    drawGrass();
    glPopMatrix();
}

//--------------------------------------------------------------------------draw the bridge --------NOT WORKING-

//--------------------------end testing------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//---------------------------draw pond--------------------ok
void drawDisk(double radius,int n ) {
    double angle = 0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID3);
    glBegin(GL_POLYGON);
    for (int c = 0;c <= n;c++) {
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glTexCoord2d((x + 1) / 2, (y + 1) / 2);
        glVertex3d(x, y, 0);
        angle = angle + ((2 * pi) / n);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void drawStone(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.5f, 0.5f, 0.5f); 
    glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}

void drawPond(float centerX, float centerY, float radius, int numStones) {
    for (int i = 0; i < numStones; ++i) {
        float angle = 2.0f * pi * i / numStones;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        drawStone(x, y);
    }
}


//add river---------------------------------------ok
void drawRiver() {
        // Define points along the path of the river
    float riverPoints[numPoints][3];

        // Define the river points using a loop
   for (int i = 0; i < numPoints; ++i) {
            float t = (float)i / (numPoints - 1); // Parameter for interpolation (0 to 1)
            float x = -10.0f + t * 20.0f; // Interpolate x-coordinate along the river
            float y = 2.0f * sin(2.0f * pi * t); // Sine wave for y-coordinate
            riverPoints[i][0] = x+1;
            riverPoints[i][1] = y;
            riverPoints[i][2] = 0.0f;
    }

        // Draw the river using triangle strips
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureID4);
   glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < numPoints - 1; ++i) {
            glTexCoord2f((float)i / (numPoints - 1), 0.0f); 
            glVertex3fv(riverPoints[i]);

            glTexCoord2f((float)i / (numPoints - 1), 1.0f); 
            glVertex3f(riverPoints[i][0], -1.0f, riverPoints[i][2]);

            glTexCoord2f((float)(i + 1) / (numPoints - 1), 0.0f); 
            glVertex3fv(riverPoints[i + 1]);

            glTexCoord2f((float)(i + 1) / (numPoints - 1), 1.0f); 
            glVertex3f(riverPoints[i + 1][0], -1.0f, riverPoints[i + 1][2]);
        
        }
        glEnd();
   glDisable(GL_TEXTURE_2D);
 }


//draw lamps--------------------------------------------------------------------------------------------
void drawpost(int v1,int v2,int v3,int v4) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID5);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1); glVertex3fv(vertices[v1]);
    glTexCoord2f(1, 1); glVertex3fv(vertices[v2]);
    glTexCoord2f(1, 0); glVertex3fv(vertices[v3]);
    glTexCoord2f(0, 0); glVertex3fv(vertices[v4]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawPole() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID5);

    gluCylinder(quad, 0.2f, 0.2f, 4.0f, 32, 32);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

void drawLight() {

    cube();
}
void drawLamp() {
    glPushMatrix();
    glTranslatef(0,-1,0);
    drawpost(0, 1, 2, 3);
    glTranslatef(2,2,12);
    glRotatef(90, 1, 0, 0);
    glScalef(4, 4, 4);
    drawPole();
    glPopMatrix();

   // glPushMatrix();
    //glTranslatef()
    //glScalef(0.3, 0.3, 0.3);
    //drawPole();
    //glPopMatrix();

    //glPushMatrix();
    //glTranslatef();
    //glScalef(0.3, 0.3, 0.3);
    //roofScaled();
    //glPopMatrix();


}


//-------------------------------------------------------------code templete

void init(void) {
    glClearColor(0.19, 0.6, 0.8, 1.0);
    glClearDepth(1.0);
    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    //glPopMatrix();
    loadTextures();
}

void setLighting() {

    // Lighting set up
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);

    // Set lighting intensity and color - light 0
    GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position - light 0
    GLfloat qaLightPosition[] = { -10.0, 1.0, -2, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    // Set lighting intensity and color - light 1
    GLfloat qaAmbientLight1[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat qaDiffuseLight1[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat qaSpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);

    // Set the light position - light 1
    GLfloat qaLightPosition1[] = { 10.0, 1.0, -2, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

    GLfloat SpecRef[] = { 0.7,0.7,0.7,1.0 };
    GLint Shine = 128;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);//Tell OpenGL that material properties are defined by glColor*()
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//Set Ambient and Diffuse to the color defined by glColor*()
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);//Set specular reflectivity and shininess
    glMateriali(GL_FRONT, GL_SHININESS, Shine);
}

void animate(int value) {
    glutPostRedisplay();
    glutTimerFunc(15, animate, 1);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0, 5.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // move the scene (all the rendered environment) using keyboard keys
    glTranslatef(sceTX, sceTY, sceTZ);
    glRotatef(sceRY, 0.0, 1.0, 0.0);

    setLighting();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    //----------------------------------------Draw the floor
    glPushMatrix();
    drawGrid1(-80, 80);
    glPopMatrix();
    //glScalef(0.2, 0.2, 0.2);
    // --------------------------------------Draw grass tiles-----------
    glPushMatrix();
    moreGrass();
    glTranslated(0, 0, -40);
    moreGrass();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-80, 0, 0);
    moreGrass();
    glTranslated(0, 0, -40);
    moreGrass();
    glTranslated(10, 0, 0);
    glRotatef(90,0,1,0);
    moreGrass();
    glTranslated(0,0, 40);
    moreGrass();
    glTranslated(0, 0, 40);
    moreGrass();
    glTranslated(-20, 0, 70);
    glRotatef(90, 0, 1, 0);
    moreGrass();
    glTranslated(0, 0, -40);
    moreGrass();
    glTranslated(0, 0, -40);
    moreGrass();
    glTranslated(10, 0, 20);
    glRotatef(90, 0, 1, 0);
    moreGrass();
    glTranslated(0, 0, 40);
    moreGrass();
    glTranslated(0, 0, 40);
    moreGrass();
    glTranslated(0, 0, 20);
    moreGrass();
    glPopMatrix();

    //---------------------------draw Lamp------------------testing---------
    //glPushMatrix();
    //drawLamp();
    //glPopMatrix();
    //--------------------------------Draw river  ---------------------- working with ballon
    glPushMatrix();
    glTranslatef(0, 0.3, 12);
    glRotatef(90,1,0,0);
    drawRiver();
    glTranslatef(-10, 0,0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glTranslatef(-10, 0, 0);
    drawRiver();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10, 0.3,12 );
    glRotatef(90, 1, 0, 0);
    drawRiver();
    glTranslatef(10, 0,0);
    drawRiver();
    glTranslatef(10, 0, 0);
    drawRiver();
    glTranslatef(10, 0, 0);
    drawRiver();
    glTranslatef(10, 0, 0);
    drawRiver();
    glTranslatef(10, 0, 0);
    drawRiver();
    glTranslatef(10, 0, 0);
    drawRiver();
    glPopMatrix();
    // ------------------------------------------ Draw Tree   --Working with ballon 
    //glPushMatrix();
    glPushMatrix();
    trees();
    glPopMatrix();
    //glTranslatef(2, 0, 0);
    //trees();
    glTranslatef(2, 0, 0);
    trees();
    glTranslatef(0, 0, 2);
    trees();
    glTranslatef(0, -2, 0);
    trees();
    glTranslatef(0, 2, 2);
    trees();
    glTranslatef(0, -2, 0);
    trees();
    glTranslatef(0, 2, 2);
    trees();
    glTranslatef(0, -2, 0);
    trees();
    glTranslatef(0, 2, 2);
    trees();
    glTranslatef(0, 0, 8);
    trees();
    glTranslatef(0, 0, 2);
    trees();
    glTranslatef(0, 0, 2);
    trees();
    //glTranslatef(0, 0, 2);
    //trees();

    //moreTrees();
    //------------------------------------------------Draw Pond------ working with ballon
    glPushMatrix();
    glTranslated(-15, 0, -10);
    glRotatef(90, 1.0, 0.0, 0.0);
    drawPond(-10, -10, 8, 64);
    glPopMatrix();
    glPushMatrix();
    glTranslated(-25,0.1,-20);
    glRotatef(90, 1.0, 0.0, 0.0);
    drawDisk(8, 32);
    glPopMatrix();
    //--------------------------------------two store house------------
    //glPushMatrix();
    //glScalef(0, 1, 0);
    //buildingFloor();
    //drawHouse();
    //housepills();
    //glPushMatrix();
    //glTranslatef(0, 0, 0);
    //groundHouse();
    //glPopMatrix();
    //---------------------------------------Draw Buildings  -- gound house  --working  with ballon
    //glPushMatrix();
    //glTranslatef(8, 0, 0);
    groundHouse();
    glTranslatef(10, 0, 0);
    groundHouse();
    glTranslatef(0, 0, -15);
    groundHouse();
    glTranslatef(30, 0, 0);
    groundHouse();
    glTranslatef(-30, 0, -15);
    groundHouse();
    glTranslatef(-40, 0, 0);
    groundHouse();
    glTranslatef(40,0,30);
    groundHouse();
    glTranslatef(0, 0, 15);
    groundHouse();
    //groundHouse();
    glTranslatef(10, 0, 0);
    groundHouse();
    glTranslatef(-80, 0, 0);
    groundHouse();
    glTranslatef(0, 0, 30);
    groundHouse();
    //glPopMatrix();

    //-------------------------------------- -- twostorehouse  ---not working  with ballon
    //glPushMatrix();
    //glTranslatef(0, -24, 0);
    //twostorehouse();
    //glPopMatrix();
    //-----------------------------------------  --- Draw the ballon---------
    glPushMatrix();
   // glTranslatef(animationFactor / 100, 0, 0);
    drawAirBallon();
    glPopMatrix();
    animationFactor++;
    //-----------------------------------------------------------------------
    glPopMatrix();
    glutSwapBuffers();
}

//--------------------------------------------------------------------------------------------------------

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 1;

    if (key == GLUT_KEY_DOWN)
        camY -= 1;

    if (key == GLUT_KEY_RIGHT)
        sceTX += 1;

    if (key == GLUT_KEY_LEFT)
        sceTX -= 1;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'l')
        objRY += 1;

    if (key == 'r')
        objRY -= 1;

    if (key == 'Z')
        sceTZ += 1;

    if (key == 'z')
        sceTZ -= 1;

    if (key == 'w')
        sceTX += 1;

    if (key == 's')
        sceTX -= 1;

    if (key == 'y')
        sceRY += 1;

    if (key == 'Y')
        sceRY -= 1;

    if (key == 'L')

        glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    if (key == '@')
        glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glutPostRedisplay();
}


int main(void) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Air ballon tour");
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    loadTexture1();
    loadTexture3();
    loadTexture4();
    loadTexture5();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(15,animate,1);
    init();
    glutMainLoop();
    return 0;
}
