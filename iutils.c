#include "iutils.h"
#include <stdio.h>
static u_int64_t seed = 0;
//https://en.wikipedia.org/wiki/Linear-feedback_shift_register
u_int64_t RandomInt(void){
  if(seed == 0){
    seed = time(0);
  }
  seed ^= seed >> 7;
  seed ^= seed << 9;
  seed ^= seed >> 13;
  return seed;
}
int RandomIntInRange(int min, int max){
  return RandomInt()%(max-min)+min;
}
double RandomDouble(void){
  return ((double)RandomInt())/((double)0xFFFFFFFFFFFFFFFF);
}
void * regionAlloc(region_t * region, size_t amount){
    if(region->ptr+amount>REGIONMAX){
        fprintf(stderr, "Region Maximum Memory Allocated");
        return NULL;
    }
    unsigned long oldptr = (unsigned long)(region->ptr+region->memory);
    region->ptr = region->ptr+amount;
    return(void *)oldptr;
}
void * regionRealloc(region_t * region, void * ptr,size_t curAmount,size_t newAmount){
    unsigned char * newptr = regionAlloc(region,newAmount);
    unsigned char * cptr = (unsigned char * ) ptr;
    if((unsigned long)ptr+curAmount == region->ptr){
        region->ptr = ((unsigned long)(region->ptr)-curAmount+newAmount);
        return ptr;
    }
    if(newAmount<= curAmount){
        memcpy(newptr,cptr,newAmount);
    }
    else{
        memcpy(newptr, cptr, curAmount);
    }
    return (void *)cptr;
}
void regionReset(region_t * region){
    memset(region->memory, '\0', REGIONMAX);
}
//https://www.geeksforgeeks.org/quick-sort/ is the sorce for all the sorting algorythm stuff;
int intPartition(int arr[], int low, int high){
    // Choosing the pivot
    int pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void intQuickSort(int arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = intPartition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        intQuickSort(arr, low, pi - 1);
        intQuickSort(arr, pi + 1, high);
    }
}
void intArraySort(intArray_t * arr){
    intQuickSort(arr->vals,0, arr->length-1);
}
void intArrayPrint(intArray_t * arr){
    printf("<");
    for(int i =0; i<arr->length; i++){
        printf("%d", arr->vals[i]);
        if(i != arr->length-1){
            printf(", ");
        }
    }
    printf(">\n");
}
int longPartition(long arr[], int low, int high)
{
    // Choosing the pivot
    long pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    long temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void longQuickSort(long arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = longPartition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        longQuickSort(arr, low, pi - 1);
        longQuickSort(arr, pi + 1, high);
    }
}
void longArraySort(longArray_t * arr){
    longQuickSort(arr->vals,0, arr->length-1);
}
int floatPartition(float arr[], int low, int high)
{
    // Choosing the pivot
    float pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    float temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void floatQuickSort(float arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = floatPartition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        floatQuickSort(arr, low, pi - 1);
        floatQuickSort(arr, pi + 1, high);
    }
}

void floatArraySort(floatArray_t * arr){
    floatQuickSort(arr->vals,0, arr->length-1);
}
int doublePartition(double arr[], int low, int high)
{
    // Choosing the pivot
    double pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    double temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void doubleQuickSort(double arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = doublePartition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        doubleQuickSort(arr, low, pi - 1);
        doubleQuickSort(arr, pi + 1, high);
    }
}
void doubleArraySort(doubleArray_t * arr){
    doubleQuickSort(arr->vals,0, arr->length-1);
}
void longArrayPrint(longArray_t * arr){
    printf("<");
    for(int i =0; i<arr->length; i++){
        printf("%ld", arr->vals[i]);
        if(i != arr->length-1){
            printf(", ");
        }
    }
    printf(">\n");
}
void floatArrayPrint(floatArray_t * arr){
    printf("<");
    for(int i =0; i<arr->length; i++){
        printf("%f", arr->vals[i]);
        if(i != arr->length-1){
            printf(", ");
        }
    }
    printf(">\n");
}
void doubleArrayPrint(doubleArray_t * arr){
    printf("<");
    for(int i =0; i<arr->length; i++){
        printf("%f", arr->vals[i]);
        if(i != arr->length-1){
            printf(", ");
        }
    }
    printf(">\n");
}
void stringArrayPrint(stringArray_t * arr){
    printf("<");
    for(int i =0; i<arr->length; i++){
        printf("%s", arr->vals[i]);
        if(i != arr->length-1){
            printf(", ");
        }
    }
    printf(">\n");
}
vector_t vectorAdd(vector_t a, vector_t b){
    return (vector_t){a.x+b.x, a.y+b.y, a.z+b.z};
}
vector_t vectorSub(vector_t a, vector_t b){
    return (vector_t){a.x-b.x, a.y-b.y, a.z-b.z};
}
double vectorLength(vector_t a){
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
vector_t vectorNormalize(vector_t a){
    return vectorScale(1/vectorLength(a), a);
}
vector_t vectorCrossProduct(vector_t a, vector_t b){
    return (vector_t){a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
double vectorDotProduct(vector_t a, vector_t b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
vector_t vectorReflect(vector_t a, vector_t b){
    return vectorSub(vectorNormalize(a), vectorScale(2*vectorDotProduct(vectorNormalize(a),vectorNormalize(b)),vectorNormalize(b)));
}
vector_t vectorScale(double f, vector_t a){ 
    return (vector_t){a.x*f, a.y*f, a.z*f};   
}
void printVector(vector_t a){
    printf("<%f,%f,%f>\n", a.x, a.y, a.z);
}