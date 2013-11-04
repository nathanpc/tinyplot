CXX = clang++
CXXSTD = c++11

CXXFLAGS = -Wall -std=$(CXXSTD) $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image SDL2_ttf)
LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image SDL2_ttf)

OBJ = src/main.o src/tinyplot.o src/graphics.o src/plot.o src/text.o src/clog.o
PREFIX = /usr/bin
NAME = tinyplot

all: build

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(NAME) $(LIBS)

debug: CXXFLAGS += -g3 -DDEBUG
debug: build

%.o: %.c
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $<

clean:
	rm -rf src/*.o
	rm -rf $(NAME)

install: build
	sudo chmod a+x ./$(NAME)
	sudo mkdir ${PREFIX)
	sudo install ./$(NAME) $(PREFIX)

uninstall:
	sudo rm $(PREFIX)/$(NAME)
