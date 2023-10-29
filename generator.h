#pragma once

#include <stdbool.h>
#ifdef __linux__
#include <Raylib/raylib.h>
#endif
#ifndef __linux__
#include <raylib.h>
#endif

#define width 4000
#ifdef __linux__
#define swidth 2000
#endif
#ifndef __linux__
#define swidth 1000
#endif
typedef enum {
    ground_grass = 0, ground_forest = 1, water = 2, street = 3, wall = 4
} square;
#define sz 200
#define gsz 40000
#define MAX_INTERESTING 2000
typedef struct{
    int x;
    int y;
    char type;
} building_t;
void renderGrid(void);
building_t * get_buildings();
void setNumBuildings(int value);
int getNumBuildings();
typedef enum{
    water_north, water_south, water_east, water_west, river_north_south, river_east_west, island,inland
}land_type;
typedef enum{
    village, small_town, medium_town, large_town, small_city, medium_city, large_city
}city_size;
void generateCity(land_type land, city_size size, bool walled);
void flipShouldShow();
void save_city(char * name,RenderTexture2D Map);
void load_city(char * name);
