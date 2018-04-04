#include<iostream>
#include<vector>
#include<fstream>
#include <string>
#include "Knapsackdata1.h"
#include <math.h>
#include<time.h>

using namespace std;


//
int main()
{
	
	//*****************Begin Main function*******************************//
	Initialize * init;
	init=new Initialize("TestData(0-1Knapsack).txt");// Read the data from file and split the data into vector // we read the file here which contains profit and weight values
	init->TotalWeightCapacity=13743;// Assign the total weight capacity// it is our weight limit
	init->populationsize=100;//Population Size is 100 and each chromosomes has binary value which is total items that represents 0-1
	cout<<"0/1 KnapSack Problem using GA"<<endl;
	cout<<"Reading Data Completed."<<endl;
	Chromostruct param;
	init->GenerateIndividuals(*init,param);// Generate Initial Chromosomes
	init->Initialpopulationfitness(*init,param);//
	int iteration=0;
	cout<<"Please see the output file at the base directory after iteration"<<endl<<endl;


	//******************UMDA knapsack iteration begins*******************************//
	ofstream myfile("Output.txt");// store the output results
	while(iteration<100)
	{
	init->TruncateSelection(*init,param,0.5);// TruncateSelection executes selection procedure 
	init->CreateProbablityModel(*init,param);//Probablity model is created for Knapsack data
	init->CheckFitness(*init,param);// computes the fitness keep increased profit eliminate over weight
	init->SaveResults(*init,param,iteration,myfile);// Stores the results and get the final solution;
	iteration++;
	}
	myfile.close();// close the open file stream
	
	cin>>iteration;

	return 0;
}
