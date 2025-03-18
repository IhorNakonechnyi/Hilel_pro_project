#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxMaxNumber->setMaximum(static_cast<int>(std::numeric_limits<int>::max()));
    ui->sliderThreads->setMaximum(static_cast<int>(QThread::idealThreadCount()));
    ui->labelMaxTheads->setText(QString::number(ui->sliderThreads->maximum()));

    connect(ui->sliderThreads,&QAbstractSlider::valueChanged, this,[this](int value){ui->labelThreads->setText(QString::number(value));});
}

MainWindow::~MainWindow()
{
    delete ui;
}
