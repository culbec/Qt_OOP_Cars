#pragma once

#include "Observer.h"
#include "Service.h"
#include <QPushButton>
#include <QListWidget>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>

class CosCRUDGUI: public Observer {
    Service& service;
private:
    QWidget *wnd = new QWidget;
    QVBoxLayout *lay = new QVBoxLayout;

    QListWidget *lst = new QListWidget;
    QPushButton *btnClear = new QPushButton("&Clear");
    QPushButton *btnGen = new QPushButton("&Generate");

    void initCRUD() {
        this->wnd->setLayout(this->lay);

        this->lay->addWidget(this->lst);

        auto *btnSection = new QGroupBox("Actions");
        auto *layBtnSection = new QHBoxLayout;
        btnSection->setLayout(layBtnSection);

        layBtnSection->addWidget(this->btnGen);
        layBtnSection->addWidget(this->btnClear);

        this->lay->addWidget(btnSection);

        this->wnd->setWindowTitle("Wash List CRUD");
        this->wnd->show();
    }

    void connectSigs() {
        QObject::connect(this->btnClear, &QPushButton::clicked, [&](){
            this->lst->clear();
        });

        QObject::connect(this->btnGen, &QPushButton::clicked, [&](){
            if(this->service.getCars().empty()) {
                QMessageBox::warning(this->wnd, "Warning", "Car list is empty!");
                return;
            }

            auto *sld = new QSlider;
            sld->setMinimum(1);
            sld->setMaximum(this->service.getCars().size());
            sld->setOrientation(Qt::Horizontal);

            auto *sldWnd = new QWidget;
            auto *sldLay = new QVBoxLayout;
            sldWnd->setLayout(sldLay);

            auto *genBtn = new QPushButton("Generate");
            auto *lbl = new QLabel{"Cars to generate: " + QString::fromStdString(std::to_string(sld->value()))};

            sldLay->addWidget(new QLabel{"Minimum cars to generate: " + QString::fromStdString(std::to_string(sld->minimum()))});
            sldLay->addWidget(new QLabel{"Minimum cars to generate: " + QString::fromStdString(std::to_string(sld->maximum()))});
            sldLay->addWidget(lbl);
            sldLay->addWidget(sld);
            sldLay->addWidget(genBtn);

            sldWnd->show();

            QObject::connect(sld, &QSlider::valueChanged, [=](){
                lbl->setText("Cars to generate: " + QString::fromStdString(std::to_string(sld->value())));
            });

            QObject::connect(genBtn, &QPushButton::clicked, [=](){
                this->service.randomWashingList(sld->value(), this->service.getCars());
                this->update();
                sldWnd->close();
            });

        });
    }

public:
    CosCRUDGUI(Service& serv): service{serv} {
        this->initCRUD();
        this->connectSigs();
    }

    void update() override {
        this->lst->clear();

        for(const auto& car: this->service.getWashingList().washCars()) {
                auto *item = new QListWidgetItem;
                auto str = car.getRegNumber() + "\t" + car.getProducer() + "\t" + car.getModel() + "\t" + car.getType();
                item->setText(QString::fromStdString(str));

                this->lst->addItem(item);
        }
    }
};