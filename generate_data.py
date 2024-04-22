from random import choices, randint
from string import ascii_lowercase
import os


with open(os.path.join(os.getcwd(), r"src\config.h"), "r") as f:
    file = f.readlines()
    amount = 100
    for line in file:
        if "TABLES_NUMBER" in line:
            semi_parsed_amount = line[line.index("=") + 2:]
            amount = 0
            i = 0
            while semi_parsed_amount[i].isdigit():
                amount = amount * 10 + int(semi_parsed_amount[i])
                i += 1
            amount *= 2
            break
    output_file = open("data.txt", "w")
    for _ in range(amount):
        string = "".join(choices(ascii_lowercase, k=randint(3, 10)))
        output_file.write(string + "\n")
    output_file.close()
