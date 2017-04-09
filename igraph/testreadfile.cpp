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

#include <igraph/igraph.h>
#include <math.h>

#include <iostream>
#include <map>

using namespace std;

typedef std::map<long int, void *> VertextAttr;

static igraph_attribute_table_t s_attribute_table;
static VertextAttr s_vertex_attr;

static int attribute_init(igraph_t *graph, igraph_vector_ptr_t *attr) {
    graph->attr = reinterpret_cast<void *>(1); 
    return 0;
}

static int add_edges(igraph_t *graph, const igraph_vector_t *edges, 
                   igraph_vector_ptr_t *attr) {
    return 0;
}

static int add_vertices(igraph_t *graph, long int nv, igraph_vector_ptr_t *attr) {
    if (!attr) {
        return 0;
    }
    const igraph_strvector_t *namevec = reinterpret_cast<const igraph_strvector_t *>(
            reinterpret_cast<igraph_attribute_record_t *>(VECTOR(*attr)[0])->value);
    graph->attr = const_cast<igraph_strvector_t *>(namevec);
    return 0;
}

static int get_info(const igraph_t *graph,
                         igraph_strvector_t *gnames,
                         igraph_vector_t *gtypes,
                         igraph_strvector_t *vnames,
                         igraph_vector_t *vtypes,
                         igraph_strvector_t *enames,
                         igraph_vector_t *etypes) {
    igraph_strvector_t *ver_attr = reinterpret_cast<igraph_strvector_t *>(graph->attr);
    igraph_strvector_copy(vnames, ver_attr);
    return 0;
} 

int print_attributes(const igraph_t *g) {

  igraph_vector_t gtypes, vtypes, etypes;
  igraph_strvector_t gnames, vnames, enames;
  long int i,j;

  igraph_vector_init(&gtypes, 0);
  igraph_vector_init(&vtypes, 0);
  igraph_vector_init(&etypes, 0);
  igraph_strvector_init(&gnames, 0);
  igraph_strvector_init(&vnames, 0);
  igraph_strvector_init(&enames, 0);

  if (igraph_has_attribute_table()) {
      printf("has attribute table\n");
  } else {
      printf("no attribute table\n");
  }
  cout << g->attr << endl;

  igraph_i_attribute_get_info(g, &gnames, 0, &vnames, 0, 0, 0);
  //igraph_cattribute_list(g, &gnames, &gtypes, &vnames, &vtypes, &enames, &etypes);

  printf("lenth %li: ", igraph_strvector_size(&vnames));
  for (i=0; i<igraph_vcount(g); i++) {
    long int j;
    printf("Vertex %li: ", i);
    for (j=0; j<igraph_strvector_size(&vnames); j++) {
      printf("%s=", STR(vnames, j));
      if (VECTOR(vtypes)[j]==IGRAPH_ATTRIBUTE_NUMERIC) {
    igraph_real_printf(VAN(g, STR(vnames,j), i));
    putchar(' ');
      } else {
    printf("\"%s\" ", VAS(g, STR(vnames,j), i));
      }
    }
    printf("\n");
  }



  igraph_strvector_destroy(&enames);
  igraph_strvector_destroy(&vnames);
  igraph_strvector_destroy(&gnames);
  igraph_vector_destroy(&etypes);
  igraph_vector_destroy(&vtypes);
  igraph_vector_destroy(&gtypes);

  return 0;
}


int main() {

  igraph_t g;
  FILE *f;
  FILE *f1;
  int i, n = 0;
  long int no_of_nodes;
  igraph_matrix_t merges;
  igraph_vector_t modularity;
  igraph_vector_t membership;
//  char * names="abd";

  s_attribute_table.init = attribute_init;
  s_attribute_table.add_vertices = add_vertices;
  s_attribute_table.add_edges = add_edges;
  s_attribute_table.get_info = get_info;

  igraph_vector_init(&modularity, 0);
  igraph_vector_init(&membership, 0);
  igraph_matrix_init(&merges, 0, 0);
  /* long int i, n; */

  igraph_i_set_attribute_table(&s_attribute_table);

  f=fopen("./testuser.txt", "r");
  f1=fopen("./userresult.txt", "w");
  //igraph_read_graph_edgelist(&g, f, 0, 1);
  igraph_read_graph_ncol(&g, f, 0, 1, IGRAPH_ADD_WEIGHTS_YES, 0);
  //igraph_matrix_init(&coords, 0, 0);
  //igraph_layout_reingold_tilford(&g, &coords, IGRAPH_IN, 0, 0); 

  print_attributes(&g);

  n=igraph_vcount(&g);
  printf("befor the node of graph is:%d \n",n);
  n=igraph_ecount(&g);
  printf("befor the edge of graph is:%d \n",n);

  igraph_simplify(&g, /*multiple=*/1, /*loops=*/1, /*edge_comb=*/ 0);
  
  n=igraph_vcount(&g);
  printf("after the node of graph is:%d \n",n);
  n=igraph_ecount(&g);
  printf("after the edge of graph is:%d \n",n);

  igraph_community_walktrap(&g,
                              0 /* no weights */,
                            4 /* steps */,
                            &merges,
                            &modularity, 
                            &membership/* membership=*/);
  
  no_of_nodes=igraph_vcount(&g);
  printf("Merges:\n");
  for (i=0; i<igraph_matrix_nrow(&merges); i++) {
    printf("%2.1li + %2.li -> %2.li (modularity %4.2f)\n", 
       (long int)MATRIX(merges, i, 0), 
       (long int)MATRIX(merges, i, 1), 
       no_of_nodes+i,
       VECTOR(modularity)[i]);
  }

  n=igraph_vector_size(&membership);
  for (i=0;i<n;i++)
  {
      //printf("membership[%u]:%.2g \n", i, VECTOR(membership)[i]);
      fprintf(f1, "%u    %.2g \n", i, VECTOR(membership)[i]);
  }

  //igraph_write_graph_edgelist(&g, f1);
//  print_attributes(&g);
  //for (i=0; i<n; i++) {
   // printf("%6.3f %6.3f\n", MATRIX(coords, i, 0), MATRIX(coords, i, 1));
 // }
  
  //igraph_matrix_destroy(&coords);
  igraph_destroy(&g);
  return 0;
}

