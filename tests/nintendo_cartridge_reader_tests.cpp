#include "ApprovalTests.hpp"
#include "catch2\catch_all.hpp"
#include <array>
#include <string>

extern "C" {
#include "nds_cart.h"
#include "util.h"
}

template <>
std::string ApprovalTests::StringMaker::toString(const s_key2& key)
{
    return "[" + std::to_string(key.x) + ", " + std::to_string(key.y) + "]";
}

std::ostream& operator<<(std::ostream& os, const s_key2& key)
{
    return os << ApprovalTests::StringMaker::toString(key);
}

namespace CartridgeReader
{
    TEST_CASE("key1_encrypt_cmd approval test")
    {
        std::array<uint64_t, 2> currentCmdValues{1209961685412968144, 1541103208622303741};

        auto functionConverter = [](uint64_t cmd){
            return key1_encrypt_cmd(cmd);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentCmdValues
        );
    }

    TEST_CASE("key1_decrypt_cmd approval test")
    {
        std::array<uint64_t, 2> currentCmdValues{207014743889323454, 10601478588930356};

        auto functionConverter = [](uint64_t cmd){
            return key1_decrypt_cmd(cmd);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentCmdValues
        );
    }

    TEST_CASE("key2_init approval test")
    {
        std::vector<bool> currentHwReset{true, false};

        auto functionConverter = [](bool hwReset){
            return key2_init(hwReset);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentHwReset
        );
    }

    TEST_CASE("key2_xcrypt approval test")
    {
        size_t length = 25;

        std::array<uint64_t, 2> currentXValues{1, 2};
        std::array<uint64_t, 2> currentYValues{1, 2};

        std::vector<bool> currentDataValidValues{true, false};
        std::vector<size_t> currentLenValues{length, 0};

        auto functionConverter = [](uint64_t valX, uint64_t valY, bool dataValid, size_t len){
            std::array<uint8_t, 25> dataBuf{};
            dataBuf.fill(1);

            uint8_t* data = nullptr;

            if (dataValid)
            {
                data = dataBuf.data();
            }

            s_nds_cart_state state = {
                    .state = 0,
                    .normal_gap_clk = false,
                    .key1_gap_clk = false,
                    .normal_clk_rate = false,
                    .key1_clk_rate = false,
                    .nds = false,
                    .dsi = false,
                    .has_secure_area = false,
                    .protocol_rev = false,
                    .normal_gap2 = 0,
                    .key1_gap2 = 0,
                    .normal_gap1 = 0,
                    .key1_gap1 = 0,
                    .key1_delay_ms = 0,
                    .game_code = 0,
                    .secure_area_disable = {0},
                    .seed_byte = 0,
                    .chip_id = {.nand = 0, .cart_protocol = 0},
                    .kkkkk = 0,
                    .iii = 0,
                    .jjj = 0,
                    .llll = 0,
                    .mmm = 0,
                    .nnn = 0,
                    .key2 = {.x = valX, .y = valY}
            };

            return key2_xcrypt(&state, data, len);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentXValues,
                currentYValues,
                currentDataValidValues,
                currentLenValues
        );
    }

    TEST_CASE("key2_encrypt_cmd approval test")
    {
        std::array<uint64_t, 2> currentXValues{1, 2};
        std::array<uint64_t, 2> currentYValues{1, 2};
        std::array<uint64_t, 2> currentCmdValues{1, 2};

        auto functionConverter = [](uint64_t valX, uint64_t valY, uint64_t cmd){
            s_nds_cart_state state = {
                    .state = 0,
                    .normal_gap_clk = false,
                    .key1_gap_clk = false,
                    .normal_clk_rate = false,
                    .key1_clk_rate = false,
                    .nds = false,
                    .dsi = false,
                    .has_secure_area = false,
                    .protocol_rev = false,
                    .normal_gap2 = 0,
                    .key1_gap2 = 0,
                    .normal_gap1 = 0,
                    .key1_gap1 = 0,
                    .key1_delay_ms = 0,
                    .game_code = 0,
                    .secure_area_disable = {0},
                    .seed_byte = 0,
                    .chip_id = {.nand = 0, .cart_protocol = 0},
                    .kkkkk = 0,
                    .iii = 0,
                    .jjj = 0,
                    .llll = 0,
                    .mmm = 0,
                    .nnn = 0,
                    .key2 = {.x = valX, .y = valY}
            };

            return key2_encrypt_cmd(&state, cmd);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentXValues,
                currentYValues,
                currentCmdValues
        );
    }
}
