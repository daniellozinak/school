#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
 
//@attribute outlook{ sunny, overcast, rainy }
//@attribute temperature{ hot, mild, cool }
//@attribute humidity{ high, normal }
//@attribute windy{ TRUE, FALSE }
//@attribute play{ yes, no }
 
const unsigned count = 14;
 
const std::string data[count] = {
"sunny,hot,high,FALSE,no",
"sunny,hot,high,TRUE,no",
"overcast,hot,high,FALSE,yes",
"rainy,mild,high,FALSE,yes",
"rainy,cool,normal,FALSE,yes",
"rainy,cool,normal,TRUE,no",
"overcast,cool,normal,TRUE,yes",
"sunny,mild,high,FALSE,no",
"sunny,cool,normal,FALSE,yes",
"rainy,mild,normal,FALSE,yes",
"sunny,mild,normal,TRUE,yes",
"overcast,mild,high,TRUE,yes",
"overcast,hot,normal,FALSE,yes",
"rainy,mild,high,TRUE,no"};


unsigned get_r(std::string permutation[4] ) {
	unsigned r = 0;
	for(int i = 0; i < count; i ++){
		bool contains = true;
		for(int j = 0; j < 4; j++){
			if(permutation[j] != "-"){
				if(data[i].find(permutation[j]) == std::string::npos) {
					contains = false;
				}	
			}
		}
		r+= (contains)? 1:0;
	}
	return r;
}

double calculate_supp(std::string permutation[4]) {
	return get_r(permutation) /(double)count;
}

double calculate_conf(std::string permutation[4]){
	unsigned c_max = 0;
	unsigned r = get_r(permutation);
	if (r == 0)  {return 0;}
	for(int i = 0; i < count;i++){
		bool contains = true;
		for(int j = 0; j < 4; j++){
			if(permutation[j] != "-"){
				if(data[i].find(permutation[j]) == std::string::npos) {
					contains = false;
				}	
			}
		}
		if (data[i].find("yes") != std::string::npos && contains){
			c_max ++;
		}
	}
	return c_max/ (double) r;
}

std::string format_output(std::string &str, const unsigned limit, unsigned index) {
	int start_offset = 2 - (int)std::log10(index);
	str = str.insert(0,start_offset, ' ');
	return str.insert(str.size()-1,limit - str.size() + start_offset , ' ');
}
 
int main() {
	const unsigned outlook_count = 4;
	const unsigned temperature_count = 4;
	const unsigned humidity_count = 3;
	const unsigned windy_count = 3;
 
	const std::string outlook[outlook_count] = {  "-", "sunny", "overcast", "rainy" };
	const std::string temperature[temperature_count] = {  "-", "hot", "mild", "cool" };
	const std::string humidity[humidity_count] = {"-", "high", "normal"};
	const std::string windy[windy_count] = { "-", "TRUE", "FALSE" };
 
	std::ofstream file_stream("output_cv1.txt");
	if(!file_stream.is_open()) {
		std::cout << "Can't open file\n";
		return 0;
	}
 
	for (int i = 0; i < outlook_count; i++) {
		for (int j = 0; j < temperature_count; j++) {
			for (int k = 0; k < humidity_count; k++) {
				for (int l = 0; l < windy_count; l++) {
					unsigned current_rule = (i * temperature_count * humidity_count * windy_count) + 
						(j * humidity_count * windy_count) + (k * windy_count) + (l + 1);
						
					std::string o = outlook[i];
					std::string t = temperature[j];
					std::string h = humidity[k];
					std::string w = windy[l];
					bool play = (o == "sunny" && h == "high") || (o == "rainy" && w == "true")? false: true;
					std::string play_str = play? "true" : "false";
					
					std::string permutation[] = {o, t, h, w};
					double supp = calculate_supp(permutation);
					double conf = calculate_conf(permutation);
					std::string rules = "{" + o + " , " + t + " , " + h + " , " + w + "}";
					std::string output = "[" + std::to_string(current_rule) + "]" + format_output(rules,45, current_rule) + " play: " + play_str + " supp: " +std::to_string(supp) + " conf: " + std::to_string(conf) + "\n";
					std::cout << output;
					file_stream << output;				
				}
			}
		}
	}
	
	file_stream.close();
 
	return 0;
}