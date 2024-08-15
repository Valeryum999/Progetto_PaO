#include "view/MainContentSensorVisitor.h"
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"
#include "model/PressureSensor.h"
#include "model/RadiationSensor.h"

MainContentSensorVisitor::MainContentSensorVisitor(MainContentSensor *mainContentSensor): mainContentSensor(mainContentSensor){

};

void MainContentSensorVisitor::visit(HumiditySensor& sensor) {
    //QPixmap image("assets/icons/umidita.svg");
    mainContentSensor->setName(sensor.getName());
    mainContentSensor->setId("ID: " + sensor.getUUID());
    mainContentSensor->setDescription("Description: " + sensor.getDescription());
    mainContentSensor->setMinValue("Minimum Value: " + QString::number(sensor.getMinValue()) + "%");
    mainContentSensor->setMaxValue("Maximum Value: " + QString::number(sensor.getMaxValue()) + "%");
};

void MainContentSensorVisitor::visit(TemperatureSensor& sensor) {
    mainContentSensor->setName(sensor.getName());
    mainContentSensor->setId("ID: " + sensor.getUUID());
    mainContentSensor->setDescription("Description: " + sensor.getDescription());
    mainContentSensor->setMinValue("Minimum Value: " + QString::number(sensor.getMinValue()) + " " + sensor.getUnityOfMeasure());
    mainContentSensor->setMaxValue("Maximum Value: " + QString::number(sensor.getMaxValue()) + " " + sensor.getUnityOfMeasure());
};

void MainContentSensorVisitor::visit(PressureSensor& sensor) {
    mainContentSensor->setName(sensor.getName());
    mainContentSensor->setId("ID: " + sensor.getUUID());
    mainContentSensor->setDescription("Description: " + sensor.getDescription());
    mainContentSensor->setMinValue("Minimum Value: " + QString::number(sensor.getMinValue()) + " " + sensor.getUnityOfMeasure());
    mainContentSensor->setMaxValue("Maximum Value: " + QString::number(sensor.getMaxValue()) + " " + sensor.getUnityOfMeasure());
};

void MainContentSensorVisitor::visit(RadiationSensor& sensor) {
    mainContentSensor->setName(sensor.getName());
    mainContentSensor->setId("ID: " + sensor.getUUID());
    mainContentSensor->setDescription("Description: " + sensor.getDescription());
    mainContentSensor->setMinValue("Minimum Value: " + QString::number(sensor.getMinValue()) + " " + sensor.getUnityOfMeasure());
    mainContentSensor->setMaxValue("Maximum Value: " + QString::number(sensor.getMaxValue()) + " " + sensor.getUnityOfMeasure());
};

