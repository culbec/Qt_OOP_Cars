#pragma once

#include "Car.h"
#include <QAbstractTableModel>
#include <vector>
#include <QFont>
#include <QBrush>

class TableViewModel : public QAbstractTableModel {
private:
    const std::vector<Car> cars;

public:
    explicit TableViewModel(const std::vector<Car> &c): cars{c} {}

    int rowCount(const QModelIndex &parent) const override {
        return this->cars.size();
    }

    int columnCount(const QModelIndex &parent) const override {
        return 4;
    }

    QVariant data(const QModelIndex &parent, int role) const override {
        int row = parent.row();
        int col = parent.column();

        if(role == Qt::DisplayRole) {
            auto car = this->cars.at(row);
            if(col == 0) {
                return QString::fromStdString(car.getRegNumber());
            } else if (col == 1) {
                return QString::fromStdString(car.getProducer());
            } else if (col == 2) {
                return QString::fromStdString(car.getModel());
            } else if (col == 3) {
                return QString::fromStdString(car.getType());
            }
        } else if (role == Qt::FontRole) {
            QFont ft;
            if(col % 2 == 0) {
                ft.setBold(true);
            } else {
                ft.setItalic(true);
            }
            return ft;
        } else if (role == Qt::BackgroundRole) {
            if(row % 2 == 0) {
                if (col % 2 == 0) {
                    return QBrush{Qt::black};
                } else {
                    return QBrush{Qt::darkMagenta};
                }
            } else {
                if (col % 2 == 0) {
                    return QBrush{Qt::darkGreen};
                } else {
                    return QBrush{Qt::darkRed};
                }
            }
        }
    }
};