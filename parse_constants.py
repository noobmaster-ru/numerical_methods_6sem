import re

# Путь к файлу constants.h
header_file = "constants.h"
output_file = "constants.py"

# Регулярное выражение для поиска #define
define_pattern = re.compile(r"#define\s+(\w+)\s+(.+)")

# Словарь для хранения констант
constants = {}

# Чтение файла constants.h
with open(header_file, 'r') as file:
    for line in file:
        match = define_pattern.match(line)
        if match:
            key, value = match.groups()
            constants[key] = value

# Генерация файла constants.py
with open(output_file, 'w') as file:
    file.write("# This file is auto-generated from constants.h\n\n")
    for key, value in constants.items():
        file.write(f"{key} = {value}\n")

print(f"Constants from constants.h save to {output_file}")