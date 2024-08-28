#include "view/MainContentSensor.h"
#include "view/MainContentSensorVisitor.h"
#include "view/ChartSensorVisitor.h"
#include <QChartView>
#include <QValueAxis>
#include <stdlib.h>
#include <array>
#include <QList>
#include <QPointF>
#include <iostream>

MainContentSensor::MainContentSensor(QWidget *parent): QWidget(parent),chart(new QChart),series(new QLineSeries), sensor() {
    mainLayout = new QVBoxLayout(this);
    dataLayout = new QVBoxLayout();
    id = new QLabel();
    id->setTextInteractionFlags(Qt::TextSelectableByMouse);
    name = new QLabel();
    name->setStyleSheet("font-size: 35px;");
    description = new QLabel();
    minValue = new QLabel();
    maxValue = new QLabel();
    simulate = new QPushButton("Simulate");
    chartView = new QChartView(chart);
    chart->addSeries(series);

    axisX = new QValueAxis;
    axisX->setRange(0,20);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    axisY = new QValueAxis;
    axisY->setRange(0,20);
    axisY->setTitleText("test");

    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->hide();
    chart->setTitle("SESSO");

    //QList<QPointF> buffer;
    //buffer.reserve(5);
    //for(int i=0;i<10;i++){
    //    buffer.append(QPointF(i,0));
    //}
    //for(int i=0;i<10;i++){
    //    buffer[i].setY(rand()%10);
    //}
    series->replace(buffer);

    dataLayout->addWidget(name);
    dataLayout->addWidget(id);
    dataLayout->addWidget(description);
    dataLayout->addWidget(minValue);
    dataLayout->addWidget(maxValue);
    dataLayout->addWidget(simulate);

    //dataLayout->addStretch();

    mainLayout->addLayout(dataLayout);
    //mainLayout->addWidget(simulate);
    mainLayout->addWidget(chartView,1);
    chartView->adjustSize();
    setLayout(mainLayout);

    connect(simulate,&QPushButton::released,this,&MainContentSensor::simulateChart);
};

MainContentSensor::MainContentSensor(AbstractSensor* sensor,QWidget *parent): QWidget(parent),chart(new QChart),series(new QLineSeries), sensor(sensor) {
    mainLayout = new QVBoxLayout(this);
    dataLayout = new QVBoxLayout();
    id = new QLabel();
    id->setTextInteractionFlags(Qt::TextSelectableByMouse);
    name = new QLabel();
    name->setStyleSheet("font-size: 35px;");
    description = new QLabel();
    minValue = new QLabel();
    maxValue = new QLabel();
    simulate = new QPushButton("Simulate");

    chartView = new QChartView(chart);
    chart->addSeries(series);

    axisX = new QValueAxis;
    axisX->setRange(0,19);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");

    axisY = new QValueAxis;
    axisY->setRange(0,19);
    axisY->setTitleText("test");

    chart->addAxis(axisX,Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisY);
    chart->legend()->hide();
    chart->setTitle("blank");

    dataLayout->addWidget(name,1);
    dataLayout->addWidget(id,1);
    dataLayout->addWidget(description);
    dataLayout->addWidget(minValue);
    dataLayout->addWidget(maxValue);
    dataLayout->addWidget(simulate);

    MainContentSensorVisitor *visitor = new MainContentSensorVisitor(this);
    this->sensor->accept(*visitor);

    mainLayout->addLayout(dataLayout);
    //mainLayout->addWidget(simulate);
    mainLayout->addWidget(chartView,1);
    setLayout(mainLayout);

    connect(simulate,&QPushButton::released,this,&MainContentSensor::simulateChart);
};

AbstractSensor* MainContentSensor::getAbstractSensor() const{
    return sensor;
}

void MainContentSensor::setId(const QString& id){
    this->id->setText(id);
};

void MainContentSensor::setName(const QString& name){
    this->name->setText(name);
};

void MainContentSensor::setDescription(const QString& description){
    this->description->setText(description);
};

void MainContentSensor::setMinValue(const QString& minValue){
    this->minValue->setText(minValue);
};

void MainContentSensor::setMaxValue(const QString& maxValue){
    this->maxValue->setText(maxValue);
};

void MainContentSensor::setChartTitle(const QString& title){
    chart->setTitle(title);
};

void MainContentSensor::setChartRangeY(const double& minRange,const double& maxRange){
    axisY->setRange(minRange,maxRange);
};

void MainContentSensor::setUnityOfMeasure(const QString& unityOfMeasure){
    axisY->setTitleText(unityOfMeasure);
};

void MainContentSensor::setAbstractSensor(AbstractSensor* sensor){
    this->sensor = sensor->clone();
    MainContentSensorVisitor *visitor = new MainContentSensorVisitor(this);
    this->sensor->accept(*visitor);
    
    ChartSensorVisitor *chartVisitor = new ChartSensorVisitor(this);
    this->sensor->accept(*chartVisitor);
    if(!buffer.isEmpty()){
        buffer.clear();
        series->replace(buffer);
    }
    //chartView->adjustSize();
};

void MainContentSensor::simulateChart(){
    if(!buffer.isEmpty()){
        buffer.clear();
    }
    std::vector<double> data = sensor->generateData();
    buffer.reserve(data.size());
    axisX->setRange(0,data.size()-1);
    for(int i=0;i<static_cast<int>(data.size());i++){
        buffer.append(QPointF(i,0));
    }
    for(int i=0;i<static_cast<int>(data.size());i++){
        buffer[i].setY(data.at(i));
    }
    series->replace(buffer); 
};

void MainContentSensor::selectedSensorWidgetHandler(AbstractSensor* sensor){
    setAbstractSensor(sensor);
};