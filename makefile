all: main.c
	# Initialization
	mkdir -p build

	# argparse part
	gcc -c argparse/index.c -o build/argparse_index.o

	# utils part
	## tokens folder
	gcc -c utils/tokens/tokens.c -o build/utils_tokens_token.o
	## conversions folder
	gcc -c utils/conversions/findIntVal.c -o build/utils_conversions_findIntVal.o

	#lexer part
	gcc -c lexer/lexer.c -o build/lexer_lexer.o

	# Final compilation step
	# Note: Please specify all the object files generated before 'main.c'
	gcc build/lexer_lexer.o build/utils_conversions_findIntVal.o build/utils_tokens_token.o build/argparse_index.o main.c -o erplag

clean:
	rm -rf build/