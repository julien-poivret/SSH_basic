# A Basic Makefile.
cc = gcc
src = main.c
obj = out
flags = -Wall -O3
$(obj):$(src)
	@($(cc) $(src) -o $(obj) $(flags) && strip $(obj) && ./$(obj))  
