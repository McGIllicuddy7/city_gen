#define GL_SILENCE_DEPRECATION
#include "generator.h"
#ifdef __linux__
#include <GL/gl.h>
#include <GL/freeglut.h>
#endif
#ifdef __osx__
#include <OPENGL/gl.h>
#include <GLUT/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "geography.h"
#include "buildings.h"
square grid[gsz];
building_t buildings[10000] = {450, 450, 0};
int num_buildings = 0;
bool shouldShow = true;
int interestingIndices[100] = {-1};
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
    glColor3f((float)r/127,(float)g/127,(float)b/127);
    glVertex2d(x, y);
    glVertex2d(x, y+height);
    glVertex2d(x+width, y+height);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f((float)r/127,(float)g/127,(float)b/127);
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
void displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen( string );
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i] );
    }
}
void renderGrid(void){
    for(int y = 0; y<sz; y++){
        for(int x = 0; x<sz; x++){
            square sq = grid[y*sz+x]; 
            //printf("%d, ", sq);
            if(sq == ground_grass){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz,0,60,0);
            }
            else if(sq ==ground_forest){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 25,45,5);
            }
            else if(sq == water){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 0,0,127);
            }
            else if(sq == wall){
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz, 0,0,0);
            }
            else{
                standardDrawRectangle(x*900/sz, y*900/sz, 900/sz, 900/sz,45,45,45);
            }
        }
    }
    for(int i = 0; i<num_buildings; i++){
        standardDrawRectangle(buildings[i].x+1, buildings[i].y+1, 7, 7,40, 20, 0);
    }
    for(int x =0; x<sz; x++){
        standardDrawRectangle(x*900/sz,0,900, 1,0,0,0);
    }
    for(int y = 0; y<= sz; y++){
        standardDrawRectangle(0,y*900/sz,1,900,0,0,0);
    }
    if(!shouldShow){
        return;
    }
    for(int i =0; i<num_buildings; i++){
        char buff[100];
        sprintf(buff,"%d", i);
        float x = buildings[i].x+5;
        float y = buildings[i].y+5;
        displayText(x/450-1, y/450-1, 125,125,125, buff);
    }
}
void recalculateLocations(){
    //exit(0);
    int indices[gsz] = {-1};
    for(int i = 0; i<gsz; i++){
        indices[i] = -1;
    }
    for(int i = 0; i<num_buildings; i++){
        indices[(sz*sz-(buildings[i].y*sz/900*sz))+buildings[i].x*sz/900] = i;
    }
    building_t nbuildings[10000];
    int c = 0;
    for(int i = 0; i<gsz; i++){
        if(indices[i]>-1){
            nbuildings[c] = buildings[indices[i]];
            c++;
        }
    }
    for(int i =0 ; i<num_buildings; i++){
        buildings[i] = nbuildings[i];
    }
}
void generateCity(land_type land, city_size size, bool walled){
    long t = time(0);
    calcGeography(grid, land);
    printf("geography done %ld seconds\n", time(0)-t);
    t = time(0);
    GenerateBuildings(grid, size);
    printf("buidlings done %ld seconds\n", time(0)-t);
    t = time(0);
    if(walled){
        GenerateWalls(grid);
    }
    remove_streets(grid);
    recalculateLocations();
    prettifyGeography(grid);
    printf("streets done %ld seconds\n", time(0)-t);
}
void save_city(char * name){
    char buffer[1000] = "output/";
    int l = strlen(name);
    int d = strlen(buffer);
    for(int i = 0; i<l-1; i++){
        buffer[i+d] = name[i];
    }
    l = strlen(buffer);
    buffer[l] = '.';
    buffer[l+1] = 'b';
    buffer[l+2] = 'i';
    buffer[l+3] = 'n';
    FILE * file = fopen(buffer, "wb");
    fwrite(grid, sizeof(square),gsz, file);
    fwrite(&num_buildings,sizeof(int), 1, file);
    fwrite(buildings,sizeof(building_t), num_buildings, file);
    fclose(file);
}
void load_city(char * name){
    char buffer[1000] = "output/";
    int l = strlen(name);
    int d = strlen(buffer);
    for(int i = 0; i<l-1; i++){
        buffer[i+d] = name[i];
    }
    l = strlen(buffer);
    buffer[l] = '.';
    buffer[l+1] = 'b';
    buffer[l+2] = 'i';
    buffer[l+3] = 'n';
    FILE * file = fopen(buffer, "rb");
    if(!file){
        fprintf(stderr, "failed to find city: %s", name);
    }
    fread(grid, sizeof(square),gsz, file);
    fread(&num_buildings,sizeof(int), 1, file);
    fread(buildings,sizeof(building_t), num_buildings, file);
    fclose(file);
}
void flipShouldShow(){
    shouldShow= !shouldShow;
}