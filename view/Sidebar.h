#ifndef VIEW_SIDEBAR_H
#define VIEW_SIDEBAR_H

#include <QWidget>
#include <QLineEdit>
#include "view/PanelSensor.h"
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>

class Sidebar : public QWidget{
    Q_OBJECT
    private:
        QVBoxLayout *layout;
        QLineEdit* searchBar;
        QScrollArea *scrollArea;
        QHBoxLayout *scrollAreaLayout;
        QScrollBar *scrollBar;
        PanelSensor *sensorPanel;
        QPushButton *jolly;
    public slots:
        void handleSensorWidgetInSensorPanelSelected(AbstractSensor* sensor);
        void handleSensorWidgetDeleted(AbstractSensor* sensor);
        void handleSearchBarTextChanged(const QString& query);
        void handleModifyButtonPressed(AbstractSensor* sensor);
        void handleCreateNewSensorButtonPressed();
    signals:
        void createNewSensor();
        void sensorSelectedInSensorPanel(AbstractSensor* sensor);
        void searchBarTextChanged(const QString& query);
        void sensorDeleted(AbstractSensor* sensor);
        void modifySensor(AbstractSensor* sensor);
    public:
        Sidebar(QWidget* parent);
        Sidebar(std::vector<WidgetSensor*> sensors,QWidget* parent);
        void setSensorPanel(std::vector<AbstractSensor*> sensorsWidget);
        void setSensorPanel(std::vector<WidgetSensor*> sensorsWidget);
        void setSensorPanel(PanelSensor *sensors);
        void addSensor(AbstractSensor* sensor);
        void modifySensorInSensorPanel(AbstractSensor* sensor);
        void debug();
};

#endif