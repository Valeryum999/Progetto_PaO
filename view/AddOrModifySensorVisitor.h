#ifndef VIEW_ADD_OR_MODIFY_SENSOR_VISITOR_H
#define VIEW_ADD_OR_MODIFY_SENSOR_VISITOR_H

#include "model/Visitor.h"
#include "view/AddOrModifySensor.h"

class AddOrModifySensorVisitor : public Visitor{
    private:
        AddOrModifySensor* addOrModifySensor;
    public:
        AddOrModifySensorVisitor(AddOrModifySensor* sensor);
        virtual void visit(HumiditySensor&) override;
        virtual void visit(TemperatureSensor&) override;
        virtual void visit(PressureSensor&) override;
        virtual void visit(RadiationSensor&) override;
};

#endif