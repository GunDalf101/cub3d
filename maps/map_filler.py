import random

def generate_room(size, num_rooms):
    # Initialize the map with all walls
    game_map = [['1' for _ in range(size + 2)] for _ in range(size + 2)]

    # Create a list to store room information
    rooms = []

    # Function to check if a point is inside any existing room
    def point_in_rooms(row, col):
        for room in rooms:
            if room['left'] <= col <= room['right'] and room['top'] <= row <= room['bottom']:
                return True
        return False

    # Function to create a room
    def create_room():
        room_width = random.randint(3, 8)
        room_height = random.randint(3, 8)
        room_left = random.randint(1, size - room_width - 1)
        room_top = random.randint(1, size - room_height - 1)
        room_right = room_left + room_width
        room_bottom = room_top + room_height
        return {'left': room_left, 'top': room_top, 'right': room_right, 'bottom': room_bottom}

    # Function to connect two rooms with a corridor
    def connect_rooms(room1, room2):
        row, col = room1['bottom'] + 1, random.randint(room1['left'], room1['right'])
        game_map[row][col] = 'D'
        while row < room2['top']:
            game_map[row][col] = '0'
            row += 1
        if col < room2['left']:
            while col < room2['left']:
                game_map[row][col] = '0'
                col += 1
        else:
            while col > room2['right']:
                game_map[row][col] = '0'
                col -= 1
        game_map[row][col] = 'D'

    # Generate rooms
    for _ in range(num_rooms):
        room = create_room()

        # Check if the new room overlaps with existing rooms
        while any(point_in_rooms(row, col) for row in range(room['top'], room['bottom'] + 1)
                  for col in range(room['left'], room['right'] + 1)):
            room = create_room()

        # Place the room on the map
        for row in range(room['top'], room['bottom'] + 1):
            for col in range(room['left'], room['right'] + 1):
                game_map[row][col] = '0'

        # Connect the new room to an existing room (if any)
        if rooms:
            connect_rooms(room, random.choice(rooms))

        # Add a door 'D' at the entrance of the room
        # door_row, door_col = room['bottom'], (room['left'] + room['right']) // 2
        # game_map[door_row][door_col] = 'D'

        # Add the new room to the list
        rooms.append(room)

    # Place player (E) and exit (L) in random rooms
    player_room = random.choice(rooms)
    player_row, player_col = random.randint(player_room['top'], player_room['bottom']), random.randint(player_room['left'], player_room['right'])
    game_map[player_row][player_col] = 'E'

    exit_room = random.choice(rooms)
    while exit_room == player_room:
        exit_room = random.choice(rooms)
    exit_row, exit_col = random.randint(exit_room['top'], exit_room['bottom']), random.randint(exit_room['left'], exit_room['right'])
    game_map[exit_row][exit_col] = 'L'

    # Place 'Z' and 'Y' in random positions on the map
    z_row, z_col = random.randint(1, size), random.randint(1, size)
    y_row, y_col = random.randint(1, size), random.randint(1, size)

    game_map[z_row][z_col] = 'Z'
    game_map[y_row][y_col] = 'Y'

    return game_map

def print_map(game_map):
    for row in game_map:
        print("".join(row))

map_size = 100
num_rooms = 100
game_map = generate_room(map_size , num_rooms)
# game_map = generate_map(map_size)

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

probability = 0.15

output_map = generate_random_map(game_map, probability)

for row in output_map:
    print(''.join(row))
