  // Raquel Yuri da Silveira Aoki
  // Trabalho Final de PAA 2015/2
 // ADAPTADO 

//=======================================================================
// Copyright 2009 Trustees of Indiana University.
// Authors: Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include <boost/property_map/shared_array_property_map.hpp>

using namespace boost;

// Callback that looks for the first common subgraph whose size
// matches the user's preference.
template <typename Graph>
struct example_callback{

  typedef typename graph_traits<Graph>::vertices_size_type VertexSizeFirst;

  example_callback(const Graph& graph1) :
    m_graph1(graph1) { }

  template <typename CorrespondenceMapFirstToSecond,
            typename CorrespondenceMapSecondToFirst>
  bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                  CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                  VertexSizeFirst subgraph_size) {

    // Fill membership map for first graph
    typedef typename property_map<Graph, vertex_index_t>::type VertexIndexMap;
    typedef shared_array_property_map<bool, VertexIndexMap> MembershipMap;

    MembershipMap membership_map1(num_vertices(m_graph1),
                                  get(vertex_index, m_graph1));

    fill_membership_map<Graph>(m_graph1, correspondence_map_1_to_2, membership_map1);

    // Generate filtered graphs using membership map
    typedef typename membership_filtered_graph_traits<Graph, MembershipMap>::graph_type
      MembershipFilteredGraph;

    MembershipFilteredGraph subgraph1 =
      make_membership_filtered_graph(m_graph1, membership_map1);

    // Print the graph out to the console

    std::cout << "Found common subgraph (size " << subgraph_size << ")" << std::endl;
    //print_graph(subgraph1);

    // Explore the entire space
    return (true);
  }

private:
  const Graph& m_graph1;
  VertexSizeFirst m_max_subgraph_size;
};

int main (int argc, char *argsvalues[]) {
  // Using a vecS graph here so that we don't have to mess around with
  // a vertex index map; it will be implicit.
  typedef adjacency_list<listS, vecS, directedS,
    property<vertex_name_t, unsigned int,
    property<vertex_index_t, unsigned int> >,
    property<edge_name_t, unsigned int> > Graph;

  typedef graph_traits<Graph>::vertex_descriptor Vertex;
  typedef graph_traits<Graph>::edge_descriptor Edge;

  typedef property_map<Graph, vertex_name_t>::type VertexNameMap;
  typedef property_map<Graph, edge_name_t>::type EdgeNameMap;

  // Test maximum and unique variants on known graphs
  Graph graph_simple1, graph_simple2;
  example_callback<Graph> user_callback(graph_simple1);

  VertexNameMap vname_map_simple1 = get(vertex_name, graph_simple1);
  VertexNameMap vname_map_simple2 = get(vertex_name, graph_simple2);

  // Carregando os grafos
   //std::ifstream infile1("grafo11.txt");
   //std::ifstream infile2("grafo22.txt");
   std::ifstream infile1(argsvalues[1]);
   std::ifstream infile2(argsvalues[2]);

  int n1,n2, i;
  infile1 >> n1;
  infile2 >> n2;

  for(i=1;i<=n1;i++) {
      put(vname_map_simple1, add_vertex(graph_simple1), i);
  }
  for(i=1;i<=n2;i++) {
      put(vname_map_simple2, add_vertex(graph_simple2), i);
  }

    int aux,j;
    for (i = 0; i < n1; i++){
        for(j=0; j<n1;j++ ){
        infile1 >> aux;
        if (aux != 0 & j>i)
            add_edge(i, j, graph_simple1);
        }
   }

    for (i = 0; i < n2; i++){
        for(j=0; j<n2;j++ ){
        infile2 >> aux;
        if (aux != 0 & j>i)
            add_edge(i, j, graph_simple2);
        }
   }

  std::cout << "First graph:" << std::endl;
  print_graph(graph_simple1);
  std::cout << std::endl;

  std::cout << "Second graph:" << std::endl;
  print_graph(graph_simple2);
  std::cout << std::endl;


  // Maximum subgraphs
  // funcao de interesse 
  std::cout << "mcgregor_common_subgraphs_maximum:" << std::endl;
  mcgregor_common_subgraphs_maximum(graph_simple1, graph_simple2,
        true, user_callback ) ;//, vertices_equivalent(make_property_map_equivalent(vname_map_simple1, vname_map_simple2)));
  std::cout << std::endl;

  return 0;
}
