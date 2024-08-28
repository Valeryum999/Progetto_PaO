#include "Reader.h"
#include <iostream>
#include <string>

AbstractSensor* Reader::read(const QJsonObject& object){
    std::string objectType = object["type"].toString().toStdString();
    if(objectType.compare("Humidity") == 0){
        return readHumiditySensor(object);
    } else if (objectType.compare("Temperature") == 0){
        return readTemperatureSensor(object);
    } else if(objectType.compare("Pressure") == 0){
        return readPressureSensor(object);
    } else if(objectType.compare("Radiation") == 0){
        return readRadiationSensor(object);
    }
    return new HumiditySensor(QString::fromStdString("null"),QString::fromStdString("null"),QString::fromStdString("null"));
};

HumiditySensor* Reader::readHumiditySensor(const QJsonObject& object) const {
    return new HumiditySensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble()
    );
};

TemperatureSensor* Reader::readTemperatureSensor(const QJsonObject& object) const {
    return new TemperatureSensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble(),
        object["unity_of_measure"].toString()
    );
};

PressureSensor* Reader::readPressureSensor(const QJsonObject& object) const {
    return new PressureSensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble(),
        object["unity_of_measure"].toString()
    );
};

RadiationSensor* Reader::readRadiationSensor(const QJsonObject& object) const {
    return new RadiationSensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble(),
        object["unity_of_measure"].toString()
    );
};