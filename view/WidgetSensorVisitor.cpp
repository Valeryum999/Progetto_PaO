#include "view/WidgetSensorVisitor.h"
#include <QLabel>
#include <QGridLayout>
#include <iostream>

WidgetSensorVisitor::WidgetSensorVisitor(WidgetSensor* widget): widget(widget) {

};

void WidgetSensorVisitor::visit(HumiditySensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/umidita.svg"));
};

void WidgetSensorVisitor::visit(TemperatureSensor& sensor){
    widget->setType("type: " + sensor.getType());
    widget->setName(sensor.getName());
    widget->setDescription(sensor.getDescription());
    widget->setIcon(QPixmap("assets/icons/termometro.svg"));
};