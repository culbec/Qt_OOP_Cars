#pragma once

#include "Car.h"
#include <utility>
#include <vector>
#include <exception>
#include <algorithm>
#include <iterator>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::exception;
using std::remove;
using std::find_if;
using std::copy;
using std::back_inserter;
using std::copy_if;

typedef vector<Car> carList;

// declaram o exceptie custom pentru repository:
class RepositoryException : std::exception {
private:
    string errorMessage;
public:
    explicit RepositoryException(string message) : errorMessage(std::move(message)) {}

    string getMessage() { return this->errorMessage; }
};

class Repository {
    friend class Car;

private:
    carList cars; // lista de masini
public:

    Repository() noexcept = default; // constructor implicit
    Repository(const Repository &) = delete; // nu permitem copierea

    /*
        Returneaza lista de masini a repository-ului
        @pre: true
        @post: lista de masini a repo-ului
    */
    [[nodiscard]] virtual const carList &getCars() const;

    /*
        Size-ul listei de masini
        @pre: true
        @post: size-ul listei de masini
    */
    [[nodiscard]] virtual size_t getSize() const noexcept;

    /*
        Cauta o masina dupa un anumit id si ii returneaza pozitia.
        @pre: string -> numar de inmatriculare
        @post: pozitia masinii
        @exception: masina nu exista in lista
    */

    [[nodiscard]] virtual size_t findCar(const string &) const;

    /*
        Adauga o masina la lista de masini
        @pre: Car -> obiect de tip Car valid
        @post: obiectul de tip Car adaugat la lista de masini
    */
    virtual void addCar(const Car &);

    /*
        Sterge o masina din lista de masini
        @pre: string -> numar de inmatriculare
        @post: masina stearsa
        @exception: nu exista masina in lista
    */
    virtual Car deleteCar(const string &);

    /*
        Modifica o masina din lista de masini
        @pre: string -> numar de inmatriculare
              string -> producator
              string -> model
              string -> tip
        @post: masina modificata
        @exception: nu exista masina in lista
    */
    virtual Car modifyCar(const Car &);

    /*
        Functie de copiere (deep copy)
        @pre: true
        @post: lista de masini este copiata
    */
    static carList copyList(const carList &);

    // destructor virtual -> pentru ca clasele derivate sa isi apeleze constructorul in functie de obiectul lor
    virtual ~Repository() = default;
};

// using inheritance to create a file repository

class FileRepository : public Repository {
private:
    string fileName; // numele fisierului in care facem scriere/citire
    void loadFromFile(); // functie de incarcare din fisier
    void writeToFile(); // functie de stocare in fisier
public:
    // constructorul pentru clasa derivata
    explicit FileRepository(const string &file) {
        this->fileName = file;
        this->loadFromFile();
    }

    // metode suprascrise din clasa de baza
    void addCar(const Car &) override;

    Car deleteCar(const string &) override;

    Car modifyCar(const Car &) override;
};

