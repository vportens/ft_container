NAME    =	vector

# --   Directory   -- #
OBJ_DIR     =   objs
INC_DIR        =    incs
CLONE		= FOLDERTEST

# --  Search All files in SRCS  -- #
SRC_DIR     =    $(shell find . -type d)
vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

SRCS =   erase.cpp	\

# --  Redirection in OBJS  -- #
OBJS    = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))

# --   Compilation flags  -- #
CC        = clang++
CPPFLAG    = -std=c++98 -g #-Wall -Wextra -Werror -std=c++98

.PHONY: all

all: | $(CLONE)
	cd $(CLONE) && ./do.sh	

$(CLONE) :
	git clone https://github.com/mli42/containers_test $@

$(NAME): $(OBJS)
		$(CC) $(CPPFLAG) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	${CC} ${CPPFLAG} -o $@ -c $< -I $(INC_DIR)

$(OBJ_DIR) :
	mkdir -p $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean

fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all


