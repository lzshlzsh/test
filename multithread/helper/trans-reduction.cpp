#include "helper.h"

int main(int argc, char **argv)
{
	Graph *graph;
	FileReader fr(argc, const_cast<const char **>(argv));
	ALGraphBuilder builder;

	fr.ConstructDepGraph(&builder);

	graph = builder.GetGraph();

	graph->TransitiveReduction(fr);
	
	return 0;
}





