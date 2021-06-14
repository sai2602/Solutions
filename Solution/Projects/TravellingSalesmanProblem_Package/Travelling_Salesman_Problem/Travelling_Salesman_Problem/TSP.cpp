#include<math.h>
#include<algorithm>
#include "TSP.h"

/*
* This method adds the new node into the existing graph provided the graph meets the requirements of having non-zero positive values.
* It takes the vector containing the graph details as input and returns a SUCCESS if the node was added to the graph.
*/
bool TSP::Add_Node(std::vector<int>& new_node)
{
	if (new_node.size() == (this->total_nodes_available + 1) && new_node[new_node.size() - 1] == 0) {
		for (int i = 0; i < new_node.size() - 1; i++) {
			if (new_node[i] <= 0) {
				return FAILURE;
			}
		}
		for (int j = 0; j < this->graph.size(); j++) {
			this->graph[j].push_back(new_node[j]);
		}
		this->graph.push_back(new_node);
		this->total_nodes_available += 1;
	}
	else {
		return FAILURE;
	}
	return SUCCESS;
}

/*
* This method deletes the requested node from the existing graph provided the the node number exists in the graph.
* It takes the node number as input and returns SUCCESS if the node was deleted.
*/
bool TSP::Delete_Node(int& node_number)
{
	if ((node_number - 1) < (int)(this->graph.size()) && (node_number) > 0) {
		this->graph.erase(this->graph.begin() + (node_number - 1));
		for (int i = 0; i < this->graph.size(); i++) {
			this->graph[i].erase(this->graph[i].begin() + (node_number - 1));
		}
		this->total_nodes_available -= 1;
	}
	else
		return FAILURE;

	return SUCCESS;
}

/*
* This algorithm reads the existing graph, performs all the permutations and calculates the shortest possible route.
* It reads the graph from the current object and returns a SUCCESS after calculating the distance.
*/
bool TSP::Calculate_Shortest_Distance()
{
	std::vector<int> Non_Source_Nodes;
	Non_Source_Nodes.clear();
	std::vector<int> current_route;
	this->shortest_distance = pow(2, sizeof(int) * 8) - 1;

	for (int i = 0; i < this->total_nodes_available; i++) {
		if (i != DEFAULT_ENTRY_NODE) {
			Non_Source_Nodes.push_back(i);
		}
	}

	do {
		current_route.clear();
		int current_iteration_distance = 0;
		int parent_node = DEFAULT_ENTRY_NODE;
		current_route.push_back(parent_node);

		for (int child_node = 0; child_node < Non_Source_Nodes.size(); child_node++) {
			current_iteration_distance += this->graph[parent_node][Non_Source_Nodes[child_node]];
			parent_node = Non_Source_Nodes[child_node];
			current_route.push_back(parent_node);
		}
		current_iteration_distance += this->graph[parent_node][DEFAULT_ENTRY_NODE];
		current_route.push_back(DEFAULT_ENTRY_NODE);

		if (this->shortest_distance > current_iteration_distance) {
			this->shortest_distance = current_iteration_distance;
			this->best_route.clear();
			this->best_route = current_route;
		}
		else {
			//Do Nothing
		}

	} while (std::next_permutation(Non_Source_Nodes.begin(), Non_Source_Nodes.end()));


	return SUCCESS;
}

/*
* This function reads the exiting graph and prints the details on the console in an understandable format.
* The input and output are void.
*/
void TSP::Return_Current_Graph_Information()
{
	std::cout << std::endl;
	std::cout << "Current Graph Details:" << std::endl;
	std::cout << "Total Number of Nodes: " << this->total_nodes_available << std::endl;
	std::cout << "Node names are: " << std::endl;

	for (int i = 0; i < this->graph.size(); i++) {
		std::cout << (i + 1) << std::endl;
	}

	for (int i = 0; i < this->graph.size(); i++) {
		std::cout << "Distance of " << (i + 1) << " from: " << std::endl;
		for (int j = 0; j < this->graph[i].size(); j++) {
			if (this->graph[i][j] != 0) {
				std::cout << (j + 1) << ": " << this->graph[i][j] << " units" << std::endl;
			}
		}
	}

}

/*
* This method is the help document for the available options. It explains all the possible options and explains how to use them.
* It doesn't take any input or provide any output.
*/
void TSP::Help()
{
	std::cout << std::endl;
	std::cout << "Additional Functions include: Add a node(a), Delete a node(d), Exit(e)" << std::endl;
	std::cout << "--Add a node option helps you add a new node to the graph and the distances of this node from every other node (non-zero value) should be specified." << std::endl;
	std::cout << "The new node name will be the next integer value (last node name + 1). If a zero value for distance is entered, the code will not add this node to the graph." << std::endl;
	std::cout << "--Delete a node option will delete the specific node information from the graph." << std::endl;
	std::cout << "--Exit will terminate the code." << std::endl << std::endl;
	std::cout << "Enter the character (a, d, e) for further operation: ";
}

/*
* This method reads the details pertaining to the new node being entered by the user from the console.
* It doesn't take any input parameters and returns a vector with all the distance values in it.
*/
std::vector<int> TSP::Read_New_Node_Values()
{
	int distance_entered;
	std::vector<int> New_Node_Vector;
	New_Node_Vector.clear();

	std::cout << "Add distance of new node to node:" << std::endl;
	for (int i = 0; i < this->graph.size(); i++) {
		std::cout << i + 1 << ": ";
		std::cin >> distance_entered;
		New_Node_Vector.push_back(distance_entered);
	}
	New_Node_Vector.push_back(0);
	return New_Node_Vector;

}

/*
* This method reads the node number entered by the user from the console to delete from the graph.
* It doesn't take any input and returns the node number entered by the user.
*/
int TSP::Read_Node_Value_To_Delete()
{
	int delete_node;
	std::cout << "Available nodes are: " << std::endl;
	for (int i = 0; i < this->graph.size(); i++) {
		std::cout << i + 1 << std::endl;
	}
	std::cout << "Choose a node to delete: ";
	std::cin >> delete_node;
	return delete_node;
}

/*
* This method prints the shortest distance calculated and the corresponding traverse route.
* It has no inputs or outputs.
*/
void TSP::print()
{
	std::cout << std::endl;
	std::cout << "The shortest distance is: " << this->shortest_distance << " units" << std::endl;
	std::cout << "The route is: ";
	for (int i = 0; i < this->best_route.size(); i++) {
		std::cout << "->" << this->best_route[i] + 1;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

/*
* This is the constructor which intializes the graph to the default graph, the shortest distance to the max possible unsigned int value and
* totatl node available in the default graph.
*/
TSP::TSP()
{
	this->total_nodes_available = DEFAULT_NODES;
	this->shortest_distance = pow(2, sizeof(int) * 8) - 1;

	this->graph.push_back(std::vector<int> {0, 10, 15, 20});
	this->graph.push_back(std::vector<int> {10, 0, 35, 25});
	this->graph.push_back(std::vector<int> {15, 35, 0, 30});
	this->graph.push_back(std::vector<int> {20, 25, 30, 0});
}
