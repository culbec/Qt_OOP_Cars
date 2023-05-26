#pragma once

#include "Observable.h"
#include "Car.h"
#include <vector>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};