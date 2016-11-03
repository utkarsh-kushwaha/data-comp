make
mkdir LZW
./project -c lzw Test-Files/text_1 LZW/text_1.lzw
./project -c lzw Test-Files/text_2 LZW/text_2.lzw
./project -c lzw Test-Files/binary_1 LZW/binary_1.lzw
./project -c lzw Test-Files/binary_2 LZW/binary_2.lzw
./project -c lzw Test-Files/datastructure.jpg LZW/datastructure.jpg.lzw
./project -c lzw Test-Files/hw_strings_maths.odt LZW/hw_strings_maths.odt.lzw
./project -x lzw LZW/text_1.lzw LZW/text_1
./project -x lzw LZW/text_2.lzw LZW/text_2
./project -x lzw LZW/binary_1.lzw LZW/binary_1
./project -x lzw LZW/binary_2.lzw LZW/binary_2
./project -x lzw LZW/datastructure.jpg.lzw LZW/datastructure.jpg
./project -x lzw LZW/hw_strings_maths.odt.lzw LZW/hw_strings_maths.odt
diff Test-Files/text_1 LZW/text_1
diff Test-Files/text_2 LZW/text_2
diff Test-Files/binary_1 LZW/binary_1
diff Test-Files/binary_2 LZW/binary_2
diff Test-Files/datastructure.jpg LZW/datastructure.jpg
diff Test-Files/hw_strings_maths.odt LZW/hw_strings_maths.odt
