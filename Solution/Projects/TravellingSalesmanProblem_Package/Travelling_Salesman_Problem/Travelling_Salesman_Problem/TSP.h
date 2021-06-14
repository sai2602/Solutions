#include <iostream>
#include "Default_Defines.h"

class TSP {
private:
	int total_nodes_available;

	unsigned int shortest_distance;

	std::vector<std::vector<int>> graph;

	std::vector<int> best_route;

public:
	bool Add_Node(std::vector<int>& new_node);

	bool Delete_Node(int& node_number);

	bool Calculate_Shortest_Distance();

	void Return_Current_Graph_Information();

	void Help();

	std::vector<int> Read_New_Node_Values();

	int Read_Node_Value_To_Delete();

	void print();

	TSP();
};
