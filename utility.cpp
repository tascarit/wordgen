#include <string>
#include <vector>
#include <algorithm>
#include <libstemmer.h>

#include "word_model.cpp"

bool find(std::vector<std::string> source, std::string pattern){
	for (std::string i: source)	{
		if (i == pattern)
			return true;
	}

	return false;
}

int GetNextIndex(std::vector<int> existing){
	int mx = *std::max_element(existing.begin(), existing.end()) + 1;
	return mx;
}

int split(std::string input, std::vector<std::string>& out){
	std::string ret = "";

	for (char i: input){
		
		if (i == ' ' || i == '\0'){
			if (ret.size() > 0)
				out.push_back(ret);
			ret.clear();
			continue;
		}

		ret += i;
	}

	out.push_back(ret);

	return 0;
}

int Vectorize(std::string input, WordModel& model){
	std::vector<std::string> patterns;
	struct sb_stemmer *stemmer = sb_stemmer_new("russian", "UTF_8");
	
	split(input, patterns);
	
	for (std::string word: patterns){
		if (!find(model.words, word)){
		
			// LEMMATIZING

			const sb_symbol* inp = reinterpret_cast<const sb_symbol*>(word.c_str());
			const sb_symbol* stemmed = sb_stemmer_stem(stemmer, inp, word.length());
			std::string result(reinterpret_cast<const char*>(stemmed));

			model.words.push_back(result);
			model.wordCodes.push_back(GetNextIndex(model.wordCodes));
		}
	}
	
	sb_stemmer_delete(stemmer);

	return 0;
}

