#ifndef MODEL_READER_INTERFACE_H
#define MODEL_READER_INTERFACE_H

#include <QJsonObject>
#include "model/AbstractSensor.h"

class ReaderInterface{
    public:
        ~ReaderInterface() = default;
        virtual AbstractSensor* read(const QJsonObject& object) = 0;
};

#endif
