#include "../Headers/UI.h"

using std::cout;
using std::cin;

void UI::uiCommands() {
    cout << "\nComenzile sunt: ";
    cout << "\nhelp, show_cars, add_car, delete_car, modify_car, find_car, filter_producer, filter_type\n"
            "sort_reg_number, sort_type, sort_producer_model, export, undo, exit.\n\n";
    cout << "Washing List commands: add_to_wash, clear_wash, generate_wash\n";
    cout << "Count models: count_models\n\n";
}

void UI::uiShowCars() {
    if (this->carService.getCars().empty()) {
        cout << "\nNu exista masini in lista!\n";
        return;
    }

    cout << "\nLista de masini este: \n\n";

    for (const auto &car: this->carService.getCars())
        cout << car;
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiAddCar() {
    string regNumber, producer, model, type;

    cout << "Nr. de inmatriculare: ";
    cin >> regNumber;
    cout << "Producator: ";
    cin >> producer;
    cout << "Model: ";
    cin >> model;
    cout << "Tip: ";
    cin >> type;

    try {
        this->carService.addCarService(regNumber, producer, model, type);
        cout << "\nMasina adaugata cu succes!\n";
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (RepositoryException &rE) { cout << rE.getMessage(); }
    catch (ValidatorException &vE) { cout << vE.getMessage(); }
}

void UI::uiDeleteCar() {
    string regNumber;

    cout << "\nMasinile disponibile pentru stergere sunt urmatoarele: \n";

    this->uiShowCars();

    cout << "\nIntroduceti numarul de inmatriculare al masinii pe care vreti sa o stergeti: ";
    cin >> regNumber;

    try {
        const Car &deletedCar = this->carService.deleteCarService(regNumber);

        cout << "\nS-a sters cu succes masina: ";
        cout << deletedCar;
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (RepositoryException &rE) { cout << rE.getMessage(); }
}

void UI::uiModifyCar() {
    string regNumber;
    string newProducer, newModel, newType;

    cout << "Masinile disponibile pentru modificare sunt: \n";

    this->uiShowCars();

    cout << "\nIntroduceti numarul de inmatriculare al masinii pe care doriti sa o modificati: ";
    cin >> regNumber;

    cout << "Producator nou: ";
    cin >> newProducer;
    cout << "Model nou: ";
    cin >> newModel;
    cout << "Tip nou: ";
    cin >> newType;

    try {
        Car modifiedCar = this->carService.modifyCarService(regNumber, newProducer, newModel, newType);

        cout << "\nS-a modificat cu succes masina: ";
        cout << modifiedCar;
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (RepositoryException &rE) { cout << rE.getMessage(); }
    catch (ServiceException &sE) { cout << sE.getMessage(); }
}

void UI::uiFindCar() {
    string regNumber;

    cout << "Introduceti numarul de inmatriculare al masinii pe care o cautati: ";
    cin >> regNumber;

    try {
        Car foundCar = this->carService.findCarService(regNumber);

        cout << "\nMasina este: ";
        cout << foundCar;
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (RepositoryException &rE) { cout << rE.getMessage(); }
}

void UI::uiFilterByProducer() {
    string producer;

    cout << "Introduceti producatorul dupa care vreti sa filtrati: ";
    cin >> producer;

    try {
        const carList &filteredCars = this->carService.filter(producer, Service::compareByProducer);

        cout << "\nLista de masini filtrata dupa producatorul " << producer << " este:\n";
        for (const auto &car: filteredCars)
            cout << car;
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (ServiceException &sE) { cout << sE.getMessage(); }
}

void UI::uiFilterByType() {
    string type;

    cout << "Introduceti tipul dupa care vreti sa filtrati: ";
    cin >> type;

    try {
        const carList &filteredCars = this->carService.filter(type, Service::compareByType);

        cout << "\nLista de masini filtrata dupa tipul " << type << " este:\n";
        for (const auto &car: filteredCars)
            cout << car;
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    }
    catch (ServiceException &sE) { cout << sE.getMessage(); }
}

void UI::uiSortRegNumber() {
    cout << "\nLista de masini sortata dupa numarul de inmatriculare este:\n";
    for (const auto &car: Service::sortRegNumber(this->carService.getCars()))
        cout << car;
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiSortType() {
    cout << "\nLista de masini sortata dupa tip este:\n";
    for (const auto &car: Service::sortType(this->carService.getCars()))
        cout << car << "\n";
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiSortProducerModel() {
    cout << "\nLista de masini sortata dupa producator si model este:\n";
    for (const auto &car: Service::sortProducerModel(this->carService.getCars()))
        cout << car << "\n";
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiAddToWash() {
    string regNumber;
    cout << "Numarul de inmatriculare al masinii de adaugat: ";
    cin >> regNumber;

    try {
        this->carService.addToWashingList(regNumber);
        cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
    } catch (ServiceException &sE) { cout << sE.getMessage(); }
}

void UI::uiClearWash() {
    this->carService.getWashingList().clearWash();
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiGenerateRandomWash() {
    unsigned int numberToGenerate;
    if (this->carService.getCars().empty()) {
        cout << "Nu exista masini in lista!\n";
        return;
    }
    while (true) {
        cout << "Numarul de masini de generat: ";
        cin >> numberToGenerate;

        if (numberToGenerate == 0 || numberToGenerate >= this->carService.getCars().size()) {
            cout << "Numarul de masini de generat trebuie sa fie intre 1 si " << this->carService.getCars().size() - 1
                 << ".\n";
            continue;
        }
        break;
    }
    carService.randomWashingList(numberToGenerate, this->carService.getCars());
    cout << "\nMasini pentru spalat: " << carService.getWashingList().washSize() << "\n";
}

void UI::uiCountModels() {
    if (this->carService.getCars().empty()) {
        cout << "Nu exista masini in lista!\n";
        return;
    }

    unordered_map<string, DTO> totalModels = this->carService.countModels();

    cout << "The models are: \n";

    for (const auto &entry: totalModels)
        cout << entry.first << " " << entry.second.getCount() << "\n";
}

void UI::uiExportToFile() {
    string fileName;
    cout << "Nume fisier: ";
    cin >> fileName;
    while (true) {
        string option;
        cout << "Doriti sa exportati fisierul in format CSV sau in format HTML? Tastati 'exit' pentru iesire: ";
        cin >> option;
        if (option == "exit") {
            cout << "Iesire export...\n";
            return;
        } else if (option == "CSV") {
            fileName.append(".csv");
            this->carService.exportToFile(fileName, ".csv");
            break;
        } else if (option == "HTML") {
            fileName.append(".html");
            this->carService.exportToFile(fileName, ".html");
            break;
        } else {
            cout << "Optiune invalida!\n";
        }
    }
    cout << "Export cu succes!\n";
}

void UI::uiUndo() {
    try {
        this->carService.undo();
        cout << "Undo done!" << std::endl;
    } catch (ServiceException &sE) {
        cout << sE.getMessage() << std::endl;
    }
}

void UI::uiRun() {
    cout << "\n--------------- Car Rental Service ---------------\n";
    string option;
    while (true) {
        /*this->uiCommands();
        cout << "Introduceti optiunea: ";
        cin >> option;
        if (option == "help")
            continue;
        else if (option == "show_cars")
            this->uiShowCars();
        else if (option == "add_car")
            this->uiAddCar();
        else if (option == "delete_car")
            this->uiDeleteCar();
        else if (option == "modify_car")
            this->uiModifyCar();
        else if (option == "find_car")
            this->uiFindCar();
        else if (option == "filter_producer")
            this->uiFilterByProducer();
        else if (option == "filter_type")
            this->uiFilterByType();
        else if (option == "sort_reg_number")
            this->uiSortRegNumber();
        else if (option == "sort_type")
            this->uiSortType();
        else if (option == "sort_producer_model")
            this->uiSortProducerModel();
        else if (option == "add_to_wash")
            this->uiAddToWash();
        else if (option == "clear_wash")
            this->uiClearWash();
        else if (option == "generate_wash")
            this->uiGenerateRandomWash();
        else if (option == "count_models")
            this->uiCountModels();
        else if (option == "export")
            this->uiExportToFile();
        else if (option == "undo")
            this->uiUndo();
        else if (option == "exit") {
            cout << "Leaving...";
            return;
        } else
            cout << "Optiune invalida.\n";*/
        (this->*commands["help"])();
        cout << "Option: ";
        cin >> option;
        if (this->commands.find(option) != this->commands.end()) {
            if (option == "exit") {
                cout << "Leaving...\n";
                return;
            } else {
                (this->*commands[option])();
            }
        } else {
            cout << "Invalid option!\n";
        }
    }
}
