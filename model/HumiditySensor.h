#ifndef MODEL_HUMIDITY_SENSOR_H
#define MODEL_HUMIDITY_SENSOR_H

#include "model/AbstractSensor.h"

class HumiditySensor : public AbstractSensor{
    private:
        std::vector<double> data;
    public:
        //HumiditySensor(QString name,QString description,int minValue=0,int maxValue=100, int percentage=0);
        HumiditySensor(QString name,QString description,double minValue=0,double maxValue=100);
        HumiditySensor(QString uuid,QString name,QString description,double minValue=0,double maxValue=100);
        HumiditySensor(const HumiditySensor& sensor);
        std::vector<double> generateData() override;
        QJsonObject toJson() const override;
        virtual HumiditySensor* clone() const override;
        virtual void accept(Visitor& visitor) override;
};

#endif