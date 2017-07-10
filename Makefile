GCCPARAMS = -Iinclude -O3

OBJECTS=obj/main.o \
	obj/soduku.o \

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

all: soduku

soduku: $(OBJECTS)
	gcc $(OBJECTS) -o soduku $(GCCPARAMS)

clean:
	rm -rf soduku obj

