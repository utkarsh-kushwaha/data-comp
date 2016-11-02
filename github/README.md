# Huffman compression/decompression #

## Usage Instructions ##

File by name `test` is provided for testing of program.

`huff-encode` reads in a byte stream from `filename` and outputs a compressed version of the byte stream to `filename`.huffzip

It can be used as:
`$ ./encode filename`

`decode` reads in byte stream from `filename`(along with .huffzip extension) and outputs the uncompressed version of byte stream to `filename`.

It can be used as:
`$ ./decode filename`

In addition, -h flag is available for `encode` and `decode` which tells the above usage instructions.

## List of features yet to be implemented ##
->Improve Compression/Decompression time-complexity.

->Read more bytes of data(per read) from input files and write the same to compressed file.
  Similar changes for decompression.


### Results ###

|---------------------------------------|
|					                              |
|       Input file : 	139kb;		        |
|       Output file:	81.73kb;		      |
|					                              |
|---------------------------------------|

# Run Length Encoding (RLE) #
File `rle_test` is provided for testing of program.

For compressing:
    `./rle filename`
   
For decompressing:
    `./drle filename <output-filename>`
# LZW(incomplete) #

`lzw.c`: for compression

`dlzw.c`:for decompression

## To do ##

->Write the generated codes in binary form to output file.

->Improve utilisation method of dictonary.

->and much more...

# TO DO #
`Link all compression algorithms`into one file and allow access through flags

`Implement one more compression algorithm`

`Allow multiple compression` files as argument
