TARGET = main
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): main.c
	cc main.c $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean

