#ifndef MODEL_ABSTRACT_SENSOR_H
#define MODEL_ABSTRACT_SENSOR_H

#include <QJsonObject>
#include "view/Visitor.h"

class AbstractSensor {
    private:
        QString uuid;
        QString name;
        QString description;
        QString type;
        double minValue;
        double maxValue;
    public:
        AbstractSensor();
        virtual ~AbstractSensor() = 0;
        AbstractSensor(QString name);
        AbstractSensor(QString name,QString description,QString type);
        AbstractSensor(QString name,QString description,QString type,double minValue=0,double maxValue=100);
        AbstractSensor(QString id,QString name,QString description,QString type,double minValue=0,double maxValue=100);
        QString getUUID() const;
        void setUUID(const QString&);
        QString getName() const;
        void setName(const QString&);
        QString getDescription() const;
        void setDescription(const QString&);
        QString getType() const;
        void setType(const QString&);
        double getMinValue() const;
        void setMinValue(double);
        double getMaxValue() const;
        void setMaxValue(double);
        virtual std::vector<double> generateData() = 0;
        virtual QJsonObject toJson() const = 0;
        //virtual AbstractSensor* fromJson(const QJsonObject&) = 0;
        virtual AbstractSensor* clone() const = 0;
        virtual void accept(Visitor&) = 0;
        bool operator==(const AbstractSensor &) const;  
};

#endif