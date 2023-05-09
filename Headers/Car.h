#pragma once

#include <string>
#include <iostream>

using std::string;

class Car {
private:
    // O masina contine un ID unic - nr. inmatriculare
    // pe de alta parte, contine un model si un tip
    string regNumber, producer, model, type;
public:
    // constructor explicit, instantiaza un obiect cu anumite atribute
    /*
        @pre: atributele trebuie sa fie de tip string
        @post: se creeaza obiectul cu atributele specificate
    */
    Car(string, string, string, string);

    // copy constructor
    Car(const Car &other);

    // gettere peste atributele obiectului
    [[nodiscard]] string getRegNumber() const;

    [[nodiscard]] string getProducer() const;

    [[nodiscard]] string getModel() const;

    [[nodiscard]] string getType() const;

    // settere peste atributele obiectului, atribute ce pot fi modificate
    // am ales arbitrar ca acestea sa fie producatorul, modelul si tipul
    /*
        @pre: atributele trebuie sa fie de tip string, fiind de asemenea o referinta
        @post: obiectul isi modifica atributele specificate
    */
    void setRegNumber(const string &);

    void setProducer(const string &);

    void setModel(const string &);

    void setType(const string &);

    // overriding operators
    bool operator==(const Car &otherCar) const {
        return this->getRegNumber() == otherCar.getRegNumber();
    }

    friend std::ostream &operator<<(std::ostream &os, const Car &car) {
        os << car.getRegNumber() << " | " << car.getProducer() << " | " << car.getModel() << " | " << car.getType()
           << "\n";
        return os;
    }
};


