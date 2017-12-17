
FFLIBS = libavcodec libavformat libavutil libavdevice libswscale
FFCFLAGS = `pkg-config --cflags $(FFLIBS)`
FFLDFLAGS = `pkg-config --libs $(FFLIBS)`

LOCAL_CFLAGS += $(CFLAGS) $(FFCFLAGS)
LOCAL_LDFLAGS += $(LDFLAGS) $(FFLDFLAGS)

export

all:
	cd ui/ && \
		qmake && \
		make

# this is mac specific, probably want to fix this
debug:
	./player.app/Contents/MacOS/player

clean:
	cd ui/ && make clean
