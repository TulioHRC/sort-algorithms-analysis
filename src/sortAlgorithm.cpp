#include "sortAlgorithm.hpp"

void clkDiff(struct timespec t1, struct timespec t2,
                   struct timespec * res)
{
  if (t2.tv_nsec < t1.tv_nsec){
    res-> tv_nsec = 1000000000+t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec-1;
  } else {
    res-> tv_nsec = t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec;
  } 
}


/*
#include <iostream>
#include "sortAlgorithm.hpp"

void clkDiff(struct timespec t1, struct timespec t2,
                   struct timespec * res)
{
  if (t2.tv_nsec < t1.tv_nsec){
    res-> tv_nsec = 1000000000+t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec-1;
  } else {
    res-> tv_nsec = t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec;
  } 
}

template <class T>
SortAlgorithms<T>::SortAlgorithms(int vectorSize, int itemSize) { 
    sortPerformanceObject.comparations = 0; 
    sortPerformanceObject.movements = 0;
    sortPerformanceObject.functionCalls = 0;
    sortPerformanceObject.secs = 0;
    sortPerformanceObject.milissecs = 0;
    sortPerformanceObject.settings.vectorSize = vectorSize;
    sortPerformanceObject.settings.itemSize = itemSize;
}

template <class T>
void SortAlgorithms<T>::incrementComparations(int numToIncrement)
{
    this->sortPerformanceObject.comparations += numToIncrement;
}

template <class T>
void SortAlgorithms<T>::incrementMovements(int numToIncrement)
{
    this->sortPerformanceObject.movements += numToIncrement;
}

template <class T>
void SortAlgorithms<T>::incrementFunctionCalls(int numToIncrement)
{
    this->sortPerformanceObject.functionCalls += numToIncrement;
}

template <class T>
sortPerformance_t SortAlgorithms<T>::getSortPerformanceObject()
{
    return this->sortPerformanceObject;
}

template <class T>
void SortAlgorithms<T>::runInsertionSort(T * vector, int start, int end)
{
    int timer;
    struct timespec inittp, endtp, restp;


    timer = clock_gettime(CLOCK_MONOTONIC, &inittp);
    timer = clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);

    std::cout << this->vectorSize << " " << restp.tv_sec << "." << restp.tv_nsec << std::endl;
    //char pref[100];
    //sprintf(pref,"size %d time %ld.%.9ld",
     //       vectorSize, restp.tv_sec,restp.tv_nsec);
}
*/