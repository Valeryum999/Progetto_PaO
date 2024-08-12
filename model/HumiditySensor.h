#ifndef MODEL_HUMIDITY_SENSOR_H
#define MODEL_HUMIDITY_SENSOR_H

#include "model/AbstractSensor.h"

class HumiditySensor : public AbstractSensor{
    private:
        int percentage;
        std::vector<double> data;
    public:
        //HumiditySensor(QString name,QString description,int minValue=0,int maxValue=100, int percentage=0);
        HumiditySensor(QString name,QString description,QString type,double minValue=0,double maxValue=100, int percentage=0);
        HumiditySensor(QString id,QString name,QString description,QString type,double minValue=0,double maxValue=100, int percentage=0);
        HumiditySensor(const HumiditySensor& sensor);
        int getPercentage() const;
        void setPercentage(int percentage=0);
        std::vector<double> generateData() override;
        QJsonObject toJson() const override;
        virtual HumiditySensor* clone() const override;
        virtual void accept(Visitor& visitor) override;
};

#endif