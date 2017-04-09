/*
 * =====================================================================================
 *
 *       Filename:  graphs_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/11/2014 04:57:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <igraph/igraph.h>

int main(void) {
  igraph_real_t avg_path;
  igraph_t graph;
  igraph_vector_t dimvector;
  igraph_vector_t edges;
  int i;
  
  igraph_vector_init(&dimvector, 2);
  VECTOR(dimvector)[0]=40;
  VECTOR(dimvector)[1]=40;
  igraph_lattice(&graph, &dimvector, 0, IGRAPH_UNDIRECTED, 0, 1);

  printf("igraph_vcount = %d\n", igraph_vcount(&graph));

  igraph_rng_seed(igraph_rng_default(), 48);
  igraph_vector_init(&edges, 80);
  for (i=0; i<igraph_vector_size(&edges); i++) {
    VECTOR(edges)[i] = rand() % (int)igraph_vcount(&graph);
  }

  igraph_average_path_length(&graph, &avg_path, IGRAPH_UNDIRECTED, 1);
  printf("Average path length (lattice):            %f\n", (double) avg_path);

  igraph_add_edges(&graph, &edges, 0);
  igraph_average_path_length(&graph, &avg_path, IGRAPH_UNDIRECTED, 1);
  printf("Average path length (randomized lattice): %f\n", (double) avg_path);
  
  igraph_vector_destroy(&dimvector);
  igraph_vector_destroy(&edges);
  igraph_destroy(&graph);

  return 0;
}
