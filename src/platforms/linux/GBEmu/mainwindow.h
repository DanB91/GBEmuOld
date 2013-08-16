#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpustatus.h"
#include "Emulator/GameBoy.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    
private slots:
    void on_action_CPU_Status_triggered();

private:
    Ui::MainWindow *ui;
    CPUStatus *cpuStatusWindow;
    GBEmu::GameBoyPtr gameBoy;
};

#endif // MAINWINDOW_H
