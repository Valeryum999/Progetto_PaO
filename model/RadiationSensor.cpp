#include "model/RadiationSensor.h"
#include <stdlib.h>
#include <iostream>

RadiationSensor::RadiationSensor(QString name, QString description, double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(name,description,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

RadiationSensor::RadiationSensor(QString id,QString name, QString description, double minValue, double maxValue,QString unityOfMeasure): AbstractSensor(id,name,description,minValue,maxValue), unityOfMeasure(unityOfMeasure){

};

RadiationSensor::RadiationSensor(const RadiationSensor& sensor): AbstractSensor(sensor.getUUID(),sensor.getName(),sensor.getDescription(),sensor.getMinValue(),sensor.getMaxValue()),unityOfMeasure(sensor.getUnityOfMeasure()){

};

QString RadiationSensor::getUnityOfMeasure() const {
    return unityOfMeasure;
};

void RadiationSensor::setUnityOfMeasure(const QString& unityOfMeasure) {
    this->unityOfMeasure = unityOfMeasure;
};

std::vector<double> RadiationSensor::generateData(){
    data.clear();
    int range = static_cast<int>(getMaxValue()-getMinValue());
    for(int i=0;i<21;i++){
        data.push_back(rand()%range + getMinValue());
    }
    return data;
};

void RadiationSensor::RadiationSensor::accept(Visitor& visitor) {
    visitor.visit(*this);
};

QJsonObject RadiationSensor::RadiationSensor::toJson() const{
    QJsonObject json;
    json["uuid"] = this->getUUID();
    json["name"] = this->getName();
    json["description"] = this->getDescription();
    json["type"] = QString::fromStdString("Radiation");
    json["unity_of_measure"] = unityOfMeasure;
    json["min_value"] = this->getMinValue();
    json["max_value"] = this->getMaxValue();
    return json;
};

RadiationSensor* RadiationSensor::clone() const{
    return new RadiationSensor(*this);
};

