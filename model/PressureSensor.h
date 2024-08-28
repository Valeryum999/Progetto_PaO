#ifndef MODEL_PRESSURE_SENSOR_H
#define MODEL_PRESSURE_SENSOR_H

#include "model/AbstractSensor.h"

class PressureSensor : public AbstractSensor{
    private:
        QString unityOfMeasure;
        std::vector<double> data;
    public:
        PressureSensor(QString name,QString description,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("Bar (bar)"));
        PressureSensor(QString id,QString name,QString description,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("Bar (bar)"));
        PressureSensor(const PressureSensor& sensor);
        QString getUnityOfMeasure() const;
        void setUnityOfMeasure(const QString&);
        std::vector<double> generateData() override;
        virtual QJsonObject toJson() const;
        virtual PressureSensor* clone() const override;
        virtual void accept(Visitor& visitor) override;
};

#endif