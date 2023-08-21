import pygame
import random

# Kích thước cửa sổ trò chơi
WIDTH = 800
HEIGHT = 600

# Kích thước ô trong mê cung
CELL_SIZE = 40

# Màu sắc
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

# Khởi tạo mê cung
maze = [[0] * (WIDTH // CELL_SIZE) for _ in range(HEIGHT // CELL_SIZE)]
start_pos = (0, 0)
end_pos = (WIDTH // CELL_SIZE - 1, HEIGHT // CELL_SIZE - 1)

# Thêm chướng ngại vật ngẫu nhiên
obstacle_positions = []
for _ in range((WIDTH // CELL_SIZE) * (HEIGHT // CELL_SIZE) // 4):
    x = random.randint(0, WIDTH // CELL_SIZE - 1)
    y = random.randint(0, HEIGHT // CELL_SIZE - 1)
    if (x, y) != start_pos and (x, y) != end_pos:
        obstacle_positions.append((x, y))

# Khởi tạo Pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# Hàm vẽ mê cung
def draw_maze():
    screen.fill(BLACK)
    for y in range(HEIGHT // CELL_SIZE):
        for x in range(WIDTH // CELL_SIZE):
            rect = pygame.Rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE)
            if maze[y][x] == 0:
                pygame.draw.rect(screen, WHITE, rect)
            elif maze[y][x] == 1:
                pygame.draw.rect(screen, BLUE, rect)
            elif maze[y][x] == 2:
                pygame.draw.rect(screen, RED, rect)
            elif maze[y][x] == 3:
                pygame.draw.rect(screen, GREEN, rect)
            elif maze[y][x] == 4:
                pygame.draw.rect(screen, BLACK, rect)
    pygame.display.flip()

# Hàm tìm đường đi với thuật toán DFS
def dfs(x, y):
    if x < 0 or x >= WIDTH // CELL_SIZE or y < 0 or y >= HEIGHT // CELL_SIZE:
        return False
    if maze[y][x] == 2:
        return False
    if maze[y][x] == 3:
        return True
    maze[y][x] = 2
    draw_maze()
    pygame.time.wait(100)
    if dfs(x + 1, y) or dfs(x - 1, y) or dfs(x, y + 1) or dfs(x, y - 1):
        maze[y][x] = 3
        draw_maze()
        pygame.time.wait(100)
        return True
    maze[y][x] = 4
    draw_maze()
    pygame.time.wait(100)
    return False

# Hàm hiển thị lưu ý khi gặp chướng ngại vật
def show_alert():
    font = pygame.font.Font(None, 30)
    text = font.render("Chướng ngại vật!", True, YELLOW)
    screen.blit(text, (10, 10))
    pygame.display.flip()
    pygame.time.wait(1000)

# Hàm chạy trò chơi
def run_game():
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        draw_maze()
        if dfs(start_pos[0], start_pos[1]):
            print("Tìm thấy đường đi!")
        else:
            print("Không tìm thấy đường đi!")
            show_alert()

    pygame.quit()

run_game()

