.PHONY:clean
CC=g++
CCFLAGS=-Wall -g
BIN=miniftp
OBJS=main.o sysutils.o network_service.o

$(BIN):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o:%.cpp
	$(CC) $(CCFLAGS) $^ -c -o $@

clean:
	rm $(OBJS) $(BIN)

