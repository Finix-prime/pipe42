##

NAME = pipex
FLAGS = -Wall -Werror -Wextra -I
SRCS = main.c split.c utils.c get_next_line.c get_next_line_utils.c

all:
	@gcc -g $(SRCS) -o $(NAME)

clean:
	@rm -rf a.out
	@rm -rf outfile
	@rm -rf *.dSYM
	@rm -rf x
	@rm -rf log

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test11: re
	./$(NAME) infile "ls -l" "wc -l" outfile
	cat outfile
test12: re
	< infile ls -l | wc -l > outfile
	cat outfile

test21: re
	./$(NAME) infile "grep a1" "wc -w" outfile
	cat outfile
test22: re
	< infile grep a1 | wc -w > outfile
	cat outfile

test31: re
	./$(NAME) infile "ls -l" "wc -l" "cat -e" outfile
	cat outfile
test32: re
	< infile ls -l | wc -l | cat -e > outfile
	cat outfile

test41: re
	./$(NAME) infile "cat -e" "grep a1" "wc -w" "cat -e" "wc -l" outfile
	cat outfile
test42: re
	< infile cat -e | grep a1 | wc -w | cat -e | wc -l> outfile
	cat outfile

test51: re
	./$(NAME) infile "mkdir x" "ls -l" outfile
	cat outfile
test52: re
	< infile mkdir x | ls -l > outfile
	cat outfile

testb1: re
	./pipex here_doc EOF "ls" "wc" outfile
	cat outfile
testb2: re
	 "ls" << EOF | "wc" >> outfile
	 cat outfile


test1: test11 test12
test2: test21 test22
test3: test31 test32
test4: test41 test42
test5: test51 test52
testb: testb1 testb2
