NAME=ex3207
SRC=$(NAME).cpp
TARGET=$(NAME).bin
CPPFLAGS=-lm -lcrypt -std=c++11 -pipe -DONLINE_JUDGE -O2 -g
CPP=g++
$(TARGET): $(SRC)
	$(CPP) $(CPPFLAGS) $< -o $@
