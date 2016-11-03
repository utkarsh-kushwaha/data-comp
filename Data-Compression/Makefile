all: project *.o
clean:
	rm *.o
	rm project
project: main.o file_size.o huffman.o dehuffman.o huffman_file.o queue.o merge.o lndzw.o lzw.o dlzw.c rle.o drle.o
	gcc main.o file_size.o huffman.o dehuffman.o huffman_file.o queue.o merge.o lndzw.o lzw.o dlzw.c rle.o drle.o -o project
	rm *.o
main.o: main.c algorithm.h
	gcc -c -Wall main.c -g
file_size.o: file_size.c file_size.h
	gcc -c -Wall file_size.c -g
dehuffman.o: dehuffman.c
	gcc -c -Wall dehuffman.c -g
huffman.o: huffman.c head.h queue.h huffman_tree.h huffman_file.h
	gcc -c -Wall huffman.c -g
huffman_file.o: head.h huffman_file.h huffman_file.c merge.c file_size.h file_size.c
	gcc -c -Wall huffman_file.c -g
queue.o: queue.c queue.h
	gcc -c -Wall queue.c -g
merge.o: merge.c head.h
	gcc -c -Wall merge.c -g
lndzw.o: lndzw.h lndzw.c dictionary.h
	gcc -c -Wall lndzw.c -g
lzw.o: lzw.h lzw.c lndzw.c lndzw.h dictionary.h
	gcc -c -Wall lzw.c -g
dlzw.o: dlzw.h dlzw.c dictionary.h lndzw.h lndzw.c
	gcc -c -Wall dlzw.c -g
rle.o: rle.c
	gcc -c -Wall rle.c
drle.o: drle.c
	gcc -c -Wall drle.c
