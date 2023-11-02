#include "data.h"
#include "generator.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <assert.h>
#include "iutils.h"
static int icount = 0;
extern char cityName[1000];
int spinNewProcess(char **args){
    int pid = fork();
    if(pid == 0){
        int v = execvp(args[0], args);
    }
    else{
        waitpid(-1,NULL, 0);
    }
    return 0;
}
typedef enum{
    House,Cobbler, Tailor,Barber,Jewelers, Tavern, Bakers,Butchers, Masons,Weavers, WineSellers, Hatmakers,Saddlers, Woodsellers,MagicShop, 
    BookBinders, FishMongers, BeerSellers,BuckleMakers, Plasterers, SpiceMerchants,Blacksmiths,Painters,Doctors,Roofers,Locksmiths,
    Ropemakers,Inn,Copyists,Tanners,Glovemakers,Bookseller,GaurdHouse,Alchemists, buildings_size
}building_e;
const int thresholds[] = {0, 150, 250, 350, 400, 405, 800, 1000, 500, 600, 900, 950, 1005, 2400, 2800,3000,1200, 1400, 1405, 1410, 1420, 1505, 1510,1800, 1900, 1905, 2000, 2005,2010,2015,2405, 6300,605,2500};
int needs[buildings_size] = {0};
building_e calculate_next(int population){
    for(int i = 1; i<buildings_size; i++){
        if(needs[i] <1){
            return i;
        }
    }
    return House;
}
char * names[] = {"House","Cobbler", "Tailor","Barber","Jewelers", "Tavern", "Bakers","Butchers", "Masons","Weavers", "WineSellers", 
    "Hatmakers" ,"Saddlers", "Woodsellers","MagicShop", 
    "BookBinders", "FishMongers", "BeerSellers","BuckleMakers", "Plasterers", "SpiceMerchants","Blacksmiths","Painters","Doctors","Roofers","Locksmiths",
    "Ropemakers","Inn","Copyists","Tanners","Glovemakers","Bookseller","GaurdHouse","Alchemists"};
void data_print(FILE * F, building_e b,int index){
    //calling convention: class level martial_type magic_type
    char level[100];
    snprintf(level,100 ,"%d",RandomIntInRange(1,4));
    char * args[] = {"./CharacterGen", "me", level, "none", "none", "i", "temp.txt", NULL};
    spinNewProcess(args);
    fprintf(F ,"%d: %s\n",index, names[b]);
    FILE * c = fopen("temp.txt", "r");
    assert(c != 0);
    char buffer[1000];  
    while(fgets(buffer, 1000,c)){
        fprintf(F, "%s", buffer);
    }
    fclose(c);
    fprintf(F, "\n");
}
void calculate_building_data(building_t * buildings, int * interesting){
    int numbuildings = getNumBuildings();
    for(int i = 0; i<numbuildings; i++){
        buildings[i].type = House;
    }
    memcpy(needs, thresholds,sizeof(needs));
    int population = 0;
    char buffer[1000];
    snprintf(buffer, 1000, "output/%s.txt", cityName);
    FILE * data = fopen(buffer, "w");
    assert(data != NULL);
    for(int i = numbuildings-1; i>-1; i--){
        building_e b = calculate_next(population);
        if(b == House){
            const int addr = 5;
            population += addr;
            for(int j = 1; j<buildings_size; j++){
                needs[j]-= addr;
            }
        }
        else if(icount<MAX_INTERESTING){
            needs[b] = thresholds[b];
            interesting[icount] = i;
            data_print(data, b, icount);
            icount++;
        }   
    }
    fclose(data);
}
