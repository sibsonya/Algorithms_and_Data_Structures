#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

void make_forest(int n,
                 std::vector<std::unordered_set<int>>& adj_list,
                 std::set<int>& vertices) {
    int m, neigh;
    for (int i = 0; i != n; ++i) {
        std::cin >> m;
        if (m != 0) 
            vertices.insert(i);
        for (size_t j = 0; j != m; ++j) {
            std::cin >> neigh;
            adj_list[i].insert(neigh);
        }
    }
}

int find_one_deg_vertex(std::set<int>& vertices,
                        std::vector<std::unordered_set<int>>& adj_list) {
    int one_deg_vertex = -1;
    for (int v : vertices) {
        if (adj_list[v].size() == 1) {
            one_deg_vertex = v;
            break;
        }
    }
    return one_deg_vertex;
}

int find_min_cover_value(std::set<int>& vertices,
                         std::vector<std::unordered_set<int>>& adj_list) {
    int min_cover_value = 0;
    while (!vertices.empty()) {
        int u = find_one_deg_vertex(vertices, adj_list);
        int parent = *adj_list[u].begin();
        vertices.erase(u);
        vertices.erase(parent);
        for (auto neigh : adj_list[parent]) {
            adj_list[neigh].erase(parent);
            if (adj_list[neigh].size() == 0) 
                vertices.erase(neigh);
        }
        ++min_cover_value;
    }
    return min_cover_value;    
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> adj_list(n);
    std::set<int> vertices;
    make_forest(n, adj_list, vertices);
    int min_cover_value = find_min_cover_value(vertices, adj_list);
    std::cout << min_cover_value << std::endl;
    return 0;
}

