#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Emulator/GameBoy.h"

class RenderThread;
class CPUControlWindow;

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

    void on_action_Quit_triggered();

private:
    Ui::MainWindow *ui;
    CPUControlWindow *cpuStatusWindow;
    RenderThread *rt;
    GBEmu::GameBoy gameBoy;
};

#endif // MAINWINDOW_H
