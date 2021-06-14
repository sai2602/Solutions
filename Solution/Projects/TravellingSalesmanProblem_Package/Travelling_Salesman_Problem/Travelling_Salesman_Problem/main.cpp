// TravellingSalesmanProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "TSP.h"

int main()
{
    TSP Distance_Calculator;
    std::vector<int> new_node;
    int node_to_delete;
    char user_option;

    //Print the default graph which was constructed when the object was created.
    Distance_Calculator.Return_Current_Graph_Information();

    //Print the shortest distance and the route for this default graph.
    if (Distance_Calculator.Calculate_Shortest_Distance()) {
        Distance_Calculator.print();
    }

    //Run continuously to read user data for further operations and terminate when the corresponding character is entered.
    do {
        //Print the help document to display user options and read the choice from console..
        Distance_Calculator.Help();
        std::cin >> user_option;

        /*
        * char 'a' signifies new node is to be appended
        * char 'd' signifies a node is to be deleted
        * char 'e' or any other char signifies termination of the program
        */
        switch (user_option) {
        case 'a':
            new_node.clear();
            new_node = Distance_Calculator.Read_New_Node_Values();
            if (Distance_Calculator.Add_Node(new_node)) {
                std::cout << "New node added to the graph." << std::endl;
                Distance_Calculator.Return_Current_Graph_Information();
                if (Distance_Calculator.Calculate_Shortest_Distance()) {
                    Distance_Calculator.print();
                }
            }
            else {
                std::cout << "Node could not be added due to invalid information (0 or negative number entered)." << std::endl;
            }
            break;
        case 'd':
            node_to_delete = Distance_Calculator.Read_Node_Value_To_Delete();
            if (Distance_Calculator.Delete_Node(node_to_delete)) {
                std::cout << "Deleted the node from the graph." << std::endl;
                Distance_Calculator.Return_Current_Graph_Information();
                if (Distance_Calculator.Calculate_Shortest_Distance()) {
                    Distance_Calculator.print();
                }
            }
            else {
                std::cout << "Could not find the node number." << std::endl;
            }
            break;
        default:
            std::cout << "Terminating the code due to invalid or 'e' character input" << std::endl;
            break;
        }
    } while (user_option == 'a' || user_option == 'd');

    return 0;
}
