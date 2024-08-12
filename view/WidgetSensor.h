#ifndef VIEW_SENSOR_WIDGET_H
#define VIEW_SENSOR_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QPushButton>
#include "model/AbstractSensor.h"

class WidgetSensor : public QWidget{
    Q_OBJECT
    private:
        QWidget *backgroundWidget;
        QLabel *iconLabel;
        QPixmap icon;
        QVBoxLayout *layout;
        QVBoxLayout *backgroundLayout;
        QHBoxLayout *infoLayout;
        QVBoxLayout *dataLayout;
        QLabel *name;
        QLabel *type;
        QLabel *description;
        QHBoxLayout *buttonsLayout;
        QPushButton *modifySensor;
        QPushButton *deleteSensor;
        AbstractSensor* sensor;

    public slots:
        void handleModifyButton();
        void handleDeleteButton();

    signals:
        void selected(AbstractSensor* sensor);
        void modify(AbstractSensor* sensor);
        void deleted(AbstractSensor* sensor);

    public:
        WidgetSensor(QWidget *parent=nullptr);
        WidgetSensor(AbstractSensor* ,QWidget* parent=nullptr);
        WidgetSensor(const WidgetSensor& sensorWidget, QWidget* parent=nullptr);
        AbstractSensor* getAbstractSensor() const;
        QString getId() const;
        QString getType() const;
        void setType(const QString& id);
        QString getName() const;
        void setName(const QString& name);
        QString getDescription() const;
        void setDescription(const QString& description);
        QPixmap getIcon() const;           
        void setIcon(const QPixmap& pixmap);
        void mousePressEvent(QMouseEvent* event);
        WidgetSensor* clone() const;
};

#endif