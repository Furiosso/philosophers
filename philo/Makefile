NAME = philo
CC = cc
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
CFILES = $(wildcard $(SRC_DIR)/*.c)
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3 -pthread #-fsanitize=address,leak
OFILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))

all: $(NAME)

$(NAME):$(OFILES)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c |  $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
