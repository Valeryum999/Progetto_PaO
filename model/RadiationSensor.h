#ifndef MODEL_RADIATION_SENSOR_H
#define MODEL_RADIATION_SENSOR_H

#include "model/AbstractSensor.h"

class RadiationSensor : public AbstractSensor{
    private:
        QString unityOfMeasure;
        std::vector<double> data;
    public:
        RadiationSensor(QString name,QString description,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("Sievert (Sv)"));
        RadiationSensor(QString id,QString name,QString description,double minValue=0,double maxValue=100,QString unityOfMeasure=QString::fromStdString("Sievert (Sv)"));
        RadiationSensor(const RadiationSensor& sensor);
        QString getUnityOfMeasure() const;
        void setUnityOfMeasure(const QString&);
        std::vector<double> generateData() override;
        virtual QJsonObject toJson() const;
        virtual RadiationSensor* clone() const override;
        virtual void accept(Visitor& visitor) override;
};

#endif