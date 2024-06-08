#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
void swap(string& target,int i,int j){
	char tmp = target[i];
	target[i] = target[j];
	target[j] = tmp;
	return;
}
void Permute(ofstream& outputFile, string& target,int index){
	int n = target.length();
	if(index==n){
		outputFile << "<|" << target << "|>" << endl;
	}
	for(int i = index;i<n;i++){
			swap(target,index,i);
			Permute(outputFile, target, index+1);
			swap(target,index,i);
	}
};
int main(){
    ofstream outputFile;
    outputFile.open("test.in");	
	string permute = "1234567";
	int index = 0;
	outputFile << "7\nm\n5040\n";
	Permute(outputFile, permute,index);
	return 0;
}
