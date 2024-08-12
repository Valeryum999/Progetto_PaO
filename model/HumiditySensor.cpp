#include "model/HumiditySensor.h"
#include "view/Visitor.h"

HumiditySensor::HumiditySensor(QString name, QString description, QString type, double minValue, double maxValue,int percentage) : AbstractSensor(name,description,type,minValue,maxValue),percentage(percentage){
    
};

HumiditySensor::HumiditySensor(QString id, QString name, QString description, QString type, double minValue, double maxValue,int percentage) : AbstractSensor(id,name,description,type,minValue,maxValue),percentage(percentage){
    
};

HumiditySensor::HumiditySensor(const HumiditySensor& sensor): AbstractSensor(sensor.getUUID(),sensor.getName(),sensor.getDescription(),sensor.getType(),sensor.getMinValue(),sensor.getMaxValue()),percentage(sensor.getPercentage()){

};

int HumiditySensor::getPercentage() const{
    return percentage;
};

void HumiditySensor::setPercentage(int percentage) {
    this->percentage = percentage;
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
    json["type"] = this->getType();
    json["min_value"] = this->getMinValue();
    json["max_value"] = this->getMaxValue();
    json["percentage"] = percentage;
    return json;
};

HumiditySensor* HumiditySensor::clone() const{
    return new HumiditySensor(*this);
};
