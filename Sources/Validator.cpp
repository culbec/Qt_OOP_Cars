#include "../Headers/Validator.h"

bool Validator::validateRegNumber(const Car &car) {
    string errors; // vom pastra toate erorile

    string regNumber = car.getRegNumber(); // retinem numarul de inmatriculare

    // verificam daca nr. de inmatriculare este string-ul vid
    if (regNumber.empty())
        throw ValidatorException("Nr. de inmatriculare nu poate fi vid!"); // aruncam direct exceptie

    // verificam daca nr. de inmatriculare se incadreaza ca lungime intre 6 si 7
    if (regNumber.size() < 6 || regNumber.size() > 7)
        throw ValidatorException(
                "Nr. de inmatriculare trebuie sa fie de forma: \n Exemplu: CJ12CEVA, pentru toate judetele inafara de Bucuresti\n Exemplu: B76XZY sau B777ZZZ pentru judetul Bucuresti.\n");

    // acum putem valida numarul de inmatriculare
    if (regNumber.at(0) == 'B' && !(regNumber.at(1) >= 'A' && regNumber.at(1) <= 'Z')) {
        if (regNumber.size() == 7) {
            if ((regNumber.at(1) >= '1' && regNumber.at(1) <= '9') &&
                (regNumber.at(2) >= '0' && regNumber.at(2) <= '9') &&
                (regNumber.at(3) >= '0' && regNumber.at(3) <= '9')) { //numar de genul B132XYZ
                if (!(regNumber.at(4) >= 'A' && regNumber.at(4) <= 'Z')) errors = errors +
                                                                                  "Caracterul de pe pozitia 5 trebuie sa fie litera majuscula!\n";
                else if (!(regNumber.at(5) >= 'A' && regNumber.at(5) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 6 trebuie sa fie litera majuscula!\n";
                else if (!(regNumber.at(6) >= 'A' && regNumber.at(6) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 7 trebuie sa fie litera majuscula!\n";
            } else
                errors = errors + "'B' trebuie sa fie urmat de 3 cifre!\n";
        } else {
            // numar de genul B10YCZ
            if (!(regNumber.at(3) >= 'A' && regNumber.at(3) <= 'Z')) errors = errors +
                                                                              "'B' trebuie sa fie urmat de 2 cifre si 3 litere!\n";
            else if ((regNumber.at(1) >= '0' && regNumber.at(1) <= '9') &&
                     (regNumber.at(2) >= '0' && regNumber.at(2) <= '9')) { // avem numar de genul B100XYZ
                // numar de genul B10_YZ
                if (!(regNumber.at(3) >= 'A' && regNumber.at(3) <= 'Z')) errors = errors +
                                                                                  "Caracterul de pe pozitia 5 trebuie sa fie litera majuscula!\n";
                    // numar de genul B10X_Z
                else if (!(regNumber.at(4) >= 'A' && regNumber.at(4) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 6 trebuie sa fie litera majuscula!\n";
                    // numar de genul B10XY_
                else if (!(regNumber.at(5) >= 'A' && regNumber.at(5) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 7 trebuie sa fie litera majuscula!\n";
            } else errors = errors + "'B' trebuie sa fie urmat de 2 cifre si 3 litere!\n";
        }
    } else {
        if (regNumber.size() != 7)
            errors = errors + "Numarul de inmatriculare trebuie sa fie de forma: CJ77ZZZ!\n";
        else {
            if ((regNumber.at(2) >= '0' && regNumber.at(2) <= '9') &&
                (regNumber.at(3) >= '0' && regNumber.at(3) <= '9')) {
                if (!(regNumber.at(4) >= 'A' && regNumber.at(4) <= 'Z')) errors = errors +
                                                                                  "Caracterul de pe pozitia 5 trebuie sa fie litera majuscula!\n";
                else if (!(regNumber.at(5) >= 'A' && regNumber.at(5) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 6 trebuie sa fie litera majuscula!\n";
                else if (!(regNumber.at(6) >= 'A' && regNumber.at(6) <= 'Z')) errors = errors +
                                                                                       "Caracterul de pe pozitia 7 trebuie sa fie litera majuscula!\n";
            } else errors = errors + "Judetul trebuie sa fie urmat de 2 cifre!\n";
        }
    }
    if (!errors.empty())
        throw ValidatorException(errors);
    return true;
}

bool Validator::validateProducer(const Car &car) {
    string producer = car.getProducer(); // salvam producatorul

    if (producer.empty())
        throw ValidatorException("Producatorul nu poate fi vid!\n");

    string errors; // aici salvam erorile

    if (producer.at(0) < 'A' || producer.at(0) > 'Z')
        errors += "Producatorul trebuie sa inceapa cu majuscula!\n";

    for (unsigned int i = 1; i < producer.size(); i++)
        if (!(producer.at(i) >= 'a' && producer.at(i) <= 'z') && !(producer.at(i) >= 'A' && producer.at(i) <= 'Z')) {
            errors += "Producatorul trebuie sa contina doar litere!\n";
            break;
        }
    if (!errors.empty())
        throw ValidatorException(errors);

    return true;
}

bool Validator::validateModel(const Car &car) {
    string model = car.getModel(); // aici salvam modelul masinii

    if (model.empty())
        throw ValidatorException("Modelul nu poate sa fie vid!\n");

    return true;
}

bool Validator::validateType(const Car &car) {
    string type = car.getType(); // aici salvam tipul masinii;

    if (type.empty())
        throw ValidatorException("Tipul nu poate sa fie nul!\n");
    return true;
}

bool Validator::validateCar(const Car &car, const Repository &carRepo) {
    string errors; // aici salvam erorile

    try {
        validateRegNumber(car);
    }
    catch (ValidatorException &validatorException) {
        errors += validatorException.getMessage();
    }

    try {
        validateProducer(car);
    }
    catch (ValidatorException &validatorException) {
        errors += validatorException.getMessage();
    }

    try {
        validateModel(car);
    }
    catch (ValidatorException &validatorException) {
        errors += validatorException.getMessage();
    }

    try {
        carRepo.findCar(car.getRegNumber());
        errors += "Masina exista deja in lista!\n";
    }
    catch (RepositoryException &repositoryException) {}

    if (!errors.empty())
        throw ValidatorException(errors);
    return true;
}
