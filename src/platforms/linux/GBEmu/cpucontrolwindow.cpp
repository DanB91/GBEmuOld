#include "cpucontrolwindow.h"
#include "ui_cpucontrolwindow.h"
#include "Emulator/GBEmuExceptions.h"
#include <QMessageBox>

CPUControlWindow::CPUControlWindow(QWidget *parent, GBEmu::GameBoy *gb) :
    QMainWindow(parent),
    ui(new Ui::CPUControlWindow), gameBoy(gb), cpuInfo(gb)
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
    updateData();
}

void CPUControlWindow::indicateROMIsNotLoaded(){
    ui->romLoadedStatus->setStyleSheet(tr("QLabel {color : red }"));
    ui->romLoadedStatus->setText(tr("ROM is not loaded!"));
    updateData();
}

void CPUControlWindow::updateData(){
    ui->aValue->setText(QString::fromStdString(cpuInfo.getA()));
    ui->bValue->setText(QString::fromStdString(cpuInfo.getB()));
    ui->cValue->setText(QString::fromStdString(cpuInfo.getC()));
    ui->dValue->setText(QString::fromStdString(cpuInfo.getD()));
    ui->eValue->setText(QString::fromStdString(cpuInfo.getE()));
    ui->fValue->setText(QString::fromStdString(cpuInfo.getF()));
    ui->spValue->setText(QString::fromStdString(cpuInfo.getSP()));
    ui->pcValue->setText(QString::fromStdString(cpuInfo.getPC()));
    ui->totalCycles->setText(QString::fromStdString(cpuInfo.getTotalCycles()));
    ui->currentInstruction->setText(QString::fromStdString(cpuInfo.getCurrentInstruction()));
    ui->cyclesOfLastInstruction->setText(QString::fromStdString(cpuInfo.getCyclesSinceLastInstruction()));
}



void CPUControlWindow::on_step_clicked()
{
    try{
        gameBoy->step();
        updateData();
    } catch(GBEmu::GBEmuException &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}
