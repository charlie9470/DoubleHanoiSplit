#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<utility>

using namespace std;

int main(){
    string fileName;
    cin >> fileName;

    std::ifstream file(fileName);
    std::ofstream output_file("DD/DD_" + fileName);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    // String to hold each line
    std::string line;
    vector<pair<string,int> > DD;

    // Read file line by line
    int n;
    while (std::getline(file, line)) {
        string state;
        int dist;

        // Find the positions of '<' and '>'
        std::size_t startPos = line.find('<');
        std::size_t endPos = line.find('>');

        // Check if both characters are found
        if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
            // Extract the state part
            state = line.substr(startPos + 1, endPos - startPos - 1);

            // Find the position of "Dist:"
            std::size_t distPos = line.find("Dist:");

            // Check if "Dist:" is found
            if (distPos != std::string::npos) {
                // Extract and convert the dist part to integer
                std::string distStr = line.substr(distPos + 5);
                dist = std::stoi(distStr);

                // Display the extracted information
                std::cout << "State: " << state << ", Dist: " << dist << std::endl;
            } else {
                std::cerr << "Dist: not found in line: " << line << std::endl;
            }
        }
        else {
            std::cerr << "State not properly wrapped in line: " << line << std::endl;
        }

        n = state.size()-2;
        char prev = ':';
        int count = 0;
        for(auto i:state){
            if(count>2) break;
            if(i == '<' || i == '>' || i == '|') continue;
            if(i<prev) count++;
            prev = i;
        }
        if(count == 2) DD.push_back(pair<string,int>(state,dist));
    }

    output_file << "3n-3(" << 3*n-3 << "): " << endl;

    for(auto i:DD){
        if(i.second == 3*n-3){
            output_file << i.first << endl;
        }
    }

    output_file << endl << "3n-4(" << 3*n-4 << "): " << endl;

    for(auto i:DD){
        if(i.second == 3*n-4){
            output_file << i.first << endl;
        }
    }

    output_file << endl << "Others: (if any)" << endl;
    for(auto i:DD){
        if(i.second != 3*n-4 && i.second != 3*n-3){
            output_file << i.first << endl;
        }
    }

    // Close the file
    file.close();
    output_file.close();

    return 0;
}
