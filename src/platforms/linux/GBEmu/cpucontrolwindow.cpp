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
    updateData();
}

void CPUControlWindow::indicateROMIsNotLoaded(){
    ui->romLoadedStatus->setStyleSheet(tr("QLabel {color : red }"));
    ui->romLoadedStatus->setText(tr("ROM is not loaded!"));
    updateData();
}

void CPUControlWindow::updateData(){
    ui->aValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getA()));
    ui->bValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getB()));
    ui->cValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getC()));
    ui->dValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getD()));
    ui->eValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getE()));
    ui->fValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getF()));
    ui->spValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getSP()));
    ui->pcValue->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getPC()));
    ui->totalCycles->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getTotalCycles()));
    ui->currentInstruction->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getCurrentInstruction()));
    ui->cyclesOfLastInstruction->setText(QString::fromStdString(gameBoy->getCPUDebugInfo().getCyclesSinceLastInstruction()));
}


