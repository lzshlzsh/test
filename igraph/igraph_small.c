/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006-2012  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard st, Cambridge MA, 02139 USA
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <iostream>
#include <assert.h>

#include <igraph.h>

using namespace std;

#define VERBOSE(__v) #__v

static int print_vector(const igraph_vector_t *v, const char *name)
{
	cout << "------" << name << "-------" << endl;
	for (int i = 0; i < igraph_vector_size(v); i++) {
    cout << i << " ";
  }
	cout << endl;
	for (int i = 0; i < igraph_vector_size(v); i++) {
		cout << VECTOR(*v)[i] << " ";
	}
	cout << endl;
	return 0;
}

static int test_igraph_vector_order(const igraph_vector_t *v, const igraph_vector_t *v2,
		igraph_real_t nodes)
{
	igraph_vector_t _res, *res = &_res;
  long int edges=igraph_vector_size(v);
  igraph_vector_t ptr;
  igraph_vector_t rad;
  long int i, j;

  assert(v!=NULL);
  assert(v->stor_begin != NULL);

  IGRAPH_VECTOR_INIT_FINALLY(&ptr, (long int) nodes+1);
  IGRAPH_VECTOR_INIT_FINALLY(&rad, edges);
	IGRAPH_CHECK(igraph_vector_init(res, 0));
  IGRAPH_CHECK(igraph_vector_resize(res, edges));

	print_vector(v, VERBOSE(v));
	print_vector(v2, VERBOSE(v2));
  
  for (i=0; i<edges; i++) {
    long int radix=(long int) v2->stor_begin[i];
    if (VECTOR(ptr)[radix]!=0) {
      VECTOR(rad)[i]=VECTOR(ptr)[radix];
    }
    VECTOR(ptr)[radix]=i+1;
  }  

	print_vector(&ptr, VERBOSE(ptr));
	print_vector(&rad, VERBOSE(rad));

  j=0;
  for (i=0; i<nodes+1; i++) {
    if (VECTOR(ptr)[i] != 0) {
      long int next=(long int) VECTOR(ptr)[i]-1;
      res->stor_begin[j++]=next;
      while (VECTOR(rad)[next] != 0) {
	next=(long int) VECTOR(rad)[next]-1;
	res->stor_begin[j++]=next;
      }
    }
  }
	print_vector(res, VERBOSE(res));

  igraph_vector_null(&ptr);
  igraph_vector_null(&rad);

  for (i=0; i<edges; i++) {
    long int edge=(long int) VECTOR(*res)[edges-i-1];
    long int radix=(long int) VECTOR(*v)[edge];
    if (VECTOR(ptr)[radix]!= 0) {
      VECTOR(rad)[edge]=VECTOR(ptr)[radix];
    }
    VECTOR(ptr)[radix]=edge+1;
  }
	print_vector(&ptr, VERBOSE(ptr));
	print_vector(&rad, VERBOSE(rad));
  
  j=0;
  for (i=0; i<nodes+1; i++) {
    if (VECTOR(ptr)[i] != 0) {
      long int next=(long int) VECTOR(ptr)[i]-1;
      res->stor_begin[j++]=next;
      while (VECTOR(rad)[next] != 0) {
	next=(long int) VECTOR(rad)[next]-1;
	res->stor_begin[j++]=next;
      }
    }
  } 
  
	print_vector(res, VERBOSE(res));

  igraph_vector_destroy(&ptr);
  igraph_vector_destroy(&rad);
	igraph_vector_destroy(res);
  IGRAPH_FINALLY_CLEAN(2);
  
  return 0;
}

static int test_igraph_i_create_start(igraph_vector_t *el, igraph_vector_t *iindex, 
		igraph_integer_t nodes)
{
  
# define EDGE(i) (VECTOR(*el)[ (long int) VECTOR(*iindex)[(i)] ])
  
  long int no_of_nodes;
  long int no_of_edges;
  long int i, j, idx;
	igraph_vector_t _res, *res = &_res;

	igraph_vector_init(res, 0);
  
  no_of_nodes=nodes;
  no_of_edges=igraph_vector_size(el);
  
  /* result */
  
  IGRAPH_CHECK(igraph_vector_resize(res, nodes+1));
  
  /* create the index */

  if (igraph_vector_size(el)==0) {
    /* empty graph */
    igraph_vector_null(res);
  } else {
    idx=-1;
		cout << "EDGE(0) = " << EDGE(0) << endl;
    for (i=0; i<=EDGE(0); i++) {
      idx++; VECTOR(*res)[idx]=0;
			cout << "res[" << idx << "] = 0" << endl; 
    }
    for (i=1; i<no_of_edges; i++) {
			cout << "i - x = " << i << "-" << (long int)VECTOR(*res)[idx] << "(" << idx << ")" << endl;
			cout << "EDGE(i) - EDGE(x) = " << EDGE(i) << "-" << EDGE((long int)VECTOR(*res)[idx]) << endl;
      long int n=(long int) (EDGE(i) - EDGE((long int)VECTOR(*res)[idx]));
      for (j=0; j<n; j++) {
	idx++; VECTOR(*res)[idx]=i;
			cout << "res[" << idx << "] = " << i << endl; 
      }
    }
    j=(long int) EDGE((long int)VECTOR(*res)[idx]);
		cout << "j = " << j << ", idx = " << idx << endl;
    for (i=0; i<no_of_nodes-j; i++) {
      idx++; VECTOR(*res)[idx]=no_of_edges;
			cout << "res[" << idx << "] = " << no_of_edges << endl; 
    }
  }

  /* clean */

	igraph_vector_destroy(res);
# undef EDGE
  return 0;
}

int main() {
  
  igraph_t g;
  
  igraph_small(&g, 0, IGRAPH_DIRECTED, 0,1, 1,2, 2,3, 3,4, 6,1, 2,4, 2,6, 6,0, -1);
	cout << "from->to" << endl;
	for (int i = 0; i < igraph_vector_size(&g.from); i++) {
		cout << i << ":" << VECTOR(g.from)[i] << "->" << VECTOR(g.to)[i] << endl;
	}
	cout << "--------------" << endl;
	cout << "oi->ii" << endl;
	for (int i = 0; i < igraph_vector_size(&g.oi); i++) {
		cout << i << ":" << VECTOR(g.oi)[i] << "->" << VECTOR(g.ii)[i] << endl;
	}
	cout << "--------------" << endl;
	cout << "os->is" << endl;
	for (int i = 0; i < igraph_vector_size(&g.os); i++) {
		cout << i << ":" << VECTOR(g.os)[i] << "->" << VECTOR(g.is)[i] << endl;
	}

	cout << "--------------" << endl;

	test_igraph_vector_order(&g.from, &g.to, g.n);
	cout << endl << endl;
	test_igraph_vector_order(&g.to, &g.from, g.n);

	cout << endl << endl;
	test_igraph_i_create_start(&g.from, &g.oi, g.n);
	cout << endl << endl;
	test_igraph_i_create_start(&g.to, &g.ii, g.n);
//  igraph_write_graph_edgelist(&g, stdout);
  igraph_destroy(&g);
  
  return 0;
}
