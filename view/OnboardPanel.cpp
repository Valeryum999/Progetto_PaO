#include "view/OnboardPanel.h"

#include <QVBoxLayout>

OnboardPanel::OnboardPanel(QWidget* parent): QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    shortcuts = new QWidget(this);

    QVBoxLayout *shortcutsLayout = new QVBoxLayout(shortcuts);

    titleLabel = new QLabel("NuclearSensors");
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px");

    layout->addWidget(titleLabel);

    descriptionLabel = new QLabel("Create a new sensor or open a file with existing sensors");
    newLabel = new QLabel("CTRL + N : Create a new file");
    openLabel = new QLabel("CTRL + O : Open an existing file");
    saveLabel = new QLabel("CTRL + S : Save current file");
    saveAsLabel = new QLabel("CTRL + Shift + S : Save current file as");
    closeLabel = new QLabel("CTRL + Q : Quit");

    shortcutsLayout->addWidget(descriptionLabel);
    shortcutsLayout->addWidget(newLabel);
    shortcutsLayout->addWidget(openLabel);
    shortcutsLayout->addWidget(saveLabel);
    shortcutsLayout->addWidget(saveAsLabel);
    shortcutsLayout->addWidget(closeLabel);
    shortcuts->setLayout(shortcutsLayout);
    
    layout->addWidget(shortcuts);
    layout->insertStretch(-1,1);
    
    setLayout(layout);
}