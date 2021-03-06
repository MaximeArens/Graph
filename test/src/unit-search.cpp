//
// Created by Terae on 01*5/01/18.
//

#include "catch.hpp"

#if defined(TEST_SINGLE_HEADER_FILE)
    #include "graph.hpp"
#else
    #include "GraphSearch.h"
#endif

TEST_CASE("search") {
    SECTION("A*") {
        using Graph = graph_undirected<std::string, int, double>;

        Graph g;
        g["node 1"] = 1;
        g["node 2"] = 2;
        g["node 3"] = 3;
        g["node 4"] = 4;
        g("node 1", "node 2") = 12;
        g("node 1", "node 3") = 13;
        g("node 3", "node 2") = 32;
        g("node 2", "node 4") = 24;

        std::list<std::string> targets = {"node 4"};
        search::astar<std::string, int, double, UNDIRECTED> a(g, targets);
        search::path<Graph::const_iterator, double> p{a.run(g.find("node 1"), [&g](const Graph::const_iterator & it) -> double {
                return std::abs(it->second->get() - g["node 4"]);
            })
        };

        CHECK(p.total_cost() == 36);
    }
}
