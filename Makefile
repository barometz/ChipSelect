PROJECT_NAME := ChipSelect

CXX := g++-7
CPPFLAGS := -Iinclude
CXXFLAGS := -Wall -Wextra -std=c++1z
LDLIBS := -lpthread

TARGET := out/$(PROJECT_NAME)_test
GTEST_PATH := test/googletest/googletest

IMPL_SOURCES := $(wildcard src/*.cpp)
IMPL_HEADERS := $(wildcard include/*.h)
IMPL_OBJS := $(patsubst %.cpp,%.o,$(IMPL_SOURCES))
GTEST_OBJS := $(GTEST_PATH)/src/gtest-all.o
TEST_SOURCES := $(wildcard test/*.cpp)
TEST_OBJS := $(patsubst %.cpp,%.o,$(TEST_SOURCES))

.PHONY: clean clean_all test

all: $(TARGET)

clean:
	rm -f $(IMPL_OBJS)
	rm -f $(TEST_OBJS)
	rm -rf $(dir $(TARGET))

clean_all: clean
	rm -f $(GTEST_OBJS)

test: $(TARGET)
	$(TARGET)

$(TARGET): $(IMPL_OBJS) $(GTEST_OBJS) $(TEST_OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(IMPL_OBJS): $(IMPL_HEADERS)

$(GTEST_OBJS): CPPFLAGS += -I$(GTEST_PATH)/include -I$(GTEST_PATH)
$(TEST_OBJS): CPPFLAGS += -I. -I$(GTEST_PATH)/include
$(TEST_OBJS): CXXFLAGS += -Wno-missing-field-initializers
$(TEST_OBJS): $(IMPL_HEADERS)
