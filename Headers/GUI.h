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
#include <QComboBox>

#include <QRadioButton>
#include <QPushButton>

#include <QLineEdit>
#include <QLabel>

#include <QMessageBox>

#include <QListView>
#include <QListWidget>
#include "ListViewModel.h"

#include <QTableView>
#include "TableViewModel.h"

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
    QLayout *mainLayout = new QHBoxLayout;

    // the washing window -> will show only the current cars in the washing list
    QWidget *washWindow = new QWidget;
    QLayout *washWindowLayout = new QVBoxLayout;
    QTableWidget *tableWash = new QTableWidget;

    // the cars list ( left part of the GUI )
    QTableWidget *tableCars = new QTableWidget;

    // ( right part of the GUI )
    // Group Boxes -> arranging the commands in some way
    QGroupBox *commandsBox = new QGroupBox("Commands");;     // for grouping all the commands
    QGroupBox *operationsBox = new QGroupBox("Operations");   // for grouping the basic commands
    QGroupBox *filterBox = new QGroupBox("Filter");       // for grouping the filter options
    QGroupBox *sortBox = new QGroupBox("Sort");         // for grouping the sort options
    QGroupBox *washBox = new QGroupBox("Wash");         // for grouping the washing list options
    QGroupBox *otherBox = new QGroupBox("Others");        // for grouping other commands

    // Buttons -> for interaction between the user and the app
    QPushButton *btnAdd = new QPushButton("&Add");        // for adding a car
    QPushButton *btnDelete = new QPushButton("&Delete");     // for deleting a car
    QPushButton *btnModify = new QPushButton("&Modify");     // for modifying a car
    QPushButton *btnFind = new QPushButton("&Find");      // for finding a car

    QRadioButton *radioFilterProducer = new QRadioButton("By producer");; // for filtering by the producer
    QRadioButton *radioFilterType = new QRadioButton("By type");     // for filtering by the type
    QLineEdit *filterCriteria = new QLineEdit;        // the element on which we will filter
    QPushButton *btnFilter = new QPushButton("&Filter");          // for filtering

    QRadioButton *radioSortRegNumber = new QRadioButton(
            "By registration number");  // for sorting by the registration number
    QRadioButton *radioSortType = new QRadioButton("By type");      // for sorting by the type
    QRadioButton *radioSortProdMod = new QRadioButton(
            "By producer and model");   // for sorting by the producer and model
    QPushButton *btnSort = new QPushButton("&Sort");             // for sorting

    QPushButton *btnAddToWash = new QPushButton("&Add to wash");         // for adding to the washing list
    QPushButton *btnClearWash = new QPushButton("&Clear wash");      // for clearing the washing list
    QPushButton *btnGenerateWash = new QPushButton("&Generate wash");      // for generating a random washing list

    QPushButton *btnUndo = new QPushButton("&Undo");              // for undoing the last op
    QPushButton *btnCountModels = new QPushButton("&Count models");       // for counting all the models
    QPushButton *btnExport = new QPushButton("&Export"); // for exporting the car wash data
    QPushButton *btnClose = new QPushButton("&Close");            // for closing the app

    // dynamic btns widget
    QGroupBox *btnsDynamicGB = new QGroupBox("Dynamic Buttons");
    QVBoxLayout *btnsDynamicLay = new QVBoxLayout;

    // list widget for adding the cars on a list
    QListWidget *listCars = new QListWidget;

    void initGUI();                             // method to initialize the GUI

    void createListView();                      // creates a list view

    void connectSignals_Slots();                // method to add actions to the elements of the GUI

    void reloadTable(const vector<Car> &);        // method to update the cars list of the GUI

    void reloadWashingList();                   // method for updating the washing list

    void reloadList(const vector<Car> &);

public:
    explicit CarGUI(Service &serv);

    // overriding the close event behavior
    void closeEvent(QCloseEvent *) override;

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

    // method for adding elements to the car wash
    void guiAddToWash();

    // method for clearing the washing list
    void guiClearWash();

    // method for generating a random list of cars to wash
    void guiGenerateWash();

    // method for undo
    void guiUndo();

    // method for counting the models
    void guiCountModels() const;

    // method for exporting the washing list to a CSV or HTML file
    void guiExport() const;

    // method for updating the dynamic btns
    void updateDynamicBtns();

};