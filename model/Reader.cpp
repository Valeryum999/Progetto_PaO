#include "Reader.h"
#include <iostream>
#include <string>

AbstractSensor* Reader::read(const QJsonObject& object){
    std::string objectType = object["type"].toString().toStdString();
    if(objectType.compare("Humidity") == 0){
        return readHumiditySensor(object);
    } else if (objectType.compare("Temperature") == 0){
        return readTemperatureSensor(object);
    }
    return new HumiditySensor(QString::fromStdString("null"),QString::fromStdString("null"),QString::fromStdString("null"));
};

HumiditySensor* Reader::readHumiditySensor(const QJsonObject& object) const {
    return new HumiditySensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["type"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble(),
        object["percentage"].toInt()
    );
};

TemperatureSensor* Reader::readTemperatureSensor(const QJsonObject& object) const {
    return new TemperatureSensor(
        object["uuid"].toString(),
        object["name"].toString(),
        object["description"].toString(),
        object["type"].toString(),
        object["min_value"].toDouble(),
        object["max_value"].toDouble(),
        object["unity_of_measure"].toString()
    );
};