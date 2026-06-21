target:=libstr.a
objfile:=str.o
srcfile:= str.c
headerfile:=str.h
binary=str

$(target): $(objfile)
	ar rcs $@  $<
$(objfile): $(srcfile) $(headerfile)
	clang -c  $< -o $@


$(binary): $(objfile)
	clang -lstr $< -o $@

run: $(binary)
	./$(binary)

install: $(target) $(headerfile)
	cp $(target) /usr/local/lib
	cp $(headerfile) /usr/local/include


clean: 
	rm -rf $(target) $(binary) $(objfile)

