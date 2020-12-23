#define CURL_STATICLIB

#include <stdio.h>
#include <iostream>
#include <string>
#include "curl/curl.h"
#include <stdlib.h>
#include <sstream> //for std::stringstream
#include <iomanip> //for std::setprecision

using namespace std;
//size_t size = 0;

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
	((string*)stream)->append((char*)ptr, 0, size*count);
	return size * count;
}

int main() {
	for (int i = 0; i < 10; i++){
		std::string result;
		float dogeEx, btcEx, ltcEx;
		CURL* curl;
		CURLcode res;

		//curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();
		if (!curl) {
			fprintf(stderr, "curl initialisation error");
			return 1;
		}
		else {
			//curl_easy_setopt(curl, CURLOPT_URL, "https://www.coingecko.com/en");
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cdogecoin%2Clitecoin&vs_currencies=gbp");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
			res = curl_easy_perform(curl);
			size_t foundD = result.find("dogecoin");
			size_t foundB = result.find("bitcoin");
			size_t foundL = result.find("litecoin");
			size_t foundEnd = result.find("}}");
			size_t foundDStart = foundD + 17;
			size_t foundBStart = foundB + 16;
			size_t foundLStart = foundL + 17;
			size_t foundDEnd = foundB - 3;
			size_t foundBEnd = foundL - 3;
			size_t foundLEnd = foundEnd;
			size_t lengthD = foundDEnd - foundDStart;
			size_t lengthB = foundBEnd - foundBStart;
			size_t lengthL = foundLEnd - foundLStart;
			dogeEx = stof(result.substr(foundDStart, lengthD));
			btcEx = stof(result.substr(foundBStart, lengthB));
			ltcEx = stof(result.substr(foundLStart, lengthL));
		
			std::stringstream outD;
			std::stringstream outB;
			std::stringstream outL;
			outD << std::fixed << std::setprecision(12) << stof(result.substr(foundDStart, lengthD));
			dogeEx = std::stof(outD.str());
			outB << std::fixed << std::setprecision(12) << stof(result.substr(foundBStart, lengthB));
			btcEx = std::stof(outB.str());
			outL << std::fixed << std::setprecision(12) << stof(result.substr(foundLStart, lengthL));
			ltcEx = std::stof(outL.str());
			std::cout << "DOGE: " << dogeEx << std::endl;
			std::cout << "BTC: " << btcEx << std::endl;
			std::cout << "LTC: " << ltcEx << std::endl;
		}
		curl_easy_cleanup(curl);
		Sleep(60000);
	}
	return 0;
}