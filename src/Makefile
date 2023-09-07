CC = g++ -std=c++17
FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g
LIBRARY = s21_matrix_oop.a
CLEAN = clean
REPORT = gcov_report
TESTS = ./TEST_PATH/
SRC = $(wildcard *.cpp)
UNAME := $(shell uname)
SRC_TEST = $(wildcard $(TESTS)*.cpp)
TARGET = test

GCOV_FLAGS = -g -fprofile-arcs -ftest-coverage -lgcov 

ifeq ($(UNAME), Linux)
 TEST_FLAGS += -lgtest -lm
else
 TEST_FLAGS += -lgtest -lgtest_main -pthread -lm
endif
all : $(CLEAN) $(LIBRARY) $(TARGET)
$(TARGET) : $(SRC) 
	$(CC) $(FLAGS) $(SRC_TEST) $(SRC) $(TEST_FLAGS) -o tests
	./tests
$(LIBRARY) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC) $(TEST_FLAGS)
	ar rc $(LIBRARY) *.o
	ranlib $(LIBRARY)

$(REPORT) : rm_buld_file $(SRC) $(SRC_TEST) build_file
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(SRC_TEST) $(SRC) $(TEST_FLAGS) -o Build/$(REPORT)
	Build/./$(REPORT)
	lcov -o $(REPORT).info -c -d .
	genhtml $(REPORT).info -o html_report
	open html_report/index.html

build_file:
	mkdir Build

rm_buld_file:
	rm -rf Build



style: 
	clang-format -i *.cpp *.h $(SRC_TEST)

$(CLEAN) :
	rm -rf tests *.a *.o $(TESTS).*o ./html_report/ gcov_report *.gcno *.gcda *.info *.out Build
