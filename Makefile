CXX=g++
CXXFLAGS=

# 소스 파일 디렉토리
SRC_DIR = ./src

TARGET = mips-sim

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cc))

OBJS = $(SRCS:.cc=.o)

all: $(TARGET)

%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY=clean

clean:
	rm -f $(OBJS) $(TARGET)