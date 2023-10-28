#include <stdlib.h>
#ifdef __linux__
#include <Raylib/raylib.h>
#endif
#ifndef __linux__
#include <raylib.h>
#endif
#include "generator.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
char cityName[1000];
RenderTexture2D map;
void tick(void){
    BeginTextureMode(map);
    renderGrid();
    EndTextureMode();
    BeginDrawing();
    ClearBackground(CLITERAL(Color){0,0,0,255});
    DrawTextureEx(map.texture, CLITERAL(Vector2){0,0}, 0,(float)swidth/(float)width,WHITE);
    EndDrawing();
}
bool h_down = false;
void KeyboardHandler(){
    if(IsKeyDown(KEY_ESCAPE)){
        CloseWindow();
    }
    if(IsKeyDown(KEY_H)){
        if(!h_down){
            flipShouldShow();
        }
        h_down = true;
    }
    else{
        h_down = false;
    }
}
int main(int argc, char ** argv){
    char buff[100];
    SetTraceLogLevel(LOG_ERROR);  
    memset(buff, '\0',100);
    printf("enter land type(water_north 0, water_south 1,water_east 2, water_west 3, river_north_south 4, river_east_west 5, island 6, inland 7 or 8 to load): ");
    fgets(buff, 100, stdin);
    int t = atoi(buff);
    if(t != 8){
        memset(buff, '\0',100);
        printf("enter city size(village 0, small_town 1, medium_town 2, large_town 3, small_city 4, medium_city 5, large_city 6): ");
        fgets(buff, 100, stdin);
        int s = atoi(buff);
        memset(buff, '\0',100);
        printf("enter walled(t,f): ");
        fgets(buff, 100, stdin);
        printf("enter city name: ");
        fgets(cityName, 1000, stdin);
        generateCity(t,s, buff[0] == 't');
    }
    else{         
        printf("enter city name: ");
        fgets(cityName, 1000, stdin);
        load_city(cityName);
    }
    printf("number buildings: %d\n", getNumBuildings());
    InitWindow(swidth,swidth, cityName);
    map = LoadRenderTexture(width,width);
    while(!WindowShouldClose()){
        KeyboardHandler();
        tick();
    }
    save_city(cityName, map);
}
