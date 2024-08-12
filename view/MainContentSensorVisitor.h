#ifndef VIEW_MAIN_CONTENT_SENSOR_VISITOR_H
#define VIEW_MAIN_CONTENT_SENSOR_VISITOR_H

#include "view/Visitor.h"
#include "model/HumiditySensor.h"
#include "model/TemperatureSensor.h"
#include "view/MainContentSensor.h"

class MainContentSensorVisitor: public Visitor{
    private:
        MainContentSensor *mainContentSensor;
    public:
        MainContentSensorVisitor(MainContentSensor*);
        virtual void visit(HumiditySensor& sensor) override;
        virtual void visit(TemperatureSensor& sensor) override;
};

#endif