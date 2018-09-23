#include <bits/stdc++.h>

using namespace std;
vector<string> data;

string addressFile, cacheType, numEntries;	


void display(int totalmiss,int compulsorymiss, vector<string>hm)
{
	ofstream output;
	addressFile= addressFile.substr(0,addressFile.size()-4);
	string temp = "ES16BTECH11009_"+cacheType+"_" + addressFile + "_" + numEntries + ".out";
	output.open(temp.c_str());
	output<<"TOTAL_ACCESSES = " <<data.size()	 << endl;
	output<<"TOTAL_MISSES = "<<totalmiss <<endl;
	output<<"COMPULSORY_MISSES = "<< compulsorymiss <<endl;
	output<<"CAPACITY_MISSES = "<< totalmiss - compulsorymiss << endl;
	for(int i= 0; i< hm.size(); i++)
	{
		output<< hm[i] << endl;
	} 
	output.close();
}

void lru( int cacheSize)
{
	int compulsorymiss =0,totalmiss =0;
	set<string> compm;
	vector<string> hm;
	list<string> cache; 
	list<string> :: iterator it;
	for(int i =0; i< data.size(); i++ )
	{
	   it =  find(cache.begin(),cache.end(),data[i]);
	   if(it != cache.end())
	   {
		 hm.push_back("HIT");
		 cache.erase(it);
		 cache.push_back(data[i]);
	   }
	   else
	   {
		   totalmiss++;
		   if(compm.find(data[i]) == compm.end())
		   {
		   	compm.insert(data[i]);
			compulsorymiss++;
		   }
		   hm.push_back("MISS");
		   if(cache.size() < cacheSize)
				 cache.push_back(data[i]);
		   else
		   { 	
			   cache.pop_front();
			   cache.push_back(data[i]);
			   
		   }
	   }
	}
	display(totalmiss,compulsorymiss,hm);
}

void fifo(int cacheSize)
{
	int compulsorymiss =0,totalmiss =0;
	set<string> compm;
	vector<string> hm;
	list<string>cache;
	list<string> :: iterator it;
	for(int i =0; i< data.size(); i++ )
	{	
	   it =  find(cache.begin(),cache.end(),data[i]);
	   if(it != cache.end())
	   {
		 hm.push_back("HIT");
	   }
	   else
	   {
		   totalmiss++;
		   if(compm.find(data[i]) == compm.end())
		   {
		   	compm.insert(data[i]);
			compulsorymiss++;
		   }
		   hm.push_back("MISS");
	       if(cache.size() < cacheSize)
		   cache.push_back(data[i]);
		   else
		   { 	
			   cache.pop_front();
			   cache.push_back(data[i]);
		   }
	   }
	}
	display(totalmiss,compulsorymiss,hm);
	
}

void optimal(int cacheSize)
{
	int compulsorymiss =0,totalmiss =0;
	set<string> compm;
	vector<string> hm;
	vector<string> cache;
	vector<int>	distance;
	vector<string> :: iterator it;
	for(int i =0; i< data.size(); i++)
	{	
		it =  find(cache.begin(),cache.end(),data[i]);
		if(it != cache.end())
	   {
		 hm.push_back("HIT");
	   }
	   else
	   {
		   totalmiss++;
		   if(compm.find(data[i]) == compm.end())
		   {
		   	compm.insert(data[i]);
			compulsorymiss++;
		   }
		    hm.push_back("MISS");
			if(cache.size() < cacheSize)
			{
				cache.push_back(data[i]);
				distance.push_back(0);
			}
			else
			{
				for( int l = 0; l < cache.size(); l++)
				{	

					distance[l] = find(data.begin() + i,data.end(),cache[l]) - data.begin();
				}	
			 	cache[max_element(distance.begin(),distance.end()) - distance.begin()] = data[i];
			}   
	   }
	}
	display(totalmiss,compulsorymiss,hm); 
}

int main(int argc, char const *argv[])
{
	string  tempWord ;
	char tempChar;
	int check =0;
	cacheType = argv[1];
	numEntries  = argv[3];
	addressFile  = argv[2];
	ifstream reader;
	reader.open(argv[2]);
	int i =0;
	if(reader.is_open() == 0)
	{	
		cout << "Error in opening the file.\n";
		return 1;
	}
	while(!reader.eof())
	{
		
		reader.get(tempChar);
		if(tempChar ==' '||tempChar == '\n' ||tempChar == '\b'||tempChar == '\t'||tempChar == '\v')
		{
			if(check == 0)
			{
				check = 1;
				data.push_back(tempWord);
				tempWord = "";
			}
			continue;
		}
		tempWord.push_back(tempChar);
		check = 0;
	}
	if(cacheType == "LRU")
		lru(atoi(argv[3]));
	if(cacheType == "FIFO")
		fifo(atoi(argv[3]));
	if(cacheType == "OPTIMAL")
		optimal(atoi(argv[3]));
	reader.close();
	return 0;
}