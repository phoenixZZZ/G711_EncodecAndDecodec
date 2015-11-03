decode:
	gcc -ggdb -o decode decode.c g711.c g711codec.c 
encode:
	gcc -ggdb -o encode encode.c g711.c g711codec.c 
clean:
	rm -f encode decode
