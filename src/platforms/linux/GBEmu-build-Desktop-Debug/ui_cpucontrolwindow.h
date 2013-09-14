/********************************************************************************
** Form generated from reading UI file 'cpucontrolwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPUCONTROLWINDOW_H
#define UI_CPUCONTROLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
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
    QGridLayout *gridLayout_3;
    QFrame *line;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *aValue;
    QLabel *label_3;
    QLabel *bValue;
    QLabel *label_5;
    QLabel *cValue;
    QLabel *label_7;
    QLabel *dValue;
    QLabel *label_2;
    QLabel *eValue;
    QPushButton *step;
    QLabel *romLoadedStatus;
    QFormLayout *formLayout_3;
    QLabel *label_11;
    QLabel *currentInstruction;
    QLabel *label_13;
    QLabel *cyclesOfLastInstruction;
    QLabel *label_15;
    QLabel *totalCycles;
    QFormLayout *formLayout;
    QLabel *label_9;
    QLabel *fValue;
    QLabel *label_19;
    QLabel *hValue;
    QLabel *label_21;
    QLabel *lValue;
    QLabel *label_23;
    QLabel *spValue;
    QLabel *label_25;
    QLabel *pcValue;

    void setupUi(QMainWindow *CPUControlWindow)
    {
        if (CPUControlWindow->objectName().isEmpty())
            CPUControlWindow->setObjectName(QStringLiteral("CPUControlWindow"));
        CPUControlWindow->resize(542, 269);
        centralwidget = new QWidget(CPUControlWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 2, 0, 1, 2);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        aValue = new QLabel(centralwidget);
        aValue->setObjectName(QStringLiteral("aValue"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, aValue);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        bValue = new QLabel(centralwidget);
        bValue->setObjectName(QStringLiteral("bValue"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, bValue);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        cValue = new QLabel(centralwidget);
        cValue->setObjectName(QStringLiteral("cValue"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, cValue);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_7);

        dValue = new QLabel(centralwidget);
        dValue->setObjectName(QStringLiteral("dValue"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, dValue);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_2);

        eValue = new QLabel(centralwidget);
        eValue->setObjectName(QStringLiteral("eValue"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, eValue);


        gridLayout_3->addLayout(formLayout_2, 1, 0, 1, 1);

        step = new QPushButton(centralwidget);
        step->setObjectName(QStringLiteral("step"));

        gridLayout_3->addWidget(step, 5, 1, 2, 1);

        romLoadedStatus = new QLabel(centralwidget);
        romLoadedStatus->setObjectName(QStringLiteral("romLoadedStatus"));
        romLoadedStatus->setTextFormat(Qt::AutoText);

        gridLayout_3->addWidget(romLoadedStatus, 4, 1, 1, 1);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_11);

        currentInstruction = new QLabel(centralwidget);
        currentInstruction->setObjectName(QStringLiteral("currentInstruction"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, currentInstruction);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_13);

        cyclesOfLastInstruction = new QLabel(centralwidget);
        cyclesOfLastInstruction->setObjectName(QStringLiteral("cyclesOfLastInstruction"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, cyclesOfLastInstruction);

        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_15);

        totalCycles = new QLabel(centralwidget);
        totalCycles->setObjectName(QStringLiteral("totalCycles"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, totalCycles);


        gridLayout_3->addLayout(formLayout_3, 3, 0, 1, 2);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_9);

        fValue = new QLabel(centralwidget);
        fValue->setObjectName(QStringLiteral("fValue"));

        formLayout->setWidget(0, QFormLayout::FieldRole, fValue);

        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_19);

        hValue = new QLabel(centralwidget);
        hValue->setObjectName(QStringLiteral("hValue"));

        formLayout->setWidget(1, QFormLayout::FieldRole, hValue);

        label_21 = new QLabel(centralwidget);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_21);

        lValue = new QLabel(centralwidget);
        lValue->setObjectName(QStringLiteral("lValue"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lValue);

        label_23 = new QLabel(centralwidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_23);

        spValue = new QLabel(centralwidget);
        spValue->setObjectName(QStringLiteral("spValue"));

        formLayout->setWidget(3, QFormLayout::FieldRole, spValue);

        label_25 = new QLabel(centralwidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_25);

        pcValue = new QLabel(centralwidget);
        pcValue->setObjectName(QStringLiteral("pcValue"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pcValue);


        gridLayout_3->addLayout(formLayout, 1, 1, 1, 1);

        CPUControlWindow->setCentralWidget(centralwidget);

        retranslateUi(CPUControlWindow);

        QMetaObject::connectSlotsByName(CPUControlWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CPUControlWindow)
    {
        CPUControlWindow->setWindowTitle(QApplication::translate("CPUControlWindow", "CPU Status", 0));
        label->setText(QApplication::translate("CPUControlWindow", "A:", 0));
        aValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_3->setText(QApplication::translate("CPUControlWindow", "B:", 0));
        bValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_5->setText(QApplication::translate("CPUControlWindow", "C:", 0));
        cValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_7->setText(QApplication::translate("CPUControlWindow", "D:", 0));
        dValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_2->setText(QApplication::translate("CPUControlWindow", "E:", 0));
        eValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        step->setText(QApplication::translate("CPUControlWindow", "Step", 0));
        romLoadedStatus->setText(QApplication::translate("CPUControlWindow", "ROM Not Loaded!", 0));
        label_11->setText(QApplication::translate("CPUControlWindow", "Current Instruction:", 0));
        currentInstruction->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_13->setText(QApplication::translate("CPUControlWindow", "Cycles Since Last Instruction:", 0));
        cyclesOfLastInstruction->setText(QApplication::translate("CPUControlWindow", "0                        ", 0));
        label_15->setText(QApplication::translate("CPUControlWindow", "Total Cyles:", 0));
        totalCycles->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_9->setText(QApplication::translate("CPUControlWindow", "F:", 0));
        fValue->setText(QApplication::translate("CPUControlWindow", "0                               ", 0));
        label_19->setText(QApplication::translate("CPUControlWindow", "H:", 0));
        hValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_21->setText(QApplication::translate("CPUControlWindow", "L:", 0));
        lValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
        label_23->setText(QApplication::translate("CPUControlWindow", "SP:", 0));
        spValue->setText(QApplication::translate("CPUControlWindow", "0                                                            ", 0));
        label_25->setText(QApplication::translate("CPUControlWindow", "PC:", 0));
        pcValue->setText(QApplication::translate("CPUControlWindow", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class CPUControlWindow: public Ui_CPUControlWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPUCONTROLWINDOW_H
