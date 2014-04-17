/*	Jayesh Lahori	    */
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
#include<iomanip>
#include<fstream>

using namespace std;

/* General Declarations */

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

VS where_string;
string table_of_query;

//#include "create.cpp"
map<string,string> where_datatype;

bool is_a_float(string s)
{
	LL l=s.size();
	REP(i,l)
		if(s[i]=='.')
			return true;
	return false;
}
bool where_check(string s)
{
	LL l=s.size();
	string temp;
	char prev;
	REP(i,l)
	{
		if(i!=0 && prev==' ' && s[i]==' ')
			continue;
		prev=s[i];
		temp+=s[i];
	}
	//cout << temp << endl;
	l=temp.size();
	s.clear();
	for(int i=0;i<l;i++)
	{
		s+=temp[i];
	}
	string attribute1,opt,attribute2,delim;
	LL flag=0;
	for(int i=0;i<l;)
	{
		if(s[i]==';' || s[i]==' ' || s[i]=='\t' ||  s[i]=='\n')
		{
			i++;
			continue;
		}
		if(flag==0)//attribute
		{
			attribute1.clear();
			LL lf=0;
			if(s[i]=='`')
			{
				lf++;
				i++;
				while(s[i]!='`')
				{
					attribute1+=s[i];
					i++;
				}
				i++;
			}
			if(lf==0)
			{
				while(s[i]!=' ' && s[i]!='\t' && s[i]!='=' && s[i]!='!' && s[i]!='<' && s[i]!='>' && s[i]!='\n')
				{
					attribute1+=s[i];
					i++;
				}
			}
			flag++;
			where_string.PB(attribute1);
		}
		else if(flag==1)//operator
		{
			opt.clear();
			if(i+3<l && s[i]=='l' && s[i+1]=='i' && s[i+2]=='k' && s[i+3]=='e')
			{
				opt+="=";
				i+=4;
			}
			else
			{
				while(s[i]=='=' || s[i]=='!' || s[i]=='<' || s[i]=='>')
				{
					opt+=s[i];
					i++;
				}
			}
			flag++;
			where_string.PB(opt);
		}
		else if(flag==2)//value
		{
			attribute2.clear();
			if(s[i]=='\"')
			{
				attribute2+=s[i];
				i++;
				while(s[i]!='\"')
				{
					attribute2+=s[i];
					i++;
				}
				attribute2+=s[i];
				i++;
			}
			else if(s[i]=='\'')
			{
				attribute2+=s[i];
				i++;
				while(s[i]!='\'')
				{
					attribute2+=s[i];
					i++;
				}
				attribute2+=s[i];
				i++;
			}
			else
			{
				while(i<l && s[i]!=' ' && s[i]!='\t' && s[i]!='\n')
				{
					attribute2+=s[i];
					i++;
				}
			}
			flag++;
			where_string.PB(attribute2);	
		}
		else if(flag==3)//operand
		{
			delim.clear();
			while(i<l && s[i]!=' ' && s[i]!='\t' && s[i]!='\n')
			{
				delim+=s[i];
				i++;
			}
			i++;
			flag=0;
			where_string.PB(delim);
		}
	}
	if(flag!=3)
		return false;
	l=where_string.size();
	flag=0;
	attribute1.clear();
	attribute2.clear();
	string datatype;
	REP(i,l)
	{
		if(flag==0)
		{
			// check attribute 1
			attribute1=where_string[i];
			flag++;
		}
		else if(flag==1)
		{
			// check operator
			if(where_string[i]!="=" && where_string[i]!=">=" && where_string[i]!="<="
					&& where_string[i]!="!=" && where_string[i]!="<" && where_string[i]!=">")
			{
				//cout << "op1\n";
				return false;
			}
			flag++;
		}
		else if(flag==2)
		{
			// check attribute 2
			attribute2=where_string[i];
			cout << attribute2 << endl;
			if(attribute2[0]=='\"')
				datatype="string";
			else if(attribute2[0]=='\'')
			{
				datatype="string";
				attribute2[0]='\"';
				LL lll=attribute2.size();
				attribute2[lll-1]='\"';
				where_string[i]=attribute2;
			}
			else
			{
				if(is_a_float(attribute2))
					datatype="float";
				else
					datatype="integer";
			}
			flag++;
			bool local_flag=false;
			string tl1="VARCHAR(50)",tl2="varchar(50)",tl3="VARCHAR (50)",tl4="varchar (50)",tl5="Varchar(50)",tl6="Varchar (50)";
			REP(j,mymap[table_of_query].size())
			{
				if(datatype=="string")
				{
					if((mymap[table_of_query][j]==MP(attribute1,datatype)))
					{
						local_flag=true;
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl1)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl2)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl3)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl4)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl5)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
					if((mymap[table_of_query][j]==MP(attribute1,tl6)))
					{
						local_flag=true;
						datatype="string";
						break;
					}
				}
				else
				{
					if(mymap[table_of_query][j]==MP(attribute1,datatype))
					{
						local_flag=true;
						break;
					}
				}
			}
			if(!local_flag)
			{
				//cout << "op2\n";
				return false;
			}
			where_datatype[attribute1]=datatype;
			//cout << attribute1 << " = " << datatype << endl;
		}
		else if(flag==3)
		{
			// check delim
			if(where_string[i]!="and" && where_string[i]!="or")
			{
				//cout << "op3\n";
				return false;
			}
			flag=0;
		}
	}
	return true;
}
bool check_record(VS S,LL i,LL j)
{
	/*REP(ii,where_string.size())
		cout << where_string[ii] << " ";
	cout << endl;
	cout << "Called from " << i << " " << j << endl;
	*/static int l=where_string.size();
	if(i>=l)
		return true;
	if(j>=l)
	{
		if(where_string[i+1]=="=")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]==where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())==atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())==atof(where_string[i+2].c_str()))
					return true;
			}
		}
		else if(where_string[i+1]==">=")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]>=where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>=atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())>=atof(where_string[i+2].c_str()))
					return true;
			}

		}
		else if(where_string[i+1]=="<=")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]<=where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<=atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())<=atof(where_string[i+2].c_str()))
					return true;
			}

		}
		else if(where_string[i+1]=="!=")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]!=where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())!=atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())!=atof(where_string[i+2].c_str()))
					return true;
			}

		}
		else if(where_string[i+1]=="<")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]<where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())<atof(where_string[i+2].c_str()))
					return true;
			}

		}
		else if(where_string[i+1]==">")
		{
			if(where_datatype[where_string[i]]=="string")
			{
				if(S[attribute_to_id[where_string[i]]]>where_string[i+2])
					return true;
			}
			else if(where_datatype[where_string[i]]=="integer")
			{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>atoi(where_string[i+2].c_str()))
					return true;
			}
			else if(where_datatype[where_string[i]]=="float")
			{
				if(atof(S[attribute_to_id[where_string[i]]].c_str())>atof(where_string[i+2].c_str()))
					return true;
			}
		}
		return false;
	}
	else
	{
		if(where_string[j]=="and")
		{
			if(where_string[i+1]=="=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]==where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())==atoi(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())==atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}

			}
			else if(where_string[i+1]==">=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]>=where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					//cout << attribute_to_id[where_string[i]] << " " << S[attribute_to_id[where_string[i]]].c_str() << " ";
					//cout << atoi((S[attribute_to_id[where_string[i]]]).c_str()) << " " << atoi(where_string[i+2].c_str()) << endl;
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>=atoi(where_string[i+2].c_str()))
					{
						return (true && check_record(S,i+4,j+4));
					}
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())>=atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="<=")
			{
				cout << "in <=\n";
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]<=where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					//cout << attribute_to_id[where_string[i]] << " " << S[attribute_to_id[where_string[i]]].c_str() << " ";
					//cout << atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str()) << " " << atoi(where_string[i+2].c_str()) << endl;
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<=atoi(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())<=atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="!=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]!=where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())!=atoi(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())!=atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="<")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]<where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<atoi(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())<atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]==">")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]>where_string[i+2])
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>atoi(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())>atof(where_string[i+2].c_str()))
						return (true && check_record(S,i+4,j+4));
				}
			}
			return false;
		}
		else if(where_string[j]=="or")
		{
			if(where_string[i+1]=="=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]==where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())==atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())==atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]==">=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]>=where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>=atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())>=atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="<=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]<=where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<=atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())<=atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="!=")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]!=where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())!=atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())!=atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]=="<")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]<where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())<atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())<atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			else if(where_string[i+1]==">")
			{
				if(where_datatype[where_string[i]]=="string")
				{
					if(S[attribute_to_id[where_string[i]]]>where_string[i+2])
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="integer")
				{
					if(atoi(S[attribute_to_id[where_string[i]]].substr(1,S[attribute_to_id[where_string[i]]].size()-2).c_str())>atoi(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
				else if(where_datatype[where_string[i]]=="float")
				{
					if(atof(S[attribute_to_id[where_string[i]]].c_str())>atof(where_string[i+2].c_str()))
						return (true || check_record(S,i+4,j+4));
				}
			}
			return (false || check_record(S,i+4,j+4));
		}
	}
}
void compute_where()
{
	//table_of_query="test1";
	table_of_query=ftables[0];
	//parse();
	/*TR(mymap,it)
	{
		cout << it->F << endl;
		REP(i,it->S.size())
			cout << it->S[i].F << " " << it->S[i].S << endl;
	}*/
	//table_of_query is assumed to be gnerated before this code executes
	//parse function of create is called before execution
	string s;
	//s=raw_input1(cin);
	if(fconditions.size()!=0)		//if no condition
	s=fconditions[0];	
	else
		s="";
	if(s!="" && !where_check(s))  //added s!=""
	{
		cout << "query invalid\n";
		return;
	}
	//cout << where_check(s) << endl;
	//check if where_check(s) == true
	/*cout << "begin\n";
	REP(i,where_string.size())
	{
		cout << where_string[i] << " ";
	}
	cout << endl;
	cout << "over\n";*/
	attribute_to_id.clear();
	REP(i,mymap[table_of_query].size())
	{
		attribute_to_id[mymap[table_of_query][i].F]=i;
	}
	/*cout << "attr\n";
	TR(attribute_to_id,it)
		cout << it->F << " " << it->S << endl;
	cout << "attr\n";*/
	string filename=table_of_query;
	filename+=".csv";
	ifstream file(filename.c_str());
	ofstream fp;
	fp.open("temp_results");
	string temp;
	//cout << "reading csv file" << endl;
	while(file.good())
	{
		temp=raw_input1(file);
		if(temp.size()==0)
			continue;
		//cout << temp << endl;
		VS S=split(temp,",");
		if(check_record(S,0,3))
		{
			//cout << temp << endl;
			fp << temp << endl;
		}
	}
	//cout << "reading csv file" << endl;
	fp.close();
	filename="temp_results";
	/*fstream file1(filename.c_str());
	while(file1.good())
	{
		temp=raw_input1(file1);
		cout << temp << endl;
	}
	*/
	cout <<"~~~~[Ordered Below]~~~~~\n";
	order_it("temp_results",table_of_query);
}
