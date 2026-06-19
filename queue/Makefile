target:=libqueue.a
objfile:=queue.o
srcfile:= queue.c
headerfile:=queue.h

binary=queue


$(target): $(objfile)
	ar rcs $@  $<
$(objfile): $(srcfile) $(headerfile)
	clang -c  $< -o $@


$(binary): $(objfile)
	clang -llist $< -o $@

run: $(binary)
	./$(binary)

install: $(target) $(headerfile)
	cp $(target) /usr/local/lib
	cp $(headerfile) /usr/local/include


clean: 
	rm -rf $(target) $(binary) $(objfile)

