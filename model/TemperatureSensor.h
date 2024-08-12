#ifndef MODEL_TEMPERATURE_SENSOR_H
#define MODEL_TEMPERATURE_SENSOR_H

#include "view/Visitor.h"
#include "model/AbstractSensor.h"

class TemperatureSensor : public AbstractSensor{
    private:
        QString unityOfMeasure;
        std::vector<double> data;
    public:
        TemperatureSensor(QString name,QString description,QString type,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("°C"));
        TemperatureSensor(QString id,QString name,QString description,QString type,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("°C"));
        TemperatureSensor(const TemperatureSensor& sensor);
        QString getUnityOfMeasure() const;
        void setUnityOfMeasure(const QString&);
        std::vector<double> generateData() override;
        virtual QJsonObject toJson() const;
        virtual TemperatureSensor* clone() const override;
        virtual void accept(Visitor& visitor) override;
};

#endif