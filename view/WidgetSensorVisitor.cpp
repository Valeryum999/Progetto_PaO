#include "view/WidgetSensorVisitor.h"
#include <QLabel>
#include <QGridLayout>
#include <iostream>
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"
#include "model/PressureSensor.h"
#include "model/RadiationSensor.h"

WidgetSensorVisitor::WidgetSensorVisitor(WidgetSensor* widget): widget(widget) {

};

void WidgetSensorVisitor::visit(HumiditySensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/humidity.png"));
};

void WidgetSensorVisitor::visit(TemperatureSensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/temperature.ico"));
};

void WidgetSensorVisitor::visit(PressureSensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/pressure.png"));
};

void WidgetSensorVisitor::visit(RadiationSensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/radiation.png"));
};