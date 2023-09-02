#include "buildings.h"
#include <iutils.h>
#include <stdio.h>

void addBuildingAtGridSpaceCoord(int x, int y){
    building_t * b = get_buildings();
    int x1 = x*900/sz;
    int y1 = y*900/sz;
    b[getNumBuildings()] = (building_t){x1, y1, 0};
    setNumBuildings(getNumBuildings()+1);
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
    int len = getNumBuildings();
    for(int i = 0; i<len; i++){
        if(((get_buildings())[i].x == x) && ((get_buildings())[i].y == y)){
            return false;
        }
    }
    return true;
}
int2 calcCityCenterMass(){
    int2 out = {0,0};
    if(getNumBuildings() == 0){
        return (int2){37, 37};
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
    pop+=1;
    return 4*sqrt(sqrt(pop));
}
int2Array_t calcSuitablePositions(square * grid, int pop){
    int2Array_t out;
    out.length = 0;
    out.vals = malloc(10000*sizeof(int2));
    for(int y = 1; y<sz-1; y++){
        for(int x = 1; x<sz-1; x++){
            if(gridGet(x,y) != water && gridGet(x,y) != street){
                if(gridGet(x+1,y) == street || gridGet(x, (y+1)) == street || gridGet(x-1, y) == street || gridGet(x, (y-1)) == street){
                    if(gridCheck(x,y)){
                        if(int2Distance((int2){37,37}, (int2){x,y})<=max_distance_pop(pop)){
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
    while(true){
        int2Array_t poses =  calcSuitablePositions(grid,pop);
        if(poses.length<1){
            free(poses.vals);
            break;
        }
        int2 position = calcLocation(poses);
        addBuildingAtGridSpaceCoord(position.x, position.y);
        pop+=1;
        if(pop>=max_population){
            free(poses.vals);
            break;
        }
        free(poses.vals);
    }
    for(int y = 0; y<sz; y++){
        for(int x= 0; x<sz; x++){
            int d = max_distance_pop(pop)+1;
            if(int2Distance((int2){x,y}, calcCityCenterMass())>d){
                if(gridGet(x,y) == street){
                    gridGet(x,y) = ground_grass;
                }
            }
        }
    }
}