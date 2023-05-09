#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include "../Headers/Service.h"

class UI {
private:
    // UI-ul contine un service pentru masini
    Service &carService;

    // meniul de comenzi
    std::unordered_map<std::string, void (UI::*)()> commands{
            {"help",                &UI::uiCommands},
            {"show_cars",           &UI::uiShowCars},
            {"add_car",             &UI::uiAddCar},
            {"delete_car",          &UI::uiDeleteCar},
            {"modify_car",          &UI::uiModifyCar},
            {"find_car",            &UI::uiFindCar},
            {"filter_producer",     &UI::uiFilterByProducer},
            {"filter_type",         &UI::uiFilterByType},
            {"sort_reg_number",     &UI::uiSortRegNumber},
            {"sort_type",           &UI::uiSortType},
            {"sort_producer_model", &UI::uiSortProducerModel},
            {"exit",                nullptr},
            {"add_to_wash",         &UI::uiAddToWash},
            {"clear_wash",          &UI::uiClearWash},
            {"generate_wash",       &UI::uiGenerateRandomWash},
            {"count_models",        &UI::uiCountModels},
            {"export",              &UI::uiExportToFile},
            {"undo",                &UI::uiUndo}
    };
public:
    // constructorul implicit al UI-ului
    explicit UI(Service &service) noexcept: carService(service) {}

    // afiseaza comenzile disponibile
    void uiCommands();

    /*
        Functie de afisare a masinilor
        @pre: true
        @post: lista de masini
        @eroare: nu exista masini in lista
    */
    void uiShowCars();

    /*
        Functie de adaugare a unei masini
        @pre: true
        @post: masina adaugata
        @eroare: nu se poate adauga masina din cazurile de validitate
    */
    void uiAddCar();

    /*
        Functie de stergere a unei masini
        @pre: true
        @post: masina stearsa
        @eroare: nu se poate sterge masina, daca nu exista
    */
    void uiDeleteCar();

    /*
        Functie de cautare a unei masini dupa nr. de inmatriculare
        @pre: true
        @post: masina cautata
        @eroare: masina nu exista
    */

    void uiFindCar();

    /*
        Functie de modificare a unei masini
        @pre: true
        @post: masina modificata
        @eroare: nu se poate modifica masina, daca nu exista sau parametrii sunt invalizi
    */
    void uiModifyCar();

    /*
        Functie de filtrare a masinilor dupa producator
        @pre: true
        @post: lista de masini filtrate
        @eroare: lista filtrata este goala
    */
    void uiFilterByProducer();

    /*
        Functie de filtrare a masinilor dupa tip
        @pre: true
        @post: lista de masini filtrate
        @eroare: lista filtrata este goala
    */
    void uiFilterByType();


    // functiile de sortare
    void uiSortRegNumber();

    void uiSortType();

    void uiSortProducerModel();

    // functiile pentru washing list
    void uiAddToWash();

    void uiClearWash();

    void uiGenerateRandomWash();

    void uiCountModels();

    /*
     * Functie de export in fisier a datelor din lista de masini pentru spalat
     * @pre: true
     * @post: se exporta masinile, daca exista, in fisierul specificat
     */
    void uiExportToFile();

    /*
     * Functie de undo a ultimei operatii efectuate
     * @pre: sa se fi efectuat operatii inainte de apel
     * @post: se va restaura starea precedenta ultimei operatii executate
     */
    void uiUndo();

    // rulare pentru UI
    void uiRun();
};


