all: main.c
	# Initialization
	make clean
	mkdir -p build

	# argparse part
	gcc -c argparse/index.c -o build/argparse_index.o

	# utils part
	## Buffer folder
	gcc -c utils/Buffer/readFile.c -o build/utils_Buffer_readfile.o
	gcc -c utils/Buffer/twinBuffer.c -o build/utils_Buffer_twinBuffer.o
	## tokens folder
	gcc -c utils/tokens/tokens.c -o build/utils_tokens_token.o
	## colorText folder
	gcc -c utils/colorText/index.c -o build/utils_colorText_index.o

	#lexer part
	gcc -c lexer/lexer.c -o build/lexer_lexer.o
	gcc -c lexer/tokenize.c -o build/lexer_tokenize.o

	# Final compilation step
	# Note: Please specify all the object files generated before 'main.c'
	gcc build/*.o main.c -o erplag

clean:
	rm -rf build/