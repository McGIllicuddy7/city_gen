#pragma once
#define REGIONMAX 16384
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
//region stuff
//returns a random int that doesn't have to be initialized. the iutils.c file stores a variable which is set to zero and if its zero 
//it uses current time as a seed
u_int64_t RandomInt(void);
int RandomIntInRange(int min, int max);
double RandomDouble(void);
//https://youtu.be/UYLHA_Ey8Ys?si=4otMgZ6K6SNS8nbB
//this defines a region of memory that can be used for allocation that will automatically be cleaned up when the stack frame ends
typedef struct {
    unsigned char memory[REGIONMAX];
    unsigned long ptr;
}region_t;
//use this to set up a region in a new stack frame 
#define RegionSetUp() region_t local; local.ptr = 0;
//basically just malloc
void * regionAlloc(region_t * region, size_t amount);
//basically just realloc
void * regionRealloc(region_t * region, void * ptr,size_t curAmount,size_t newAmount);
//resets the region to its initial state, it is literally just seting pointer to zero;
void regionReset(region_t * region);
//this 
#define localAlloc(amount) regionAlloc(&local,amount)
#define localRealloc(ptr,curamount,amount) regionRealloc(&local,curamount, amount)
#define localReset() regionReset(&local)
//this creates an array type of whatever t is named TArray_t where capital T is the name of the type;
//this array can be added to, subtracted from, etc.
#define EnableArrayType(t)\
typedef struct {\
    unsigned long length; \
    unsigned long allocLength;\
    t * vals; \
} t##Array_t; \
static t##Array_t t##ArrayNew(region_t * region){\
    t * i = regionAlloc(region,sizeof(t));\
    return (t##Array_t){0,1,i}; \
}\
static void t##ArrayPush(region_t * region, t##Array_t * arr, t val){\
    if(arr->allocLength>=arr->length+1){\
        arr->vals[arr->length] = val;\
        arr->length+=1;\
        return;\
    }\
    arr->vals =  regionRealloc(region, arr->vals, arr->length*sizeof(t), arr->length*sizeof(t)+4*sizeof(t));\
    arr->allocLength +=4;\
    arr->vals[arr->length] = val;\
    arr->length += 1;\
}\
static void t##ArrayInsert(region_t * region, t##Array_t * arr, unsigned long index, t val){\
    t##ArrayPush(region, arr, val);\
    t temp = arr->vals[index];\
    arr->vals[index] = arr->vals[arr->length-1];\
    arr->vals[arr->length-1] = temp;\
}\
static void t##ArrayRemove(t##Array_t * arr, unsigned long index){\
    if(index < arr->length){\
        memmove(&(arr->vals[index]),&(arr->vals[index+1]),(arr->length-index)*sizeof(t));\
    }\
    arr->length -=1;\
}\
static void t##ArrayPop(t##Array_t * arr){\
    if(arr->length>0){\
        arr->length-=1;\
    }\
}\
static t##Array_t t##ArrayCopy(region_t * region, t##Array_t * arr){\
    t##Array_t out;\
    out.length = arr->length;\
    out.allocLength = out.length;\
    out.vals = regionAlloc(region, sizeof(t)*arr->length);\
    memcpy(out.vals, arr->vals, sizeof(t)*arr->length);\
    return out;\
}\
static t t##ArrayGetRandom(t##Array_t * arr){\
    return arr->vals[RandomInt()%arr->length];\
}\
static t##Array_t t##ArrayChoose(region_t * region, t##Array_t * arr, unsigned long numToChoose){\
    if(numToChoose>arr->length){\
        return t##ArrayCopy(region, arr);\
    }\
    RegionSetUp();\
    t##Array_t temp = t##ArrayCopy(&local, arr);\
    t##Array_t out;\
    out.allocLength = numToChoose;\
    out.length =numToChoose;\
    out.vals = regionAlloc(region, sizeof(t)*numToChoose);\
    for(int i = 0; i<numToChoose; i++){\
        int r = RandomInt()%temp.length;\
        out.vals[i] = temp.vals[r];\
        t##ArrayRemove(&temp, r);\
    }\
    return out;\
}\
static void t##ArrayReverse(t##Array_t * arr){\
    for(int i = 0; i<arr->length/2; i++){\
        t temp = arr->vals[i];\
        arr->vals[i] = arr->vals[arr->length-i-1];\
        arr->vals[arr->length-i-1] = temp;\
    }\
}
typedef char * string;
EnableArrayType(int)
EnableArrayType(long)
EnableArrayType(float)
EnableArrayType(double)
EnableArrayType(string)

void intArraySort(intArray_t * arr);
void intArrayPrint(intArray_t * arr);
void longArraySort(longArray_t * arr);


void floatArraySort(floatArray_t * arr);
void doubleArraySort(doubleArray_t * arr);
void longArrayPrint(longArray_t * arr);
void floatArrayPrint(floatArray_t * arr);
void doubleArrayPrint(doubleArray_t * arr);
void stringArrayPrint(stringArray_t * arr);
typedef struct{
    double x;
    double y;
    double z;
} vector_t;
vector_t vectorAdd(vector_t a, vector_t b);
vector_t vectorSub(vector_t a, vector_t b);
double vectorLength(vector_t a);
vector_t vectorNormalize(vector_t a);
vector_t vectorCrossProduct(vector_t a, vector_t b);
double vectorDotProduct(vector_t a, vector_t b);
vector_t vectorReflect(vector_t a, vector_t b);
vector_t vectorScale(double f, vector_t a);
void printVector(vector_t a);