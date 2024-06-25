#include <time.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "terminalFunctions.hpp"
#include "menu.hpp"
#include "sortAlgorithm.hpp"
#include "algorithmsMenu.hpp"
#include "visualizeMenu.hpp"
#include "commandsMap.hpp"


std::vector<sortPerformance_t> sortingAlgorithmsPerformances;

commandStringToChar_t commandStringToChar[] = {
    {"Algorithms Menu", 'a'},
    {"Visualize Menu", 'v'},
    {"Exit", 'e'}
};

class MainMenu : public Menu {
  public:
    MainMenu(std::vector<std::string> options, int size) : Menu(options, size) {};

    void commandSwitch(std::string command){
      switch(nameToKey(command, commandStringToChar))
      {
        case 'a':
          openAlgorithmMenu(sortingAlgorithmsPerformances);
          break;
        case 'v':
          openVisualizeMenu(sortingAlgorithmsPerformances);
          break;
        case 'e':
          //exitCommand();
          clearTerminal();
          loadProgramTerminal("See you later!\n");
          exit(1);
          break;
      }
    }
};

int main(){
  std::vector<std::string> operationsList = {"Algorithms Menu", "Visualize Menu", "Exit"};
  MainMenu mainMenu = MainMenu(operationsList, 3);

  while(true){
    std::string operationSelected = mainMenu.selectItemOnMenu();

    mainMenu.commandSwitch(operationSelected);

    clearTerminal();
  }

  return 0;
}