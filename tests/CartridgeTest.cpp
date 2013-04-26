#include <gtest/gtest.h>
#include <fstream>
#include "Cartridge.h"

using namespace GBEmu;

class CartridgeTest : public ::testing::Test{

    protected:
        CartridgeTest():
            cart("/home/dan/Downloads/Tetris.gb")
        {
        }
        
        virtual void SetUp(){
        }

        Cartridge cart;
};

TEST_F(CartridgeTest, loadrom){
    const char *fn = "/home/dan/Downloads/Tetris.gb";
    std::ifstream f(fn, std::ios::in | std::ios::binary);
    unsigned char byte;
    int i = 0;

    if(!f.is_open()){
        FAIL();
    }

    while(f.good()){
        f.read((char*)&byte, 1);

        ASSERT_EQ(cart.getROM()[i], byte) << "Index: "<< i;

        i++;
    }

    std::cout << cart.getCartType() << '\n';

    f.close();


}
