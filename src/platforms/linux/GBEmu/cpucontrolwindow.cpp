#include "cpucontrolwindow.h"
#include "ui_cpucontrolwindow.h"

CPUControlWindow::CPUControlWindow(QWidget *parent, GBEmu::GameBoy *gb) :
    QMainWindow(parent),
    ui(new Ui::CPUControlWindow), gameBoy(gb)
{
    ui->setupUi(this);


    if(gameBoy->isROMLoaded()){
        indicateROMIsLoaded();
    } else{
        indicateROMIsNotLoaded();
    }

}

CPUControlWindow::~CPUControlWindow()
{
    delete ui;
}

void CPUControlWindow::indicateROMIsLoaded(){
    ui->romLoadedStatus->setStyleSheet(tr("QLabel {color : green }"));
    ui->romLoadedStatus->setText(tr("ROM is loaded!"));
}

void CPUControlWindow::indicateROMIsNotLoaded(){
    ui->romLoadedStatus->setStyleSheet(tr("QLabel {color : red }"));
    ui->romLoadedStatus->setText(tr("ROM is not loaded!"));
}
