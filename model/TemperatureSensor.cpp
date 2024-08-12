#include "model/TemperatureSensor.h"
#include "view/Visitor.h"
#include <stdlib.h>
#include <iostream>

TemperatureSensor::TemperatureSensor(QString name, QString description, QString type,double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(name,description,type,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

TemperatureSensor::TemperatureSensor(QString id,QString name, QString description, QString type,double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(id,name,description,type,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

TemperatureSensor::TemperatureSensor(const TemperatureSensor& sensor): AbstractSensor(sensor.getUUID(),sensor.getName(),sensor.getDescription(),sensor.getType(),sensor.getMinValue(),sensor.getMaxValue()),unityOfMeasure(sensor.getUnityOfMeasure()){

};

QString TemperatureSensor::getUnityOfMeasure() const {
    return unityOfMeasure;
};

void TemperatureSensor::setUnityOfMeasure(const QString& unityOfMeasure) {
    this->unityOfMeasure = unityOfMeasure;
};

std::vector<double> TemperatureSensor::generateData(){
    data.clear();
    int range = static_cast<int>(getMaxValue()-getMinValue());
    for(int i=0;i<21;i++){
        data.push_back(rand()%range + getMinValue());
    }
    return data;
};

void TemperatureSensor::TemperatureSensor::accept(Visitor& visitor) {
    visitor.visit(*this);
};

QJsonObject TemperatureSensor::TemperatureSensor::toJson() const{
    QJsonObject json;
    json["uuid"] = this->getUUID();
    json["name"] = this->getName();
    json["description"] = this->getDescription();
    json["type"] = this->getType();
    json["unity_of_measure"] = unityOfMeasure;
    json["min_value"] = this->getMinValue();
    json["max_value"] = this->getMaxValue();
    return json;
};

TemperatureSensor* TemperatureSensor::clone() const{
    return new TemperatureSensor(*this);
};

