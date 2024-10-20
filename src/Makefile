CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g
SRC = *.cc
SRC_TEST = tests/*.cc
OBJ = $(patsubst %.cc, %.o, $(wildcard $(SRC)))
OBJ_TEST = $(patsubst %.cc, %.o, $(wildcard $(SRC_TEST)))

.PHONY: all clean test gtest
$(OBJ): s21_containers.h
$(OBJ_TEST): tests/s21_containers_test.h

NAME:=$(shell uname -s)
ifeq ($(NAME), Linux)
		LDFLAGS= -lgtest -lgmock -lpthread
else ifeq ($(NAME), Darwin)
		LDFLAGS= -lgtest -lgmock
endif

all: clean test

test: $(OBJ_TEST)
		$(CXX) $^ $(LDFLAGS) -o $@
		./test
%.o: %.cc
		$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
		@rm -rf $(OBJ) $(OBJ_TEST)
		@rm -rf test gtest test.dSYM/ 
		@rm -rf *.info *.gcno *.gcda report
		@rm -rf test/*.info tests/*.gcda tests/*.gcno

leaks: clean test
		leaks -atExit -- ./test
val: clean test
		valgrind --tool=memcheck --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
check:
		@cp ../materials/linters/.clang-format ./
		clang-format -n *.h tests/*.cc tests/*.h
		@rm -rf .clang-format
check2:
		@cp ../materials/linters/.clang-format ./
		clang-format -i *.h tests/*.cc tests/*.h
		@rm -rf .clang-format
gcov_report: clean add_coverage $(OBJ_TEST)
		@$(CXX) $(CXXFLAGS) $(OBJ_TEST) $(LDFLAGS) -o test
		@./test
		@mkdir report
		lcov --ignore-errors mismatch --ignore-errors empty  --no-external -t "test" -q  -o test.info -c -d .  
		genhtml  -o report test.info
		open report/index.html
		rm -rf *.gcda *.gcno *.out
add_coverage:
	$(eval CXXFLAGS += --coverage)

