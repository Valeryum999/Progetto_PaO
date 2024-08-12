#ifndef VIEW_VISITOR_H
#define VIEW_VISITOR_H

class TemperatureSensor;
class HumiditySensor;

class Visitor{
    public:
        virtual ~Visitor() = default;
        virtual void visit(TemperatureSensor& sensor) = 0;
        virtual void visit(HumiditySensor& sensor) = 0;
};

#endif