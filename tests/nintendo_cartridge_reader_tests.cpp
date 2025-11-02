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
    TEST_CASE("nds_cart_exec_command approval test")
    {
        size_t length = 1024;

        std::array<e_nds_cart_state, 4> currentState{NDS_CART_UNINITIALIZED, NDS_CART_RAW, NDS_CART_KEY1, NDS_CART_KEY2};

        std::array<e_nds_cart_clk_rate, 2> currentKey1ClkRate{NDS_CART_CLK_6P7_MHZ, NDS_CART_CLK_4P2_MHZ};
        std::array<bool, 2> currentKey1GapClk{false, true};

        std::array<e_nds_cart_clk_rate, 2> currentNormalClkRate{NDS_CART_CLK_6P7_MHZ, NDS_CART_CLK_4P2_MHZ};
        std::array<bool, 2> currentNormalGapClk{false, true};

        std::vector<bool> currentDataValidValues{true};
        std::vector<size_t> currentLenValues{length, 0};

        auto functionConverter = [](e_nds_cart_state state, e_nds_cart_clk_rate key1ClkRate, bool key1GapClk, e_nds_cart_clk_rate normalClkRate, bool normalGapClk, bool dataValid, size_t len) {
            std::array<uint8_t, 1024> dataBuf{};
            dataBuf.fill(1);

            uint8_t* data = nullptr;

            if (dataValid)
            {
                data = dataBuf.data();
            }

            s_nds_cart_config cfg = {
                    .state = state,
                    .normal_gap_clk = normalGapClk,
                    .key1_gap_clk = key1GapClk,
                    .normal_clk_rate = normalClkRate,
                    .key1_clk_rate = key1ClkRate,
                    .nds = false,
                    .dsi = false,
                    .has_secure_area = false,
                    .protocol_rev = false,
                    .normal_gap2 = 0x18,
                    .key1_gap2 = 0x18,
                    .normal_gap1 = 0x8F8,
                    .key1_gap1 = 0x8F8,
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
                    .key2 = {0x15631934, 0x02DF76D0}
            };

            nds_cart_exec_command(&cfg, 0x10CAA5BE02DF76D0, data, len);

            return cfg.key2;
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentState,
                currentKey1ClkRate,
                currentKey1GapClk,
                currentNormalClkRate,
                currentNormalGapClk,
                currentDataValidValues,
                currentLenValues
        );
    }

    TEST_CASE("key1_encrypt_cmd approval test")
    {
        std::array<uint64_t, 2> currentCmdValues{0x10CAA5BE02DF76D0, 0x156319340025A9FD};

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
        std::array<uint64_t, 2> currentCmdValues{0x2DF76D010CAA5BE, 0x25A9FD15631934};

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

            s_nds_cart_config cfg = {
                    .state = NDS_CART_UNINITIALIZED,
                    .normal_gap_clk = false,
                    .key1_gap_clk = false,
                    .normal_clk_rate = NDS_CART_CLK_6P7_MHZ,
                    .key1_clk_rate = NDS_CART_CLK_6P7_MHZ,
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

            return key2_xcrypt(cfg.key2, data, len);
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
            s_nds_cart_config cfg = {
                    .state = NDS_CART_UNINITIALIZED,
                    .normal_gap_clk = false,
                    .key1_gap_clk = false,
                    .normal_clk_rate = NDS_CART_CLK_6P7_MHZ,
                    .key1_clk_rate = NDS_CART_CLK_6P7_MHZ,
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

            return key2_encrypt_cmd(&cfg, cmd);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentXValues,
                currentYValues,
                currentCmdValues
        );
    }
}
