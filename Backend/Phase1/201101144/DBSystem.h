/*      Jayesh Lahori   & Karan Dhamele    */  
#include<cstdio>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<iomanip>

using namespace std;

/* General Declarations */

#define INF             1000000007
#define LL              long long int
#define SI(n)           scanf("%lld",&n)
#define SC(c)           scanf("%c",&c)
#define FOR(x,a,b)      for(LL x=a;x<b;x++)
#define REP(i,n)        for(LL i=0;i<n;i++)
#define MP              make_pair
#define PB              push_back
#define F               first
#define S               second
#define TR(container,it) for(typeof(container.begin()) it = container.begin();it != container.end(); it++)


/* Container's */

#define VI              vector<LL>
#define PLL             pair<LL,LL>  /* A Single Pair  */
#define VP              vector<PLL> /* Vector of Pairs */
#define VS              vector<string>
#define VVI             vector<VI>

typedef struct page
{
	LL cumulative;
	LL index;
	LL start;
	LL end;
	LL occupied;
	VI bytes;
	LL overflow;
}page;

string PAGESIZE,NUM_PAGES,PATH_FOR_DATA;
vector<string> table_names;
map<string, vector<page> > virtual_map;
LL cumulative_sum=0;

vector<string> memory;
vector<LL> LRU;
map<LL,pair<string,LL> > miss_map; 

LL LRU_ct=0;

string raw_input(istream& stream)
{
	string res;
	getline(stream,res);
	return res;
}
vector<string> split(string x, string d)
{
	vector<string> res;
	int prev = 0, found = x.find(d); // string find returns int
	while(found!=std::string::npos) // special cnstnt returned when not found
	{
		res.push_back(x.substr(prev,found-prev)); // substr : give start    point and length to include
		prev = found+1;
		found = x.find(d, found+1); // find from index >= found+1
	}           
	res.push_back(x.substr(prev,x.size()-prev));
	return res;
}
LL stoi(string s)
{
	return atoi(s.c_str());
}
void func(string filename)
{
	ifstream file(filename.c_str());
	LL ct=0,flg=0;
	while(file.good())
	{
		string temp=raw_input(file);
		VS v;
		if(flg==1)
		{
			table_names.PB(temp);
			flg=0;
			continue;
		}
		if(ct==0)
		{
			v=split(temp," ");
			PAGESIZE=v[1];
		}
		else if(ct==1)
		{
			v=split(temp," ");
			NUM_PAGES=v[1];
		}
		else if(ct==2)
		{
			v=split(temp," ");
			PATH_FOR_DATA=v[1];
		}
		if(temp=="BEGIN")
		{
			flg=1;
		}
		ct++;
	}
	LRU.resize(stoi(NUM_PAGES),0);
}
void read_from_tables()
{
	LL table_size=table_names.size();
	page current_page;

	current_page.start=0;
	current_page.end=-1;
	current_page.occupied=0;
	current_page.cumulative=0;

	REP(i,table_size)
	{
		// Reading from table file starts;
		string PATH=PATH_FOR_DATA;
		PATH+=table_names[i];
		PATH+=".csv";

		//cout << "~ "  << PATH << endl;

		ifstream file(PATH.c_str());
		LL record_id=0;
		LL record_size;
		LL last_element;
		cumulative_sum=0;
		while(file.good())
		{
			string temp=raw_input(file);
			if(temp.size()==0)
				continue;
			//cout << temp << endl;
			
			record_size=temp.size();
			record_size++;
			cumulative_sum+=record_size;
			
			if(stoi(PAGESIZE)-current_page.occupied>=record_size)
			{
				current_page.occupied+=record_size;
				current_page.end=record_id;
				current_page.bytes.PB(record_size);
				///flag=0
			}
			else if(stoi(PAGESIZE)-current_page.occupied==record_size-1)
			{
				current_page.occupied+=record_size-1;
				current_page.overflow=1;
				current_page.end=record_id;
				current_page.bytes.PB(record_size-1);
				last_element=current_page.end;
				current_page.index=-1;
				current_page.cumulative=cumulative_sum-1;
				virtual_map[table_names[i]].PB(current_page);
				
				current_page.start=record_id+1;
				current_page.end=record_id+1;
				current_page.occupied=1;
				current_page.bytes.clear();
				current_page.bytes.PB(1);
				current_page.overflow=0;
			
			}
			else
			{
				last_element=current_page.end;
				current_page.index=-1;
				current_page.cumulative=cumulative_sum-record_size;
				virtual_map[table_names[i]].PB(current_page);

				current_page.start=record_id;
				current_page.end=record_id;
				current_page.occupied=record_size;
				current_page.bytes.clear();
				current_page.bytes.PB(record_size);
			}
			record_id++;
		}
		if(last_element!=record_id-1)
		{
			current_page.index=-1;
			current_page.cumulative=cumulative_sum;
			virtual_map[table_names[i]].PB(current_page);
		}
		file.close();
		// cout << "~~ " << record_id << endl;

		/*cout << table_names[i] << endl;
		REP(j,(virtual_map[table_names[i]]).size())
		{
			cout << "Index: " <<  virtual_map[table_names[i]][j].index << endl;
			cout << "Start: " <<  virtual_map[table_names[i]][j].start << endl;
			cout << "End: " << virtual_map[table_names[i]][j].end << endl;
			cout << "Occupied: " <<  virtual_map[table_names[i]][j].occupied << endl;
			cout << "Cumulative: " <<  virtual_map[table_names[i]][j].cumulative << endl;
			cout << "Bytes: " << endl;
			REP(k,virtual_map[table_names[i]][j].bytes.size())
				cout << virtual_map[table_names[i]][j].bytes[k] << " ";
			cout << endl;
		}*/
	}
}
string search(string tableName, int recordId)
{
	string answer="";
	bool write_flag=false;
	if(recordId==-1)
	{
		write_flag=true;
	}
	else
	{
		/* Remove Before Submit */
		recordId--;
	}

	LL l=virtual_map[tableName].size();
	LL new_index,cur_start,cur_end;
	LL is_in_mem;

	if(write_flag!=true)
	{
		REP(i,l)
		{
			if(recordId>=virtual_map[tableName][i].start && recordId<=virtual_map[tableName][i].end)
			{
				new_index=i;
				is_in_mem=virtual_map[tableName][i].index;
				cur_start=virtual_map[tableName][i].start;
				cur_end=virtual_map[tableName][i].end;
				break;
			}
		}
	}
	else
	{
		new_index=l-1;
		is_in_mem=virtual_map[tableName][new_index].index;
		cur_start=virtual_map[tableName][new_index].start;
		cur_end=virtual_map[tableName][new_index].end;
	}
	if(is_in_mem==-1)
	{
		if(write_flag!=true)
			cout << "MISS ";
		//cout << "MISS came for " << recordId << endl;
		string to_append="";
		string PATH=PATH_FOR_DATA;
		PATH+=tableName;
		PATH+=".csv";

		fstream file(PATH.c_str());
		LL page_offset;
		if(new_index>0)
			page_offset=((virtual_map[tableName])[new_index-1]).cumulative;
		else
			page_offset=0;


		LL lines_to_read=cur_end-cur_start+1;
		LL overflow_line_no=0;
		bool overflow_flg=false;
		if(new_index > 0 && (virtual_map[tableName])[new_index-1].overflow==1 &&  (virtual_map[tableName])[new_index].overflow==0)
		{
			lines_to_read++;
			overflow_line_no++;
		}
		else if(new_index > 0 && (virtual_map[tableName])[new_index-1].overflow==0  && (virtual_map[tableName])[new_index].overflow==1 )
		{
			overflow_flg=true;
		}
		else if(new_index > 0 && (virtual_map[tableName])[new_index-1].overflow==1  && (virtual_map[tableName])[new_index].overflow==1 )
		{
			lines_to_read++;
			overflow_line_no++;
			overflow_flg=true;
		}

		//cout << "Oddset " << page_offset << " " << lines_to_read << endl;
		//cout << overflow_line_no << endl;

		file.seekp(page_offset);
		
		REP(i,lines_to_read)
		{
			string res=raw_input(file);
			//cout << "Read From File " << res << endl;
			if(write_flag!=true && cur_start+i==recordId+overflow_line_no)
			{
				//cout << res << endl; 
				answer+=res;
				answer+="\n";
			}
			to_append+=res;	
			if(!(overflow_flg==true && i==lines_to_read-1))
				to_append+="\n";
		}
		//cout << "Appending\n" << to_append;
		//cout <<"~";
		file.close();

		LL l=memory.size();
		if(l<stoi(NUM_PAGES))
		{
			if(!write_flag)
				cout << l << endl;
			//cout << "Case: 1\n";
			// insert this page at index l in memory
			memory.PB(to_append); // push the contesnt after reading;
			//cout << "MEM: " << memory[l] << endl;

			// update virtual_map[tableName][new_index].index=l
			virtual_map[tableName][new_index].index=l;

			// miss_map  l=>pair<tableName,new_index>
			miss_map[l]=MP(tableName,new_index);

			// Update LRU
			LRU[l]=LRU_ct;
			LRU_ct++;
		}
		else
		{
			//cout << "Case: 2\n";
			LL MAX=INF,MAX_INDEX=0;
			REP(i,stoi(NUM_PAGES))
			{
				//cout  << LRU[i] << " ";
				if(LRU[i]<MAX)
				{
					MAX=LRU[i];
					MAX_INDEX=i;
				}
			}
			//cout << endl;
			if(!write_flag)
				cout << MAX_INDEX << endl;
			pair<string,LL> temp;
			temp=miss_map[MAX_INDEX];

			//cout << " Associated Table: " << temp.F << " index: " << temp.S << endl;

			// temp.F ke virthttps://www.facebook.com/ual_map ke temp.S index pe tha, to update to -1
			virtual_map[temp.F][temp.S].index=-1;

			// Replace this new page to MAX_INDEX
			memory[MAX_INDEX]=to_append; // read contents

			//cout << "MEM: " << memory[MAX_INDEX] << endl;

			//cout << "Mem Replaced " << memory[MAX_INDEX] << endl;

			// Update LRU to 1
			LRU[MAX_INDEX]=LRU_ct;
			LRU_ct++;

			// miss_map MAX_INDEX=>pair<tableName,new_index>
			miss_map[MAX_INDEX]=MP(tableName,new_index);

			// update contents in memory
			virtual_map[tableName][new_index].index=MAX_INDEX;
		}
	}
	else
	{
		cout << "HIT" << endl;

		//cout << " ! "<< memory[is_in_mem] << " !\n";
		
		LL offset_index=recordId-cur_start;
		LL offset_bytes=0;
		if(memory[is_in_mem][0]=='\n')
			offset_index++;

		LRU[is_in_mem]=LRU_ct;
		LRU_ct++;

		REP(i,offset_index) // Compute local offset
			offset_bytes+=((virtual_map[tableName])[new_index]).bytes[i];

		LL bytes_to_read=((virtual_map[tableName])[new_index]).bytes[offset_index];
		
		//cout << "off_index = " << offset_index << " " << " off_bytes " << offset_bytes << " bytes to read " << bytes_to_read << endl;

		LL i=offset_bytes;
		while(1)
		{
			if(i>=offset_bytes+bytes_to_read)
				break;
			//cout << memory[is_in_mem][i];
			answer+=memory[is_in_mem][i];
			i++;
		}
		if((virtual_map[tableName])[new_index].end==recordId && (virtual_map[tableName])[new_index].overflow==1)
		{
			//cout << endl;
			answer+="\n";
		}
		// seek offset_bytes in memory[is_in_mem]
		// memory[is_in_mem]
	}
	return answer;
}

void write(string tableName, string record)
{
	LL l=virtual_map[tableName].size();
	string to_append="";
	string PATH=PATH_FOR_DATA;
	PATH+=tableName;
	PATH+=".csv";
	fstream file(PATH.c_str());
	LL page_offset=virtual_map[tableName][l-1].cumulative;
	file.seekp(page_offset);
	file << record << endl;
	file.close();


	LL flag=0;
	LL l1=record.size();
	if(stoi(PAGESIZE)- virtual_map[tableName][l-1].occupied>=l1+1)
	{
		// insert in this page
		virtual_map[tableName][l-1].occupied+=l1+1;
		virtual_map[tableName][l-1].end++;
		virtual_map[tableName][l-1].bytes.PB(l1+1);
		virtual_map[tableName][l-1].cumulative+=l1+1;
		flag=1;
	}
	else if(stoi(PAGESIZE)-virtual_map[tableName][l-1].occupied==l1)
	{
		virtual_map[tableName][l-1].occupied+=l1;
		virtual_map[tableName][l-1].end++;
		virtual_map[tableName][l-1].bytes.PB(l1);
		virtual_map[tableName][l-1].cumulative+=l1;
		virtual_map[tableName][l-1].overflow=1;
		flag=2;
		// create new page

		page current_page;
		current_page.start=virtual_map[tableName][l-1].end+1;
		current_page.end=virtual_map[tableName][l-1].end+1;
		current_page.occupied=1;
		current_page.bytes.clear();
		current_page.bytes.PB(1);
		current_page.overflow=0;
		current_page.index=-1;

		virtual_map[tableName].PB(current_page);
	}
	else
	{
		page current_page;
		current_page.start=virtual_map[tableName][l-1].end+1;
		current_page.end=virtual_map[tableName][l-1].end+1;
		current_page.occupied=l1+1;
		current_page.bytes.clear();
		current_page.bytes.PB(l1+1);
		current_page.overflow=0;
		current_page.index=-1;
		
		virtual_map[tableName].PB(current_page);
		flag=3;
	}
	l=virtual_map[tableName].size();
	if(flag==1)
	{
		if(virtual_map[tableName][l-1].index==-1)
		{
			// bring this page in memeory
			search(tableName,-1);
		}
		else
		{
			// update this page in memory
			LL is_in_mem=virtual_map[tableName][l-1].index;
			memory[is_in_mem]+=record;
			memory[is_in_mem]+="\n";

			LRU[is_in_mem]=LRU_ct;
			LRU_ct++;
		}
	}
	else if(flag==2)
	{
		if(virtual_map[tableName][l-2].index==-1)
		{
			// bring this page in memeory
			search(tableName,-1);
		}
		else
		{	
			LL is_in_mem=virtual_map[tableName][l-2].index;
			memory[is_in_mem]+=record;

			LRU[is_in_mem]=LRU_ct;
			LRU_ct++;

			// update this page in memory
		}
	}
	else
	{
		// insert this is memory
		search(tableName,-1);
	}
}
class DBSystem {
	public:
		void readConfig(string configFilePath)
		{
			func(configFilePath);	
		}

		void populateDBInfo()
		{
			read_from_tables();
		}

		string getRecord(string tableName, int recordId)
		{
			string res=search(tableName,recordId+1);
			LL l=res.size();
			return res.substr(0,l-1);
		}

		void insertRecord(string tableName, string record)
		{
			write(tableName,record);
			return;
		}
};
/*int main()
{
	string config="./config.txt";
	func(config);
	read_from_tables();
	REP(i,19)
	{
		LL x;
		cin  >> x;
		if(x!=-1)
			cout <<  search("countries",x+1);
		else
			write("countries","record");
	}
}*/
