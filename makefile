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

		#SYMBOL TABLE PART
	gcc -c symbolTable.c -o build/symbolTable.o
	
		#AST part
	gcc -c ast.c -o build/ast.o

		#INTERMEDIATE CODE part
	gcc -c intermediateCodeGen.c -o build/intermediateCodeGen.o

		#CODE GENERATION PART
	gcc -c Codegen.c -o build/Codegen.o
	
		# Final compilation step
		# Note: Please specify all the object files generated before 'driver.c'

	#RUN USING ./compiler <testcase> <asmFile>

	gcc build/*.o driver.c -o compiler

clean:
	rm -rf build/
	rm -f compiler