#include <utility>

#include "../Headers/Car.h"

Car::Car(string regNumberC, string producerC, string modelC, string typeC) {
    this->regNumber = std::move(regNumberC); // placeholder pt ID, e acelasi lucru
    this->producer = std::move(producerC);
    this->model = std::move(modelC);
    this->type = std::move(typeC);
}

Car::Car(const Car &other) {
    // std::cout << "Copy constructor called!\n";

    this->setRegNumber(other.getRegNumber());
    this->setProducer(other.getProducer());
    this->setModel(other.getModel());
    this->setType(other.getType());
}

string Car::getRegNumber() const { return this->regNumber; }

string Car::getProducer() const { return this->producer; }

string Car::getModel() const { return this->model; }

string Car::getType() const { return this->type; }

void Car::setRegNumber(const string &newRegNumber) { this->regNumber = newRegNumber; }

void Car::setProducer(const string &newProducer) { this->producer = newProducer; }

void Car::setModel(const string &newModel) { this->model = newModel; }

void Car::setType(const string &newType) { this->type = newType; }

