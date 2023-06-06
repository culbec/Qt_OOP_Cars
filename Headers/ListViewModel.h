#pragma once

#include <vector>
#include <QAbstractListModel>
#include "Car.h"

class ListViewModel : public QAbstractListModel {
private:
    Service& service;

public:
    explicit ListViewModel(Service &s) : service{s} {}

    // returning the number of rows
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override {
        return this->service.getCars().size();
    }

    // returning the number of columns
    int columnCount(const QModelIndex &parent = QModelIndex{}) const override {
        return 4;
    }

    // interpreting the data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        // will analyze more roles and interpret their data
        int row = index.row();
        int col = index.column();

        if(role == Qt::DisplayRole) {
            if(index.row() < this->service.getCars().size()) {
                auto item = this->service.getCars().at(index.row());
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

    void notifica() {
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomRight);
    }

};