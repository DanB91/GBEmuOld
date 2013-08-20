#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpucontrolwindow.h"
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

signals:
    void romLoaded();
    void romUnloaded();

    
private slots:
    void on_action_CPU_Status_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    CPUControlWindow *cpuStatusWindow;
    GBEmu::GameBoy gameBoy;
};

#endif // MAINWINDOW_H
