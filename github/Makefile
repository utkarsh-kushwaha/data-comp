all: encode decode rle drle
encode: encode.c hufftree.o huff_file.o queue.o merge.o 
	cc -c -Wall encode.c
	cc encode.o hufftree.o huff_file.o queue.o merge.o -o encode
hufftree.o: head.h queue.h queue.c hufftree.c
	cc -c -Wall hufftree.c
huff_file.o: head.h huff_file.h huff_file.c
	cc -c -Wall huff_file.c
queue.o: queue.c queue.h
	cc -c -Wall queue.c
merge.o: head.h
	cc -c -Wall merge.c
decode: decode.c
	cc -Wall decode.c -o decode
rle: rle.c
	cc -Wall rle.c -o rle
drle: drle.c
	cc -Wall drle.c -o drle
