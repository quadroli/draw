all:
	$(CC) oct.c ./vendor/glad.c -O3 -lglfw -lpthread -ldl -o oct -std=c99
