CXX = clang++
CXXSTD = c++11
CXXFLAGS = -Wall -std=$(CXXSTD)
#LDFLAGS = -lboost_filesystem -lboost_system
OBJ = src/main.o
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
