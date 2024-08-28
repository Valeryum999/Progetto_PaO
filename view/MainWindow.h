#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QCloseEvent>
#include "view/MainContentSensor.h"
#include "view/OnboardPanel.h"
#include "view/Sidebar.h"
#include "view/AddOrModifySensor.h"
#include "model/JSONFile.h"

class MainWindow: public QMainWindow {
    Q_OBJECT
  private:
    QAction* create_item;
    QToolBar* toolbar;
    QWidget* centralWidget;
    QHBoxLayout *centralWidgetLayout;
    Sidebar *sidebar;
    MainContentSensor *sensorMainContent;
    AddOrModifySensor* addOrModifySensor;
    OnboardPanel *onboardPanel;
    JSONFile *currentFile;

  public slots:
    void openFile();
    void save();
    void save_as();
    void close();
    void show_shortcuts();
    void handleCreateNewSensorWindow();
    void sensorSelectedHandler(AbstractSensor* sensor);
    void handleModifySensor(AbstractSensor* sensor);
    void handleModifiedSensor(AbstractSensor* sensor);
    void sensorDeletedHandler(AbstractSensor* sensor);
    void handleCreatedSensor(AbstractSensor* sensor);
    void handleCancelCreationSensor();

  signals:
    void sensorSelected(AbstractSensor* sensor);
  public:
    MainWindow(QWidget *parent = 0);
    void freeMainWidget();
    void closeEvent(QCloseEvent* event);

};


#endif