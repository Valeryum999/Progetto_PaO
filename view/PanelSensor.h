#ifndef VIEW_SIDEPANEL_H
#define VIEW_SIDEPANEL_H

#include "view/WidgetSensor.h"
#include <QWidget>
#include <QLayout>

class PanelSensor : public QWidget{
    Q_OBJECT
    private:
        std::vector<WidgetSensor*> sensors;
        QWidget *emptyWidget;
        QVBoxLayout *sensorsLayout;
    public slots:
        void handleSensorWidgetSelected(AbstractSensor* sensor);
        void handleModifyButton(AbstractSensor* sensor);
        void handleDeleteButton(AbstractSensor* sensor);
        void searchSensors(const QString& query);
    signals:
        void sensorSelected(AbstractSensor* sensor);
        void modifySensorSignal(AbstractSensor* sensor);
        void sensorDeleted(AbstractSensor* sensor);
    public:
        PanelSensor(QWidget* parent);
        PanelSensor(std::vector<WidgetSensor*> sensors,QWidget* parent);
        void debug();
        void addSensor(AbstractSensor* sensor);
        void setSensors(std::vector<AbstractSensor*> sensors);
        void setSensors(std::vector<WidgetSensor*> sensors);
        void modifySensor(AbstractSensor* sensor);
        void clearLayout(QLayout* layout, bool deleteWidgets);
};

#endif