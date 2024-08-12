// Includes Qt header files
#include <QApplication>
#include <QIcon>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QPixmap>
#include "view/MainWindow.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Defines an application object
    QApplication app(argc, argv);

    QIcon icon(QString::fromStdString("icon.png"));

    MainWindow *window = new MainWindow();

    window->setWindowIcon(icon);
    window->resize(1024, 576);
    window->show();

    // Runs application
    return app.exec();
}
