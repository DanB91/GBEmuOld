#include "cpustatus.h"
#include "ui_cpustatus.h"

CPUStatus::CPUStatus(QWidget *parent, GBEmu::GameBoyPtr gb) :
    QMainWindow(parent),
    ui(new Ui::CPUStatus), gameBoy(gb)
{
    ui->setupUi(this);
    ui->romLoadedStatus->setStyleSheet(tr("QLabel {color : red }"));


}

CPUStatus::~CPUStatus()
{
    delete ui;
}
