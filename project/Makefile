NAME = webserv

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

RM = rm -rf

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/ConfParser.cpp \
       $(SRC_DIR)/HttpRequest.cpp \
       $(SRC_DIR)/Tokenizer.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
