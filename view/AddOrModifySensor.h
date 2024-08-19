#ifndef VIEW_ADD_OR_MODIFY_SENSOR_H
#define VIEW_ADD_OR_MODIFY_SENSOR_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "model/AbstractSensor.h"

class AddOrModifySensor : public QWidget{
    Q_OBJECT
    private:
        AbstractSensor* sensor;
        QVBoxLayout* layout;
        QFormLayout* formLayout;
        QLineEdit* name;
        QLineEdit* description;
        QComboBox* unityOfMeasure;
        QComboBox* type;
        QDoubleSpinBox* minValue;
        QDoubleSpinBox* maxValue;
        QHBoxLayout* buttonsLayout;
        QPushButton* confirm;
        QPushButton* cancel;
        bool isNewSensor;

    public slots:
        void handleSelectedTypeOfSensor(int index);
        void handleModifiedSensor();
        void handleCreatedSensor();
        void handleCancelCreationSensor();
    signals:
        void createdSensor(AbstractSensor* sensor);
        void modifiedSensor(AbstractSensor* sensor);
        void cancelCreationSensor();
    public:
        AddOrModifySensor(QWidget* parent=nullptr);
        AddOrModifySensor(AbstractSensor* sensor,QWidget* parent=nullptr);
        AddOrModifySensor(const AddOrModifySensor& addOrModifySensor,QWidget* parent=nullptr);
        AbstractSensor* getAbstractSensor() const;
        bool getIsNewSensor() const;
        void setIsNewSensor(const bool& isNewSensor);
        void setAbstractSensor(AbstractSensor* sensor);
        void setName(const QString& name);
        void setDescription(const QString& description);
        void setType(const QString& type);
        void setMinValue(const double& minValue);
        void setMaxValue(const double& maxValue);
        void reset();
        void handleEvents();
};

#endif