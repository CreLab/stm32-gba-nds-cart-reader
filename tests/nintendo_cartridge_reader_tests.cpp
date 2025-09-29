#include "catch2\catch_all.hpp"

extern "C" {
#include "util.h"
}

TEST_CASE("usb_send_data sends correct data", "[usb]")
{
    uint8_t UserTxBufferFS[64];

    const char testData[] = "Hello USB!";
    usb_send_data(testData, sizeof(testData));

    REQUIRE(std::memcmp(UserTxBufferFS, testData, sizeof(testData)) == 0);
}
