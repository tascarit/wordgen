#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class WordModel{
private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & wordCodes;
		ar & words;
	}

public:
	std::vector<int> wordCodes = {1};
	std::vector<std::string> words = {" "};

	WordModel() = default;

	int Length(){
		return wordCodes.size();
	}

	void PushWord(std::string word, int code){
		words.push_back(word);
		wordCodes.push_back(code);
	}
	
	std::vector<int> GetWordCodes(){
		return wordCodes;
	}
	
	void Dump(){
		std::ofstream ofs("model.cl");

		if (!ofs.is_open())
			return;

		boost::archive::text_oarchive oa(ofs);

		oa << *this;
	}

	void Load(){
		std::ifstream ifs("model.cl");

		if (!ifs.is_open())
			return;

		boost::archive::text_iarchive ia(ifs);

		ia >> *this;
	}

	void Display(){
		for (int i = 0; i < ((wordCodes.size() <= 10) ? wordCodes.size() : 10); i++){
			std::cerr << wordCodes[i] << ") " << words[i] << "\n";
		}

		if (wordCodes.size() > 10)
			std::cerr << "...\n";
	}
};
