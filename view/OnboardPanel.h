#ifndef VIEW_ONBOARD_PANEL
#define VIEW_ONBOARD_PANEL

#include <QLabel>
#include <QWidget>

class OnboardPanel : public QWidget{
    Q_OBJECT
    private:
        QLabel *titleLabel;
        QWidget *shortcuts;
        QLabel *descriptionLabel;
        QLabel *newLabel;
        QLabel *openLabel;
        QLabel *saveLabel;
        QLabel *saveAsLabel;
        QLabel *closeLabel;
    public:
        OnboardPanel(QWidget* parent);
};

#endif