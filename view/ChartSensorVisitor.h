#ifndef VIEW_CHART_SENSOR_VISITOR_H
#define VIEW_CHART_SENSOR_VISITOR_H

#include "model/Visitor.h"
#include "view/MainContentSensor.h"

class ChartSensorVisitor : public Visitor{
    private:
        MainContentSensor* mainContentSensor;
    public:
        ChartSensorVisitor(MainContentSensor* sensor);
        void visit(TemperatureSensor& sensor) override;
        void visit(HumiditySensor& sensor) override;
        void visit(PressureSensor& sensor) override;
        void visit(RadiationSensor& sensor) override;
};

#endif