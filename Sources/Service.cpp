#include "../Headers/Service.h"

const carList &Service::getCars() const { return this->carRepository.getCars(); }

bool Service::addCarService(const string &regNumber, const string &producer, const string &model, const string &type) {
    Car carToAdd(regNumber, producer, model, type); // initializing the car to add

    Validator::validateCar(carToAdd,
                           this->carRepository); // may have an exception, but it is handled by the repository

    // daca e cu succes, adaugam masina
    this->carRepository.addCar(carToAdd);
    this->undoList.push_back(std::make_unique<UndoAdauga>(UndoAdauga{carToAdd, this->carRepository}));
    return true;
}

Car Service::modifyCarService(const string &regNumber, const string &newProducer, const string &newModel,
                              const string &newType) {
    Car carModified(regNumber, newProducer, newModel, newType); // initializing the modified car

    // salvam erorile de la validari
    string validationErrors;

    try {
        Validator::validateProducer(carModified); // exception handled by the validator
    }
    catch (ValidatorException &vE) { validationErrors += vE.getMessage(); }

    try {
        Validator::validateModel(carModified); // exception handled by the validator
    }
    catch (ValidatorException &vE) { validationErrors += vE.getMessage(); }

    try {
        Validator::validateType(carModified); // exception handled by the validator
    }
    catch (ValidatorException &vE) { validationErrors += vE.getMessage(); }

    if (!validationErrors.empty())
        throw ServiceException(validationErrors);

    // daca e cu succes, modificam masina
    Car oldCar = this->carRepository.modifyCar(carModified); // exception handled by the repository
    this->undoList.push_back(std::make_unique<UndoModifica>(UndoModifica{oldCar, this->carRepository}));
    return oldCar;
}

Car Service::deleteCarService(const string &regNumberToDelete) {
    // returnam direct rezultatul stergerii
    // daca exista exceptie, va fi gestionata de repo
    Car deletedCar = this->carRepository.deleteCar(regNumberToDelete);
    this->undoList.push_back(std::make_unique<UndoDelete>(UndoDelete{deletedCar, this->carRepository}));
    return deletedCar;
}

Car Service::findCarService(const string &regNumberToFind) {
    // cautam masina prin intermediul repo
    // si returnam masina de pe pozitia gasita

    const unsigned int foundPosition = this->carRepository.findCar(regNumberToFind);

    return this->carRepository.getCars().at(foundPosition);
}

carList Service::filter(const string &whatFilter, bool(*compareMethod)(const Car &, const string &)) const {
    carList filteredCars; // initializam o lista vida

    // iteram prin lista
    const carList &currentCarList = this->carRepository.getCars();

    for (auto &car: currentCarList)
        if (compareMethod(car, whatFilter))
            filteredCars.push_back(car);

    // aruncam exceptie daca lista e goala
    if (filteredCars.empty())
        throw ServiceException("Nu s-au gasit masini cu parametrul specificat!\n");

    // altfel, returnam lista
    return filteredCars;
}

/*carList Service::generalSort(carList list, bool (*compareMethod)(const Car &, const Car &)) {
    for(auto i = 0; i < list.size() - 1; i++)
        for(auto j = i + 1; j < list.size(); j++)
            if(compareMethod(list.at(i), list.at(j)))
                list.swap(i, j);
    return list;
}*/

carList Service::sortRegNumber(const carList &list) {
    /*return Service::generalSort(Repository::copyList(list), [](const Car &car1, const Car &car2) {
        return car1.getRegNumber() > car2.getRegNumber();
    });*/
    carList toSort = Repository::copyList(list);

    sort(toSort.begin(), toSort.end(), [](const Car &car1, const Car &car2) {
        return car1.getRegNumber() < car2.getRegNumber();
    });

    return toSort;
}

carList Service::sortType(const carList &list) {
    /*return Service::generalSort(Repository::copyList(list), [](const Car &car1, const Car &car2) {
        return car1.getType() > car2.getType();
    });*/
    carList toSort = Repository::copyList(list);

    sort(toSort.begin(), toSort.end(), [](const Car &car1, const Car &car2) {
        return car1.getType() < car2.getType();
    });

    return toSort;
}

carList Service::sortProducerModel(const carList &list) {
    /*return Service::generalSort(Repository::copyList(list), [](const Car &car1, const Car &car2) {
        if (car1.getProducer() == car2.getProducer())
            return car1.getModel() > car2.getModel();
        return car1.getProducer() > car2.getProducer();
    });*/
    carList toSort = Repository::copyList(list);

    sort(toSort.begin(), toSort.end(), [](const Car &car1, const Car &car2) {
        if (car1.getProducer() == car2.getProducer())
            return car1.getModel() < car2.getModel();
        return car1.getProducer() < car2.getProducer();
    });

    return toSort;
}

WashingList Service::getWashingList() const {
    return this->washingList;
}

void Service::addToWashingList(const std::string &regNumber) {
    auto found = std::find_if(this->getCars().begin(), this->getCars().end(), [regNumber](const Car &car) {
        return car.getRegNumber() == regNumber;
    });

    if (found == this->getCars().end())
        throw ServiceException("Nu exista masina cu numarul de inmatriculare!\n");

    this->washingList.addToWash(*found);
}

void Service::clearWashingList() {
    this->washingList.clearWash();
}

void Service::randomWashingList(int numberToGenerate, const vector<Car> &cars) {
    vector<Car> toRandomize = Repository::copyList(cars);

    this->washingList.clearWash();
    vector<Car> randomWash = WashingList::generateRandom(numberToGenerate, toRandomize);
    for (const auto &car: randomWash)
        this->washingList.addToWash(car);
}

std::unordered_map<string, DTO> Service::countModels() const {
    unordered_map<string, DTO> totalModels;

    for (const auto &car: this->getCars())
        if (totalModels.find(car.getModel()) == totalModels.end()) {
            auto model = car.getModel();
            auto count = std::count_if(this->getCars().begin(), this->getCars().end(), [model](const Car &car) {
                return car.getModel() == model;
            });

            DTO dto(model, count);
            totalModels.insert({model, dto});
        }

    return totalModels;
}

void Service::exportToFile(const string &fileName, const string &extension) {
    std::ofstream fout(fileName + extension);

    if (!fout.is_open()) {
        throw ServiceException("Error open: " + fileName);
    }

    if (extension == ".html") {
        for (const auto &car: this->washingList.washCars()) {
            fout << "<p>";
            fout << car.getRegNumber() << "," << car.getProducer() << "," << car.getModel() << "," << car.getType() << "\n";
        }
    } else {
        for (const auto &car: this->washingList.washCars())
            fout << car.getRegNumber() << "," << car.getProducer() << "," << car.getModel() << "," << car.getType()
                 << "\n";
    }

    fout.close();
}

void Service::undo() {
    if (this->undoList.empty()) {
        throw ServiceException("No undo operations available.");
    }

    // instantiem un pointer catre obiectul ActiuneUndo pe care trebuie sa-l folosim
    // std::unique_ptr<ActiuneUndo> undoAction = std::make_unique<ActiuneUndo>(this->undoList.back());
    this->undoList.back()->doUndo();
    this->undoList.pop_back();
}