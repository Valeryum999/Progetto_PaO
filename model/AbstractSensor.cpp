#include "model/AbstractSensor.h"
#include <QUuid>
#include <iostream>

AbstractSensor::~AbstractSensor() = default;

AbstractSensor::AbstractSensor(QString name) : uuid(QUuid::createUuid().toString().remove("{").remove("}")),name(name), description("") {
};

AbstractSensor::AbstractSensor(QString name, QString description,double minValue, double maxValue) : uuid(QUuid::createUuid().toString().remove("{").remove("}")), name(name), description(description), minValue(minValue), maxValue(maxValue) {
};

AbstractSensor::AbstractSensor(QString uuid,QString name, QString description,double minValue, double maxValue) : uuid(uuid), name(name), description(description), minValue(minValue), maxValue(maxValue) {
};

QString AbstractSensor::getUUID() const {
    return uuid;
};

void AbstractSensor::setUUID(const QString& uuid) {
    this->uuid = uuid;
};

QString AbstractSensor::getName() const {
    return name;
};

void AbstractSensor::setName(const QString& name) {
    this->name = name;
};

QString AbstractSensor::getDescription() const {
    return description;
};

void AbstractSensor::setDescription(const QString& description) {
    this->description = description;
};


double AbstractSensor::getMinValue() const {
    return minValue;
};

void AbstractSensor::setMinValue(double minValue) {
    this->minValue = minValue;
};

double AbstractSensor::getMaxValue() const {
    return maxValue;
};

void AbstractSensor::setMaxValue(double maxValue) {
    this->maxValue = maxValue;
};

//QJsonObject AbstractSensor::toJson() const {
//    QJsonObject json;
//    json["uuid"] = uuid;
//    json["name"] = name;
//    json["description"] = description;
//    json["min_value"] = minValue;
//    json["max_value"] = maxValue;
//    return json;
//};

//AbstractSensor* AbstractSensor::fromJson(const QJsonObject& json) {
//    AbstractSensor *object;
//    object->setUUID(json["uuid"].toString());
//    object->setName(json["name"].toString());
//    object->setDescription(json["description"].toString());
//    return object;
//};

bool AbstractSensor::operator==(const AbstractSensor& obj) const{
    return uuid == obj.getUUID();
};