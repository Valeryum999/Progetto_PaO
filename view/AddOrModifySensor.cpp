#include "view/AddOrModifySensorVisitor.h"
#include "view/AddOrModifySensor.h"
#include <QLabel>
#include <iostream>
#include "model/TemperatureSensor.h"
#include "model/HumiditySensor.h"
#include "model/PressureSensor.h"
#include "model/RadiationSensor.h"
#include <QMessageBox>

AddOrModifySensor::AddOrModifySensor(QWidget* parent): QWidget(parent),isNewSensor(true) {
    layout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    name = new QLineEdit();
    name->setPlaceholderText("FantasticSensor1");
    description = new QLineEdit();
    description->setPlaceholderText("An incredible description about FantasticSensor1");
    type = new QComboBox();
    type->addItem("Humidity");
    type->addItem("Temperature");
    type->addItem("Pressure");
    type->addItem("Radiation");
    minValue = new QDoubleSpinBox();
    minValue->setRange(0,99);
    minValue->setSingleStep(1);
    minValue->setValue(25);
    minValue->setDecimals(2);
    maxValue = new QDoubleSpinBox();
    maxValue->setRange(1,100);
    maxValue->setSingleStep(1);
    maxValue->setValue(75);
    maxValue->setDecimals(2);

    formLayout->addRow(tr("Name"),name);
    formLayout->addRow(tr("Description"),description);
    formLayout->addRow(tr("Type"),type);
    formLayout->addRow(tr("Minimum Value"),minValue);
    formLayout->addRow(tr("Maximum Value"),maxValue);

    buttonsLayout = new QHBoxLayout();
    confirm = new QPushButton("Confirm");
    cancel = new QPushButton("Cancel");
    buttonsLayout->addWidget(confirm);
    buttonsLayout->addWidget(cancel);

    layout->addLayout(formLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    handleEvents();
};

AddOrModifySensor::AddOrModifySensor(AbstractSensor* sensor, QWidget* parent): QWidget(parent),isNewSensor(true){
    this->sensor = sensor;

    layout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    name = new QLineEdit();
    name->setPlaceholderText("FantasticSensor1");
    description = new QLineEdit();
    description->setPlaceholderText("An incredible description about FantasticSensor1");
    type = new QComboBox();
    type->addItem("Humidity");
    type->addItem("Temperature");
    type->addItem("Pressure");
    type->addItem("Radiation");
    minValue = new QDoubleSpinBox();
    minValue->setRange(0,99);
    minValue->setSingleStep(1);
    minValue->setValue(25);
    minValue->setDecimals(2);
    maxValue = new QDoubleSpinBox();
    maxValue->setRange(1,100);
    maxValue->setSingleStep(1);
    maxValue->setValue(75);
    maxValue->setDecimals(2);

    formLayout->addRow(tr("Name"),name);
    formLayout->addRow(tr("Description"),description);
    formLayout->addRow(tr("Type"),type);
    formLayout->addRow(tr("Minimum Value"),minValue);
    formLayout->addRow(tr("Maximum Value"),maxValue);

    buttonsLayout = new QHBoxLayout();
    confirm = new QPushButton("Confirm");
    cancel = new QPushButton("Cancel");
    buttonsLayout->addWidget(confirm);
    buttonsLayout->addWidget(cancel);

    layout->addLayout(formLayout);
    layout->addLayout(buttonsLayout);

    AddOrModifySensorVisitor* visitor = new AddOrModifySensorVisitor(this);
    sensor->accept(*visitor);

    setLayout(layout);

    handleEvents();
};

AddOrModifySensor::AddOrModifySensor(const AddOrModifySensor& addOrModifySensor,QWidget* parent): QWidget(parent),isNewSensor(true){
    this->sensor = addOrModifySensor.getAbstractSensor();

    layout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    name = new QLineEdit();
    name->setPlaceholderText("FantasticSensor1");
    description = new QLineEdit();
    description->setPlaceholderText("An incredible description about FantasticSensor1");
    type = new QComboBox();
    type->addItem("Humidity");
    type->addItem("Temperature");
    type->addItem("Pressure");
    type->addItem("Radiation");
    minValue = new QDoubleSpinBox();
    minValue->setRange(0,99);
    minValue->setValue(25);
    minValue->setSingleStep(1);
    minValue->setDecimals(2);
    maxValue = new QDoubleSpinBox();
    maxValue->setRange(1,100);
    minValue->setValue(75);
    maxValue->setSingleStep(1);
    maxValue->setDecimals(2);

    formLayout->addRow(tr("Name"),name);
    formLayout->addRow(tr("Description"),description);
    formLayout->addRow(tr("Type"),type);
    formLayout->addRow(tr("Minimum Value"),minValue);
    formLayout->addRow(tr("Maximum Value"),maxValue);

    buttonsLayout = new QHBoxLayout();
    confirm = new QPushButton("Confirm");
    cancel = new QPushButton("Cancel");
    buttonsLayout->addWidget(confirm);
    buttonsLayout->addWidget(cancel);

    layout->addLayout(formLayout);
    layout->addLayout(buttonsLayout);

    AddOrModifySensorVisitor* visitor = new AddOrModifySensorVisitor(this);
    sensor->accept(*visitor);

    setLayout(layout);

    handleEvents();
};

void AddOrModifySensor::handleEvents(){
    disconnect(type,&QComboBox::activated,this,&AddOrModifySensor::handleSelectedTypeOfSensor);
    connect(type,&QComboBox::activated,this,&AddOrModifySensor::handleSelectedTypeOfSensor);
    disconnect(confirm,&QPushButton::released,this,&AddOrModifySensor::handleCreatedSensor);
    disconnect(confirm,&QPushButton::released,this,&AddOrModifySensor::handleModifiedSensor);
    if(isNewSensor){
        connect(confirm,&QPushButton::released,this,&AddOrModifySensor::handleCreatedSensor);
    } else {
        connect(confirm,&QPushButton::released,this,&AddOrModifySensor::handleModifiedSensor);
    }
    disconnect(cancel,&QPushButton::released,this,&AddOrModifySensor::handleCancelCreationSensor);
    connect(cancel,&QPushButton::released,this,&AddOrModifySensor::handleCancelCreationSensor);
};

bool AddOrModifySensor::getIsNewSensor() const {
    return isNewSensor;
};

void AddOrModifySensor::setIsNewSensor(const bool& isNewSensor){
    this->isNewSensor = isNewSensor;
    handleEvents();
};

AbstractSensor* AddOrModifySensor::getAbstractSensor() const{
    return sensor;
};

void AddOrModifySensor::setAbstractSensor(AbstractSensor* sensor){
    this->sensor = sensor;
    AddOrModifySensorVisitor* visitor = new AddOrModifySensorVisitor(this);
    this->sensor->accept(*visitor);
}

void AddOrModifySensor::setName(const QString& name){
    this->name->setText(name);
};

void AddOrModifySensor::setDescription(const QString& description){
    this->description->setText(description);
};

void AddOrModifySensor::setMinValue(const double& minValue){
    this->minValue->setValue(minValue);
};

void AddOrModifySensor::setMaxValue(const double& maxValue){
    this->maxValue->setValue(maxValue);
};

void AddOrModifySensor::setType(const QString& type){
    int tempIndex = 0;
    if(type.compare("Temperature") == 0){
        tempIndex = 1;
    } else if(type.compare("Pressure") == 0){
        tempIndex = 2;
    } else if(type.compare("Radiation") == 0){
        tempIndex = 3;
    }
    this->type->setCurrentIndex(tempIndex);
    handleSelectedTypeOfSensor(tempIndex);
};

void AddOrModifySensor::reset(){
    name->setText("");
    description->setText("");
};

void AddOrModifySensor::handleSelectedTypeOfSensor(int index){
    std::cout << "in teoria dovrebbe passare" << std::endl;
    if(index==0){
        if(formLayout->rowCount()>5){
            formLayout->removeRow(5);
        }
    } else if(index==1){
        if(formLayout->rowCount()>5){
            formLayout->removeRow(5);
        }
        unityOfMeasure = new QComboBox();
        unityOfMeasure->addItem("Celsius (°C)");
        unityOfMeasure->addItem("Fahrenheit (°F)");
        unityOfMeasure->addItem("Kelvin (°K)");
        formLayout->addRow("Unity of measure",unityOfMeasure);
    } else if(index==2){
        if(formLayout->rowCount()>5){
            formLayout->removeRow(5);
        }
        unityOfMeasure = new QComboBox();
        unityOfMeasure->addItem("Pascal (pa)");
        unityOfMeasure->addItem("Atmosphere (atm)");
        unityOfMeasure->addItem("bar");
        formLayout->addRow("Unity of measure",unityOfMeasure);
    } else if(index==3){
        if(formLayout->rowCount()>5){
            formLayout->removeRow(5);
        }
        unityOfMeasure = new QComboBox();
        unityOfMeasure->addItem("Gray (Gy)");
        unityOfMeasure->addItem("Sievert (Sv)");
        formLayout->addRow("Unity of measure",unityOfMeasure);
    }
    
};

void AddOrModifySensor::handleCreatedSensor(){
    controlInputs();
    AbstractSensor* sensor = new HumiditySensor(QString::fromStdString("null"),QString::fromStdString("null"),QString::fromStdString("null")); //per non avere l'errore
    if(type->currentText().compare("Temperature") == 0){
        sensor = new TemperatureSensor(name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    } else if (type->currentText().compare("Humidity") == 0){
        sensor = new HumiditySensor(name->text(),
                                    description->text(),
                                    type->currentText(),
                                    minValue->value(),
                                    maxValue->value());
    } else if(type->currentText().compare("Pressure") == 0){
        sensor = new PressureSensor(name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    } else if(type->currentText().compare("Radiation") == 0){
        sensor = new RadiationSensor(name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    }
    handleEvents();
    emit createdSensor(sensor);
};

void AddOrModifySensor::controlInputs(){
    if(name->text().isEmpty()){
        QMessageBox::warning(this,
                    "Alert",
                    "You can't create a sensor without a name.",
                    QMessageBox::Ok);
        return;
    }
    if(minValue->value() > maxValue->value()){
        QMessageBox::warning(this,
                    "Alert",
                    "You can't create a sensor having a minimum value\ngreater than the maximum value.",
                    QMessageBox::Ok);
        return;
    }
};

void AddOrModifySensor::handleModifiedSensor(){
    controlInputs();

    if(type->currentText().compare("Temperature") == 0){
        sensor = new TemperatureSensor(sensor->getUUID(),
                                       name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    } else if (type->currentText().compare("Humidity") == 0){
        sensor = new HumiditySensor(sensor->getUUID(),
                                    name->text(),
                                    description->text(),
                                    type->currentText(),
                                    minValue->value(),
                                    maxValue->value());
    } else if(type->currentText().compare("Pressure") == 0){
        sensor = new PressureSensor(sensor->getUUID(),
                                       name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    } else if(type->currentText().compare("Radiation") == 0){
        sensor = new RadiationSensor(sensor->getUUID(),
                                       name->text(),
                                       description->text(),
                                       type->currentText(),
                                       minValue->value(),
                                       maxValue->value(),
                                       unityOfMeasure->currentText());
    }
   
    emit modifiedSensor(sensor);
};

void AddOrModifySensor::handleCancelCreationSensor(){
    emit cancelCreationSensor();
};