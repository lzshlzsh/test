#include <iostream>
using namespace std;

class EmptyClass{
};
struct EmptyStruct{
};

struct PoiCacheEntry
{
    enum {
        MAX_COUNTRY_LEN = 13, /*max: 10 chinese words, truncate*/
        MAX_PROVINCE_LEN = 9, /*max: 4 words*/
        MAX_CITY_LEN = 13, /*max: 7 words, trucate*/
        MAX_DISTRICT_LEN = 13, /*max: 18 words*/
        MAX_POI_NAME_LEN = 51,
        MAX_POI_ADDR_LEN = 101,
        MAX_POI_CATALOG_LEN = 41,
        DUMMY_LEN = 244 - MAX_COUNTRY_LEN - MAX_PROVINCE_LEN - MAX_CITY_LEN
            - MAX_DISTRICT_LEN - MAX_POI_NAME_LEN - MAX_POI_ADDR_LEN - MAX_POI_CATALOG_LEN,
    };
    char country_[MAX_COUNTRY_LEN];
    char province_[MAX_PROVINCE_LEN];
    char city_[MAX_CITY_LEN];
    char district_[MAX_DISTRICT_LEN];
    char poi_name_[MAX_POI_NAME_LEN];
    char poi_addr_[MAX_POI_ADDR_LEN];
    char poi_catalog_[MAX_POI_CATALOG_LEN];
    char dummy_[DUMMY_LEN];
};

int main()
{
	cout << "sizeof(EmptyClass) = " << sizeof(EmptyClass) << endl;
	cout << "sizeof(EmptyStruct) = " << sizeof(EmptyStruct) << endl;
    cout << "sizeof(PoiCacheEntry) = " << sizeof(PoiCacheEntry) << endl;
    cout << "sizeof(int) = " << sizeof(int) << endl;
    cout << "sizeof(size_t) = " << sizeof(size_t) << endl;
	return 0;
}
