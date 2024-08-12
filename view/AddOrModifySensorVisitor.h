#ifndef VIEW_ADD_OR_MODIFY_SENSOR_VISITOR_H
#define VIEW_ADD_OR_MODIFY_SENSOR_VISITOR_H

#include "view/Visitor.h"
#include "view/AddOrModifySensor.h"
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"

class AddOrModifySensorVisitor : public Visitor{
    private:
        AddOrModifySensor* addOrModifySensor;
    public:
        AddOrModifySensorVisitor(AddOrModifySensor* sensor);
        virtual void visit(HumiditySensor&) override;
        virtual void visit(TemperatureSensor&) override;
};

#endif