#include "view/ChartSensorVisitor.h"
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"
#include <iostream>

ChartSensorVisitor::ChartSensorVisitor(MainContentSensor* mainContentSensor): mainContentSensor(mainContentSensor){

};

void ChartSensorVisitor::visit(TemperatureSensor& sensor){
    mainContentSensor->setChartTitle("Temperature");
    mainContentSensor->setChartRangeY(sensor.getMinValue(),sensor.getMaxValue());
    mainContentSensor->setUnityOfMeasure(sensor.getUnityOfMeasure());
};

void ChartSensorVisitor::visit(HumiditySensor& sensor){
    mainContentSensor->setChartTitle("Humidity");
    mainContentSensor->setChartRangeY(sensor.getMinValue(),sensor.getMaxValue());
    mainContentSensor->setUnityOfMeasure("Percentage %");
};
