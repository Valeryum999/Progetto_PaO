#ifndef MODEL_ABSTRACT_SENSOR_H
#define MODEL_ABSTRACT_SENSOR_H

#include <QJsonObject>
#include "model/Visitor.h"

class AbstractSensor {
    private:
        QString uuid;
        QString name;
        QString description;
        double minValue;
        double maxValue;
    public:
        virtual ~AbstractSensor() = 0;
        AbstractSensor(QString name);
        AbstractSensor(QString name,QString description,double minValue=0,double maxValue=100);
        AbstractSensor(QString uuid,QString name,QString description,double minValue=0,double maxValue=100);
        QString getUUID() const;
        void setUUID(const QString&);
        QString getName() const;
        void setName(const QString&);
        QString getDescription() const;
        void setDescription(const QString&);
        double getMinValue() const;
        void setMinValue(double);
        double getMaxValue() const;
        void setMaxValue(double);
        bool operator==(const AbstractSensor &) const; 
        virtual std::vector<double> generateData() = 0;
        virtual QJsonObject toJson() const = 0;
        virtual AbstractSensor* clone() const = 0;
        virtual void accept(Visitor&) = 0;
};

#endif