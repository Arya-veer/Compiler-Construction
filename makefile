all: main.c
		# Initialization
	make clean
	mkdir -p build

		# argparse part
	gcc -c argparse/index.c -o build/argparse_index.o

		#lexer part
	gcc -c lexer/lexer.c -o build/lexer_lexer.o

		#Parser folder
			##dataStructures folder
	gcc -c parser/dataStructures/linkedList.c -o build/parser_dataStructures_linkedList.o
	gcc -c parser/dataStructures/parseTree.c -o build/parser_dataStructures_parseTree.o
	gcc -c parser/dataStructures/stack.c -o build/parser_dataStructures_stack.o
	gcc -c parser/dataStructures/parseTable.c -o build/parser_dataStructures_parseTable.o
	gcc -c parser/dataStructures/addRules.c -o build/parser_dataStructures_addRules.o
			##FnFsets folder
	gcc -c parser/FnFsets/automation.c -o build/parser_FnFsets_automation.o
			##
	gcc -c parser/parser.c -o build/parser_parser.o
			##csvReader folder
	gcc -c parser/csvReader/csvReader.c -o build/parser_csvReader_csvReader.o

		# constants => These are hard coded arrays or enums
	gcc -c constants/constants.c -o build/constants.o
		# Final compilation step
		# Note: Please specify all the object files generated before 'main.c'
	gcc build/*.o main.c -o erplag

clean:
	rm -rf build/