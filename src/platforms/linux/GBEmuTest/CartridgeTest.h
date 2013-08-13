#ifndef CARTRIDGETEST_H
#define CARTRIDGETEST_H
#include "AutoTest.h"
#include "Cartridge.h"
#include "GBEmuExceptions.h"
#include <QFile>
#include <QString>

using namespace GBEmu;

class CartridgeTest : public QObject
{
    Q_OBJECT

public:
    CartridgeTest();

private Q_SLOTS:
    void loadROM();
    void readROM();

private:
    CartridgePtr cart;
    std::string fn = "/home/dan/Downloads/Tetris.gb";

};

CartridgeTest::CartridgeTest()
{
    cart = CartridgePtr(new Cartridge(fn));
}

void CartridgeTest::loadROM(){

    QFile f(tr(fn.c_str()));

    if(!f.open(QIODevice::ReadOnly)) QFAIL("File does not exist");
    QByteArray rom = f.readAll();

    for(int i = 0; i < rom.size(); i++){
        byte b1 = rom[i], b2 = cart->getROM()[i];

        //files should be read in correctly
        QVERIFY2(b1 == b2, QString("i: %1, TestRom: %2X, CartRom: %3X").
                 arg(i).arg(b1).arg(b2).toUtf8());

    }

}

void CartridgeTest::readROM(){
    QVERIFY_THROW(cart->readROM(0x8000), GBEmuException);
    QVERIFY(cart->readROM(0) == 0xC3);
}



DECLARE_TEST(CartridgeTest)
#endif // CARTRIDGETEST_H
