#include "geography.h"
#include <stdio.h>
#include "iutils.h"
#include <limits.h>
#define north 0
#define south 1
#define east 2
#define west 3
static inline double randDouble(){
    int x= (RandomInt()%4096);
    x = x-2048;
    double y = x;
    return y/2048;
}
void createRoad(square * grid, bool ns,int start){
    double x_direction,y_direction;
    if(ns){
        x_direction = 0;
        y_direction =1;
    }
    else{
        x_direction =1;
        y_direction = 0;
    }
    double x,y;
    if(ns){
        x = start;
        y = 0;
    }
    else{
        y = start;
        x = 0;
    }
    for(int i = 0; i<sz; i++){
        if(x<0||y<0 ||x>sz || y>sz){
            return;
        }
        grid[(int)round(y)*sz+(int)round(x)] = street;
        x+=x_direction;
        y+=y_direction;
        if(abs(round(x+x_direction)-round(x)>=1) && abs(round(y+y_direction)-round(y)>=1)){
            if(fabs(x_direction)>fabs(y_direction)){
                grid[(int)round(y+y_direction)*sz+(int)round(x)] = street;
            }
            else{
                grid[(int)round(y)*sz+(int)round(x+x_direction)] = street;
            }
            
        }
        if(RandomInt()%100<25){
            x_direction += randDouble()/2;
            y_direction += randDouble()/2;
            y_direction = y_direction/sqrt(x_direction*x_direction+y_direction*y_direction);
            x_direction = x_direction/sqrt(x_direction*x_direction+y_direction*y_direction);
        }
        if(x<0||y<0 ||x>sz || y>sz){
            return;
        }
    }
}
void createRiver(square * grid, bool ns){
    int offset = sz/2;
    for(int i = 0; i<sz; i++){
        if(ns){
            grid[i*sz+offset+1] = water;
            grid[i*sz+offset] = water;
            grid[i*sz+offset-1] = water;
        }
        else{
            grid[(offset+1)*sz+i] = water;
            grid[offset*sz+i] = water;
            grid[(offset-1)*sz+i] = water;
        }
        offset += RandomInt()%3-1;
        if(offset>sz-1){
            offset = sz-1; 
        }
        else if(offset<1){
            offset =1;
        }
    }
}

void create_coastline(square * grid, int direction){
    int offset = RandomInt()%5+5;
    for(int i = -1; i<=sz; i++){
        for(int k = 0; k<offset; k++){
            if(direction == north){
                grid[(sz-k)*sz+i] = water;
            }
            else if(direction == south){
                grid[k*sz+i] = water;
            }
            else if(direction == east){
                grid[i*sz+(sz-k)] =water;
            }
            else if(direction == west){
                grid[i*sz+k] = water;
            }
        }
        offset += RandomInt()%3-1;
        if(offset<10){
            offset =10;
        }
        if(offset > 30){
            offset = 30;
        }
    }
}

void calcGeography(square * grid, land_type t){
    int s = 25;
    for(int i = 0; i<s; i++){
        if(RandomInt()%100<100){
            createRoad(grid, true, i*sz/s);
        }
    }
    for(int i = 0; i<s; i++){
        if(RandomInt()%100<100){
            createRoad(grid, false, i*sz/s);
        }
    }
    if(t ==water_north){
         create_coastline(grid, north);
    }
    else if(t ==water_south){
         create_coastline(grid, south);
    }
    else if(t ==water_west){
         create_coastline(grid, west);
    }
    else if(t == water_east){
        create_coastline(grid, east);
    }
    else if(t == island){
        create_coastline(grid, north);
        create_coastline(grid, south);
        create_coastline(grid, east);
        create_coastline(grid, west);
    }
    else if(t == river_east_west){
        createRiver(grid, false);
    }
    else if(t == river_north_south){
        createRiver(grid, true);
    }
}
static void drawCircle(square * grid, int x, int y, int rad){
    for(int x1 = 0; x1<sz; x1++){
        for(int y1 = 0; y1<sz; y1++){
            int d = sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
            if(d<=rad){
                if(RandomInt()%10<9){
                    if(grid[y*sz+x] != water){
                        grid[y*sz+x] = ground_forest;
                    }
                }
            }
        }
    }
}
void prettifyGeography(square * grid){
    for(int i = 0; i<1000; i++){
        drawCircle(grid, RandomInt()%sz, RandomInt()%sz, RandomInt()%5+4);
    }
}