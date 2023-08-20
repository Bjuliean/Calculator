CC=g++
CFLAGS=-Wall -Wextra -Werror
TFLAGS=-lgtest -std=c++17
SRC=controller/*.cc model/*.cc
TEST=tests/test.cc
TEST_OUTPUT=unit_test
GCOV_PATH=report
DOC_PATH=documentation
APPNAME=SmartCalc_V2.0

all: gcov_report

clean:
	rm -rf *.gcda *.gcno *.info $(TEST_OUTPUT) $(GCOV_PATH)

cleanall: clean uninstall
	rm -rf Archive_calc_v2.0.tgz
	rm -rf documentation/html

install: uninstall
	mkdir build
	cd view && qmake && make && make clean && rm Makefile && mv view.app ../build
	cd build && mv view.app $(APPNAME)

uninstall:
	rm -rf build

test: clean
	$(CC) $(TEST) $(SRC) $(CFLAGS) $(TFLAGS) -o $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

gcov_report: clean
	mkdir $(GCOV_PATH) && cd $(GCOV_PATH) && $(CC) --coverage ../controller/*.cc ../model/*.cc ../tests/test.cc $(CFLAGS) $(TFLAGS) -o gcov_report
	./$(GCOV_PATH)/gcov_report
	lcov -t "gcov_report" -o $(GCOV_PATH)/gcov_report.info --no-external -c -d ./
	genhtml -o report $(GCOV_PATH)/gcov_report.info
	open $(GCOV_PATH)/index.html

dvi:
	cd documentation && doxygen Doxyfile && cd ..
	open $(DOC_PATH)/html/index.html

dist: install
	rm -rf Archive_calc_v2.0/
	mkdir Archive_calc_v2.0/
	mkdir Archive_calc_v2.0/src
	cp -r ./build/$(APPNAME) Archive_calc_v2.0/src/
	tar cvzf Archive_calc_v2.0.tgz Archive_calc_v2.0/
	rm -rf Archive_calc_v2.0/

clang:
	clang-format -style=google -n *.cc model/*.cc controller/*.cc view/mainwindow/*.cc