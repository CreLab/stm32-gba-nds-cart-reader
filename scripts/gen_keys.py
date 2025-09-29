#!/usr/bin/env python3

import argparse


def convert_file_to_char_array(file_path, array_name, start_byte):
    try:
        with open(file_path, "rb") as f:
            binary_data = f.read()

        valid_data = binary_data[start_byte:(start_byte + 4168)]

        array_definition = "__attribute__((aligned(4))) const unsigned char "
        array_definition += array_name
        array_definition += "[0x1048] = {\n"
        for i in range(0, len(valid_data), 12):
            line = ", ".join(f"0x{byte:02X}" for byte in valid_data[i:i + 12])
            array_definition += f"    {line},\n"
        array_definition += "\n};"

        return array_definition
    except FileNotFoundError:
        return f"Die Datei '{file_path}' wurde nicht gefunden."
    except Exception as e:
        return f"Es ist ein Fehler aufgetreten: {e}"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Konvertiere Binärdatei zu C-Array.")
    parser.add_argument("path", type=str, help="path to project source.")

    args = parser.parse_args()

    nds_cart_key = convert_file_to_char_array(f"{args.path}/bios/biosnds7.rom", "nds_cart_key", 48)
    dsi_cart_key = convert_file_to_char_array(f"{args.path}/bios/biosdsi7.rom", "dsi_cart_key",
                                              50896)

    with open(f"{args.path}/src/nds_cart_key.c", "w") as out_file:
        out_file.write(nds_cart_key)
        out_file.write("\n")
        out_file.write(dsi_cart_key)
