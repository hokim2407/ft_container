
CC = clang++

CFLAGS = -Wall -Wextra -Werror

NAME = data

RM = rm -f

SRCS = main_stack.cpp
SRCS = main_map.cpp
SRCS = main_vector.cpp
SRCS = main.cpp tester/tester.cpp  tester/tester_vector.cpp tester/tester_stack.cpp tester/tester_map.cpp

OBJS = $(SRCS:.cpp=.o)

.cpp.o :

	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)

	$(CC) $(CFLAGS) -o $@ $^

all : $(NAME)

clean:

	$(RM) $(OBJS) $(BOBJS)

fclean:	clean

	$(RM) $(NAME)

re : clean all

.PHONY:	all clean fclean re