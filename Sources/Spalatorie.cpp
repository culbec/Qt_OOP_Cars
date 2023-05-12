#include "../Headers/Spalatorie.h"

vector<Car> WashingList::washCars() const {
    return this->toWash;
}

size_t WashingList::washSize() const {
    return this->toWash.size();
}

void WashingList::addToWash(const Car &carToAdd) {
    this->toWash.push_back(carToAdd);
}

void WashingList::clearWash() {
    this->toWash.clear();
}

vector<Car> WashingList::generateRandom(unsigned int numberToGenerate, vector<Car> &cars) {
    vector<Car> randomList;
    randomList.reserve(numberToGenerate);

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cars.begin(), cars.end(), std::default_random_engine(seed));

    for (auto i = 0; i < numberToGenerate; i++)
        randomList.push_back(cars.at(i));

    return randomList;}