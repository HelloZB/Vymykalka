#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    
private slots:
    void counterMinus();
    void slotOFF();
    void slotReboot();


    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

private:
    Ui::Widget *ui;
    int couunter;
    QTimer counterTimer;
    QTimer offTimeer;
    QTimer rebootTimer;
};

#endif // WIDGET_H
