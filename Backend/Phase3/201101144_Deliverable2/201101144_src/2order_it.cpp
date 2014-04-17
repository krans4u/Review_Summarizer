LL divide(string filename);
LL numof(string a);
void printing(string s)
{
	if(s=="")
		return;
	VS splitted=split(s,",");
	VI v;
	if(splitted.size()==0)
	{
		cout << "NO RESULTS\n";
		return;


	}
	REP(i,fcolumns.size())
	{
		
		if(i==0)
			cout << splitted[attribute_to_id[fcolumns[i]]];
		else
			cout  << "," << splitted[attribute_to_id[fcolumns[i]]];
	}
	cout << endl;
}
float floatof(string s)
{
	float ans=0.0;
	string t;
	LL flg=1;
	LL ct=0;
	REP(i,s.size())
	{
		if(s[i]=='.')
		{
			flg=1;
			continue;
		}
		if(flg==1)
			ct++;
		t.PB(s[i]);
	}
	LL tempo=numof(t);
	return tempo*1.0/POW1(10LL,ct,INF);
}
struct OrderBy
{
	bool operator()(pair<string,LL> a, pair<string,LL> b)
	{
		LL ind;
		string type;
		if(cols_in_orderby.size()==0)
			return true;
		VS av=split(a.F,",");
		VS bv=split(b.F,",");
		REP(i,cols_in_orderby.size())
		{
			ind=order_map[cols_in_orderby[i]].F;
			type=order_map[cols_in_orderby[i]].S;
			if(type=="string")
			{
				if(av[ind]!=bv[ind])
					return (av[ind] < bv[ind]);
			}
			else if(type=="float")
			{
				if(av[ind]!=bv[ind])
					return (floatof(av[ind]) < floatof(bv[ind]));
			}
			else
			{
				if(numof(av[ind])!=numof(bv[ind]))
					return (numof(av[ind]) < numof(bv[ind]));
			}
		}
		return true;
	}

};

string num2string(LL x)
{
	if(x==0)
		return "0";
	string ans,finans;
	while(x!=0)
	{
		ans.PB(x%10 + '0');
		x/=10;
	}
	REP(i,ans.size())
	{
		finans.PB(ans[ans.size()-1-i]);
	}
	return finans;
}
void merge(LL file_ct)
{
	ifstream files[file_ct];
	priority_queue<pair<string, LL>, vector<pair<string,LL> >, OrderBy > pq;
	REP(i,file_ct)
	{
		files[i].open(("temp"+num2string(i)).c_str());
		string a=raw_input1(files[i]);
		pq.push(MP(a,i));
	}
	while(!pq.empty())
	{
		pair<string,LL> a = pq.top();
		printing(a.F);
		//	cout << a.F << " final" << endl;
		pq.pop();
		LL ind=a.S;
		if(files[ind].good())
		{
			string t=raw_input1(files[ind]);
			if(t=="")
				break;
			pq.push(MP(t,ind));
		}
	}
}
void order_it(string filename, string tab)
{
	order_map.clear();
	cout << "here\n";
	cout << filename << " " << tab << endl;
	cout << cols_in_orderby.size() << endl;
	REP(i,mymap[tab].size())
	{
		order_map[mymap[tab][i].F]=MP(i,mymap[tab][i].S);
	}
	LL file_ct=divide(filename);	
	cout << file_ct << endl;
	merge(file_ct);

}
LL numof(string a)
{
	LL ans=0;
	LL ten=1;
	for(LL i=a.size()-1;i>=0;i--)
	{
		ans+=ten*(a[i]-'0');
		ten*=10;
	}
	return ans;
}
bool comp(string a, string b)
{
	LL ind;
	string type;
	LL sz=cols_in_orderby.size();
	cout << sz << endl;
	if(sz==0)
		return true;
	VS av=split(a,",");
	VS bv=split(b,",");
	REP(i,sz)
	{
		ind=order_map[cols_in_orderby[i]].F;
		type=order_map[cols_in_orderby[i]].S;
		if(type=="string")
		{
			if(av[ind]!=bv[ind])
				return (av[ind] < bv[ind]);
		}
		else if(type=="float")
		{
			if(av[ind]!=bv[ind])
				return (floatof(av[ind]) < floatof(bv[ind]));
		}

		else
		{
			if(numof(av[ind])!=numof(bv[ind]))
				return (numof(av[ind]) < numof(bv[ind]));
		}
	}
	return true;
}
LL divide(string filename)
{
	ifstream file(filename.c_str());
	int file_ct=0;
	VS temp;
	while(file.good())
	{
		temp.clear();
		string t="";
		LL ct=0;
		while(ct<1000)
		{
			if(!file.good())
				break;
			t=raw_input1(file);
			if(t=="")
				break;
			//cout << "~~" << t << endl;
			temp.PB(t);
			ct++;
		}
		cout << "out of single file " << temp.size() << endl;
	//	REP(i,temp.size())
	//		cout << temp[i] << endl;
		sort(temp.begin(),temp.end(),comp);
	//	sort(temp.begin(),temp.end());
		cout << "out of single file aftersort\n";
		ofstream fp;
		string fnm = "temp"+num2string(file_ct);
		cout << fnm << endl;
		fp.open(fnm.c_str());
		REP(i,temp.size())
			fp << temp[i] << endl;
		fp.close();
		file_ct++;
	}
	return file_ct;
}

