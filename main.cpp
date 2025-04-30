#include <iostream>
#include <libstemmer.h>

#include "definitions.h"

int main(){
	std::string input;

	WordModel model;
	
	// READING PREVIOUS MODEL IF EXISTS
	
	model.Load();

	if (model.Length() > 0){
		std::cout << "Successfully loaded model with " << model.Length() << " words data\n";
		std::cout << "Model contents:\n";

		model.Display();
	}

	// GETTING THE INPUT

	std::cout << "Your input: ";
	std::getline(std::cin, input);
	
	// VECTORIZING INPUT WORDS

	Vectorize(input, model);

	// SAVING MODEL
	
	model.Dump();

	return 0;
}
