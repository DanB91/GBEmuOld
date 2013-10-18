#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Pixel.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include "cpucontrolwindow.h"



static void initScene(QGraphicsScene *scene){


    for(int i = 0; i < GBEmu::GameBoy::SCREEN_LENGTH; i++){
        for(int j = 0; j < GBEmu::GameBoy::SCREEN_HEIGHT; j++){
            scene->addItem(new GUIPixel(Qt::black, i, j, 2));
        }
    }


}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()), scene, SLOT(update()));

    initScene(scene);
    ui->graphicsView->setScene(scene);
    timer->start(50);
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
    ui->graphicsView->invalidateScene();
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

void MainWindow::on_action_Quit_triggered()
{
    QApplication::exit();
}
