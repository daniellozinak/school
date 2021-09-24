#include <iostream>
#include <string>
 
 
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

double calculate_supp(std::string permutation[4]) {
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

	return r /(double)count;
}
 
int main() {
	const unsigned outlook_count = 4;
	const unsigned temperature_count = 4;
	const unsigned humidity_count = 3;
	const unsigned windy_count = 3;
 
	const std::string outlook[outlook_count] = {  "-", "sunny", "overcast", "rainy" };
	const std::string temperature[temperature_count] = {  "-", "hot", "mild", "cool" };
	const std::string humidity[humidity_count] = {"-", "high", "normal"};
	const std::string windy[windy_count] = { "-", "true", "false" };
 
 
	for (int i = 0; i < outlook_count; i++) {
		for (int j = 0; j < temperature_count; j++) {
			for (int k = 0; k < humidity_count; k++) {
				for (int l = 0; l < windy_count; l++) {
					unsigned current_rule = (i * temperature_count * humidity_count * windy_count) + 
						(j * humidity_count * windy_count) + (k * windy_count) + (l + 1);
					bool play = (outlook[i] == "sunny" && humidity[k] == "high") || (outlook[i] == "rainy" && windy[l] == "true")? false: true;
					
					std::string permutation[] = {outlook[i],temperature[j], humidity[k],windy[l] };
					double supp = calculate_supp(permutation);
					
					std::cout << "[" << current_rule << "] { " << outlook[i] << "," << temperature[j] << "," << humidity[k] << "," << windy[l] << "} \tplay: " << play << " supp: " << supp <<  "\n";
					
					
					
				}
			}
		}
	}
 
	return 0;
}