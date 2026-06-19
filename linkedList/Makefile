
liblist.a: list.o
	ar rcs $@ -o $<
list.o: list.c list.h
	clang -c $< $@


install: liblist.a list.h
	cp liblist.a /usr/local/lib
	cp list.h /usr/local/include
