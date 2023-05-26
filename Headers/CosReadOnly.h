#pragma once

#include <random>
#include <QWidget>
#include <QLayout>
#include <QPainter>
#include "Observer.h"
#include "Service.h"

class CosReadOnly: public QWidget, public Observer {
private:
    Service& service;

    QLayout *lay = new QHBoxLayout;

    void initRDO() {
        this->setLayout(this->lay);

        this->setFixedSize(500, 500);
        this->setWindowTitle("Wash List Read Only");
        this->show();
    }

public:
    explicit CosReadOnly(Service& serv): service{serv} {
        this->initRDO();
    }

    void paintEvent(QPaintEvent*) override {
        QPainter painter{this};

        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<> distW(0, this->width() - 100);
        std::uniform_int_distribution<> distH(0, this->height() - 100);

        for(auto i = 0; i < this->service.getWashingList().washSize(); i++) {
            auto randW = distW(mt);
            auto randH = distH(mt);

            if(i % 4 == 0) {
                painter.setBrush(QBrush{Qt::red});
            } else if(i % 4 == 1) {
                painter.setBrush(QBrush{Qt::green});
            } else if(i % 4 == 2) {
                painter.setBrush(QBrush{Qt::blue});
            } else {
                painter.setBrush(QBrush{Qt::yellow});
            }
            painter.drawEllipse(randW, randH, 50, 50);

        }
    }

    void update() override {
        qDeleteAll(this->lay->findChildren<QObject*>());
        this->repaint();
    }
};