#include <time.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "terminalFunctions.hpp"
#include "menu.hpp"
#include "sortAlgorithm.hpp"
#include "commandsMap.hpp"
#include "visualizeMenu.hpp"


commandStringToChar_t commandStringToCharVisualizeMenu[] = {
    {"See Table", 't'},
    {"See Graph", 'g'},
    {"Go Back", 'b'}
};

void showTable(std::vector<sortPerformance_t>& sortingAlgorithmsPerformances)
{
  std::cout << "Sort name - Comparations - Movements - Function calls - Time - Vector size - Item size - Vector type - Seed" << std::endl;
  for(int i = 0; i < (int)sortingAlgorithmsPerformances.size(); i++){
    sortPerformance_t actualPerformance = sortingAlgorithmsPerformances[i];
    std::cout << actualPerformance.sortName << " - " << actualPerformance.comparations << " - " << actualPerformance.movements << " - "
      << actualPerformance.functionCalls << " - " << actualPerformance.milissecs << " - " 
      << actualPerformance.settings.vectorSize << " - " << actualPerformance.settings.itemSize << " - " << actualPerformance.settings.vectorType 
      << " - "  << actualPerformance.settings.seed << std::endl;
  }
  std::cin.ignore();
}

class AlgorithmMenu : public Menu {
  public:
    AlgorithmMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitchWithPerformances(std::string command, std::vector<sortPerformance_t>& sortingAlgorithmsPerformances){
      switch(nameToKey(command, commandStringToCharVisualizeMenu))
      {
        case 't':
          //insertSort();
          std::cout << "Table" << std::endl;
          clearTerminal();
          showTable(sortingAlgorithmsPerformances);
          break;
        case 'g':
          //insertSort();
          std::cout << "Graph" << std::endl;
          break;
        case 'b':
          clearTerminal();
          break;
      }
    }
};

int openVisualizeMenu(std::vector<sortPerformance_t>& sortingAlgorithmsPerformances){
  std::vector<std::string> operationsList = {"See Table", "See Graph", "Go Back"};
  AlgorithmMenu algorithmMenu = AlgorithmMenu(operationsList, 3);
  bool keepAlive = true;

  while(keepAlive){
    std::string operationSelected = algorithmMenu.selectItemOnMenu();

    algorithmMenu.commandSwitchWithPerformances(operationSelected, sortingAlgorithmsPerformances);

    clearTerminal();
    if(nameToKey(operationSelected, commandStringToCharVisualizeMenu) == 'b') keepAlive = false;
    else {
      std::cout << "\nCommand executed. Press enter to continue" << std::endl;

      std::cin.ignore();
    }
  }

  return 0;
}