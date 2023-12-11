import random

def generate_random_map(input_map, probability):
    symbols = ['B', 'V', 'P', 'T', 'M', 'D']
    output_map = []

    for row in input_map:
        new_row = []
        for cell in row:
            if cell == '0' and random.random() < probability:
                new_row.append(random.choice(symbols))
            else:
                new_row.append(cell)
        output_map.append(new_row)

    return output_map

input_map = []
print("Enter the map (each row on a new line, replaces '0' with random characters of your choosing):")
while True:
    row = input()
    if not row:
        break
    input_map.append(row)

probability = 0.1

output_map = generate_random_map(input_map, probability)

for row in output_map:
    print(''.join(row))
