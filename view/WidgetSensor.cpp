#include "view/WidgetSensor.h"
#include "view/WidgetSensorVisitor.h"
#include <QHBoxLayout>
#include <iostream>


WidgetSensor::WidgetSensor(QWidget* parent): QWidget(parent), sensor(){
    backgroundWidget = new QWidget();
    backgroundWidget->setFixedSize(270, 130);

    layout = new QVBoxLayout(backgroundWidget);

    infoLayout = new QHBoxLayout();

    iconLabel = new QLabel(backgroundWidget);

    infoLayout->addWidget(iconLabel);

    dataLayout = new QVBoxLayout();

    icon = QPixmap("/home/valeryum/Desktop/hello-world/assets/icons/close.svg");
    type = new QLabel();
    name = new QLabel();
    description = new QLabel();
    name->setStyleSheet("font-weight: bold;font-size: 20px");
    type->setStyleSheet("font-style: italic;font-size: 14px");

    //buttonsWidget = new QWidget();
    //buttonsWidget->setFixedSize(270, 100);

    modifySensor = new QPushButton("✎");
    modifySensor->setFixedSize(130,20);
    deleteSensor = new QPushButton("🗑");
    deleteSensor->setFixedSize(130,20);

    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(modifySensor);
    buttonsLayout->addWidget(deleteSensor);

    dataLayout->addWidget(name);
    dataLayout->addWidget(type);

    infoLayout->addLayout(dataLayout);

    layout->addLayout(infoLayout);
    layout->addWidget(description);
    layout->addLayout(buttonsLayout);

    setFixedSize(270,130);

    backgroundWidget->setStyleSheet("border: 1px solid black;");
    //setStyleSheet("border: 1px solid black;");

    setLayout(layout);

    connect(modifySensor, &QPushButton::released, this, &WidgetSensor::handleModifyButton);
    connect(deleteSensor, &QPushButton::released, this, &WidgetSensor::handleDeleteButton);
};

WidgetSensor::WidgetSensor(AbstractSensor* sensor,QWidget* parent): QWidget(parent),sensor(sensor){
    backgroundWidget = new QWidget();
    backgroundWidget->setFixedSize(270, 130);

    layout = new QVBoxLayout(backgroundWidget);

    infoLayout = new QHBoxLayout();

    iconLabel = new QLabel(backgroundWidget);

    infoLayout->addWidget(iconLabel);

    dataLayout = new QVBoxLayout();

    icon = QPixmap("/home/valeryum/Desktop/hello-world/assets/icons/close.svg");
    name = new QLabel();
    type = new QLabel();
    description = new QLabel();
    name->setStyleSheet("font-weight: bold;font-size: 20px");
    type->setStyleSheet("font-style: italic;font-size: 14px");

    //buttonsWidget = new QWidget();
    //buttonsWidget->setFixedSize(270, 100);

    modifySensor = new QPushButton("✎");
    modifySensor->setFixedSize(130,20);
    deleteSensor = new QPushButton("🗑");
    deleteSensor->setFixedSize(130,20);

    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(modifySensor);
    buttonsLayout->addWidget(deleteSensor);

    dataLayout->addWidget(name);
    dataLayout->addWidget(type);

    infoLayout->addLayout(dataLayout);

    layout->addLayout(infoLayout);
    layout->addWidget(description);
    layout->addLayout(buttonsLayout);

    setFixedSize(270,130);
    //setStyleSheet("border: 1px solid black;");

    WidgetSensorVisitor *visitor = new WidgetSensorVisitor(this);
    sensor->accept(*visitor);

    setLayout(layout);

    connect(modifySensor, &QPushButton::released, this, &WidgetSensor::handleModifyButton);
    connect(deleteSensor, &QPushButton::released, this, &WidgetSensor::handleDeleteButton);
};

WidgetSensor::WidgetSensor(const WidgetSensor& sensorWidget,QWidget* parent): QWidget(parent){
    backgroundWidget = new QWidget();
    backgroundWidget->setFixedSize(270, 130);

    layout = new QVBoxLayout(backgroundWidget);

    infoLayout = new QHBoxLayout();

    iconLabel = new QLabel(backgroundWidget);

    infoLayout->addWidget(iconLabel);

    dataLayout = new QVBoxLayout();

    icon = QPixmap("/home/valeryum/Desktop/hello-world/assets/icons/close.svg");
    name = new QLabel();
    type = new QLabel();
    description = new QLabel();
    name->setStyleSheet("font-weight: bold;font-size: 20px");
    type->setStyleSheet("font-style: italic;font-size: 14px");

    //buttonsWidget = new QWidget();
    //buttonsWidget->setFixedSize(270, 100);

    modifySensor = new QPushButton("✎");
    deleteSensor = new QPushButton("🗑");
    modifySensor->setFixedSize(130,20);
    deleteSensor->setFixedSize(130,20);

    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(modifySensor);
    buttonsLayout->addWidget(deleteSensor);

    dataLayout->addWidget(name);
    dataLayout->addWidget(type);

    infoLayout->addLayout(dataLayout);

    layout->addLayout(infoLayout);
    layout->addLayout(buttonsLayout);
    layout->addWidget(description);

    setFixedSize(270,130);

    backgroundWidget->setStyleSheet("border: 1px solid black;");

    sensor = sensorWidget.getAbstractSensor();
    WidgetSensorVisitor *visitor = new WidgetSensorVisitor(this);
    sensor->accept(*visitor);

    //backgroundWidget->setStyleSheet("border: 1px solid black;");
    //setStyleSheet("border: 1px solid black;");

    setLayout(layout);

    connect(modifySensor, &QPushButton::released, this, &WidgetSensor::handleModifyButton);
    connect(deleteSensor, &QPushButton::released, this, &WidgetSensor::handleDeleteButton);
};

AbstractSensor* WidgetSensor::getAbstractSensor() const{
    return sensor;
}

QString WidgetSensor::getId() const{
    return sensor->getUUID();
};

void WidgetSensor::setType(const QString& type){
    this->type->setText(type);
};

QString WidgetSensor::getName() const{
    return sensor->getName();
}

void WidgetSensor::setName(const QString& name){
    this->name->setText(name);
};

QString WidgetSensor::getDescription() const{
    return sensor->getDescription();
}

void WidgetSensor::setDescription(const QString& description){
    this->description->setText(description);
};

QPixmap WidgetSensor::getIcon() const{
    return icon;
}

void WidgetSensor::setIcon(const QPixmap& pixmap){
    icon = pixmap;
    iconLabel->setPixmap(icon.scaledToHeight(32));
    iconLabel->setFixedSize(32, 32);
};

void WidgetSensor::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit selected(sensor);
    }
    QWidget::mousePressEvent(event);
};

void WidgetSensor::handleModifyButton(){
    emit modify(this->getAbstractSensor());
}

void WidgetSensor::handleDeleteButton(){
    emit deleted(this->getAbstractSensor());
};

WidgetSensor* WidgetSensor::clone() const{
    return new WidgetSensor(*this,nullptr);
};






