#include <unordered_map>
#include <iostream>
#include <cstring>

using namespace std;


struct eqstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) == 0;
	}
};

int main()
{
	unordered_map<const char*, int, hash<const char*>, eqstr> months;

	typedef unordered_map<const char*, int, hash<const char*>, eqstr> MyUnorderedMap;

	pair<MyUnorderedMap::iterator, bool> iret;

	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;
	
	iret = months.insert(MyUnorderedMap::value_type("december", 2));
	if (iret.second){
		cout << "insert sucess" << endl;
	}else{
		cout << "insert fail" << endl;
	}

	cout << "september -> " << months["september"] << endl;
	cout << "april     -> " << months["april"] << endl;
	cout << "june      -> " << months["june"] << endl;
	cout << "november  -> " << months["november"] << endl;
}
