#pragma once
#ifndef KNAPSACKDATA1_H
#define KNAPSACKDATA1_H
#include<string>
#include<time.h>
#include<algorithm>
using namespace std;
 typedef struct 
 {
	 //******************Structure Variables*******************************//
	vector<vector<bool>>Population;
	vector<vector<double>>FitnessValues;
	vector<vector<bool>>ProbModelPopulation;
	 vector<vector<bool>>Newpopulation;
	vector<int>FinalSolution;

}Chromostruct;

 class Initialize
{
	public:	
		//******************Variables*******************************//

		Initialize(string fname);// constuctor read the file 
		~Initialize();//Destrctor
		vector<int>item;// holds the item number
		vector<int>weight;// holds the item weight
		vector<int>profit;// holds the item profit
	   int TotalWeightCapacity;// totoalweightcapacity
	   int populationsize;// population size
	//******************Definations*******************************//
	vector<double>FitnessFunction(vector<int>Weight,vector<int>Profit,vector<bool>type);	//compute the fitness 
	void GenerateIndividuals(Initialize & data, Chromostruct & val);// generate the chromosomes
	void Initialpopulationfitness(Initialize & data, Chromostruct & val);//  initial population fitness
	void TruncateSelection(Initialize & data, Chromostruct & val,double tau);// truncate selection 
	void CreateProbablityModel(Initialize & data, Chromostruct & val);
	void CheckFitness(Initialize & data, Chromostruct & val);
	void SaveResults(Initialize & data, Chromostruct & val,int iter, ofstream & myfile);
};
void Initialize::SaveResults(Initialize & data, Chromostruct & val,int iter, ofstream & myfile)
{
	 int sum=0;
	 if (myfile.is_open())// open the text file and save the data
	 {	double tmp;
		tmp=0;
		int indx;
		for(int w=0;w<val.FinalSolution.size();w++)
		{
			cout<<"Total Fitness:    "<<val.FitnessValues[val.FinalSolution[w]][0]<<"    Weight Limit:    "<<val.FitnessValues[val.FinalSolution[w]][1]<<endl;
			sum=sum+val.FitnessValues[val.FinalSolution[w]][0];
			if(val.FitnessValues[val.FinalSolution[w]][0]>tmp)
			{
				tmp=val.FitnessValues[val.FinalSolution[w]][0];
				indx=w;
			}
		}

		if (val.FinalSolution.size()>1)
		{
			myfile<<iter<<" "<<val.FitnessValues[val.FinalSolution[indx]][0]<<" "<<val.FitnessValues[val.FinalSolution[indx]][1]<<" "<<sum/val.FinalSolution.size()<<"\n";
			cout<<iter<<"  Max Fitness:"<<val.FitnessValues[val.FinalSolution[indx]][0]<<endl;
		}
		val.FinalSolution.clear();
	}
}

void  Initialize::CheckFitness(Initialize & data, Chromostruct & val)
{
		int cnt=0;
		vector<vector<double>>OLDFitnessValues=	val.FitnessValues;
		vector<vector<bool>>OLDPopulation=val.Population;
		val.FitnessValues.clear();
		for(int i=0;i<val.Newpopulation.size();i++)
		{
			val.FitnessValues.push_back(FitnessFunction(data.weight,data.profit,val.Newpopulation[i]));	// compute the new population fitness	
		}
	
		for(int i=0;i<val.FitnessValues.size();i++)
		{
			if((int)val.FitnessValues[i][1]<=data.TotalWeightCapacity)// check weight capacity of the population
			{
				if(val.FitnessValues[i][0]>=OLDFitnessValues[i][0])
				{
					if((int)val.FitnessValues[i][1]>data.TotalWeightCapacity)
						continue;					
							
					val.Population[i]=val.Newpopulation[i];		// if fitness is greater than old one then add up to next generation
							val.FinalSolution.push_back(i);
				}
		}
			else if((int)val.FitnessValues[i][1]<=data.TotalWeightCapacity)
			{
			val.FitnessValues[i]=OLDFitnessValues[i];
				val.Population[i]=OLDPopulation[i];			
			}else if((int)val.FitnessValues[i][1]>data.TotalWeightCapacity)
			{
				val.FitnessValues[i][0]=0;//In addittion if Chromosomes exceeds weight limit capacity
			}
		}
}
void Initialize::CreateProbablityModel(Initialize & data, Chromostruct & val)
{
	//******************Compute probability*******************************//
		// create the probablity vector
	vector<double>probabilityvector;
	for(int i=0;i<data.item.size();i++)
	{
	
		int sum=0;
			for(int j=0;j<val.ProbModelPopulation.size();j++)
			sum=sum+val.ProbModelPopulation[j][i];// sumup the occurance 
			probabilityvector.push_back(double(sum)/double(val.ProbModelPopulation.size()));// probablity vector
	}
	val.Newpopulation.clear();
	// sampling the probablity vector
	//******************Sampling probability*******************************//
	for(int j=0;j<data.populationsize;j++)
	{
			vector<bool>uniformed;
				for(int i=0;i<probabilityvector.size();i++)
				{
					double x= (((double) rand() / (RAND_MAX)));
					if(probabilityvector[i]>x)
						uniformed.push_back(1);
					else
						uniformed.push_back(0);
				}
				val.Newpopulation.push_back(uniformed);// generate the new population
				uniformed.clear();
	}

}
void Initialize::TruncateSelection(Initialize & data, Chromostruct & val,double tau)
{
	//******************Population sorting*******************************//
	val.ProbModelPopulation.clear();
	 vector<int> map(val.FitnessValues.size());	 
	 for(int i=0;i<val.FitnessValues.size();i++)
		  map[i]=i;
	sort( map.begin(),map.end(), [&](int x,int y){return val.FitnessValues[x][0]>val.FitnessValues[y][0];}); // we get the index of population
	vector<vector<double>>sortedftiness;
	vector<vector<bool>>sortedpopulation;//
		 for(int i=0;i<data.populationsize;i++)
	 {
		 sortedftiness.push_back(val.FitnessValues[map[i]]);
		 sortedpopulation.push_back(val.Population[map[i]]);// we map the index of population to get the real one
	 }
	 val.Population=sortedpopulation;
	 val.FitnessValues=sortedftiness;
	 	//******************Truncate selection*******************************//
	  double portion=(1-tau)*data.populationsize;
	 	for(int N=0;N<portion;N++)
		val.ProbModelPopulation.push_back(val.Population[N]);// get the best half portion of the population as tau=0.5
		
}
void Initialize::Initialpopulationfitness(Initialize & data,Chromostruct & val)// Population fiteness computation
{
	val.FitnessValues.clear();
		 	//******************Fitness Computation*******************************//
	for(int i=0;i<data.populationsize;i++)
	{
		val.FitnessValues.push_back(FitnessFunction(data.weight,data.profit,val.Population[i]));// we compute the fitness value of each population
	}
}

void Initialize::GenerateIndividuals(Initialize & data, Chromostruct & val)// generate the chromosomes 
{
	val.Population.clear();
	val.Population.reserve(data.populationsize);
	 srand ( time(NULL) );

	for(int i=0;i<data.populationsize;i++)
	{
		vector<bool>rnd;
		for (int j=0;j<(data.item.size());j++)
			rnd.push_back(rand()%2);// Generate random bianary values 0 or 1 for total number item size			
		val.Population.push_back(rnd);// stores the chromosomes 
		
	}

}

vector<double> Initialize::FitnessFunction(vector<int>Weight,vector<int>Profit,vector<bool>type)// Fitness calculations
{
//******************Compute fitness*******************************//
vector<double>values(2);
	for(int i=0;i<Profit.size();i++)
	{
		values[0]=values[0]+Profit[i]*type[i];   
		values[1]=values[1]+Weight[i]*type[i];//fitness function computes the total profit and weight at postion 0
	}
	return values;
}


Initialize::Initialize(string fname)// read file data ans stores into vector. Data contains profit and weight
{
//******************Read Data*******************************//
	string buf;//
	ifstream fp( fname,std::ios_base::in );// read the data from txt file
	 string val; 
	 int cnt=0;
		  while(!fp.eof())	
	  {
		       getline(fp,val);// read each string in txt file checking CR+LF
			 // cout<<val<<endl;
			   cnt++;
			    if (cnt<6)// Ignore some beginning text from file 
			  continue;
			  std::string delimiter = "	";
			size_t pos =0;
			double token;
			vector<double>element;		
			while ((pos = val.find(delimiter)) != std::string::npos) // split the string values into 3 vector item/profit/weight
			{				
				element.push_back(atof( val.substr(0, pos).c_str()));			
				val.erase(0, pos + delimiter.length());
			}	
				element.push_back(atof( val.c_str()));
				item.push_back(element[0]);
				weight.push_back(element[1]);
				profit.push_back(element[2]);		
				element.clear();
		 }
		
}
#endif KNAPSACKDATA1_H





