all: main.c
	# Initialization
	mkdir -p build

	# argparse part
	gcc -c argparse/index.c -o build/argparse_index.o

	# utils part
	## tokens folder
	gcc -c utils/tokens/tokens.c -o build/utils_tokens_token.o

	# Final compilation step
	# Note: Please specify all the object files generated before 'main.c'
	gcc build/utils_tokens_token.o build/argparse_index.o main.c -o erplag

clean:
	rm -rf build/