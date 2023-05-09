#include "../Headers/Repository.h"

const carList &Repository::getCars() const { return this->cars; }

size_t Repository::getSize() const noexcept { return this->cars.size(); }

size_t Repository::findCar(const string &regNumberToFind) const {
    auto found = std::find_if(this->cars.begin(), this->cars.end(), [regNumberToFind](const Car &car) {
        return car.getRegNumber() == regNumberToFind;
    });

    if (found != this->cars.end())
        return found - this->cars.begin();
    throw RepositoryException("Masina nu exista in lista!\n");
}

void Repository::addCar(const Car &carToAdd) {
    this->cars.push_back(carToAdd);
}

Car Repository::deleteCar(const string &regNumberOfCarToDelete) {
    try {
        auto position = this->cars.begin() + findCar(regNumberOfCarToDelete);

        Car deletedCar(*position);
        this->cars.erase(position);

        return deletedCar;
    }
    catch (const RepositoryException &) {
        throw RepositoryException("Nu se poate sterge deoarece nu exista masina in lista!\n");
    }
}

Car Repository::modifyCar(const Car &newCar) {
    try {
        auto position = this->cars.begin() + findCar(newCar.getRegNumber());

        Car modifiedCar(*position);
        *position = Car(newCar.getRegNumber(), newCar.getProducer(), newCar.getModel(), newCar.getType());

        return modifiedCar;
    }
    catch (const RepositoryException &) {
        throw RepositoryException("Nu se poate modifica deoarece nu exista masina in lista!\n");
    }
}

carList Repository::copyList(const carList &list) {
    carList copyList;
    copy(list.begin(), list.end(), back_inserter(copyList));

    return copyList;
}

void FileRepository::loadFromFile() {
    // initializam stream-ul de citire
    ifstream fin(this->fileName);

    // verificam daca s-a deschis
    if (!fin.is_open()) {
        throw RepositoryException("Error opening: " + this->fileName);
    }

    while (!fin.eof()) {
        // preluam parametrii din fisier dupa delimitatorul ','
        string regNumber, producer, model, type;
        std::getline(fin, regNumber, ',');
        if (regNumber.empty()) // check pentru linii goala
            break;
        std::getline(fin, producer, ',');
        std::getline(fin, model, ',');
        std::getline(fin, type, '\n');

        // adaugam masina in lista de masini apeland metoda din clasa de baza
        // daca am fi apelat metoda din clasa derivata, am fi intrat intr-un loop continuu
        // deoarece metoda ar fi incercat sa prelucreze fisierul in continuu
        Car car{regNumber, producer, model, type};
        Repository::addCar(car);
    }

    fin.close();
}

void FileRepository::writeToFile() {
    // initializam stream-ul de scriere
    ofstream fout(this->fileName);

    // verificam daca s-a deschis
    if (!fout.is_open()) {
        throw RepositoryException("Error open: " + this->fileName);
    }

    for (const auto &car: this->getCars()) {
        fout << car.getRegNumber() << "," << car.getProducer() << "," << car.getModel() << "," << car.getType();
        fout << std::endl;
        std::flush(fout);
    }

    fout.close();
}

void FileRepository::addCar(const Car &car) {
    Repository::addCar(car); // apelam metoda din clasa de baza
    this->writeToFile(); // scriem in fisier
}

Car FileRepository::deleteCar(const string &regNumber) {
    Car deleted = Repository::deleteCar(regNumber); // apelam metoda din clasa de baza
    this->writeToFile(); // scriem in fisier
    return deleted;
}

Car FileRepository::modifyCar(const Car &car) {
    Car modified = Repository::modifyCar(car); // apelam metoda din clasa de baza
    this->writeToFile(); // scriem in fisier
    return modified;
}