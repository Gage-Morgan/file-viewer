all:
	gcc -o disassemble main.c file_utils.c disassemble.c -lcapstone
clean:
	rm disassemble
