#ifndef VIEW_SENSOR_MAIN_CONTENT_H
#define VIEW_SENSOR_MAIN_CONTENT_H

#include <QWidget>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QPushButton>
#include <QList>
#include <QPointF>
#include <QVBoxLayout>
#include "model/AbstractSensor.h"

class MainContentSensor : public QWidget {
    Q_OBJECT
    private:
        QVBoxLayout *mainLayout;
        QVBoxLayout *dataLayout;
        QLabel *id;
        QLabel *name;
        QLabel *description;
        QLabel *minValue;
        QLabel *maxValue;
        QPushButton* simulate;
        QChart* chart;
        QChartView* chartView;
        QLineSeries* series;
        QValueAxis* axisX;
        QValueAxis* axisY;
        QList<QPointF> buffer;
        AbstractSensor* sensor;
    public slots:
        void selectedSensorWidgetHandler(AbstractSensor* sensor);
    
    public:
        MainContentSensor(QWidget* parent=nullptr);
        MainContentSensor(AbstractSensor* sensor,QWidget* parent=nullptr);
        AbstractSensor* getAbstractSensor() const;
        void addLabel(const QLabel);
        void setId(const QString& id);
        void setName(const QString& name);
        void setDescription(const QString& description);
        void setMinValue(const QString& minValue);
        void setMaxValue(const QString& maxValue);
        void setAbstractSensor(AbstractSensor* sensor);
        void setChartTitle(const QString& title);
        void setChartRangeY(const double& minRange,const double& maxRange);
        void setUnityOfMeasure(const QString& unityOfMeasure);
        void simulateChart();
};

#endif