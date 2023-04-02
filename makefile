#                         GROUP - 30
# ID:  2020A7PS0094P                     Name:  Arya Veer Singh Chauhan
# ID:  2020A7PS0049P                     Name:  Madhav Madhusoodanan
# ID:  2020A7PS0016P                     Name:  Ruchika Sarkar
# ID:  2020A7PS0984P                     Name:  Utsav Goel
# ID:  2020A7PS0102P                     Name:  Hardik Jain

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

		#AST part
	gcc -c ast.c -o build/ast.o
	
		# Final compilation step
		# Note: Please specify all the object files generated before 'driver.c'
	gcc build/*.o driver.c -o stage1exe

clean:
	rm -rf build/
	rm -f stage1exe