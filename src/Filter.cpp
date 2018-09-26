/*
 * 	PH filter functions for various data types				Nick Carrara
 */
#include "Filter.h"
using namespace std;

//	Filter 2D
Filter2D::Filter2D(){}
Filter2D::~Filter2D(){}

void Filter2D::loadBinaryFromFile(const char* input_file){
		std::ifstream inputFile(input_file);
		int l = 0;
		 
		while (inputFile) {
			l++;
			std::string s;
			if (!std::getline(inputFile, s)) break;
		        if (s[0] != '#') {
		            std::istringstream ss(s);
		            std::vector<int> record;
		 
		            while (ss) {
		                std::string line;
		                if (!std::getline(ss, line, ','))
		                    break;
		                try {
		                    record.push_back(stoi(line));
		                }
		                catch (const std::invalid_argument e) {
		                    std::cout << "NaN found in file " << input_file << " line " << l
		                         << std::endl;
		                    e.what();
		                }
		            }
		 
		            m_Binary.push_back(record);
		       }
		   }
		 
		   if (!inputFile.eof()) {
		       std::cerr << "Could not read file " << input_file << "\n";
		       std::__throw_invalid_argument("File not found.");
		   }
		
}
void Filter2D::loadContinuousFromFile(const char* input_file){

}

void Filter2D::countDeadCells(){
	int deadCells;
	for (int i = 0; i < m_Binary.size(); i++){
		for (int j = 0; j < m_Binary[i].size(); j++){
			if (m_Binary[i][j] == 0) deadCells++;
		}
	}
	m_DeadCells = deadCells;
}
		
//	Various filterings
//	Binary filterings
void Filter2D::filterBinaryVonNeumann(int threshold){	//	only hard boundary right now
	//	count the number of dead cells
	countDeadCells();
	int deadCells = m_DeadCells;
	bool thres = true;
	int currentState = 1;
	//	loop
	vector<vector<int> > binaryCopy = m_Binary;
	while(deadCells > 0 || thres == false){
		for (int i = 0; i < binaryCopy.size(); i++){
			for (int j = 0; j < binaryCopy[i].size(); j++){
				//	Check state
				if (binaryCopy[i][j] == currentState){
					//	Look at all neighbors
					if (i == 0){
						if (j == 0){
							if (binaryCopy[0][1] == 0) binaryCopy[0][1] = currentState + 1; deadCells--;
							if (binaryCopy[1][0] == 0) binaryCopy[1][0] = currentState + 1; deadCells--;
						}
						else if (j == binaryCopy[i].size()-1){
							if (binaryCopy[0][j-2] == 0) binaryCopy[0][j-2] = currentState + 1;deadCells--;
							if (binaryCopy[1][j-1] == 0) binaryCopy[1][j-1] = currentState + 1;deadCells--;
						}
						else{
							if (binaryCopy[0][j-1] == 0) binaryCopy[0][j-1] = currentState + 1;deadCells--;
							if (binaryCopy[0][j+1] == 0) binaryCopy[1][j+1] = currentState + 1;	deadCells--;
							if (binaryCopy[1][j] == 0) binaryCopy[1][j] = currentState + 1;deadCells--;
						}
					}
					else if (i == binaryCopy[i].size() - 1){
						if (j == 0){
							if (binaryCopy[i][1] == 0) binaryCopy[i][1] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][0] == 0) binaryCopy[i-1][0] = currentState + 1;deadCells--;
						}
						else if (j == binaryCopy[i].size()-1){
							if (binaryCopy[i][j-2] == 0) binaryCopy[i][j-2] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][j-1] == 0) binaryCopy[i-1][j-1] = currentState + 1;deadCells--;
						}
						else{
							if (binaryCopy[i][j-1] == 0) binaryCopy[i][j-1] = currentState + 1;deadCells--;
							if (binaryCopy[i][j+1] == 0) binaryCopy[i][j+1] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][j] == 0) binaryCopy[i-1][j] = currentState + 1;deadCells--;
						}	
					}
					else{
						if (j == 0){
							if (binaryCopy[i][1] == 0) binaryCopy[i][1] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][0] == 0) binaryCopy[i-1][0] = currentState + 1;deadCells--;
							if (binaryCopy[i+1][0] == 0) binaryCopy[i+1][0] = currentState + 1;deadCells--;
						}
						else if (j == binaryCopy[i].size()-1){
							if (binaryCopy[i][j-2] == 0) binaryCopy[i][j-2] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][j-1] == 0) binaryCopy[i-1][j-1] = currentState + 1;deadCells--;
							if (binaryCopy[i+1][j-1] == 0) binaryCopy[i+1][j-1] = currentState + 1;deadCells--;
						}
						else{
							if (binaryCopy[i][j-1] == 0) binaryCopy[i][j-1] = currentState + 1;deadCells--;
							if (binaryCopy[i][j+1] == 0) binaryCopy[i][j+1] = currentState + 1;deadCells--;
							if (binaryCopy[i-1][j] == 0) binaryCopy[i-1][j] = currentState + 1;deadCells--;
							if (binaryCopy[i+1][j] == 0) binaryCopy[i+1][j] = currentState + 1;deadCells--;
						}	
					}
				}
			}
		}
		currentState++;
		if (currentState >= threshold) thres = false;
	}
	m_Binary = binaryCopy;
}
void Filter2D::filterBinaryMoore(int threshold){
	
}

void Filter2D::saveBinaryFiltration(const char* output_file){
	std::ofstream myfile;
		myfile.open(output_file);
		for (int i = 0; i < m_Binary.size(); i++){
			for (int j = 0; j < m_Binary[i].size(); j++){
				myfile << m_Binary[i][j];
				if (j < m_Binary[i].size() - 1){
					myfile << ",";
				}
			}
			myfile << "\n";
		}
		myfile.close();
	
}

