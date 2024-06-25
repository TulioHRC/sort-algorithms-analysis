#include <time.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <random>
#include <vector>
#include "terminalFunctions.hpp"
#include "menu.hpp"
#include "sortAlgorithm.hpp"
#include "commandsMap.hpp"
#include "algorithmsMenu.hpp"


commandStringToChar_t commandStringToCharAlgorithmsMenu[] = {
  {"Bubble Sort", 'a'},
  {"Insert Sort", 'i'},
  {"Selection Sort", 's'},
  {"Merge Sort", 'm'},
  {"Quick Sort", 'q'},
  {"Quick Sort Median 3", 'j'},
  {"Quick Sort Median 3 with Insert Sort", 'o'},
  {"Shell Sort", 'h'},
  {"Counting Sort", 'c'},
  {"Bucket Sort", 'u'},
  {"Radix Sort", 'r'},
  {"Execute all algorithms", 'e'},
  {"Go Back", 'b'}
};

const char * vectorTypeIdToNameList[] = {
  "Random",
  "Sorted",
  "Reversed Sorted"
};

template <typename T>
void reverseVector(T * vector, int size){
  int j = size - 1;

  for(int i = 0; i < j; i++){
    T aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
    j--;
  }
}

// Vector types -> [0] - random, [1] - sorted, [2] - reversed sorted

template <typename T>
void initVector(T * vector, int size, int vectorType, unsigned int seed = 0){
  std::random_device rd;
  std::default_random_engine generator(seed ? seed : rd());
  std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

  for (int i=0; i<size; i++){
    vector[i] = (T)(distribution(generator));
  }

  if(vectorType != 0){
    SortAlgorithms<T> * temporarySort = new SortAlgorithms<T>(size, sizeof(T), vectorTypeIdToNameList[0], 0);
    temporarySort->runQuickSort(vector, 0, size - 1);
    delete temporarySort;
  } 

  if(vectorType == 2){
    reverseVector(vector, size);
  }
}

template<typename T>
void printVector(T * vector, int size){
  std::cout << std::endl;
  for (int i=0; i<size; i++){
    std::cout << (long long)vector[i] << " ";
  }
  std::cout << std::endl;
}

void waitMessage(std::string message){
  std::cout << message << std::endl;
  
  std::cin.ignore();
  std::cin.get();
}

template <typename T>
void executeSortingAlgorithm(
    T * vector, 
    int vectorSize, 
    int itemSize, 
    int vectorType, 
    char algorithmKey, 
    std::vector<sortPerformance_t>& sortingAlgorithmsPerformances, 
    std::string mode = "normal", 
    unsigned int seed = 0
  )
{
  SortAlgorithms<T> sortAlgorithms(vectorSize, itemSize, vectorTypeIdToNameList[vectorType], seed);

  sortAlgorithms.runAlgorithm(vector, algorithmKey); 

  sortingAlgorithmsPerformances.push_back(sortAlgorithms.getSortPerformanceObject());
  if(mode == "normal"){
    sortAlgorithms.printPerformance();
    printVector(vector, vectorSize);
    waitMessage("Sorted."); 
  }
}

void runAlgorithm(char algorithmKey, std::vector<sortPerformance_t>& sortingAlgorithmsPerformances, int defaultVectorSize = -1, int defaultItemSize = -1, int defaultVectorType = -1, unsigned int seed = 0)
{
  int vectorSize, itemSize, vectorType;
  std::string mode;
  if(defaultVectorSize == -1 && defaultItemSize == -1 && defaultVectorType == -1){
    std::cout << "Vector size: "; std::cin >> vectorSize;
  
    do{
      std::cout << "Item size (only 8, 16, 32 and 64) in bits: ";
      std::cin >> itemSize;
    } while (itemSize != 8 && itemSize != 16 && itemSize != 32 && itemSize != 64);

    do{
      std::cout << "Vector type [0] - random, [1] - sorted, [2] - reversed sorted: ";
      std::cin >> vectorType;
    } while (vectorType != 0 && vectorType != 1 && vectorType != 2);

    mode = "normal";
  } else {
    vectorSize = defaultVectorSize;
    itemSize = defaultItemSize;
    vectorType = defaultVectorType;
    mode = "all";
  }


  if(itemSize == 8){
    char * vector = new char[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    if(mode == "normal") printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, sortingAlgorithmsPerformances, mode, seed);

  } else if (itemSize == 16){
    short int * vector = new short int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    if(mode == "normal") printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, sortingAlgorithmsPerformances, mode, seed);
  
  } else if (itemSize == 32){
    int * vector = new int[vectorSize];
    initVector(vector, vectorSize, vectorType, seed); 
    if(mode == "normal") printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, sortingAlgorithmsPerformances, mode, seed);
  
  } else { // 64 bits
    long long * vector = new long long[vectorSize];
    initVector(vector, vectorSize, vectorType, seed);
    if(mode == "normal") printVector(vector, vectorSize);
    executeSortingAlgorithm(vector, vectorSize, itemSize, vectorType, algorithmKey, sortingAlgorithmsPerformances, mode, seed);
  
  }

}


void runAllAlgorithms(std::vector<sortPerformance_t>& sortingAlgorithmsPerformances, int defaultVectorSize = -1, int defaultItemSize = -1, int defaultVectorType = -1, int defaultTimesToRun = -1, int defaultRunsPerAlgorithm = -1, int defaultFromAlgorithm = -1, int defaultToAlgorithm = -1) {
  std::vector<std::string> algorithms = {
    "Bubble Sort",
    "Insert Sort",
    "Selection Sort",
    "Merge Sort",
    "Quick Sort",
    "Quick Sort Median 3",
    "Quick Sort Median 3 with Insert Sort",
    "Shell Sort",
    "Counting Sort",
    "Bucket Sort",
    "Radix Sort"
  };

  int vectorSize, itemSize, vectorType, timesToRun, runsPerAlgorithm;
  int fromAlgorithm = 0; int toAlgorithm = 11; 

  if(defaultVectorSize == -1 && defaultItemSize == -1 && defaultVectorType == -1 && defaultTimesToRun == -1 && defaultRunsPerAlgorithm == -1){
    std::cout << "Vector size: "; std::cin >> vectorSize; 
    
    do{
      std::cout << "Item size (only 8, 16, 32 and 64) in bits: ";
      std::cin >> itemSize;
    } while (itemSize != 8 && itemSize != 16 && itemSize != 32 && itemSize != 64);

    do{
      std::cout << "Vector type [0] - random, [1] - sorted, [2] - reversed sorted: ";
      std::cin >> vectorType;
    } while (vectorType != 0 && vectorType != 1 && vectorType != 2);

    std::cout << "Times to run: "; std::cin >> timesToRun;
    std::cout << "Times to run per algorithm: "; std::cin >> runsPerAlgorithm;

    std::cout << "From algorithm on position (in the order of the last menu, 1 is bubble, and 11 is radix): "; std::cin >> fromAlgorithm;
    std::cout << "To algorithm on position (in the order of the last menu, 1 is bubble, and 11 is radix): "; std::cin >> toAlgorithm;
    fromAlgorithm--;

  } else {
    vectorSize = defaultVectorSize;
    itemSize = defaultItemSize;
    vectorType = defaultVectorType;
    timesToRun = defaultTimesToRun;
    runsPerAlgorithm = defaultRunsPerAlgorithm;
    fromAlgorithm = defaultFromAlgorithm;
    toAlgorithm = defaultToAlgorithm;
  }

  clearTerminal();
  std::cout << "Running all algorithms\n" << std::endl;

  for (int i = 0; i < timesToRun; i++ )
    for (int pos = fromAlgorithm; pos < toAlgorithm; pos++) {
      std::string algorithm = algorithms[pos];
      char key = nameToKey(algorithm, commandStringToCharAlgorithmsMenu);
      std::cout << algorithm << " " << key << std::endl;
      if (key != 0) {
        for(int j = 0; j < runsPerAlgorithm; j++)
          runAlgorithm(key, sortingAlgorithmsPerformances, vectorSize, itemSize, vectorType, i+1);
      }
    }
}

class AlgorithmMenu : public Menu {
  public:
    AlgorithmMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitchWithSortingAlgorithmsPerformances(std::string command, std::vector<sortPerformance_t>& sortingAlgorithmsPerformances){
      char key = nameToKey(command, commandStringToCharAlgorithmsMenu);
      if(key == 'e'){
        clearTerminal();
        runAllAlgorithms(sortingAlgorithmsPerformances);
        clearTerminal();
      } else if(key != 'b' && key != 0){
        clearTerminal();
        runAlgorithm(key, sortingAlgorithmsPerformances);
      }
      clearTerminal();
    }
};

int openAlgorithmMenu(std::vector<sortPerformance_t>& sortingAlgorithmsPerformances)
{
  std::vector<std::string> operationsList = {
    "Bubble Sort",
    "Insert Sort",
    "Selection Sort",
    "Merge Sort",
    "Quick Sort",
    "Quick Sort Median 3",
    "Quick Sort Median 3 with Insert Sort",
    "Shell Sort",
    "Counting Sort",
    "Bucket Sort",
    "Radix Sort",
    "Execute all algorithms",
    "Go Back"
  };

  AlgorithmMenu algorithmMenu = AlgorithmMenu(operationsList, (int)operationsList.size());
  bool keepAlive = true;

  // 64 bits - all
  //for(int i = 0; i < 3; i++){
    //for(int a : {1000000}){
      //runAllAlgorithms(sortingAlgorithmsPerformances, a, 64, i, 3, 6, 3, 6);
      //runAllAlgorithms(sortingAlgorithmsPerformances, a, 64, i, 3, 6, 7, 8);
      //runAllAlgorithms(sortingAlgorithmsPerformances, a, 64, i, 3, 6, 10, 11);
      //runAllAlgorithms(sortingAlgorithmsPerformances, a, 16, i, 3, 6, 7, 8);
    //}
  //}

  while(keepAlive){
    std::string operationSelected = algorithmMenu.selectItemOnMenu();

    algorithmMenu.commandSwitchWithSortingAlgorithmsPerformances(operationSelected, sortingAlgorithmsPerformances);

    clearTerminal();
    if(nameToKey(operationSelected, commandStringToCharAlgorithmsMenu) == 'b') keepAlive = false;
    else {
      std::cout << "Sorting performance saved!\n\n Press enter to continue..." << std::endl;

      std::cin.ignore();
    }
  }

  return 0;
}