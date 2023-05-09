#pragma once

#include "Service.h"
#include <QMainWindow>
#include <QHeaderView>
#include <QApplication>
#include <QWidget>
#include <QTableWidget>

#include <QLayout>
#include <QFormLayout>
#include <QGroupBox>

#include <QRadioButton>
#include <QPushButton>

#include <QLineEdit>
#include <QLabel>

#include <QMessageBox>

/*
 * ----- GUI using Qt6 ------
 *
 *      Arrangement will have two sides:
 *      - the left side: the current list of cars available;
 *      - the right side: specific commands to operate with the app
 */

class CarGUI : public QWidget {
    // QWidget is simply a window
private:
    Service &service;

    // declaring the components that the main app window should contain

    // the main layout -> this contains all the elements that the windows has ( a wrapper )
    QLayout *mainLayout{};

    // the washing window -> will show only the current cars in the washing list
    QWidget *washWindow{};
    QLayout *washWindowLayout{};
    QTableWidget *tableWash{};

    // the cars list ( left part of the GUI )
    QTableWidget *tableCars{};

    // ( right part of the GUI )
    // Group Boxes -> arranging the commands in some way
    QGroupBox *commandsBox{};     // for grouping all the commands
    QGroupBox *operationsBox{};   // for grouping the basic commands
    QGroupBox *filterBox{};       // for grouping the filter options
    QGroupBox *sortBox{};         // for grouping the sort options
    QGroupBox *washBox{};         // for grouping the washing list options
    QGroupBox *otherBox{};        // for grouping other commands

    // Buttons -> for interaction between the user and the app
    QPushButton *btnAdd{};        // for adding a car
    QPushButton *btnDelete{};     // for deleting a car
    QPushButton *btnModify{};     // for modifying a car
    QPushButton *btnFind{};       // for finding a car

    QRadioButton *radioFilterProducer{}; // for filtering by the producer
    QRadioButton *radioFilterType{};     // for filtering by the type
    QLineEdit *filterCriteria{};         // the element on which we will filter
    QPushButton *btnFilter{};           // for filtering

    QRadioButton *radioSortRegNumber{};  // for sorting by the registration number
    QRadioButton *radioSortType{};       // for sorting by the type
    QRadioButton *radioSortProdMod{};    // for sorting by the producer and model
    QPushButton *btnSort{};             // for sorting

    QPushButton *btnAddToWash{};         // for adding to the washing list
    QPushButton *btnClearWash{};         // for clearing the washing list
    QPushButton *btnGenerateWash{};      // for generating a random washing list

    QPushButton *btnUndo{};              // for undoing the last op
    QPushButton *btnCountModels{};       // for counting all the models
    QPushButton *btnClose{};             // for closing the app

    void initGUI();                             // method to initialize the GUI

    void loadData();                            // method to load the data into the GUI

    void connectSignals_Slots();                // method to add actions to the elements of the GUI

    void reloadList(const vector<Car> &);        // method to update the cars list of the GUI

public:
    explicit CarGUI(Service &serv);

    // method for adding a car to the car list
    void guiAdd();

    // method for deleting a car from the car list
    void guiDelete();

    // method for modifying a car from the car list
    void guiModify();

    // method for finding a car from the car list
    void guiFind() const;

    // method for filtering a car by a criteria
    void guiFilter(const string &, bool(*compareMethod)(const Car &, const string &)) const;

};