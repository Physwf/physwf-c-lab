DIR_OBJ = ./objs

OBJS = $(DIR_OBJ)/Buffer.obj\
	$(DIR_OBJ)/Connection.obj\
	$(DIR_OBJ)/EventLoop.obj\
	$(DIR_OBJ)/EventSelect.obj\
	$(DIR_OBJ)/Server.obj\
	$(DIR_OBJ)/Socket.obj\
	$(DIR_OBJ)/test.obj

FLAG = -std=c++11 -stdlib=libc++ -Weverything
LIBS=

BIN = ./bin/
CC = clang++

all:$(OBJS)
	$(CC) -o $(BIN)test $(FLAG) $(OBJS) $(LIBS)

$(DIR_OBJ)/%.obj : %.cpp
	$(CC) -c $(FLAG) $< -o $@

clean:
	rm -rf *.o