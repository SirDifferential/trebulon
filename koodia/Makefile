CC=g++
CFLAGS=-std=c++0x -I/home/gekko/SFML/include -fpermissive -I/usr/local/include/libnoise -g -o0 2>&1
LDFLAGS=-pthread -L/home/gekko/SFML/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -L/usr/local/lib -lnoise
SOURCES=$(wildcard ./*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=jokupeli

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

clean:
	rm *.o

