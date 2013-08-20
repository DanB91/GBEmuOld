#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_CPU_Status_triggered()
{
    cpuStatusWindow = new CPUControlWindow(this, &gameBoy);
    connect(this, SIGNAL(romLoaded()), cpuStatusWindow, SLOT(indicateROMIsLoaded()));
    cpuStatusWindow->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open ROM"), tr(""),
                                                    tr("Game Boy ROMS (*.gb);;All(*)"));

    try{
        if(!fileName.isNull()){
            gameBoy.loadROM(fileName.toStdString());
            emit romLoaded();
        }
    } catch(std::exception &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}
