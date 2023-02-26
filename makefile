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
			## tokens folder (has tokens dependency)
	gcc -c utils/tokens/tokens.c -o build/utils_tokens_token.o
			## colorText folder
	gcc -c utils/colorText/index.c -o build/utils_colorText_index.o
			## csvReader folder
	gcc -c utils/csvReader/csvReader.c -o build/utils_csvReader_csvReader.o
			## errors
	gcc -c utils/errors/errors.c -o build/utils_errors_errors.o
			## nonTerminals
	gcc -c utils/nonTerminals/nonTerminals.c -o build/utils_nonTerminals_nonTerminals.o
			## terminals
	gcc -c utils/terminals/terminals.c -o build/utils_terminals_terminals.o

		#lexer part
	gcc -c lexer/lexer.c -o build/lexer_lexer.o
	gcc -c lexer/tokenize.c -o build/lexer_tokenize.o

		#Parser folder
			##dataStructures folder
	gcc -c parser/dataStructures/linkedList.c -o build/parser_dataStructures_linkedList.o
	gcc -c parser/dataStructures/parseTree.c -o build/parser_dataStructures_parseTree.o
	gcc -c parser/dataStructures/stack.c -o build/parser_dataStructures_stack.o
			##FnFsets folder
	gcc -c parser/FnFsets/sets.c -o build/parser_FnFsets_sets.o
	gcc -c parser/FnFsets/automation.c -o build/parser_FnFsets_automation.o
			##parseTable folder
	gcc -c parser/parseTable/parseTable.c -o build/parser_parseTable_parseTable.o
			##rules folder
	gcc -c parser/rules/addRules.c -o build/parser_rules_addRules.o
			##
	gcc -c parser/parser.c -o build/parser_parser.o

		# Final compilation step
		# Note: Please specify all the object files generated before 'main.c'
	gcc build/*.o main.c -o erplag.o

clean:
	rm -rf build/