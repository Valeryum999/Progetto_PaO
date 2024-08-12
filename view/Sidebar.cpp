#include "view/Sidebar.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QString>
#include <QLabel>
#include <iostream>

Sidebar::Sidebar(QWidget* parent): QWidget(parent){
   
    layout = new QVBoxLayout(this);
    scrollArea = new QScrollArea();
    sensorPanel = new PanelSensor(nullptr);
    searchBar = new QLineEdit();
    searchBar->setFixedHeight(32);
    searchBar->setPlaceholderText(QString::fromStdString("Search"));
    scrollBar = scrollArea->verticalScrollBar();
    scrollBar->setParent(scrollArea);
    jolly = new QPushButton(QString::fromStdString("Create new sensor"));

    scrollAreaLayout = new QHBoxLayout(scrollArea);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0); //290
    scrollAreaLayout->setSpacing(0);
    scrollAreaLayout->addWidget(sensorPanel);
    scrollAreaLayout->addWidget(scrollBar,1,Qt::AlignRight);
    scrollArea->setLayout(scrollAreaLayout);
    
    // scrollArea->setWidget(sensorPanel);
    //scrollArea->setFixedWidth(320);
    //scrollArea->setFixedHeight(20);

    layout->addWidget(searchBar);
    layout->addWidget(scrollArea);
    layout->addWidget(jolly);

    setFixedWidth(330);
    setLayout(layout);

    connect(sensorPanel, &PanelSensor::sensorSelected, this, &Sidebar::handleSensorWidgetInSensorPanelSelected);
    connect(sensorPanel, &PanelSensor::sensorDeleted, this, &Sidebar::handleSensorWidgetDeleted);
    connect(sensorPanel, &PanelSensor::modifySensorSignal,this,&Sidebar::handleModifyButtonPressed);
    connect(searchBar,&QLineEdit::textChanged,this,&Sidebar::handleSearchBarTextChanged);
    connect(this,&Sidebar::searchBarTextChanged,sensorPanel,&PanelSensor::searchSensors);
    connect(jolly,&QPushButton::released,this,&Sidebar::handleCreateNewSensorButtonPressed);
};

Sidebar::Sidebar(std::vector<WidgetSensor*> sensors,QWidget* parent): QWidget(parent){
   
    layout = new QVBoxLayout(this);
    scrollArea = new QScrollArea();
    sensorPanel = new PanelSensor(sensors,nullptr);
    searchBar = new QLineEdit();
    searchBar->setFixedHeight(32);
    searchBar->setPlaceholderText(QString::fromStdString("Search"));
    scrollBar = scrollArea->verticalScrollBar();
    scrollBar->setParent(scrollArea);
    jolly = new QPushButton(QString::fromStdString("Create new sensor"));

    scrollAreaLayout = new QHBoxLayout(scrollArea);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);
    scrollAreaLayout->setSpacing(0);
    //scrollAreaLayout->addWidget(sensorPanel);
    scrollAreaLayout->addWidget(scrollBar,1,Qt::AlignRight);
    scrollArea->setLayout(scrollAreaLayout);
    
    scrollArea->setWidget(sensorPanel);
    //scrollArea->setFixedWidth(320);
    //scrollArea->setFixedHeight(20);

    layout->addWidget(searchBar);
    layout->addWidget(scrollArea);
    layout->addWidget(jolly);

    setFixedWidth(330);
    setLayout(layout);
    connect(sensorPanel, &PanelSensor::sensorSelected, this, &Sidebar::handleSensorWidgetInSensorPanelSelected);
    connect(sensorPanel, &PanelSensor::sensorDeleted, this, &Sidebar::handleSensorWidgetDeleted);
    connect(sensorPanel, &PanelSensor::modifySensorSignal,this,&Sidebar::handleModifyButtonPressed);
    connect(searchBar,&QLineEdit::textChanged,this,&Sidebar::handleSearchBarTextChanged);
    connect(this,&Sidebar::searchBarTextChanged,sensorPanel,&PanelSensor::searchSensors);
    connect(jolly,&QPushButton::released,this,&Sidebar::handleCreateNewSensorButtonPressed);
};

void Sidebar::setSensorPanel(std::vector<WidgetSensor*> sensors){
    sensorPanel->setSensors(sensors);
    sensorPanel->adjustSize();
    scrollArea->setWidget(sensorPanel); //per qualche motivo questo serve
};

void Sidebar::setSensorPanel(std::vector<AbstractSensor*> sensors){
    sensorPanel->setSensors(sensors);
    sensorPanel->adjustSize();
    scrollArea->setWidget(sensorPanel); //per qualche motivo questo serve
};

void Sidebar::setSensorPanel(PanelSensor *sensors){
    sensorPanel = sensors;
};

void Sidebar::addSensor(AbstractSensor* sensor){
    sensorPanel->addSensor(sensor);
    sensorPanel->adjustSize();
    scrollArea->setWidget(sensorPanel);
};

void Sidebar::modifySensorInSensorPanel(AbstractSensor* sensor){
    sensorPanel->modifySensor(sensor);
    scrollArea->setWidget(sensorPanel);
};

void Sidebar::handleSearchBarTextChanged(const QString& query){
    emit searchBarTextChanged(query);
    sensorPanel->adjustSize();
    //scrollArea->setWidget(sensorPanel);
};

void Sidebar::handleSensorWidgetInSensorPanelSelected(AbstractSensor* sensor){
    emit sensorSelectedInSensorPanel(sensor);
};

void Sidebar::handleModifyButtonPressed(AbstractSensor* sensor){
    emit modifySensor(sensor);
};

void Sidebar::handleSensorWidgetDeleted(AbstractSensor* sensor){
    sensorPanel->adjustSize();
    emit sensorDeleted(sensor);
    //scrollArea->setWidget(sensorPanel);
};

void Sidebar::handleCreateNewSensorButtonPressed(){
    emit createNewSensor();
}

void Sidebar::debug(){
    sensorPanel->debug();
}