#include <stdint.h>

#include <iostream>

#define MAX_UIN_CNT_NUMBER 4
#define Attr_API(attr, val)

struct LbsUinListValue
{
	uint32_t cnt[MAX_UIN_CNT_NUMBER];
	uint32_t time;
}__attribute__((packed));


int retrive_uin_number(const LbsUinListValue &value, const uint32_t range, uint32_t &uin_num)
{
	const uint32_t range_table[MAX_UIN_CNT_NUMBER] = {
		1000, 2000, 3000, 5000, 
	};
	int i;
	double x1, x2, y1, y2;

	for (i = 0; i < MAX_UIN_CNT_NUMBER; i++) {
		if (range == range_table[i]) {
			uin_num = value.cnt[i];
			return 0;
		} else if (range < range_table[i]) {
			break;
		}
	}

	Attr_API(ATTR_LINEAR_INTERPOLATION, 1);

	if (0 == i) {
		x1 = static_cast<double>(range_table[0]);
		y1 = static_cast<double>(value.cnt[0]);
		uin_num = static_cast<uint32_t>(y1 / (x1 * x1) * range * range);
	} else {
		if (i >= MAX_UIN_CNT_NUMBER - 1) {
			i = MAX_UIN_CNT_NUMBER - 1;
		}
		x1 = static_cast<double>(range_table[i - 1]);
		y1 = static_cast<double>(value.cnt[i - 1]);
		x2 = static_cast<double>(range_table[i]);
		y2 = static_cast<double>(value.cnt[i]);
		uin_num = static_cast<uint32_t>(((x2 * y1 - x1 * y2) * range + x1 * x1 * y2 - x2 * x2 * y1) * range / (x1 * x2 * (x1 - x2)));
	}

	return 0;
}

int main()
{
	LbsUinListValue v;
	uint32_t range, uin_num;

	v.cnt[0] = 1000;
	v.cnt[1] = 4000;
	v.cnt[2] = 16000;
	v.cnt[3] = 256000;

	for (; ;) {
		std::cin >> range;	
		retrive_uin_number(v, range, uin_num);
		std::cout << uin_num << std::endl;
	}

	return 0;
}
