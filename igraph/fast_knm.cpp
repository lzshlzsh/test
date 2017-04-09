/*
 * =====================================================================================
 *
 *       Filename:  fast_knm.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/17/2014 05:07:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

#include <igraph.h>

using namespace std;

int main()
{
	igraph_t g;
	igraph_vector_t membership;
  igraph_vector_t modularity;
  igraph_matrix_t merges;

	igraph_vector_init(&membership, 0);
	igraph_vector_init(&modularity, 0);
	igraph_matrix_init(&merges, 0, 0);


	/* Zachary Karate club */
	igraph_small(&g, 0, IGRAPH_UNDIRECTED, 
			0,  1,  0,  2,  0,  3,  0,  4,  0,  5,
			0,  6,  0,  7,  0,  8,  0, 10,  0, 11,
			0, 12,  0, 13,  0, 17,  0, 19,  0, 21,
			0, 31,  1,  2,  1,  3,  1,  7,  1, 13,
			1, 17,  1, 19,  1, 21,  1, 30,  2,  3,
			2,  7,  2,  8,  2,  9,  2, 13,  2, 27,
			2, 28,  2, 32,  3,  7,  3, 12,  3, 13,
			4,  6,  4, 10,  5,  6,  5, 10,  5, 16,
			6, 16,  8, 30,  8, 32,  8, 33,  9, 33,
			13, 33, 14, 32, 14, 33, 15, 32, 15, 33,
			18, 32, 18, 33, 19, 33, 20, 32, 20, 33,
			22, 32, 22, 33, 23, 25, 23, 27, 23, 29,
			23, 32, 23, 33, 24, 25, 24, 27, 24, 31,
			25, 31, 26, 29, 26, 33, 27, 33, 28, 31,
			28, 33, 29, 32, 29, 33, 30, 32, 30, 33,
			31, 32, 31, 33, 32, 33,
			-1);
	igraph_community_fastgreedy(&g, NULL, &merges, &modularity, &membership);

	for (int i = 0; i < igraph_vector_size(&g.from); i++) {
		cout << VECTOR(g.from)[i] << "\t" << VECTOR(g.to)[i] << endl;
	}

	cout << endl << endl;

	for (int i = 0; i < g.n; i++) {
		cout << i << "\t" << VECTOR(membership)[i] << endl;
	}

	igraph_vector_destroy(&membership);
	igraph_vector_destroy(&modularity);
	igraph_matrix_destroy(&merges);
	return 0;
}
