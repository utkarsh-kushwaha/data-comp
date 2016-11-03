make
mkdir Huffman
./project -c huffman Test-Files/text_1 Huffman/text_1.hfn
./project -c huffman Test-Files/text_2 Huffman/text_2.hfn
./project -c huffman Test-Files/text_3 Huffman/text_3.hfn
./project -c huffman Test-Files/text_4 Huffman/text_4.hfn
./project -c huffman Test-Files/text_5 Huffman/text_5.hfn
./project -c huffman Test-Files/binary_1 Huffman/binary_1.hfn
./project -c huffman Test-Files/binary_2 Huffman/binary_2.hfn
./project -c huffman Test-Files/binary_3 Huffman/binary_3.hfn
./project -c huffman Test-Files/binary_4 Huffman/binary_4.hfn
./project -c huffman Test-Files/binary_5 Huffman/binary_5.hfn
./project -x huffman Huffman/text_1.hfn	Huffman/text_1
./project -x huffman Huffman/text_2.hfn Huffman/text_2
./project -x huffman Huffman/text_3.hfn Huffman/text_3
./project -x huffman Huffman/text_4.hfn Huffman/text_4
./project -x huffman Huffman/text_5.hfn Huffman/text_5
./project -x huffman Huffman/binary_1.hfn Huffman/binary_1
./project -x huffman Huffman/binary_2.hfn Huffman/binary_2
./project -x huffman Huffman/binary_3.hfn Huffman/binary_3
./project -x huffman Huffman/binary_4.hfn Huffman/binary_4
./project -x huffman Huffman/binary_5.hfn Huffman/binary_5
diff Test-Files/text_1 Huffman/text_1
diff Test-Files/text_2 Huffman/text_2
diff Test-Files/text_3 Huffman/text_3
diff Test-Files/text_4 Huffman/text_4
diff Test-Files/text_5 Huffman/text_5
diff Test-Files/binary_1 Huffman/binary_1
diff Test-Files/binary_2 Huffman/binary_2
diff Test-Files/binary_3 Huffman/binary_3
diff Test-Files/binary_4 Huffman/binary_4
diff Test-Files/binary_5 Huffman/binary_5
