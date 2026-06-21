target:=libvec.a
objfile:=vec.o
srcfile:=vec.c
headerfile:=vec.h
binary=vec

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

