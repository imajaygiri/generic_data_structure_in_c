target:=libstack
objfile:=stack.o
srcfile:= stack.c
headerfile:=stack.h


$(target): $(objfile)
	ar rcs $@  $<
$(objfile): $(srcfile) $(headerfile)
	clang -c $< -o $@


install: $(target) stack.h
	cp $(target) /usr/local/lib
	cp $(headerfile) /usr/local/include
