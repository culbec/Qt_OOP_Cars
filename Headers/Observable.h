#pragma once

#include "Observer.h"
#include <vector>

class Observable {
protected:
    std::vector<Observer*> observers;
public:
    virtual void addObserver(Observer*) = 0;
    virtual void notify() = 0;
    virtual ~Observable() = default;
};