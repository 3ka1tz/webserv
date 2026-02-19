NAME = webserv

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/ConfParser.cpp \
       $(SRC_DIR)/RequestLine.cpp \
       $(SRC_DIR)/ServerConfig.cpp \
       $(SRC_DIR)/ServerSocket.cpp \
       $(SRC_DIR)/Tokenizer.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo $(GREEN)Webserv compiled!$(RESET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo $(RED)Webserv objects cleaned.$(RESET)

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo $(RED)Webserv objects and executable cleaned.$(RESET)

re: fclean all

.PHONY: all clean fclean re
