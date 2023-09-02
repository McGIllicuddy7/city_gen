#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include "generator.h"
#include <stdio.h>
#include <string.h>
char cityName[1000];
void tick(void){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3b(1,1,1);
    renderGrid();
    glutPostRedisplay();
    glFlush();
}
void KeyboardHandler(unsigned char c, int x, int y){
    if(c == 27){
        save_city(cityName);
        exit(0);
    }
    if(c == 'h'){
        flipShouldShow();
    }
}
int main(int argc, char ** argv){
    char buff[100];
    memset(buff, '\0',100);
    printf("enter land type(water_north 0, water_south 1,water_east 2, water_west 3, river_north_south 4, river_east_west 5, island 6, inland 7or 8 to load): ");
    fgets(buff, 100, stdin);
    int t = atoi(buff);
    if(t != 8){
        memset(buff, '\0',100);
        printf("enter city size(village 0, small_town 1, medium_town 2, large_town 3, small_city 4, medium_city 5, large_city 6): ");
        fgets(buff, 100, stdin);
        int s = atoi(buff);
        printf("enter city name: ");
        fgets(cityName, 1000, stdin);
        generateCity(t,s, false);
    }
    else{         
        printf("enter city name: ");
        fgets(cityName, 1000, stdin);
        load_city(cityName);
    }
    printf("number buildings: %d\n", getNumBuildings());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900,900);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Map");
    glutDisplayFunc(tick);
    glutKeyboardFunc(KeyboardHandler);
    glutMainLoop();
}