#pragma once

#include "Repository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0; // nu exista implementare, functie pur virtuala

    virtual ~ActiuneUndo() = default;

};

class UndoAdauga : public ActiuneUndo {
private:
    Car addedCar;
    Repository &carRepo;
public:
    UndoAdauga(const Car &car, Repository &repo) : addedCar{car}, carRepo{repo} {}

    void doUndo() override {
        this->carRepo.deleteCar(this->addedCar.getRegNumber());
    }
};

class UndoDelete : public ActiuneUndo {
private:
    Car deletedCar;
    Repository &carRepo;
public:
    UndoDelete(const Car &car, Repository &repo) : deletedCar{car}, carRepo{repo} {}

    void doUndo() override {
        this->carRepo.addCar(this->deletedCar);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Car modifiedCar;
    Repository &carRepo;
public:
    UndoModifica(const Car &car, Repository &repo) : modifiedCar{car}, carRepo{repo} {}

    void doUndo() override {
        this->carRepo.modifyCar(this->modifiedCar);
    }
};