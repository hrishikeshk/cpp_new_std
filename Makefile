include OptMake

.PHONY: pa unit_tests clean

DIRS=unit_tests

all: $(DIRS)

unit_tests:
	cd unit_tests; $(MAKE) unit_tests

clean:
	cd libs; \
        rm -rf *.so; \
        cd $(SRC_DIR)/unit_tests; \
        $(MAKE) clean
