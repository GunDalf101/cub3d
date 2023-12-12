import random

def generate_map(size):
    # Initialize the map with all walls
    game_map = [['1' for _ in range(size + 2)] for _ in range(size + 2)]

    # Place empty space inside the walls
    for row in range(1, size + 1):
        for col in range(1, size + 1):
            game_map[row][col] = '0'

    # Place walls randomly within the empty space
    for _ in range(size * size // 4):
        row, col = random.randint(1, size), random.randint(1, size)
        game_map[row][col] = '1'  # '1' represents a wall

    # Place player (E) at a random position
    player_row, player_col = random.randint(1, size), random.randint(1, size)
    game_map[player_row][player_col] = 'E'

    # Place exit (L) at a random position
    exit_row, exit_col = random.randint(1, size), random.randint(1, size)
    game_map[exit_row][exit_col] = 'L'

    # Place random squares (Z and Y)
    z_row, z_col = random.randint(1, size), random.randint(1, size)
    y_row, y_col = random.randint(1, size), random.randint(1, size)
    game_map[z_row][z_col] = 'Z'
    game_map[y_row][y_col] = 'Y'

    return game_map

def print_map(game_map):
    for row in game_map:
        print("".join(row))

map_size = 30
game_map = generate_map(map_size)

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

# input_map = []
# print("Enter the map (each row on a new line, replaces '0' with random characters of your choosing):")
# while True:
#     row = input()
#     if not row:
#         break
#     input_map.append(row)

probability = 0.2

output_map = generate_random_map(game_map, probability)

for row in output_map:
    print(''.join(row))
