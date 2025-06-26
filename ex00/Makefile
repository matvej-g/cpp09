NAME		= btc
CPP			= c++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++17

INCLUDES	= -I./includes
SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(wildcard $(SRC_DIR)/*.cpp)
OBJS		= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run