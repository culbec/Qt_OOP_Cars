#include <QFormLayout>
#include "Headers/GUI.h"

CarGUI::CarGUI(Service &serv) : service{serv} {
    this->initGUI(); // constructing the GUI
    this->connectSignals_Slots(); // connecting the buttons to actions
    this->reloadList(this->service.getCars()); // loading the existing data into the GUI
    this->updateDynamicBtns(); // for updating the dynamic created btns
}

// overriding the close event signal
// when pressing the 'x' button, the app should close

void CarGUI::closeEvent(QCloseEvent *event) {
    // quitting the whole app
    QApplication::quit();
}

void CarGUI::initGUI() {
    //  ------ BUILDING THE LEFT SIDE OF THE WINDOW ------
    auto *leftSide = new QWidget;        // left side of the window
    auto *leftSideLayout = new QHBoxLayout;  // layout for the left side

    this->tableCars->setColumnCount(4); // the columns of the table (setting the categories)

    QStringList headerTable; // header of the car table

    // adding a list of labels into the string list
    headerTable << "Registration Number" << "Producer" << "Model" << "Type";

    // setting the labels for each field in the table
    this->tableCars->setHorizontalHeaderLabels(headerTable);

    // rezising by the contents of the table
    this->tableCars->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // constructing the left side of the window
    leftSideLayout->addWidget(this->tableCars);
    leftSide->setLayout(leftSideLayout);

    // ------ BUILDING THE RIGHT SIDE OF THE WINDOW ------
    auto *rightSide = new QWidget;       // right side of the window
    auto *rightSideLayout = new QVBoxLayout; // layout for the right side

    QLayout *commandsLayout = new QVBoxLayout;
    QLayout *operationsLayout = new QHBoxLayout;
    QLayout *filterLayout = new QVBoxLayout;
    QLayout *sortLayout = new QVBoxLayout;
    QLayout *washLayout = new QHBoxLayout;
    QLayout *otherLayout = new QHBoxLayout;

    // adding the buttons to the operations section
    operationsLayout->addWidget(this->btnAdd);
    operationsLayout->addWidget(this->btnDelete);
    operationsLayout->addWidget(this->btnModify);
    operationsLayout->addWidget(this->btnFind);

    this->filterCriteria->setClearButtonEnabled(true);
    this->filterCriteria->setPlaceholderText("Filter criteria");

    auto *radioFilterButtons = new QWidget;
    QLayout *radioFilterLayout = new QHBoxLayout;

    radioFilterLayout->addWidget(this->radioFilterProducer);
    radioFilterLayout->addWidget(this->radioFilterType);
    radioFilterButtons->setLayout(radioFilterLayout);

    filterLayout->addWidget(radioFilterButtons);
    filterLayout->addWidget(this->filterCriteria);
    filterLayout->addWidget(this->btnFilter);

    auto *radioSortButtons = new QWidget;
    QLayout *radioSortLayout = new QHBoxLayout;

    radioSortLayout->addWidget(this->radioSortRegNumber);
    radioSortLayout->addWidget(this->radioSortType);
    radioSortLayout->addWidget(this->radioSortProdMod);
    radioSortButtons->setLayout(radioSortLayout);

    sortLayout->addWidget(radioSortButtons);
    sortLayout->addWidget(this->btnSort);

    washLayout->addWidget(this->btnAddToWash);
    washLayout->addWidget(this->btnClearWash);
    washLayout->addWidget(this->btnGenerateWash);

    this->tableWash->setColumnCount(4);

    QStringList headerWash;
    headerWash << "Registration Number" << "Producer" << "Model" << "Type";

    this->tableWash->setHorizontalHeaderLabels(headerWash);
    this->tableWash->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->washWindowLayout->addWidget(this->tableWash);

    this->washWindow->setLayout(this->washWindowLayout);

    otherLayout->addWidget(this->btnUndo);
    otherLayout->addWidget(this->btnCountModels);
    otherLayout->addWidget(this->btnExport);
    otherLayout->addWidget(this->btnClose);

    // setting the layout of the boxes
    this->operationsBox->setLayout(operationsLayout);
    this->filterBox->setLayout(filterLayout);
    this->sortBox->setLayout(sortLayout);
    this->washBox->setLayout(washLayout);
    this->otherBox->setLayout(otherLayout);

    // constructing the right side of the window
    commandsLayout->addWidget(this->operationsBox);
    commandsLayout->addWidget(this->filterBox);
    commandsLayout->addWidget(this->sortBox);
    commandsLayout->addWidget(this->washBox);
    commandsLayout->addWidget(this->otherBox);

    this->commandsBox->setLayout(commandsLayout);

    rightSideLayout->addWidget(this->commandsBox);
    rightSide->setLayout(rightSideLayout);


    // === ADDING THE ELEMENTS TO THE WINDOW ===
    this->mainLayout->addWidget(leftSide);
    this->mainLayout->addWidget(rightSide);
    this->setLayout(this->mainLayout);

    QIcon iconMain("car-icon.png");
    QIcon iconWash("car-wash.png");
    this->setWindowIcon(iconMain);
    this->washWindow->setWindowIcon(iconWash);

    // setting the geometry of the windows -> initial postion
    QRect mainWindowRect(50, 50, 1000, 300);
    QRect washRect(1200, 50, 600, 200);

    this->setGeometry(mainWindowRect);
    this->washWindow->setGeometry(washRect);

    this->setWindowTitle("Car Rental Service"); // title of the main window
    this->washWindow->setWindowTitle("Washing List"); // title of the washing list window

    // dynamic btns layout
    this->btnsDynamicGB->setLayout(this->btnsDynamicLay);

    this->mainLayout->addWidget(this->btnsDynamicGB);

    this->washWindow->show();
    this->show();
}

void CarGUI::connectSignals_Slots() {
    // connecting all the buttons to their assigned functionality
    QObject::connect(this->btnAdd, &QPushButton::clicked, this, &CarGUI::guiAdd);
    QObject::connect(this->btnDelete, &QPushButton::clicked, this, &CarGUI::guiDelete);
    QObject::connect(this->btnModify, &QPushButton::clicked, this, &CarGUI::guiModify);
    QObject::connect(this->btnFind, &QPushButton::clicked, this, &CarGUI::guiFind);

    QObject::connect(this->btnFilter, &QPushButton::clicked, this, [&]() {
        if (this->radioFilterProducer->isChecked())
            this->guiFilter(this->filterCriteria->text().toStdString(), Service::compareByProducer);
        else if (this->radioFilterType->isChecked())
            this->guiFilter(this->filterCriteria->text().toStdString(), Service::compareByType);
    });
    QObject::connect(this->btnSort, &QPushButton::clicked, this, [&]() {
        if (this->radioSortRegNumber->isChecked())
            this->reloadList(Service::sortRegNumber(this->service.getCars()));
        else if (this->radioSortType->isChecked())
            this->reloadList(Service::sortType(this->service.getCars()));
        else if (this->radioSortProdMod->isChecked())
            this->reloadList(Service::sortProducerModel(this->service.getCars()));
    });

    QObject::connect(this->btnAddToWash, &QPushButton::clicked, this, &CarGUI::guiAddToWash);
    QObject::connect(this->btnClearWash, &QPushButton::clicked, this, &CarGUI::guiClearWash);
    QObject::connect(this->btnGenerateWash, &QPushButton::clicked, this, &CarGUI::guiGenerateWash);

    QObject::connect(this->btnUndo, &QPushButton::clicked, this, &CarGUI::guiUndo);
    QObject::connect(this->btnCountModels, &QPushButton::clicked, this, &CarGUI::guiCountModels);
    QObject::connect(this->btnExport, &QPushButton::clicked, this, &CarGUI::guiExport);
    QObject::connect(this->btnClose, &QPushButton::clicked, this, [this] {
        QMessageBox::information(this, "Feedback", "Leaving the app...");
        QApplication::quit();
    });
}

void CarGUI::reloadList(const vector<Car> &cars) {
    // clearing the table widget of the and resizing it
    this->tableCars->clearContents();
    this->tableCars->setRowCount(cars.size());

    // keeping track of the current line number
    auto lineNumber = 0;
    for (const auto &car: cars) {
        this->tableCars->setItem(lineNumber, 0,
                                 new QTableWidgetItem(QString::fromStdString(car.getRegNumber())));
        this->tableCars->setItem(lineNumber, 1,
                                 new QTableWidgetItem(QString::fromStdString(car.getProducer())));
        this->tableCars->setItem(lineNumber, 2,
                                 new QTableWidgetItem(QString::fromStdString(car.getModel())));
        this->tableCars->setItem(lineNumber, 3,
                                 new QTableWidgetItem(QString::fromStdString(car.getType())));
        ++lineNumber;
    }
}

void CarGUI::reloadWashingList() {
    // clearing the table
    this->tableWash->clearContents();

    // setting the number of cars which should be added
    this->tableWash->setRowCount(this->service.getWashingList().washSize());

    int lineNumber = 0;

    // refreshing the list
    for (const auto &car: this->service.getWashingList().washCars()) {
        this->tableWash->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(car.getRegNumber())));
        this->tableWash->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(car.getProducer())));
        this->tableWash->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
        this->tableWash->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(car.getType())));
        ++lineNumber;
    }
}

void CarGUI::guiAdd() {
    // building a new window for this op

    auto *addWindow = new QWidget;
    auto *addWindowLayout = new QFormLayout;
    addWindow->setLayout(addWindowLayout);

    // building a form for grouping the fields of the entity to add
    auto *lblRegNumber = new QLabel{"Registration Number"};
    auto *lblProducer = new QLabel{"Producer"};
    auto *lblModel = new QLabel{"Model"};
    auto *lblType = new QLabel{"Type"};

    auto *editRegNumber = new QLineEdit;
    auto *editProducer = new QLineEdit;
    auto *editModel = new QLineEdit;
    auto *editType = new QLineEdit;

    addWindowLayout->addRow(lblRegNumber, editRegNumber);
    addWindowLayout->addRow(lblProducer, editProducer);
    addWindowLayout->addRow(lblModel, editModel);
    addWindowLayout->addRow(lblType, editType);

    auto *addBtn = new QPushButton("&Add");
    auto *addBtnClose = new QPushButton("&Close");

    addWindowLayout->addWidget(addBtn);
    addWindowLayout->addWidget(addBtnClose);

    addWindow->setFixedSize(400, 400);
    addWindow->show();

    QObject::connect(addBtnClose, &QPushButton::clicked, addWindow, [addWindow]() {
        addWindow->close();
    });

    QObject::connect(addBtn, &QPushButton::clicked, addWindow, [=]() {
        try {
            // capturing the strings from the form
            string regNumber = editRegNumber->text().toStdString();
            string producer = editProducer->text().toStdString();
            string model = editModel->text().toStdString();
            string type = editType->text().toStdString();

            // adding the car to the list
            this->service.addCarService(regNumber, producer, model, type);

            // reupdating the list
            this->reloadList(this->service.getCars());

            // showing a message of success
            QMessageBox::information(addWindow, "Feedback", "Car added successfully!");

            // updating the btns
            this->updateDynamicBtns();

            // closing the window
            addWindow->close();
        } catch (RepositoryException &rE) {
            QMessageBox::warning(addWindow, "Warning", QString::fromStdString(rE.getMessage()));
        }
        catch (ValidatorException &vE) {
            QMessageBox::warning(addWindow, "Warning", QString::fromStdString(vE.getMessage()));
        }
    });
}

void CarGUI::guiDelete() {
    // building the window for the delete operation
    auto *deleteWindow = new QWidget;
    auto *deleteWindowLayout = new QFormLayout;
    deleteWindow->setLayout(deleteWindowLayout);

    auto *labelDelete = new QLabel("Registration number");
    auto *editDelete = new QLineEdit;

    auto *deleteBtn = new QPushButton("&Delete");
    auto *deleteBtnClose = new QPushButton("&Close");

    deleteWindowLayout->addRow(labelDelete, editDelete);
    deleteWindowLayout->addWidget(deleteBtn);
    deleteWindowLayout->addWidget(deleteBtnClose);

    deleteWindow->setFixedSize(400, 400);
    deleteWindow->show();

    QObject::connect(deleteBtnClose, &QPushButton::clicked, deleteWindow, [deleteWindow]() {
        deleteWindow->close();
    });

    QObject::connect(deleteBtn, &QPushButton::clicked, deleteWindow, [=]() {
        try {
            // capturing the elements of the form
            string regNumber = editDelete->text().toStdString();

            // deleting the car from the list
            auto deleted = this->service.deleteCarService(regNumber);

            // reupdating the list
            this->reloadList(this->service.getCars());

            // feedback on the successful operation
            auto message = QString::fromStdString("Deleted: " + deleted.getRegNumber() + " | " + deleted.getProducer() +
                                                  " | " + deleted.getModel() + " | " + deleted.getType());
            QMessageBox::information(deleteWindow, "Feedback", message);

            // updating the btns
            this->updateDynamicBtns();

            // closing the window
            deleteWindow->close();
        } catch (RepositoryException &rE) {
            QMessageBox::warning(deleteWindow, "Warning", QString::fromStdString(rE.getMessage()));
        }
    });
}

void CarGUI::guiModify() {
    // new window for the modifying op
    auto *modifyWindow = new QWidget;
    auto *modifyWindowLayout = new QFormLayout;
    modifyWindow->setLayout(modifyWindowLayout);

    auto *regLabel = new QLabel("Registration number");
    auto *regNewProducer = new QLabel("New producer");
    auto *regNewModel = new QLabel("New model");
    auto *regNewType = new QLabel("New type");

    auto *editRegNumber = new QLineEdit;
    auto *editNewProducer = new QLineEdit;
    auto *editNewModel = new QLineEdit;
    auto *editNewType = new QLineEdit;

    modifyWindowLayout->addRow(regLabel, editRegNumber);
    modifyWindowLayout->addRow(regNewProducer, editNewProducer);
    modifyWindowLayout->addRow(regNewModel, editNewModel);
    modifyWindowLayout->addRow(regNewType, editNewType);

    auto *modifyBtn = new QPushButton("&Modify");
    auto *modifyBtnClose = new QPushButton("&Close");

    modifyWindowLayout->addWidget(modifyBtn);
    modifyWindowLayout->addWidget(modifyBtnClose);

    modifyWindow->setFixedSize(400, 400);
    modifyWindow->show();

    QObject::connect(modifyBtnClose, &QPushButton::clicked, modifyWindow, [modifyWindow]() {
        modifyWindow->close();
    });

    QObject::connect(modifyBtn, &QPushButton::clicked, modifyWindow, [=]() {
        try {
            // capturing the fields from the form
            string regNumber = editRegNumber->text().toStdString();
            string newProducer = editNewProducer->text().toStdString();
            string newModel = editNewModel->text().toStdString();
            string newType = editNewType->text().toStdString();

            // modifying effectively
            auto modified = this->service.modifyCarService(regNumber, newProducer, newModel, newType);

            // reloading the list
            this->reloadList(this->service.getCars());

            // showing a information message
            auto message = QString::fromStdString(
                    "Modified: " + modified.getRegNumber() + " | " + modified.getProducer()
                    + " | " + modified.getModel() + " | " + modified.getType());
            QMessageBox::information(modifyWindow, "Feedback", message);

            // updating the btns
            this->updateDynamicBtns();

            // closing the window
            modifyWindow->close();
        } catch (RepositoryException &rE) {
            QMessageBox::warning(modifyWindow, "Warning", QString::fromStdString(rE.getMessage()));
        } catch (ServiceException &sE) {
            QMessageBox::warning(modifyWindow, "Warning", QString::fromStdString(sE.getMessage()));
        }
    });
}

void CarGUI::guiFind() const {
    // new window for the finding op
    auto *findWindow = new QWidget;
    auto *findWindowLayout = new QFormLayout;

    auto *btns = new QWidget;
    auto *btnsLayout = new QHBoxLayout;

    findWindow->setLayout(findWindowLayout);
    btns->setLayout(btnsLayout);

    auto *regLabel = new QLabel("Registration number");
    auto *regEdit = new QLineEdit;

    findWindowLayout->addRow(regLabel, regEdit);

    auto *findBtn = new QPushButton("&Find");
    auto *findBtnClose = new QPushButton("&Close");

    btnsLayout->addWidget(findBtn);
    btnsLayout->addWidget(findBtnClose);

    findWindowLayout->addWidget(btns);

    findWindow->setFixedSize(400, 400);
    findWindow->show();

    QObject::connect(findBtnClose, &QPushButton::clicked, findWindow, [findWindow]() {
        findWindow->close();
    });

    QObject::connect(findBtn, &QPushButton::clicked, findWindow, [=]() {

        try {
            // capturing the fields from the form
            string regNumber = regEdit->text().toStdString();

            // finding the car
            auto found = this->service.findCarService(regNumber);

            // printing the car
            auto message = QString::fromStdString("Found: " + found.getRegNumber() +
                                                  " | " + found.getProducer() + " | " + found.getModel() + " | " +
                                                  found.getType());
            QMessageBox::information(findWindow, "Feedback", message);

            // closing the window
            findWindow->close();
        } catch (RepositoryException &rE) {
            QMessageBox::warning(findWindow, "Warning", QString::fromStdString(rE.getMessage()));
        }
    });
}

void CarGUI::guiFilter(const string &criteria, bool(*compareMethod)(const Car &, const string &)) const {
    // will show a new table containing the cars which are filtered
    try {
        // first we'll build the list using the parameters provided
        auto filteredCars = this->service.filter(criteria, compareMethod);

        // constructing a new window which will contain the filtered cars
        auto *filteredWindow = new QWidget;
        auto *tableFiltered = new QTableWidget;
        auto *tableLayout = new QVBoxLayout;
        auto *btnTableClose = new QPushButton("&Close");

        filteredWindow->setLayout(tableLayout);
        tableFiltered->setColumnCount(4);

        QStringList tableHeader;
        tableHeader << "Registration Number" << "Producer" << "Model" << "Type";

        tableFiltered->setHorizontalHeaderLabels(tableHeader);
        tableFiltered->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        tableLayout->addWidget(tableFiltered);
        tableLayout->addWidget(btnTableClose);

        filteredWindow->setFixedSize(600, 600);
        filteredWindow->show();

        // completing the table
        int lineNumber = 0;
        tableFiltered->setRowCount(filteredCars.size());
        for (const auto &car: filteredCars) {
            tableFiltered->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(car.getRegNumber())));
            tableFiltered->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(car.getProducer())));
            tableFiltered->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
            tableFiltered->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(car.getType())));

            ++lineNumber;
        }

        QObject::connect(btnTableClose, &QPushButton::clicked, filteredWindow, [filteredWindow]() {
            filteredWindow->close();
        });


    } catch (ServiceException &sE) {
        QMessageBox::warning((QWidget *) this, "Warning", "There are no cars with the specified criteria!");
    }
}

void CarGUI::guiAddToWash() {
    // initializing a new window for this app
    auto *addWashWindow = new QWidget;
    auto *addWashLayout = new QFormLayout;

    addWashWindow->setLayout(addWashLayout);

    auto *addWashLabel = new QLabel("Registration number");
    auto *addWashEdit = new QLineEdit;

    auto *addWashBtn = new QPushButton("&Add to wash");
    auto *addWashBtnClose = new QPushButton("&Close");

    addWashLayout->addRow(addWashLabel, addWashEdit);
    addWashLayout->addWidget(addWashBtn);
    addWashLayout->addWidget(addWashBtnClose);

    addWashWindow->setFixedSize(400, 400);
    addWashWindow->show();

    QObject::connect(addWashBtnClose, &QPushButton::clicked, addWashWindow, [addWashWindow]() {
        addWashWindow->close();
    });

    QObject::connect(addWashBtn, &QPushButton::clicked, addWashWindow, [=]() {
        // capturing the elements of the form
        string regNumber = addWashEdit->text().toStdString();
        try {
            // adding the car to the washing list
            this->service.addToWashingList(regNumber);

            // refreshing the washing list
            this->reloadWashingList();

            // showing a message of success
            QMessageBox::information(addWashWindow, "Feedback", "Car added successfully!");

            // showing the list if it is closed
            if (this->washWindow->isHidden()) {
                this->washWindow->show();
            }

        } catch (ServiceException &sE) {
            QMessageBox::warning(addWashWindow, "Warning",
                                 "The car with the specified registration number does not exist!");
        }
        addWashWindow->close();
    });
}

void CarGUI::guiClearWash() {
    // verifying first if the list is clear
    if (this->service.getWashingList().washSize() == 0) {
        QMessageBox::warning(this, "Warning", "The list is already clear!");
        return;
    }
    // clearing the list
    this->service.clearWashingList();

    // updating the list
    this->reloadWashingList();

    // showing a message of success
    QMessageBox::information(this, "Feedback", "Washing list clear successfully!");

    // showing the window if it is closed
    if (this->washWindow->isHidden()) {
        this->washWindow->show();
    }
}

void CarGUI::guiGenerateWash() {
    // verifying first if the list is clear
    if (this->service.getCars().empty()) {
        QMessageBox::warning(this, "Warning", "The car list is empty!");
        return;
    }
    // building a new window
    auto *generateWashWindow = new QWidget;
    auto *generateWashLayout = new QVBoxLayout;
    generateWashWindow->setLayout(generateWashLayout);

    // a layout for the buttons
    auto *generateBtnsWidget = new QWidget;
    auto *generateBtnsLayout = new QHBoxLayout;
    generateBtnsWidget->setLayout(generateBtnsLayout);

    auto *generateBtn = new QPushButton("&Generate");
    auto *closeBtn = new QPushButton("&Close");

    generateBtnsLayout->addWidget(generateBtn);
    generateBtnsLayout->addWidget(closeBtn);

    // using a slider for selecting the number of cars to be generated
    auto *numberSlider = new QSlider(Qt::Horizontal);
    numberSlider->setMinimum(1);
    numberSlider->setMaximum(this->service.getCars().size());
    numberSlider->hasTracking();

    // building a new widget of labels to show the minimum number of cars, the maximum, and the current value
    auto *labelWindow = new QWidget;
    auto *labelLayout = new QVBoxLayout;
    labelWindow->setLayout(labelLayout);

    auto *minimumLabel = new QLabel(
            QString::fromStdString("Minimum cars to be generated: " + std::to_string(numberSlider->minimum())));
    auto *maximumLabel = new QLabel(
            QString::fromStdString("Maximum cars to be generated: " + std::to_string(numberSlider->maximum())));
    auto *currentLabel = new QLabel(
            QString::fromStdString("Number of cars to be generated: " + std::to_string(numberSlider->value())));

    labelLayout->addWidget(minimumLabel);
    labelLayout->addWidget(maximumLabel);
    labelLayout->addWidget(currentLabel);

    generateWashLayout->addWidget(labelWindow);
    generateWashLayout->addWidget(numberSlider);
    generateWashLayout->addWidget(generateBtnsWidget);

    generateWashWindow->show();

    QObject::connect(closeBtn, &QPushButton::clicked, generateWashWindow, [generateWashWindow]() {
        generateWashWindow->close();
    });

    QObject::connect(numberSlider, &QSlider::valueChanged, currentLabel, [numberSlider, currentLabel]() {
        currentLabel->setText(
                QString::fromStdString("Number of cars to be generated: " + std::to_string(numberSlider->value())));
    });

    QObject::connect(generateBtn, &QPushButton::clicked, generateWashWindow, [=]() {
        // capturing the value from the slider
        auto numberOfCars = numberSlider->value();

        // generating the car list
        this->service.randomWashingList(numberOfCars, this->service.getCars());

        // reloading the washing list
        this->reloadWashingList();

        // showing a message of success
        QMessageBox::information(generateWashWindow, "Feedback", "Generated successfully!");

        // showing the wash list if it is closed
        if (this->washWindow->isHidden()) {
            this->washWindow->show();
        }

        // closing the window
        generateWashWindow->close();
    });
}

void CarGUI::guiUndo() {
    try {
        // doing undo
        this->service.undo();

        // reloading the list
        this->reloadList(this->service.getCars());

        // showing a message of success
        QMessageBox::information(this, "Feedback", "Undo successful!");

        // updating the btns
        this->updateDynamicBtns();

    } catch (ServiceException &sE) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(sE.getMessage()));
    }
}

void CarGUI::guiCountModels() const {
    if (this->service.getCars().empty()) {
        QMessageBox::warning(this->window(), "Warning", "The car list is empty!");
        return;
    }
    // building a new window
    auto *countWindow = new QWidget;
    auto *countLayout = new QVBoxLayout;
    countWindow->setLayout(countLayout);

    auto *countTable = new QTableWidget;
    auto *closeBtn = new QPushButton("&Close");

    countTable->setColumnCount(2);
    countTable->setHorizontalHeaderLabels(QStringList{"Model", "Number of"});
    countTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // populating the table
    auto countModels = this->service.countModels();
    countTable->setRowCount(countModels.size());
    int lineNumber = 0;
    for (const auto &model: countModels) {
        countTable->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(model.first)));
        countTable->setItem(lineNumber, 1, new QTableWidgetItem(QString::number(model.second.getCount())));
        ++lineNumber;
    }

    countLayout->addWidget(countTable);
    countLayout->addWidget(closeBtn);

    countWindow->setFixedSize(600, 600);
    countWindow->show();

    QObject::connect(closeBtn, &QPushButton::clicked, countWindow, [countWindow]() {
        countWindow->close();
    });
}

void CarGUI::guiExport() const {
    if (this->service.getWashingList().washSize() == 0) {
        QMessageBox::warning(this->window(), "Warning", "The washing list is empty!");
        return;
    }

    // building a new window
    auto *exportWindow = new QWidget;
    auto *exportLayout = new QFormLayout;
    exportWindow->setLayout(exportLayout);

    auto *btns = new QWidget;
    auto *btnsLayout = new QHBoxLayout;
    btns->setLayout(btnsLayout);

    auto *exportBtn = new QPushButton("&Export");
    auto *closeBtn = new QPushButton("&Close");

    btnsLayout->addWidget(exportBtn);
    btnsLayout->addWidget(closeBtn);

    // using a combo box to show the options of file extensions
    auto *extensionsList = new QComboBox;
    extensionsList->addItems(QStringList{"csv", "html"});

    // line edit for the file name
    auto *editFile = new QLineEdit;

    exportLayout->addRow("File name", editFile);
    exportLayout->addRow("Extensions", extensionsList);
    exportLayout->addWidget(btns);

    exportWindow->setFixedSize(400, 400);
    exportWindow->show();

    QObject::connect(exportBtn, &QPushButton::clicked, exportWindow, [=]() {
        // constructing the file
        string extension = "." + extensionsList->currentText().toStdString();
        string fileName = editFile->text().toStdString() + extension;
        try {
            // now we export to the file
            this->service.exportToFile(fileName, extension);
            // showing a message of success
            QMessageBox::information(exportWindow, "Feedback", "Exported successfully!");
        } catch (ServiceException &sE) {
            QMessageBox::warning(exportWindow, "Warning", QString::fromStdString(sE.getMessage()));
        }
        exportWindow->close();
    });

    QObject::connect(closeBtn, &QPushButton::clicked, exportWindow, [exportWindow]() {
        exportWindow->close();
    });
}

void CarGUI::updateDynamicBtns() {
    // clearing the contents of the btns dynamic widget
    qDeleteAll(this->btnsDynamicGB->findChildren<QPushButton *>());

    // getting the stats
    auto stats = this->service.countModels();

    // adding the buttons
    for(const auto &stat: stats) {
        auto *dynamicBtn = new QPushButton(QString::fromStdString(stat.second.getModel()));
        this->btnsDynamicLay->addWidget(dynamicBtn);

        // connecting the button to a action
        QObject::connect(dynamicBtn, &QPushButton::clicked, this, [this, stat](){
            auto message = QString::fromStdString("Number of " + stat.second.getModel() + " is " + std::to_string(stat.second.getCount()));
            QMessageBox::information(this, "Feedback", message);
        });
    }
}