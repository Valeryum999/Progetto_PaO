#include "model/HumiditySensor.h"

HumiditySensor::HumiditySensor(QString name, QString description, double minValue, double maxValue) : AbstractSensor(name,description,minValue,maxValue){
    
};

HumiditySensor::HumiditySensor(QString id, QString name, QString description, double minValue, double maxValue) : AbstractSensor(id,name,description,minValue,maxValue){
    
};

HumiditySensor::HumiditySensor(const HumiditySensor& sensor): AbstractSensor(sensor.getUUID(),sensor.getName(),sensor.getDescription(),sensor.getMinValue(),sensor.getMaxValue()){

};

std::vector<double> HumiditySensor::generateData(){
    data.clear();
    int range = static_cast<int>(getMaxValue()-getMinValue());
    for(int i=0;i<21;i++){
        data.push_back(rand()%range + getMinValue());
    }
    return data;
};


void HumiditySensor::accept(Visitor& visitor){
    visitor.visit(*this);
};

QJsonObject HumiditySensor::toJson() const {
    QJsonObject json;
    json["uuid"] = this->getUUID();
    json["name"] = this->getName();
    json["description"] = this->getDescription();
    json["type"] = QString::fromStdString("Humidity");
    json["min_value"] = this->getMinValue();
    json["max_value"] = this->getMaxValue();
    return json;
};

HumiditySensor* HumiditySensor::clone() const{
    return new HumiditySensor(*this);
};
