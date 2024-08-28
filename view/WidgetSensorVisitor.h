#ifndef VIEW_SENSOR_VISITOR_H
#define VIEW_SENSOR_VISITOR_H

#include "model/Visitor.h"
#include <QWidget>
#include "model/HumiditySensor.h"
#include "model/TemperatureSensor.h"
#include "model/PressureSensor.h"
#include "model/RadiationSensor.h"
#include "view/WidgetSensor.h"

class WidgetSensorVisitor: public Visitor{
    private:
        WidgetSensor *widget;
    public:
        WidgetSensorVisitor(WidgetSensor*);
        virtual void visit(HumiditySensor& sensor) override;
        virtual void visit(TemperatureSensor& sensor) override;
        virtual void visit(PressureSensor& sensor) override;
        virtual void visit(RadiationSensor& sensor) override;
};

#endif