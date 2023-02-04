all: main.c
	# Initialization
	mkdir -p build

	# argparse part
	gcc -c argparse/index.c -o build/argparse.o

	# Final compilation step
	gcc build/argparse.o main.c -o erplag

clean:
	rm -rf build/