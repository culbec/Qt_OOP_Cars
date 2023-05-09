#include <iostream>
#include <QApplication>
#include "Headers/GUI.h"
#include "Headers/Repository.h"
#include "Headers/Spalatorie.h"
#include "Headers/Service.h"
#include "Headers/tests.h"

int main(int argc, char** argv) {
    runTests();
    std::cout << "Tests ok!\n";

    QApplication app{argc, argv};


    Repository repository;
    WashingList washingList;
    Service service{repository, washingList};
    CarGUI carGui(service);

    return app.exec();


    /*WashingList washingList;
    while (true) {
        int option;
        std::cout << "1. Memory Repository\n2. File Repository\n";
        std::cout << "Your option: ";
        std::cin >> option;

        if (option == 1) {
            Repository carRepo;
            Service carServiceMem(carRepo, washingList);
            UI uiMem(carServiceMem);
            uiMem.uiRun();
            break;
        } else if (option == 2) {
            try {
                FileRepository fileRepo("cars.txt");
                Service carServiceFile(fileRepo, washingList);
                UI uiFile(carServiceFile);
                uiFile.uiRun();
            } catch (RepositoryException &rE) {
                std::cout << rE.getMessage();
            }
            break;
        } else {
            std::cout << "Invalid option!\n";
            break;
        }
    }*/
    // return 0;
}

