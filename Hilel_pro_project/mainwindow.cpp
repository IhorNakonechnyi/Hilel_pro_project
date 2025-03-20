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

    connect(ui->buttonStart,&QPushButton::clicked,this, &MainWindow::CollatzStart);
    connect(ui->buttonStop,&QPushButton::clicked,this, &MainWindow::CollatzStop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CollatzStart()
{
    ui->buttonStart->setEnabled(false);
    ui->buttonStop->setEnabled(true);

    CollatzNumber test(ui->spinBoxMaxNumber->value(), ui->sliderThreads->value());
    ui->textOutput->setText("Number with longest way:\nNumber: "
                            + QString::number(test.GetLongestWay().first)
                            + "\nWay steps: "
                            + QString::number(test.GetLongestWay().second));

    ui->textOutput->setText("Time: "+ QString::number(test.GetTime().count()));
}
void MainWindow::CollatzStop()
{
    ui->buttonStop->setEnabled(false);
    ui->buttonStart->setEnabled(true);

    //need to stop calculating
}
