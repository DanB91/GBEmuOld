/********************************************************************************
** Form generated from reading UI file 'cpucontrolwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPUCONTROLWINDOW_H
#define UI_CPUCONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPUControlWindow
{
public:
    QWidget *centralwidget;
    QFrame *line;
    QPushButton *step;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *bValue;
    QLabel *label;
    QLabel *cValue;
    QLabel *label_9;
    QLabel *aValue;
    QLabel *label_21;
    QLabel *fValue;
    QLabel *dValue;
    QLabel *hValue;
    QLabel *lValue;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *spValue;
    QLabel *label_19;
    QLabel *label_23;
    QLabel *label_25;
    QLabel *pcValue;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *cyclesOfLastInstruction;
    QLabel *currentInstruction;
    QLabel *totalCycles;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_11;
    QLabel *romLoadedStatus;

    void setupUi(QMainWindow *CPUControlWindow)
    {
        if (CPUControlWindow->objectName().isEmpty())
            CPUControlWindow->setObjectName(QStringLiteral("CPUControlWindow"));
        CPUControlWindow->resize(445, 269);
        centralwidget = new QWidget(CPUControlWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(99, 20, 41, 241));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        step = new QPushButton(centralwidget);
        step->setObjectName(QStringLiteral("step"));
        step->setGeometry(QRect(300, 230, 141, 31));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(15, 21, 247, 239));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        bValue = new QLabel(gridLayoutWidget);
        bValue->setObjectName(QStringLiteral("bValue"));

        gridLayout->addWidget(bValue, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cValue = new QLabel(gridLayoutWidget);
        cValue->setObjectName(QStringLiteral("cValue"));

        gridLayout->addWidget(cValue, 2, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        aValue = new QLabel(gridLayoutWidget);
        aValue->setObjectName(QStringLiteral("aValue"));

        gridLayout->addWidget(aValue, 0, 1, 1, 1);

        label_21 = new QLabel(gridLayoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout->addWidget(label_21, 6, 0, 1, 1);

        fValue = new QLabel(gridLayoutWidget);
        fValue->setObjectName(QStringLiteral("fValue"));

        gridLayout->addWidget(fValue, 4, 1, 1, 1);

        dValue = new QLabel(gridLayoutWidget);
        dValue->setObjectName(QStringLiteral("dValue"));

        gridLayout->addWidget(dValue, 3, 1, 1, 1);

        hValue = new QLabel(gridLayoutWidget);
        hValue->setObjectName(QStringLiteral("hValue"));

        gridLayout->addWidget(hValue, 5, 1, 1, 1);

        lValue = new QLabel(gridLayoutWidget);
        lValue->setObjectName(QStringLiteral("lValue"));

        gridLayout->addWidget(lValue, 6, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        spValue = new QLabel(gridLayoutWidget);
        spValue->setObjectName(QStringLiteral("spValue"));

        gridLayout->addWidget(spValue, 7, 1, 1, 1);

        label_19 = new QLabel(gridLayoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 5, 0, 1, 1);

        label_23 = new QLabel(gridLayoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout->addWidget(label_23, 7, 0, 1, 1);

        label_25 = new QLabel(gridLayoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout->addWidget(label_25, 8, 0, 1, 1);

        pcValue = new QLabel(gridLayoutWidget);
        pcValue->setObjectName(QStringLiteral("pcValue"));

        gridLayout->addWidget(pcValue, 8, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(140, 20, 301, 104));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        cyclesOfLastInstruction = new QLabel(gridLayoutWidget_2);
        cyclesOfLastInstruction->setObjectName(QStringLiteral("cyclesOfLastInstruction"));

        gridLayout_2->addWidget(cyclesOfLastInstruction, 1, 1, 1, 1);

        currentInstruction = new QLabel(gridLayoutWidget_2);
        currentInstruction->setObjectName(QStringLiteral("currentInstruction"));

        gridLayout_2->addWidget(currentInstruction, 0, 1, 1, 1);

        totalCycles = new QLabel(gridLayoutWidget_2);
        totalCycles->setObjectName(QStringLiteral("totalCycles"));

        gridLayout_2->addWidget(totalCycles, 2, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_2->addWidget(label_13, 1, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        romLoadedStatus = new QLabel(centralwidget);
        romLoadedStatus->setObjectName(QStringLiteral("romLoadedStatus"));
        romLoadedStatus->setGeometry(QRect(150, 230, 131, 31));
        romLoadedStatus->setTextFormat(Qt::AutoText);
        CPUControlWindow->setCentralWidget(centralwidget);

        retranslateUi(CPUControlWindow);

        QMetaObject::connectSlotsByName(CPUControlWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CPUControlWindow)
    {
        CPUControlWindow->setWindowTitle(QApplication::translate("CPUControlWindow", "CPU Status", 0));
        step->setText(QApplication::translate("CPUControlWindow", "Step", 0));
        label_5->setText(QApplication::translate("CPUControlWindow", "C:", 0));
        bValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label->setText(QApplication::translate("CPUControlWindow", "A:", 0));
        cValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_9->setText(QApplication::translate("CPUControlWindow", "F:", 0));
        aValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_21->setText(QApplication::translate("CPUControlWindow", "L:", 0));
        fValue->setText(QApplication::translate("CPUControlWindow", "0                               ", 0));
        dValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        hValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        lValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_3->setText(QApplication::translate("CPUControlWindow", "B:", 0));
        label_7->setText(QApplication::translate("CPUControlWindow", "D:", 0));
        spValue->setText(QApplication::translate("CPUControlWindow", "0                                                            ", 0));
        label_19->setText(QApplication::translate("CPUControlWindow", "H:", 0));
        label_23->setText(QApplication::translate("CPUControlWindow", "SP:", 0));
        label_25->setText(QApplication::translate("CPUControlWindow", "PC:", 0));
        pcValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        cyclesOfLastInstruction->setText(QApplication::translate("CPUControlWindow", "0                        ", 0));
        currentInstruction->setText(QApplication::translate("CPUControlWindow", "0", 0));
        totalCycles->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_13->setText(QApplication::translate("CPUControlWindow", "# of Last Instruction Cycles:", 0));
        label_15->setText(QApplication::translate("CPUControlWindow", "Total Cyles:", 0));
        label_11->setText(QApplication::translate("CPUControlWindow", "Current Instruction:", 0));
        romLoadedStatus->setText(QApplication::translate("CPUControlWindow", "ROM Not Loaded!", 0));
    } // retranslateUi

};

namespace Ui {
    class CPUControlWindow: public Ui_CPUControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPUCONTROLWINDOW_H
