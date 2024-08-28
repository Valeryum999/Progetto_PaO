#ifndef VIEW_MAIN_CONTENT_SENSOR_VISITOR_H
#define VIEW_MAIN_CONTENT_SENSOR_VISITOR_H

#include "model/Visitor.h"
#include "view/MainContentSensor.h"

class MainContentSensorVisitor: public Visitor{
    private:
        MainContentSensor *mainContentSensor;
    public:
        MainContentSensorVisitor(MainContentSensor*);
        virtual void visit(HumiditySensor& sensor) override;
        virtual void visit(TemperatureSensor& sensor) override;
        virtual void visit(PressureSensor& sensor) override;
        virtual void visit(RadiationSensor& sensor) override;
};

#endif