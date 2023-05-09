#pragma once

#include "Car.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class WashingList {
private:
    // lista de masini ce trebuie spalate
    vector<Car> toWash;
public:
    // constructor implicit
    WashingList() noexcept = default;

    [[nodiscard]] vector<Car> washCars() const;

    /**
     * @brief Lungimea listei masinilor de spalat
     * @pre true
     * @post true
     * @return lungimea listei masinilor de spalat
     */
    [[nodiscard]] size_t washSize() const;

    /**
     * @brief Adaugare masina in lista de spalare
     * @pre true
     * @post Se adauga o masina in lista de spalare
     */
    void addToWash(const Car &);

    /**
     * @brief Goleste lista de masini
     * @pre Exista masini in lista
     * @post Lista de masini se goleste
     */
    void clearWash();

    /**
     * @brief Generate a random list
     * @pre   Exista masini in lista ; numberToGenerate = [0, size(totalCars)]
     * @post  Se genereaza o lista random cu masini de spalat
     */
    static vector<Car> generateRandom(unsigned int, vector<Car> &);
};