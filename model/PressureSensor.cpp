#include "model/PressureSensor.h"
#include <stdlib.h>
#include <iostream>

PressureSensor::PressureSensor(QString name, QString description,double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(name,description,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

PressureSensor::PressureSensor(QString id,QString name, QString description, double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(id,name,description,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

PressureSensor::PressureSensor(const PressureSensor& sensor): AbstractSensor(sensor.getUUID(),sensor.getName(),sensor.getDescription(),sensor.getMinValue(),sensor.getMaxValue()),unityOfMeasure(sensor.getUnityOfMeasure()){

};

QString PressureSensor::getUnityOfMeasure() const {
    return unityOfMeasure;
};

void PressureSensor::setUnityOfMeasure(const QString& unityOfMeasure) {
    this->unityOfMeasure = unityOfMeasure;
};

std::vector<double> PressureSensor::generateData(){
    data.clear();
    int range = static_cast<int>(getMaxValue()-getMinValue());
    for(int i=0;i<21;i++){
        data.push_back(rand()%range + getMinValue());
    }
    return data;
};

void PressureSensor::PressureSensor::accept(Visitor& visitor) {
    visitor.visit(*this);
};

QJsonObject PressureSensor::PressureSensor::toJson() const{
    QJsonObject json;
    json["uuid"] = this->getUUID();
    json["name"] = this->getName();
    json["description"] = this->getDescription();
    json["type"] = QString::fromStdString("Pressure");
    json["unity_of_measure"] = unityOfMeasure;
    json["min_value"] = this->getMinValue();
    json["max_value"] = this->getMaxValue();
    return json;
};

PressureSensor* PressureSensor::clone() const{
    return new PressureSensor(*this);
};

