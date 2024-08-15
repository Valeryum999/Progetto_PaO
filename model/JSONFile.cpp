#include "JSONFile.h"

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <iostream>
#include "model/Reader.h"

JSONFile::JSONFile(): path(),document(),hasUnsavedChanges(false){
};

JSONFile::JSONFile(const std::string& absolute_path): path(absolute_path),hasUnsavedChanges(false){
    if(path.empty()){
        throw std::runtime_error("Empty path given.");
    }
    QFile temp;
    temp.setFileName(QString::fromStdString(path));
    if(!temp.open(QIODevice::ReadOnly)){
        throw std::runtime_error("Couldn't open file.");
    }
    document = QJsonDocument::fromJson(temp.readAll());
    temp.close();
};

const std::string& JSONFile::getPath() const{
    return path;
};

void JSONFile::setPath(const std::string& path){
    std::cout << path << std::endl;
    if(path.empty()){
        throw std::runtime_error("Empty path given.");
    }
    this->path = path;
    QFile temp;
    temp.setFileName(QString::fromStdString(path));
    if(!temp.open(QIODevice::ReadOnly)){
        throw std::runtime_error("Couldn't open file.");
    }
    document = QJsonDocument::fromJson(temp.readAll());
    temp.close();
};

bool JSONFile::hasNotBeenSaved() const{
    return hasUnsavedChanges;
};

QJsonObject JSONFile::getObject() const{
    return document.object();
};

QJsonArray JSONFile::getArray() const{
    return document.array();
};

void JSONFile::store(const std::vector<AbstractSensor*> objects){
    QJsonArray tempArray = document.array();
    while(tempArray.count()) {
        tempArray.pop_back();
    }
    for(std::vector<AbstractSensor*>::const_iterator cit = objects.begin(); cit != objects.end(); cit++){
        tempArray.push_back((*cit)->toJson());
    }
    document.setArray(tempArray);
    hasUnsavedChanges = true;
}

std::vector<AbstractSensor*> JSONFile::load() const {
    std::vector<AbstractSensor*> sensors;
    QJsonArray tempArray = document.array();
    Reader reader;
    for(QJsonValue sensor: tempArray){
        AbstractSensor* temp = reader.read(sensor.toObject());
        sensors.push_back(temp);
    }
    return sensors;
};

void JSONFile::add(const AbstractSensor& obj){
    QJsonArray tempArray = document.array();
    tempArray.push_back(obj.toJson());
    document.setArray(tempArray);
    hasUnsavedChanges = true;
};

void JSONFile::modify(const AbstractSensor& obj){
    QJsonArray tempArray = document.array();
    int count = 0;
    for(QJsonValue it: tempArray){
        Reader reader;
        AbstractSensor* temp = reader.read(it.toObject());
        if(*temp==obj){
            tempArray.removeAt(count);
            tempArray.insert(count,obj.toJson());
            document.setArray(tempArray);
            hasUnsavedChanges = true;
            return;
        }
        count++;
    };
}

void JSONFile::JSONFile::remove(const AbstractSensor& obj){
    QJsonArray tempArray = document.array();
    int count = 0;
    for(QJsonValue it: tempArray){
        Reader reader;
        AbstractSensor* temp = reader.read(it.toObject());
        if(temp->getUUID()==obj.getUUID()){
            tempArray.removeAt(count);
            document.setArray(tempArray);
            hasUnsavedChanges = true;
            return;
        }
        count += 1;
    }
};

void JSONFile::erase() {
    QJsonArray tempArray = document.array();
    while(tempArray.count()) {
        tempArray.pop_back();
    }
    document.setArray(tempArray);
    hasUnsavedChanges = true;
}

void JSONFile::save() {
    QFile temp(QString::fromStdString(path));
    if(!temp.open(QIODevice::WriteOnly)){
        throw std::runtime_error("Couldn't save the file.");
    }
    temp.write(document.toJson());
    temp.close();
    hasUnsavedChanges = false;
};

void JSONFile::save_as(const std::string& absolute_path) {
    path = absolute_path;
    QFile temp(QString::fromStdString(path));
    if(!temp.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        throw std::runtime_error("Couldn't save the file.");
    }
    temp.write(document.toJson());
    temp.close();
    hasUnsavedChanges = false;
};