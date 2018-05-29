#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <iterator>
#include <string>
#include "WeightedGraph.h"

template <class Container>
void split(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}


int main(int argc, char * argv[])
{
	if(argc != 3) {
        std::cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << std::endl;
        return 1;
    }

    ifstream infile(argv[1]);
    string line;
    // process first line
    getline(infile, line);
    vector<string> words;
    split(line,words);
    int n = stoi(words[0]);
    int m = stoi(words[1]);
    int p = stoi(words[2]);
    int k = stoi(words[3]);
    WeightedGraph MiddleEast(n);
    //add jewelers to the towns
    for(int i=0; i<k; i++){
    	getline(infile, line);
        vector<string> nums;
        split(line,nums);
        int coin_num = stoi(nums[1]);
        for(int j=0; j< coin_num; j++){
        	MiddleEast.addJeweler(stoi(nums[0])-1, stoi(nums[2+j]));	
        }
    }
    //add roads between towns
    for(int i=0; i<m; i++){
    	getline(infile, line);
        vector<string> nums;
        split(line,nums);
        //save thieves into a set
        set<int> thieves;
        int thief_num = stoi(nums[3]);
        for(int j=0; j<thief_num; j++){
        	thieves.insert(stoi(nums[4+j]));
        }
        MiddleEast.addUndirectedEdge(stoi(nums[0])-1,stoi(nums[1])-1,stoi(nums[2]), thieves);
    }
    infile.close();

    //open output file
    ofstream myfile;
    myfile.open (argv[2]);

    MiddleEast.shortestPath(0, 0);
    if(MiddleEast.min_distance != INF){
    	for(int i=0; i<MiddleEast.min_path.size(); i++) {
    		myfile << MiddleEast.min_path[i] + 1 << " ";
    	}
    }else{
    	myfile << -1;
    }

    myfile.close();
	return 0;
}