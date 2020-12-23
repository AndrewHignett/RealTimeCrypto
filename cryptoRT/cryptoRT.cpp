#define CURL_STATICLIB

#include <stdio.h>
#include <iostream>
#include <string>
#include "curl/curl.h"

int main() {
	std::string result;
	CURL* curl;
	CURLcode res;

	//curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl initialisation error");
		return 1;
	}
	else {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.coingecko.com/en");
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	return 0;
}