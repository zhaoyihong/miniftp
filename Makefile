.PHONY:clean
CC=g++ 
CCFLAGS=-Wall -g -std=c++11 -DDEBUG
BIN=miniftp
OBJS=main.o sysutils.o session.o ftp_protocol.o private_parent.o
$(BIN):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@
%.o:%.cpp
	$(CC) $(CCFLAGS) $^ -c -o $@
clean:
	rm $(OBJS) $(BIN)

