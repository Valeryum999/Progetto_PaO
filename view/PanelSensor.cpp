#include "view/WidgetSensor.h"
#include "view/PanelSensor.h"
#include "view/WidgetSensorVisitor.h"
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QScrollArea>
#include <QScrollBar>
#include <iostream>

PanelSensor::PanelSensor(QWidget* parent): QWidget(parent),sensors(){
    sensorsLayout = new QVBoxLayout(this);

    sensorsLayout->addStretch();
    sensorsLayout->setDirection(QVBoxLayout::TopToBottom);
    setLayout(sensorsLayout);
};

PanelSensor::PanelSensor(std::vector<WidgetSensor*> sensorsWidget,QWidget* parent): QWidget(parent), sensors(sensorsWidget){
    sensorsLayout = new QVBoxLayout(this); 

    for(std::vector<WidgetSensor*>::iterator it = sensorsWidget.begin(); it != sensorsWidget.end(); it++){
        sensors.push_back(*it);
    } 
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        sensorsLayout->addWidget(*it);
    }   
    sensorsLayout->addStretch();
    sensorsLayout->setDirection(QVBoxLayout::TopToBottom);
    setLayout(sensorsLayout);

    for (WidgetSensor* sensor : sensors) {
        connect(sensor, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
        connect(sensor, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
        connect(sensor, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
    }
};

void PanelSensor::setSensors(std::vector<AbstractSensor*> abstractSensors){
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        delete *it;
    }
    sensors.clear();
    for(std::vector<AbstractSensor*>::iterator it = abstractSensors.begin(); it != abstractSensors.end(); it++){
        WidgetSensor *temp = new WidgetSensor(*it,nullptr);
        sensors.push_back(temp);
    } 
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        sensorsLayout->addWidget(*it);
        (*it)->show();
    }   

    for (WidgetSensor* sensor : sensors) {
        connect(sensor, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
        connect(sensor, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
        connect(sensor, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
    }
};

void PanelSensor::debug(){
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
       
    }
};

void PanelSensor::setSensors(std::vector<WidgetSensor*> sensorsWidget){
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        delete *it;
    }
    sensors.clear();
    for(std::vector<WidgetSensor*>::iterator it = sensorsWidget.begin(); it != sensorsWidget.end(); it++){
        sensors.push_back((*it)->clone());
    } 
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        sensorsLayout->addWidget(*it);
    }   
    sensorsLayout->setStretch(-1,1);
    setLayout(sensorsLayout);
    for (WidgetSensor* sensor : sensors) {
        connect(sensor, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
        connect(sensor, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
        connect(sensor, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
    }
};

void PanelSensor::addSensor(AbstractSensor* sensor){
    WidgetSensor* tempSensor = new WidgetSensor(sensor,nullptr);
    sensors.push_back(tempSensor);
    sensorsLayout->addWidget(tempSensor);
    tempSensor->show();
    connect(tempSensor, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
    connect(tempSensor, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
    connect(tempSensor, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
};

void PanelSensor::modifySensor(AbstractSensor* sensor){
    int count = 1;
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        if(*(*it)->getAbstractSensor()==*sensor){
            delete *it;
            sensors.erase(it);
            WidgetSensor* tempSensor = new WidgetSensor(sensor);
            sensors.insert(it,tempSensor);
            connect(tempSensor, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
            connect(tempSensor, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
            connect(tempSensor, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
            sensorsLayout->insertWidget(count,tempSensor);
            //tempSensor->show();
        }
        count++;
    }   
};

void PanelSensor::searchSensors(const QString& query){
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        sensorsLayout->removeWidget(*it);
        (*it)->close();
    }
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        if((*it)->getName().contains(query) || (*it)->getId().contains(query) || (*it)->getDescription().contains(query)){
            sensorsLayout->addWidget(*it,1,Qt::AlignTop);
            (*it)->show();
        }
    }
}

void PanelSensor::handleSensorWidgetSelected(AbstractSensor* sensor){
    emit sensorSelected(sensor);
};

void PanelSensor::handleModifyButton(AbstractSensor* sensor){
    emit modifySensorSignal(sensor);
};

void PanelSensor::handleDeleteButton(AbstractSensor* sensor){
    for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
        if(*(*it)->getAbstractSensor()==*sensor){
            disconnect(*it, &WidgetSensor::selected, this, &PanelSensor::handleSensorWidgetSelected);
            disconnect(*it, &WidgetSensor::modify, this, &PanelSensor::handleModifyButton);
            disconnect(*it, &WidgetSensor::deleted, this, &PanelSensor::handleDeleteButton);
            sensorsLayout->removeWidget(*it);
            (*it)->close();
            delete *it;
            sensors.erase(it);
            break;
        }
    }
    //for(std::vector<WidgetSensor*>::iterator it = sensors.begin(); it != sensors.end(); it++){
    //   
    //    sensorsLayout->addWidget(*it);
    //}
    //sensorsLayout->insertStretch(-1,1);
    //delete sensor;
    emit sensorDeleted(sensor);
};