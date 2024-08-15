#include "MainWindow.h"
#include <QAction>
#include <QMenuBar>
#include <QToolBar>

//TEMP
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <QWindow>
#include <QJsonArray>
#include <QFileDialog>
#include <QApplication>
#include <QSplitter>
#include <QScrollArea>
#include <QScrollBar>
#include <QTextEdit>
#include <QMessageBox>
#include "model/JSONFile.h"
#include "model/HumiditySensor.h"
#include "model/TemperatureSensor.h"
#include "model/Reader.h"
#include "view/PanelSensor.h"
#include "view/OnboardPanel.h"
#include "view/Sidebar.h"
#include "view/MainContentSensor.h"
#include "view/AddOrModifySensor.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Actions
    QAction* create = new QAction(
        QIcon(QPixmap(("assets/icons/new.svg"))),
        "New"
    );
    create->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    QAction* open = new QAction(
        QIcon(QPixmap(("assets/icons/open.svg"))),
        "Open"
    );
    open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    QAction* save = new QAction(
        QIcon(QPixmap(("assets/icons/save.svg"))),
        "Save"
    );
    save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    QAction* save_as = new QAction(
        QIcon(QPixmap(("assets/icons/save_as.svg"))),
        "Save As"
    );
    save_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    QAction* close = new QAction(
        QIcon(QPixmap(("assets/icons/close.svg"))),
        "Close"
    );
    close->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    QAction* show_shortcuts = new QAction(
        "Show shortcuts"
    );

    // Sets menu bar
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(create);
    file->addAction(open);
    file->addAction(save);
    file->addAction(save_as);
    file->addSeparator();
    file->addAction(close);
    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(show_shortcuts);

    //AbstractSensor *obj = new TemperatureSensor(QString::fromStdString("ciao1"),QString::fromStdString("ciao"),QString::fromStdString("Temperature"));

    centralWidget = new QWidget(this);

    centralWidgetLayout = new QHBoxLayout(centralWidget);

    setCentralWidget(centralWidget);

    onboardPanel = new OnboardPanel(centralWidget);
    //Sidebar *sidebar = new Sidebar(tempSensorsPanel,centralWidget);
    sidebar = new Sidebar(centralWidget);
    sensorMainContent = new MainContentSensor();
    //MainContentSensor *sensorMainContent2 = new MainContentSensor(obj2,nullptr);
    //sensorMainContent->setStyleSheet("border: 0px solid red");
    //PanelSensor *test = new PanelSensor(tempSensorsPanel,nullptr);

    //QTextEdit *searchbar = new QTextEdit();
    
    centralWidgetLayout->addWidget(sidebar);
    centralWidgetLayout->addWidget(onboardPanel);

    
    centralWidget->setLayout(centralWidgetLayout);

    currentFile = new JSONFile();

    addOrModifySensor = new AddOrModifySensor();
    //currentFile->save();
    //for(AbstractSensor* it: sensors){
    //   
    //}
    //sidebar->setSensorPanel(sensors);

    //obj->setUUID("6d4c3881-b844-4ed4-8af3-b397cf0d6795");
    //obj->setDescription("amo la borra");
    //currentFile->remove(*obj);
    //currentFile->save();


    //currentFile = new JSONFile("/home/valeryum/Desktop/hello-world/test_backup.json",false);
    //sensors = currentFile->load();
    //for(AbstractSensor* it: sensors){
    //   
    //}
    //sidebar->setSensorPanel(sensors);

    // Connects actions SEND SIGNALS TO SLOTS PERCHE COSI FANNO ROBA

    connect(create, &QAction::triggered,this,&MainWindow::newFile);
    connect(open, &QAction::triggered, this, &MainWindow::openFile);
    connect(save, &QAction::triggered, this, &MainWindow::save);
    connect(save_as,&QAction::triggered,this,&MainWindow::save_as);
    connect(close,&QAction::triggered, this, &MainWindow::close);
    connect(show_shortcuts,&QAction::triggered, this, &MainWindow::show_shortcuts);

    connect(sidebar, &Sidebar::sensorSelectedInSensorPanel, this, &MainWindow::sensorSelectedHandler);
    connect(sidebar, &Sidebar::createNewSensor,this,&MainWindow::handleCreateNewSensorWindow);
    connect(sidebar, &Sidebar::modifySensor,this,&MainWindow::handleModifySensor);
    connect(sidebar, &Sidebar::sensorDeleted,this,&MainWindow::sensorDeletedHandler);

    disconnect(addOrModifySensor,&AddOrModifySensor::createdSensor,this,&MainWindow::handleCreatedSensor);
    connect(addOrModifySensor,&AddOrModifySensor::createdSensor,this,&MainWindow::handleCreatedSensor);
    disconnect(addOrModifySensor,&AddOrModifySensor::modifiedSensor,this,&MainWindow::handleModifiedSensor);
    connect(addOrModifySensor,&AddOrModifySensor::modifiedSensor,this,&MainWindow::handleModifiedSensor);
    disconnect(addOrModifySensor,&AddOrModifySensor::cancelCreationSensor,this,&MainWindow::handleCancelCreationSensor);
    connect(addOrModifySensor,&AddOrModifySensor::cancelCreationSensor,this,&MainWindow::handleCancelCreationSensor);

    connect(this, &MainWindow::sensorSelected,sensorMainContent,&MainContentSensor::selectedSensorWidgetHandler);
    
};

void MainWindow::newFile(){
    QString path = QFileDialog::getOpenFileName(
        this,
        "Creates new file",
        "./",
        "JSON files *.json"
    );
    if (path.isEmpty()) {
        return;
    }
    currentFile->setPath(path.toStdString());
};

void MainWindow::openFile(){
    QString path = QFileDialog::getOpenFileName(
        this,
        "Opens a file",
        "./",
        "JSON files *.json"
    );
    if (path.isEmpty()) {
        return;
    }
    std::cout << "Ziomela" << std::endl;
    //std::cout << path.toStdString() << std::endl;
    currentFile->setPath(path.toStdString());
    std::cout << "Ziopera" << std::endl;
    std::vector<AbstractSensor*> sensors = currentFile->load();
    sidebar->setSensorPanel(sensors);
    sidebar->debug();
};

void MainWindow::save(){
    if(currentFile->getPath().empty()){
        save_as();
    } else {
        currentFile->save();
    }
    return;
};

void MainWindow::save_as(){
    QString path = QFileDialog::getOpenFileName(
        this,
        "Saves your project as",
        "./",
        "JSON files *.json"
    );
    if (path.isEmpty()) {
        return;
    }
    currentFile->save_as(path.toStdString());
};

void MainWindow::close() {
    QApplication::quit();
};

void MainWindow::show_shortcuts(){
    freeMainWidget();
    centralWidgetLayout->addWidget(onboardPanel);
    onboardPanel->show();
};

void MainWindow::freeMainWidget(){
    centralWidgetLayout->removeWidget(addOrModifySensor);
    addOrModifySensor->close();
    centralWidgetLayout->removeWidget(onboardPanel);
    onboardPanel->close();
    centralWidgetLayout->removeWidget(sensorMainContent);
    sensorMainContent->close();
};

void MainWindow::sensorSelectedHandler(AbstractSensor* sensor){
    freeMainWidget();
    centralWidgetLayout->addWidget(sensorMainContent);
    sensorMainContent->show();
    emit sensorSelected(sensor);
};

void MainWindow::handleModifySensor(AbstractSensor* sensor){
    freeMainWidget();
    addOrModifySensor->setAbstractSensor(sensor);
    addOrModifySensor->setIsNewSensor(false);
    centralWidgetLayout->addWidget(addOrModifySensor);
    addOrModifySensor->show();
};

void MainWindow::handleModifiedSensor(AbstractSensor* sensor){ 
    currentFile->modify(*sensor);
    sidebar->modifySensorInSensorPanel(sensor);
    sensorSelectedHandler(sensor);
};

void MainWindow::sensorDeletedHandler(AbstractSensor* sensor){ 
    currentFile->remove(*sensor);
    if(*sensor==*sensorMainContent->getAbstractSensor()){
        freeMainWidget();
        centralWidgetLayout->addWidget(onboardPanel);
        onboardPanel->show();
    }
};

void MainWindow::handleCreateNewSensorWindow(){
    freeMainWidget();
    addOrModifySensor->setIsNewSensor(true);
    addOrModifySensor->reset();
    centralWidgetLayout->addWidget(addOrModifySensor);
    addOrModifySensor->show();
    //disconnect(addOrModifySensor,&AddOrModifySensor::createdSensor,this,&MainWindow::handleCreatedSensor);
    //disconnect(addOrModifySensor,&AddOrModifySensor::cancelCreationSensor,this,&MainWindow::handleCancelCreationSensor);
    //connect(addOrModifySensor,&AddOrModifySensor::createdSensor,this,&MainWindow::handleCreatedSensor);
    //connect(addOrModifySensor,&AddOrModifySensor::cancelCreationSensor,this,&MainWindow::handleCancelCreationSensor);
};

void MainWindow::handleCreatedSensor(AbstractSensor* sensor){  
    currentFile->add(*sensor);
    sidebar->addSensor(sensor);
    freeMainWidget();
    centralWidgetLayout->addWidget(onboardPanel);
    onboardPanel->show();
};

void MainWindow::handleCancelCreationSensor(){
    freeMainWidget();
    centralWidgetLayout->addWidget(onboardPanel);
    onboardPanel->show();
};

void MainWindow::closeEvent(QCloseEvent *event){
    event->ignore();
    if (currentFile->hasNotBeenSaved()) {
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(
            this,
            "Quit?",
            "There are unsaved changes.\nDo you really want to quit?",
            QMessageBox::Yes | QMessageBox::No
        );
        if (confirmation == QMessageBox::Yes) {
            event->accept();
        }
    }
    else {
        event->accept();
    }
};