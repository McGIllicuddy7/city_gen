#include "buildings.h"
#include "iutils.h"
#include <math.h>
#include <stdio.h>
int population = 0;
bool building_locs[gsz];
int num_times_called = 0;
void addBuildingAtGridSpaceCoord(int x, int y){
    building_t * b = get_buildings();
    int x1 = x*width/sz;
    int y1 = y*width/sz;
    b[getNumBuildings()] = (building_t){x1, y1, 0};
    setNumBuildings(getNumBuildings()+1);
    building_locs[y*sz+x] = false;
    num_times_called++;
}
typedef struct {
    int x; 
    int y;
} int2;
typedef struct{
    int2 * vals;
    int length;
} int2Array_t;
int int2Distance(int2 a, int2 b){
    int x = a.x - b.x;
    int y = a.y-b.y;
    return round(sqrt(x*x+y*y));
}
#define gridGet(x,y) grid[y*sz+x]

bool gridCheck(int x, int y){
    return building_locs[y*sz+x];
    int n = getNumBuildings();
    building_t * b = get_buildings();
    building_t b1;
    for(int i = 0; i<n; i++){
        b1 = b[i];
        if((b1.x == x) && (b1.y == y) ){
            return false;
        }
    }
    return true ||building_locs[y*sz+x];
}
int2 calcCityCenterMass(){
    int2 out = {0,0};
    if(getNumBuildings() == 0){
        return (int2){sz/2, sz/2};
    }
    for(int i = 0; i<getNumBuildings(); i++){
        out.x += (get_buildings())[i].x;
        out.y += (get_buildings())[i].y;
    }
    out.x = out.x/getNumBuildings();
    out.y = out.y/getNumBuildings();
    return out;
}
int max_distance_pop(int pop){ 
    if(pop<100){
        return 6;
    }
    else if(pop<200){
        return 12;
    }
    else if(pop<500){
        return 17;
    }
    else if(pop<1000){
        return 20;
    }
    else if(pop<2000){
        return 30;
    }
    else if(pop<4000){
        return 40;
    }
    else if(pop<8000){
        return 60;
    }
    else{
        return 55;
    }
}
int2Array_t calcSuitablePositions(square * grid, int pop){
    int2Array_t out;
    out.length = 0;
    out.vals = malloc(10000*sizeof(int2));
    for(int y = 1; y<sz-1; y++){
        for(int x = 1; x<sz-1; x++){
            if(gridGet(x,y) != water && gridGet(x,y) != street){
                if(gridGet(x+1,y) == street || gridGet(x, (y+1)) == street || gridGet(x-1, y) == street || gridGet(x, (y-1)) == street){
                    if(int2Distance((int2){sz/2,sz/2}, (int2){x,y})<=max_distance_pop(pop)){
                        if(gridCheck(x,y)){
                            out.vals[out.length] = (int2){x,y};
                            out.length++;
                        }
                    }
                }
            }
        }
    }
    return out;
}
int2 calcLocation(int2Array_t arr){
    int2 out = arr.vals[RandomInt()%arr.length];
    return out;
}
void GenerateBuildings(square * grid, city_size size){
    int max_population = 0;
    int pop = 0;
    for(int i = 0; i<gsz; i++){building_locs[i] = true;}
    if(size == village){
        max_population = RandomIntInRange(100, 250);
    }
    else if(size ==  small_town){
        max_population = RandomIntInRange(250, 500);
    }
    else if(size == medium_town){
        max_population = RandomIntInRange(500, 1000);
    }
    else if(size == large_town){
        max_population = RandomIntInRange(1000, 2000);
    }
    else if(size == small_city){
        max_population = RandomIntInRange(2000, 4000);
    }
    else if(size == medium_city){
        max_population = RandomIntInRange(4000, 8000);
    }
    else{
        max_population = RandomIntInRange(8000, 16000);
    }
    printf("max population: %d\n", max_population);
    while(true){
        int2Array_t poses =  calcSuitablePositions(grid,pop);
        if(poses.length<1){
            free(poses.vals);
            break;
        }
        int2 position = calcLocation(poses);
        addBuildingAtGridSpaceCoord(position.x, position.y);
        pop+=4;
        if(pop>=max_population){
            free(poses.vals);
            break;
        }
        free(poses.vals);
    }
    population = pop;
}
void remove_streets(square * grid){
    for(int y = 0; y<sz; y++){
        for(int x= 0; x<sz; x++){
            if(gridGet(x,y) == street){
                gridGet(x,y) = ground_grass;
            }
        }
    }
}
void GenerateWalls(square * grid){
    int d = max_distance_pop(population)+1;
    for(int y = 0; y<sz; y++){
        for(int x= 0; x<sz; x++){
            float distance = (sqrt((x-sz/2)*(x-sz/2)+(y-sz/2)*(y-sz/2)));
            if(false){
                if(gridGet(x,y) == ground_grass){
                    gridGet(x,y) = wall;
                }
            }
        }
    }
}
