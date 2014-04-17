
bool check_orderby(VS forderby)
{
	REP(i,forderby.size())
	{
		cols_in_orderby = split(forderby[i],",");
		//REP(j,cols_in_orderby.size())
		//{
		//	cout << cols_in_orderby[j] << endl;
			if(!check_col(cols_in_orderby))
				return false;
		//}
	}
	return true;
}
bool check_groupby(VS fgroupby)
{
	REP(i,fgroupby.size())
	{
		VS extract_having=split(fgroupby[i]," HAVING");
		VS cols_in_groupby = split(extract_having[0],",");
		if(!check_col(cols_in_groupby))
			return false;
	}
	return true;
}
