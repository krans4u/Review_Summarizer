/* Jayesh Lahori */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

/* General Declarations */

#define INF		1000000007
#define LL		long long int
#define SI(n)		scanf("%lld",&n)
#define SC(c)		scanf("%c",&c)
#define FOR(x,a,b)	for(LL x=a;x<b;x++)
#define REP(i,n)	for(LL i=0;i<n;i++)
#define MP		make_pair
#define PB		push_back
#define F		first
#define S		second
#define TR(container,it) for(typeof(container.begin()) it = container.begin();it != container.end(); it++)


/* Container's */

#define	VI		vector<LL>
#define PLL		pair<LL,LL>  /* A Single Pair  */
#define VP		vector<PLL> /* Vector of Pairs */
#define VS		vector<string>
#define VVI		vector<VI>
#define VVS		vector<VS>

string raw_input()
{
	string res;
	getline (cin,res);
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
map<string,string> attributes;

void create(string s)
{
	LL l=s.size();
	string s1;
	char prev;
	REP(i,l)
	{
		if(i==0)
		{
			if(s[i]==' ')
			{
				prev=' ';
				continue;
			}
			else
			{
				s1+=s[i];
				prev=s[i];
				continue;
			}
		}
		else if(s[i]==' ' && prev==' ')
			continue;
		else
			s1+=s[i];
		prev=s[i];
	}
	//cout << s1 << endl;
	l=s1.size();
	string temp1,temp2,temp3,temp4,temp5,temp6;
	LL i=0;
	while(i<l)
	{
		if(s1[i]==';')
			break;
		while(i<l)
		{
			if(s1[i]==' ')
			{
				i++;
				break;
			}
			temp1+=s1[i];
			i++;
		}
		//cout << temp1 << endl;
		while(i<l)
		{
			if(s1[i]==' ')
			{
				i++;
				break;
			}
			temp2+=s1[i];
			i++;
		}
		//cout << temp2 << endl;
		while(i<l)
		{
			if(s1[i]=='(')
			{
				i++;
				break;
			}
			temp3+=s1[i];
			i++;
		}
		if(mymap.find(temp3)!=mymap.end())
		{
			cout << "Table Exists\n";
			return;
		}
		cout << "Tablename:" << temp3 << endl;
		while(i<l)
		{
			if(s1[i]==')')
			{
				attributes[temp5]=temp4;
				i++;
				break;
			}
			if(s1[i]==' ')
			{
				temp5=temp4;
				temp4.clear();
				i++;
				continue;
			}
			if(s1[i]==',')
			{
				attributes[temp5]=temp4;
				i++;
				temp4.clear();
				temp5.clear();
				continue;
			}
			temp4+=s1[i];
			i++;
		}
	}
	LL ff=0;
	cout << "Attributes:";
	TR(attributes,it)
	{
		if(ff==0)
			cout << it->F << " " << it->S;
		else
			cout << "," << it->F << " " << it->S;
		ff++;
	}
	cout << endl;
	string tablename=temp3;
	string temp=tablename+".data";

	ofstream fp;
	fp.open(temp.c_str());
	fp.close();

	temp=tablename+".csv";
	fp.open(temp.c_str());
	fp.close();

	fp.open("config.txt",fstream::app);
	fp << "BEGIN\n";
	fp << temp3 << endl;
	TR(attributes,it)
		fp << it->F << " " << it->S << endl;
	fp << "END\n";
	fp.close();
}
map<string,vector<pair<string,string> > > mymap;
map<string,vector<string> > columns;
string raw_input1(istream& stream)
{
	string res;
	getline(stream,res);
	return res;
}
void parse()
{
	string temp,temp1,temp2;
	bool flag=true;
	string table;
	ifstream file("config.txt");
	while(file.good())
	{
		if(flag)
		{
			temp=raw_input1(file);
			temp=raw_input1(file);
			temp=raw_input1(file);
			flag=false;
		}
		temp=raw_input1(file);
		bool flag1=true;
		while(file.good())
		{
			temp=raw_input1(file);
			temp1.clear();
			temp2.clear();
			if(temp=="END")
				break;
			if(flag1)
			{
				table=temp;
				flag1=false;
				continue;
			}
			LL l=temp.size(),i=0;
			while(i<l)
			{
				if(temp[i]==',' || temp[i]==' ')
					break;
				temp1+=temp[i];
				i++;
			}
			while(temp[i]==' ' || temp[i]==',')
				i++;
			while(i<l)
			{
				temp2+=temp[i];
				i++;
			}
			mymap[table].PB(MP(temp1,temp2));
		}
	}
}
VS star()
{
	VS S;
	REP(j,ftables.size())
	{
		REP(i,mymap[ftables[j]].size())
			S.PB(mymap[ftables[j]][i].F);
	}
	return S;
}
