#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>

using namespace std;

#pragma pack(1)
struct IpGpsInfo
{
    uint32_t ip;
    uint32_t latitude;
    uint32_t longitude;
    uint8_t locate_type;
    uint8_t scene;
    uint16_t time_sim;
    uint32_t first_day;
    uint32_t last_day;
    uint16_t day_sim;
};
enum 
{
    MAX_IP_GPS_NUM = 500,
};
struct UinIp2GpsInfo
{
    uint64_t uin;
    uint32_t version;
    IpGpsInfo ip_gps[MAX_IP_GPS_NUM];
};
#pragma pack()

static inline int print_ipgps(const IpGpsInfo &ip_gps)
{
	char ip[INET_ADDRSTRLEN];
	char *p;

	if (!inet_ntop(AF_INET, &ip_gps.ip, ip, sizeof(ip))) {
		cerr << "inet_ntop failed" << endl;
		return -1;
	}
	
	p = strchr(ip, '.');
	if (!p) {
		cerr << "ip error: " << ip << std::endl;
		return -1;
	}
	p = strchr(++p, '.');
	if (!p) {
		cerr << "ip error: " << ip << std::endl;
		return -1;
	}
	*p = '\0';

	cout << ip
		<< '\t' << ip_gps.latitude
		<< '\t' << ip_gps.longitude
		<< '\t' << static_cast<int>(ip_gps.locate_type)
		<< '\t' << static_cast<int>(ip_gps.scene);
		if (0 == ip_gps.time_sim) {
			cout << "\t0.0";
		} else if (1000 == ip_gps.time_sim) {
			cout << "\t1.0";
		} else {
			cout << '\t' << ip_gps.time_sim / 1000.0;
		}
		if (0 == ip_gps.day_sim) {
			cout << "\t0.0";
		} else if (1000 == ip_gps.day_sim) {
			cout << "\t1.0";
		} else {
			cout << '\t' << ip_gps.day_sim / 1000.0;
		}
		cout << '\t' << ip_gps.first_day / 10000 
		<< '-' << std::setfill ('0') << std::setw (2) << (ip_gps.first_day % 10000) / 100 
		<< '-' << std::setfill ('0') << std::setw (2) << ip_gps.first_day % 100
		<< '\t' << ip_gps.last_day / 10000
		<< '-' << std::setfill ('0') << std::setw (2) << (ip_gps.last_day % 10000) / 100 
		<< '-' << std::setfill ('0') << std::setw (2) << ip_gps.last_day % 100
		<< endl;
	return 0;
}

static inline int day2tm(const char *day, uint32_t &tm)
{
	char *p;
	struct tm t;

	p = strptime(day, "%Y-%m-%d", &t);
	if (!p || '\0' != *p) {
		cerr << "input error: " << day << endl;
		return -1;
	}
#if 0
	cout << t.tm_year << '-' << t.tm_mon << '-' << t.tm_mday << endl;
#endif	
	tm = (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday;
	return 0;
}

int main(int argc, char **argv)
{
	ifstream ofs;
	string line;
	IpGpsInfo ip_gps;
	char ip[16], first_day[16], last_day[16];
	float time_sim, day_sim;
	uint64_t uin;
	int err;
	const int COUNT = 500;
	int i = 0;

#if 0
	std::cout << sizeof(UinIp2GpsInfo) << std::endl;
#endif	

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " inputfile" << std::endl;
		return -1;
	}

	ofs.open(argv[1]);

	while (getline(ofs, line)) {
		if (10 != sscanf(line.c_str(), "%ld%s%d%d%hhd%hhd%f%f%s%s", &uin, ip, &ip_gps.latitude, 
					&ip_gps.longitude, &ip_gps.locate_type, &ip_gps.scene, &time_sim, 
					&day_sim, first_day, last_day)) {
			cerr << "scanf error" << endl;
			break;
		}

		strcat(ip, ".0.0");
		err = inet_pton(AF_INET, ip, &ip_gps.ip);
		if (1 != err) {
			cerr << "inet_pton failed: " << err << endl;
			break;
		}
#if 0		
		cout << ip_gps.ip << endl;
#endif

		ip_gps.time_sim = static_cast<uint16_t>(time_sim * 1000);
		ip_gps.day_sim = static_cast<uint16_t>(day_sim * 1000);
		
		if (day2tm(first_day, ip_gps.first_day)) {
			cerr << "day2tm failed" << endl;
			break;
		}
		if (day2tm(last_day, ip_gps.last_day)) {
			cerr << "day2tm failed" << endl;
			break;
		}

		cout << uin << '\t';
		print_ipgps(ip_gps);

		if (++i >= COUNT) {
			break;
		}
	}

	ofs.close();
	return 0;
}
