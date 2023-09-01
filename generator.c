#define GL_SILENCE_DEPRECATION
#include "generator.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geography.h"
square grid[gsz];
building_t buildings[10000];
int num_buildings;
building_t * get_buildings(){
    return buildings;
}
void setNumBuildings(int value){
    num_buildings = value;
}
int getNumBuildings(){
    return num_buildings;
}
void drawRectangle(float x, float y, float height, float width, unsigned char r, unsigned char g, unsigned char b){
    glBegin(GL_TRIANGLES);
    glColor3b(r,g,b);
    glVertex2d(x, y);
    glVertex2d(x, y+height);
    glVertex2d(x+width, y+height);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3b(r,g,b);
    glVertex2d(x, y);
    glVertex2d(x+width, y);
    glVertex2d(x+width, y+height);
    glEnd();
}
typedef struct{
    float x;
    float y;
}float2;
void standardDrawRectangle(int x, int y, int height, int width, unsigned char r, unsigned char g,unsigned char b){
    float x1 = (((float)x)/900)*2-1;
    float y1 = (((float)y)/900)*2-1;
    float h = ((float)height)/450;
    float w = ((float)width)/450;
    drawRectangle(x1,y1,h,w, r,g,b);
}
void renderGrid(void){
    for(int y = 0; y<sz; y++){
        for(int x = 0; x<sz; x++){
            square sq = grid[y*sz+x]; 
            //printf("%d, ", sq);
            if(sq == ground_grass){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz,25,127,35);
            }
            else if(sq ==ground_forest){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 0,60,0);
            }
            else if(sq == water){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 0,0,127);
            }
            else{
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 90,45,0);
            }
        }
        //exit(0);
    }
    for(int x =0; x<sz; x++){
        standardDrawRectangle(x*900/sz,0,900, 1,0,0,0);
    }
    for(int y = 0; y<= sz; y++){
        standardDrawRectangle(0,y*900/sz,1,900,0,0,0);
    }
}
void generateCity(land_type land, city_size size){
    calcGeography(grid, land);
}