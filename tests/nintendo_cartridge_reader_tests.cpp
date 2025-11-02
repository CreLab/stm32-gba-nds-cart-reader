#include "ApprovalTests.hpp"
#include "catch2\catch_all.hpp"
#include <array>
#include <string>

extern "C" {
#include "nds_cart.h"
#include "util.h"
}

template <>
std::string ApprovalTests::StringMaker::toString(const s_key1& key)
{
    return "[" + std::to_string(key.x) + ", " + std::to_string(key.y) + "]";
}

template <>
std::string ApprovalTests::StringMaker::toString(const s_key2& key)
{
    return "[" + std::to_string(key.x) + ", " + std::to_string(key.y) + "]";
}

template <>
std::string ApprovalTests::StringMaker::toString(const s_blowfish_t& buf)
{
    std::ostringstream oss;
    oss << "s_blowfish_t {\n";

    // P-Array (18 Einträge)
    oss << "  P: [";
    for (size_t i = 0; i < 16; ++i)
        oss << buf.P[i] << ", ";
    oss << buf.P[17] << "]\n";

    // S-Array (4 x 256 Einträge)
    oss << "  S: [\n";
    for (size_t row = 0; row < 4; ++row)
    {
        oss << "    [";
        for (size_t col = 0; col < 254; ++col)
            oss << buf.S[row][col] << ", ";
        oss << buf.S[row][255] << "]\n";
    }
    oss << "  ]\n";

    oss << "}";
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const s_key1& key)
{
    return os << ApprovalTests::StringMaker::toString(key);
}

std::ostream& operator<<(std::ostream& os, const s_key2& key)
{
    return os << ApprovalTests::StringMaker::toString(key);
}

std::ostream& operator<<(std::ostream& os, const s_blowfish_t& buf)
{
    return os << ApprovalTests::StringMaker::toString(buf);
}

namespace CartridgeReader
{
    TEST_CASE("key1_encrypt_cmd approval test")
    {
        std::array<uint64_t, 2> currentCmdValues{1209961685412968144, 1541103208622303741};

        auto functionConverter = [](uint64_t cmd){
            s_blowfish_t buf = {0};
            memset(&buf, 0, sizeof(s_blowfish_t));

            s_key1 key = {0};
            key.y = (uint32_t)(cmd & 0x00000000FFFFFFFF);
            key.x = (uint32_t)((cmd & 0xFFFFFFFF00000000) >> 32);
            key = key1_encrypt_64bit(&buf, key);

            return ((uint64_t)key.x << 32) | (uint64_t)key.y;
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

    TEST_CASE("key1_apply_keycode approval test")
    {
        std::array<uint32_t, 1> currentXValues{564248};
        std::array<uint32_t, 1> currentYValues{784248};
        std::array<uint32_t, 1> currentZValues{235532};

        auto functionConverter = [](uint32_t value1, uint32_t value2, uint32_t value3){
            s_blowfish_t buf = {0};
            memset(&buf, 1, sizeof(s_blowfish_t));

            uint32_t keycode[3] = {value1, value2, value3};

            return key1_apply_keycode(&buf, keycode, 8);
        };

        ApprovalTests::CombinationApprovals::verifyAllCombinations(
                functionConverter,
                currentXValues,
                      currentYValues,
                      currentZValues
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
