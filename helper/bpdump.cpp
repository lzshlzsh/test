#include "helper.h"

int main(int argc, char **argv)
{
	FileReader fr(argc, const_cast<const char **>(argv));

	fr.FileDump();

	return 0;
}
