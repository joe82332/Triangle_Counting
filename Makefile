RM = rm -rf

BUILD_DIR = .build

INCLUDES := $(patsubst src/%,include/cugl/%,$(shell find src | grep -P "\.h$$" | sort))
INCLUDE_SUBDIRS := $(patsubst src/%,include/cugl/%,$(filter-out src,$(shell find src -type d | sort)))

all: include cmake

.PHONY: include cmake
include: $(INCLUDE_SUBDIRS) $(INCLUDES)

$(INCLUDE_SUBDIRS):
	mkdir -p $(INCLUDE_SUBDIRS)

include/cugl/%.h: src/%.h
	cp $< $@

cmake: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) ; make

$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) ; cmake ..

.PHONY: data data_large unit_test
data:
	cd data ; make
data_large:
	cd data ; make large
unit_test:
	cd unit_test ; make

.PHONY: clean clean_all
clean:
	$(RM) bin
	$(RM) lib
	$(RM) include
	$(RM) $(BUILD_DIR)
	cd unit_test ; make clean

clean_all: clean
	cd data ; make clean_all

