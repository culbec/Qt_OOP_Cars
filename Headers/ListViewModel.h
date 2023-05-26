#pragma once

#include <vector>
#include <QAbstractListModel>
#include "Car.h"

class ListViewModel : public QAbstractListModel {
private:
    const std::vector<Car>& cars;

public:
    explicit ListViewModel(const std::vector<Car>& c) : cars{c} {}

    // returning the number of rows
    int rowCount(const QModelIndex &parent) const override {
        return this->cars.size();
    }

    // returning the number of columns
    int columnCount(const QModelIndex &parent) const override {
        return 4;
    }

    // interpreting the data
    QVariant data(const QModelIndex &index, int role) const override {
        // will analyze more roles and interpret their data
        int row = index.row();
        int col = index.column();

        if(role == Qt::DisplayRole) {
            if(index.row() < this->cars.size()) {
                auto item = this->cars.at(index.row());
                auto msg = item.getRegNumber() + "\t" + item.getProducer() + "\t" + item.getModel() + "\t" +
                           item.getType();
                return QString::fromStdString(msg);
            }
        }

        if(role == Qt::FontRole) {
            QFont qfont;
            if(index.row() % 2 == 0) {
                qfont.setBold(true);
                return QFont(qfont);
            } else {
                qfont.setItalic(true);
                return QFont(qfont);
            }
        }

        if(role == Qt::BackgroundRole) {
            if(index.row() % 2 == 0) {
                QBrush bg{Qt::blue};
                return bg;
            } else {
                QBrush bg{Qt::green};
                return bg;
            }
        }

        if(role == Qt::ForegroundRole) {
            if(index.row() % 2) {
                QBrush fg{Qt::black};
                return fg;
            }
        }

        return QVariant();
    }


};