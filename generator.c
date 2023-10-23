#define GL_SILENCE_DEPRECATION
#include <Raylib/raylib.h>
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "geography.h"
#include "buildings.h"
square grid[gsz];
building_t buildings[10000] = {width, width, 0};
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
void renderGrid(void){
    for(int y = 0; y<sz; y++){
        for(int x = 0; x<sz; x++){
            square sq = grid[y*sz+x]; 
            //printf("%d, ", sq);
            if(sq == ground_grass){
                DrawRectangle(x*width/sz, y*width/sz, width/sz, width/sz,(Color){0,60,0,255});
            }
            else if(sq ==ground_forest){
                DrawRectangle(x*width/sz, y*width/sz, width/sz, width/sz, (Color){25,45,5,255});
            }
            else if(sq == water){
                DrawRectangle(x*width/sz, y*width/sz, width/sz, width/sz, (Color){0,0,127,255});
            }
            else if(sq == wall){
                DrawRectangle(x*width/sz, y*width/sz, width/sz, width/sz, (Color){0,0,0,255});
            }
            else{
                DrawRectangle(x*width/sz, y*width/sz, width/sz, width/sz,(Color){45,45,45,255});
            }
        }
    }
    for(int i = 0; i<num_buildings; i++){
        DrawRectangle(buildings[i].x+1, buildings[i].y+1, width/sz-1, width/sz-1,(Color){40, 20, 0,255});
    }
    for(int x =0; x<sz; x++){
        DrawRectangle(x*width/sz,0,width,1, (Color){1,0,0,255});
    }
    for(int y = 0; y<= sz; y++){
        DrawRectangle(0,y*width/sz,1,width,(Color){0,0,0,255});
    }
    if(!shouldShow){
        return;
    }
    for(int i =0; i<num_buildings; i++){
        char buff[100];
        sprintf(buff,"%d", i);
        float x = buildings[i].x+5;
        float y = buildings[i].y+5;
        DrawText(buff, x-3, y-3,1,WHITE);
    }
}
void recalculateLocations(){
    //exit(0);
    int indices[gsz] = {-1};
    for(int i = 0; i<gsz; i++){
        indices[i] = -1;
    }
    for(int i = 0; i<num_buildings; i++){
        indices[(sz*sz-(buildings[i].y*sz/width*sz))+buildings[i].x*sz/width] = i;
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
    RenderTexture2D map = LoadRenderTexture(width,width);
    BeginTextureMode(map);
    renderGrid();
    EndTextureMode();
    buffer[l+1] = 'p';
    buffer[l+2] = 'n';
    buffer[l+3] = 'g';
    Image img = LoadImageFromTexture(map.texture);
    ImageFlipVertical(&img);
    ExportImage(img,buffer);
    UnloadImage(img);
    UnloadRenderTexture(map);
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
