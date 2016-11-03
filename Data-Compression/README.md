# Data Compression-Decompression #
### Name: Utkarsh Kushwaha ###
### MIS: 111503037 ###

## Description ##
Three compression algorithms { Huffman, LZW, RLE } have been implemented
to compress the required file to output file whose locations are taken as arguments to the program.

Huffman program reads characters from the file and assigns a varible length compression code
for each character based on the its frequency(character with maximum frequency gets the code of least length ....).
It then writes the codes and their characters to the header of the compressed file and again starts
from the top and reads the text while simulatneously writing the corresponding binary codes to the compressed file.

LZW program reads character sequence from the file and writes them to dictionary if not already present in it.

RLE is useful only for compression of data involving characters having large consecutive occurence frequency.

## Usage Instructions ##

Folder `Test-Files` contains test files for project.
Run `lzw.sh`, `huffman.sh`, `rle.sh` scripts for testing the program.

usage: ./project [OPTION] [METHOD] path(input file) path(output file)

	[OPTION]

	-c 		Compress the input file

	-x 		Decompress the input file

	-h,--help 	For help

	[METHOD]

	huffman 	execute [OPTION] using Huffman

	lzw		execute [OPTION] using LZW

	rle		execute [OPTION] using RLE

## Results ##
An average 40-42% reduction of size of input file (text, binary, ...) is achieved in Huffman compressed file.
No limitation to file type has been observed in case of Huffman and RLE programs.
Very large compression ratios(12 : 1) can be achieved using LZW compression.

## Limitations ##
LZW takes considreable amount of time to compress large data.

## To do ##
Compression of directory.
