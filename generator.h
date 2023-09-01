#pragma once
typedef enum {
    ground_grass = 0, ground_forest = 1, water = 2, street = 3
} square;
#define sz 100
#define gsz 10000
typedef struct{
    
} building_t;
void renderGrid(void);

typedef enum{
    water_north, water_south, water_east, water_west, river_north_south, river_east_west, island,
}land_type;
typedef enum{
    village, small_town, medium_town, large_town, small_city, medium_city, large_city
}city_size;
void generateCity(land_type land, city_size size);