#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QTextCodec>
#include <QSettings>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8"); //qt4
    QTextCodec::setCodecForTr(utfcodec);
    QTextCodec::setCodecForCStrings(utfcodec);

    connect(&counterTimer, SIGNAL(timeout()), this, SLOT(counterMinus()));
    counterTimer.start(1000);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotOFF()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotReboot()));

    connect(&offTimeer, SIGNAL(timeout()), this, SLOT(slotOFF()));
    connect(&rebootTimer, SIGNAL(timeout()), this, SLOT(slotReboot()));
    offTimeer.setSingleShot(1);
    rebootTimer.setSingleShot(1);
    couunter=10;

    QSettings settings("Hello_ZB","Vymykalka");
    settings.beginGroup("main");
    ui->radioButton->setChecked(settings.value("defMode",0).toBool());
    ui->radioButton_2->setChecked(settings.value("defMode2",1).toBool());
    settings.endGroup();

}

Widget::~Widget()
{
    QSettings settings("Hello_ZB","Vymykalka");
    settings.beginGroup("main");
    settings.setValue("defMode",ui->radioButton->isChecked());
    settings.setValue("defMode2",ui->radioButton_2->isChecked());
    settings.endGroup();
    delete ui;
}

void Widget::counterMinus()
{

    couunter--;
    if(ui->radioButton->isChecked())
        ui->label->setText(tr("Перезавантаження через %1 секунд").arg(couunter));
    else
        ui->label->setText(tr("Вимкнення через %1 секунд").arg(couunter));
    if(couunter<=0){
        counterTimer.stop();
        if(ui->radioButton->isChecked())
            slotReboot();
        else
            slotOFF();
    }
}

void Widget::slotOFF()
{
    //shutdown
    //
    counterTimer.stop();
    ui->label->setText("");
    QProcess::startDetached("qdbus org.kde.ksmserver /KSMServer org.kde.KSMServerInterface.logout 0 2 2");
    offTimeer.start(10000);
}

void Widget::slotReboot()
{
    //reboot
    counterTimer.stop();
    ui->label->setText("");
    QProcess::startDetached("qdbus org.kde.ksmserver /KSMServer org.kde.KSMServerInterface.logout 0 1 2");
    rebootTimer.start(10000);

}

void Widget::on_radioButton_2_clicked()
{
    counterTimer.stop();
    ui->label->setText("");
}

void Widget::on_radioButton_clicked()
{
    counterTimer.stop();
    ui->label->setText("");
}
