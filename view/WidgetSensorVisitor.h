#ifndef VIEW_SENSOR_VISITOR_H
#define VIEW_SENSOR_VISITOR_H

#include "view/Visitor.h"
#include <QWidget>
#include "model/HumiditySensor.h"
#include "model/TemperatureSensor.h"
#include "view/WidgetSensor.h"

class WidgetSensorVisitor: public Visitor{
    private:
        WidgetSensor *widget;
    public:
        WidgetSensorVisitor(WidgetSensor*);
        virtual void visit(HumiditySensor& sensor) override;
        virtual void visit(TemperatureSensor& sensor) override;
};

#endif