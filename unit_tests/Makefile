include $(SRC_DIR)/OptMake

.PHONY: unit_tests clean

TST_INCLUDES=-I $(SRC_DIR)/unit_tests

simple_tests.o: simple_tests.cpp Test_Utils.h ../gcd.h ../modulars.h ../numeric_funcs.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o simple_tests.o -c simple_tests.cpp

perf_tests.o: perf_tests.cpp ../numeric_funcs.h Test_Utils.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o perf_tests.o -c perf_tests.cpp

List_Tests.o: ../pa/List.h List_Tests.cpp
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o List_Tests.o -c List_Tests.cpp

unit_tests: simple_tests.o perf_tests.o List_Tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/simple_tests simple_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/perf_tests perf_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/List_Tests List_Tests.o

clean:
	rm -rf *.o; rm -rf $(SRC_DIR)/libs/*

