#ifndef MODEL_READER_H
#define MODEL_READER_H

#include "model/ReaderInterface.h"
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"

class Reader : public ReaderInterface{
    private:
        HumiditySensor* readHumiditySensor(const QJsonObject& object) const;
        TemperatureSensor* readTemperatureSensor(const QJsonObject& object) const;
    public:
        AbstractSensor* read(const QJsonObject& object) override;
};

#endif