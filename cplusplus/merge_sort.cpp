#include <vector>
#include <stdio.h>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

template <typename T>
class merge_sort_t
{
	static std::vector<T> &merge(std::vector<T> &v1, std::vector<T> &v2)
	{
		std::vector<T> vt;
		typename std::vector<T>::iterator t1 = v1.begin();
		typename std::vector<T>::iterator t2 = v2.begin();
		
		for (; t1 != v1.end() && t2 != v2.end();) {
			if (*t1 <= *t2) {
				vt.push_back(*t1);
				t1++;
			} else {
				vt.push_back(*t2);
				t2++;
			}
		}
		for (; t1 != v1.end(); t1++) {
			vt.push_back(*t1);
		}
		for (; t2 != v2.end(); t2++) {
			vt.push_back(*t2);
		}
		v2.clear();
		return (v1 = vt);
	}
public:	
	static std::vector<T> &merge_sort(std::vector<T> &v)
	{
		if (!v.empty() && 1 != v.size()) {
			std::vector<T> carry;
			std::vector<T> tmp[64];
			std::vector<T> *source;
			std::vector<T> *fill = &tmp[0];

			do {
				carry.push_back(v.back());
				v.pop_back();
				for (source = &tmp[0]; source != fill && !source->empty(); 
						source++) {
					carry = merge(carry, *source);
				}
				*source = merge(*source, carry);
				if (source == fill) {
					fill++;
				}
			} while (!v.empty());
			for (source = &tmp[0]; source != fill; source++) {
				v = merge(v, *source);
			}
		}
		return v;
	}
};

int main()
{
#define MAX_SZ 9000	
	linear_congruential_engine<unsigned int, 1, 9999, 10000> rnd;
	vector<unsigned int> v, v1;

	for (int i = 0; i < MAX_SZ; i++) {
		v.push_back(rnd());
	}
	v1 = v;

	merge_sort_t<unsigned int>::merge_sort(v);
	sort(v1.begin(), v1.end());

	if (v != v1) {
		cout << "FAIL" << endl;
		vector<unsigned int>::iterator it = v.begin();
		vector<unsigned int>::iterator it1 = v1.begin();
		cout << v.size() << ", " << v1.size() << endl;
		for (; it != v.end() && it1 != v1.end(); it++, it1++) {
			cout << *it << ", " << *it1;
			if (*it != *it1) {
				cout << " FAIL";
			}
			cout << endl;
		}
	} else {
		cout << "SUCCESS" << endl;
	}

	return 0;
}
