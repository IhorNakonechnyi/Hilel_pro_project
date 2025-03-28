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

    collatz = new CollatzNumber(1,1);

    ui->labelSpinBoxMaxNumber->setContentsMargins(0,3,0,0);
    ui->spinBoxMaxNumber->setMaximum(static_cast<int>(std::numeric_limits<int>::max()));
    ui->labelLimit->setText("<html><head/><body><p><span style=\" color:#ff0000;\">Max value: "
                            + QString::number(ui->spinBoxMaxNumber->maximum())+"</span></p></body></html>");
    ui->labelMaxTheads->setText(QString::number(ui->sliderThreads->maximum()));
    ui->sliderThreads->setMaximum(static_cast<int>(QThread::idealThreadCount()));

    connect(ui->sliderThreads,&QAbstractSlider::valueChanged, this,[this](int value){ui->labelThreads->setText(QString::number(value));});

    connect(ui->buttonStart,&QPushButton::clicked,this, &MainWindow::Start);
    connect(ui->buttonStop,&QPushButton::clicked,this, &MainWindow::Stop);
    connect(ui->buttonExit,&QPushButton::clicked,this, &MainWindow::Exit);

}
MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------BUTTONS------------------------------------------------------

void MainWindow::Start()
{
    ui->buttonStart->setEnabled(false);
    ui->buttonStop->setEnabled(true);

    if (collatz) {
        delete collatz;
        collatz = nullptr;
    }

    collatz = new CollatzNumber(ui->spinBoxMaxNumber->value(),ui->sliderThreads->value());

    ui->textOutput->append("Processing...");

    collatz->Calculating();

    if(collatz->Success())
    {
        ui->textOutput->append("Range from 1 to "+ QString::number(ui->spinBoxMaxNumber->value()));

        ui->textOutput->append("Number with longest way: "
                                + QString::number(collatz->GetLongestWay().first)
                                + "\nWay steps: "
                                + QString::number(collatz->GetLongestWay().second));

        ui->textOutput->append("Time: "+ QString::number(collatz->GetTime().count())+" milliseconds\n");
    }
    else
    {
        ui->textOutput->append("Calculation isn`t finished!");
    }

    ui->buttonStop->setEnabled(false);
    ui->buttonStart->setEnabled(true);
};

void MainWindow::Stop()
{
    collatz->StopProcessing();

    qDebug()<<"Stop calculation";

    ui->buttonStop->setEnabled(false);
    ui->buttonStart->setEnabled(true);
};

void MainWindow::Exit()
{
    collatz->StopProcessing();

    QApplication::quit();
};

