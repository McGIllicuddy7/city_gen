#include "data.h"
#include "generator.h"
static int icount = 0;
typedef enum{
    House,Cobbler, Tailor,Barber,Jewelers, Tavern, Bakers,Butchers, Masons,Weavers, WineSellers, Hatmakers,Saddlers, Woodsellers,MagicShop, 
    BookBinders, FishMongers, BeerSellers,BuckleMakers, Plasterers, SpiceMerchants,Blacksmiths,Painters,Doctors,Roofers,Locksmiths,
    Ropemakers,Inn,Copyists,Tanners,Glovemakers,Bookseller,buildings_size
}building_e;
int thresholds[] = {0, 150, 250, 350, 400, 405, 800, 1000, 500, 600, 900, 950, 1005, 2400, 2800
,3000,1200, 1400, 1405, 1410, 1420, 1505, 1510,1800, 1900, 1905, 2000, 2005,2010,2015,2405, 6300};
int needs[buildings_size] = {0};
building_e calculate_next(building_t * buildings){
    int population;
    
    return House;
}
void calculate_building_data(building_t * buildings, int * interesting){
    int numbuildings = getNumBuildings();
    for(int i = 0; i<numbuildings; i++){
        buildings[i].type = House;
    }
}
