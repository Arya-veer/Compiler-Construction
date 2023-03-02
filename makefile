all: driver.c
		# Initialization
	make clean
	mkdir -p build

		#lexer part
	gcc -c lexer.c -o build/lexer.o

		#parser part
	gcc -c parser.c -o build/parser.o

		# constants => These are hard coded arrays or enums
	gcc -c constants.c -o build/constants.o
		# Final compilation step
		# Note: Please specify all the object files generated before 'driver.c'
	gcc build/*.o driver.c -o erplag

clean:
	rm -rf build/