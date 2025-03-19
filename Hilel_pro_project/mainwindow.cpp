#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CollatzNumber.h"
#include <limits>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelSpinBoxMaxNumber->setContentsMargins(0,3,0,0);
    ui->spinBoxMaxNumber->setMaximum(static_cast<int>(std::numeric_limits<int>::max()));
    ui->labelLimit->setText("<html><head/><body><p><span style=\" color:#ff0000;\">Max value: "+ QString::number(ui->spinBoxMaxNumber->maximum())+"</span></p></body></html>");

    ui->labelMaxTheads->setText(QString::number(ui->sliderThreads->maximum()));


    ui->sliderThreads->setMaximum(static_cast<int>(QThread::idealThreadCount()));
    connect(ui->sliderThreads,&QAbstractSlider::valueChanged, this,[this](int value){ui->labelThreads->setText(QString::number(value));});



}

MainWindow::~MainWindow()
{
    delete ui;
}
