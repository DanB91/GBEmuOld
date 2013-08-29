#ifndef CPUTEST_H
#define CPUTEST_H

#include "AutoTest.h"
#include "CPU.h"

using namespace GBEmu;

class CPUTest : public QObject
{
        Q_OBJECT

    public:
        CPUTest();

    private slots:
        void op01();
        void op02();

    private:
        CPU cpu;
};

DECLARE_TEST(CPUTest)

#endif // CPUTEST_H
