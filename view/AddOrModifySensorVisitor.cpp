#include "AddOrModifySensorVisitor.h"

AddOrModifySensorVisitor::AddOrModifySensorVisitor(AddOrModifySensor* addOrModifySensor): addOrModifySensor(addOrModifySensor){

};

void AddOrModifySensorVisitor::visit(TemperatureSensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(sensor.getType());
};

void AddOrModifySensorVisitor::visit(HumiditySensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(sensor.getType());
};