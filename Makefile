
SDLCFLAGS = `pkg-config --cflags sdl2`
SDLLDFLAGS = `pkg-config --libs sdl2`

# lol ideally this should be done with pkg-config, but not on a mac
FFLDFLAGS = -lavutil -lavformat -lavcodec -lavdevice -lswscale -lz -lm

CFLAGS += $(SDLCFLAGS)
LDFLAGS += $(SDLLDFLAGS) $(FFLDFLAGS)
BIN = player

OBJS = log.o main.o

all: $(OBJS)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

clean:
	rm -rf $(BIN) *.o
