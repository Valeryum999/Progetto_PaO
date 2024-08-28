#include "AddOrModifySensorVisitor.h"
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"
#include "model/PressureSensor.h"
#include "model/RadiationSensor.h"

AddOrModifySensorVisitor::AddOrModifySensorVisitor(AddOrModifySensor* addOrModifySensor): addOrModifySensor(addOrModifySensor){

};

void AddOrModifySensorVisitor::visit(TemperatureSensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(QString::fromStdString("Temperature"));
};

void AddOrModifySensorVisitor::visit(HumiditySensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(QString::fromStdString("Humidity"));
};

void AddOrModifySensorVisitor::visit(PressureSensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(QString::fromStdString("Pressure"));
};

void AddOrModifySensorVisitor::visit(RadiationSensor& sensor){
    addOrModifySensor->setName(sensor.getName());
    addOrModifySensor->setDescription(sensor.getDescription());
    addOrModifySensor->setMinValue(sensor.getMinValue());
    addOrModifySensor->setMaxValue(sensor.getMaxValue());
    addOrModifySensor->setType(QString::fromStdString("Radiation"));
};