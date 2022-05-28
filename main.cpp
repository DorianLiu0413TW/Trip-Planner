#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

int miniDist(float distance[], bool visited[], int totalPlaces) // finding minimum distance
{
    int minimum = INT_MAX, index;

    for (int k = 0; k < totalPlaces; k++)
    {
        if (visited[k] == false && distance[k] <= minimum)
        {
            minimum = distance[k];
            index = k;
        }
    }
    return index;
}

vector<int> Dijkstra(vector<vector<float>> graph, int origin, int destination, int totalPlaces) // adjacency matrix
{
    float distance[totalPlaces]; // array to calculate the minimum distance for each node
    bool visited[totalPlaces]; // boolean array to mark visited and unvisited for each node
    vector<int> path;
    // initialize distance to INT_MAX
    for (int k = 0; k < totalPlaces; k++)
    {
        distance[k] = INT_MAX;
        visited[k] = false;
    }

    distance[origin] = 0; // Source vertex distance is set 0

    for (int k = 0; k < totalPlaces; k++)
    {
        int m = miniDist(distance, visited, totalPlaces);
        path.push_back(m);
        if (m == destination)
        {
            return path;
        }
        // cout << "min dist: " << m << endl;
        visited[m] = true;
        for (int k = 0; k < totalPlaces; k++)
        {
            // updating the distance of neighbor vertex
            if (!visited[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k])
            {
                distance[k] = distance[m] + graph[m][k];
                // cout << "distance: " << distance[k] << endl;
            }
        }
    }
    cout << "Vertex\t\tDistance from source vertex" << endl;
    for (int k = 0; k < totalPlaces; k++)
    {
        cout << k << "\t" << distance[k] << endl;
    }
    return path;
}

vector<int> maxProductDijkstra(vector<vector<float>> graph, int origin, int destination, int totalPlaces) // adjacency matrix
{
    float distance[totalPlaces]; // array to calculate the minimum distance for each node
    bool visited[totalPlaces]; // boolean array to mark visited and unvisited for each node
    vector<int> path;
    // initialize distance to INT_MAX
    for (int k = 0; k < totalPlaces; k++)
    {
        distance[k] = INT_MAX;
        visited[k] = false;
    }

    distance[origin] = 0; // Source vertex distance is set 0

    for (int k = 0; k < totalPlaces; k++)
    {
        int m = miniDist(distance, visited, totalPlaces);
        path.push_back(m);
        if (m == destination)
        {
            return path;
        }
        cout << "min dist: " << m << endl;
        visited[m] = true;
        for (int k = 0; k < totalPlaces; k++)
        {
            // updating the distance of neighbor vertex
            if (!visited[k] && graph[m][k] && distance[m] != INT_MAX && abs(log(distance[m])) + abs(log(graph[m][k])) < abs(log(distance[k])))
            {
                distance[k] = abs(log(distance[m])) + abs(log(graph[m][k]));
                cout << "distance: " << distance[k] << endl;
            }
        }
    }
    cout << "Vertex\t\tDistance from source vertex" << endl;
    for (int k = 0; k < totalPlaces; k++)
    {
        cout << k << "\t\t\t" << distance[k] << endl;
    }
    return path;
}

vector<float> getNumberFromString(string s)
{
    vector<float> result;
    stringstream str_strm;
    str_strm << s;
    string temp_str;
    float temp_int;
    while (!str_strm.eof())
    {
        str_strm >> temp_str;
        if (stringstream(temp_str) >> temp_int)
        {
            // cout<<temp_int<<endl;
            result.push_back(temp_int);
        }
        temp_str = ""; // clear temp string
    }
    // for(int i=0; i<result.size(); i++){
    //     cout<<result[i]<<" ";
    // }
    // cout<<endl;
    return result;
}

int main()
{
    ifstream file("input.txt");
    string str;
    vector<vector<string>> infos;
    vector<vector<float>> timeGraph;
    vector<vector<float>> changingTimeGraph;
    vector<vector<float>> tendencyGraph;
    vector<vector<float>> changingTendencyGraph;
    vector<string> instructions;
    vector<int> path; // the traverse path of graph
    map<string, int> stringToNumber;
    map<string, int> changingStringToNumber;
    map<int, string> numberToString;
    map<int, string> changingNumberToString;
    map<string, int>::iterator stringToNumberIter;
    map<string, bool> state;
    map<string, bool>::iterator stateIter;
    string origin;
    int totalPlaces;
    int count = 1;
    while (getline(file, str))
    {
        // read number of places
        if (count == 1)
        {
            totalPlaces = stoi(str);
            // cout << "count: " << count << endl;
            // cout << "totalPlaces: " << totalPlaces << endl;
        }
        // read place number and preference value
        else if (1 < count && count <= totalPlaces * 1 + 1)
        {
            vector<string> temp;
            stringstream readInfos(str);
            string word;
            while (readInfos >> word)
            {
                // cout << word << endl;
                temp.push_back(word);
            }
            stringToNumber.insert(pair<string, int>(temp[1], count - 2));
            changingStringToNumber.insert(pair<string, int>(temp[1], count - 2));
            numberToString.insert(pair<int, string>(count - 2, temp[1]));
            changingNumberToString.insert(pair<int, string>(count - 2, temp[1]));
            state.insert(pair<string, bool>(temp[1], 1)); // initialize place state to true

            infos.push_back(temp);
            // cout << "count: " << count << endl;
            // cout << "str: " << str << endl;
        }
        // read distance weighted graph
        else if (totalPlaces * 1 + 1 < count && count <= 2 * totalPlaces + 1)
        {
            // cout << "count for timeGraph: " << count << endl;
            timeGraph.push_back(getNumberFromString(str));
            changingTimeGraph.push_back(getNumberFromString(str));
        }
        // read tendency weighted graph
        else if (totalPlaces * 2 + 2 < count && count <= 3 * totalPlaces + 2)
        {
            // cout << "count for tendencyGraph: " << count << endl;
            tendencyGraph.push_back(getNumberFromString(str));
            changingTendencyGraph.push_back(getNumberFromString(str));
        }
        // read instructions
        else if (count > 3 * totalPlaces + 2)
        {
            instructions.push_back(str);
        }
        count++;
    }

    /* operate instructions */
    for (int instruction = 0; instruction < instructions.size(); instruction++)
    {
        stringstream readInstructions(instructions[instruction]);
        string word;
        vector<string> inst;
        while (readInstructions >> word)
        { // inst[0] is instruction, inst[1] is place
            // cout << word << endl;
            inst.push_back(word);
        }
        if (inst[0] == "SET_ORIGIN")
        {
            if (state[inst[1]])
            {
                origin = inst[1];
                cout << inst[1] << " is the new origin" << endl;
            }
        }
        else if (inst[0] == "MARK_STATE")
        {
            for (int i = 2; i < inst.size(); i++)
            {
                if (inst[1] == "CLOSE" && !state[inst[i]]) // can not close closed place
                {
                    // cout << "cannot close closed place" << endl;
                    cout << "Fail to close " << inst[i] << endl;
                }
                else if (inst[1] == "OPEN" && state[inst[i]]) // can not reopen opened place
                {
                    // cout << "can not reopen opened place" << endl;
                    cout << "Fail to open " << inst[i] << endl;
                }
                else if (inst[1] == "CLOSE" && inst[i] == origin) // can not close origin
                {
                    // cout << "cannot close origin" << endl;
                    cout << "Fail to close " << inst[i] << endl;
                }
                else
                {
                    if (inst[1] == "CLOSE")
                    {
                        // cout << "valid close instruction" << endl;
                        state[inst[i]] = false;
                        // cout << "state: "<< inst[i] << " " << state[inst[i]] <<endl;
                        for (int j = 0; j < totalPlaces; j++)
                        {
                            cout << inst[i] << j << endl;
                            changingTimeGraph[j].erase(changingTimeGraph[j].begin()+stringToNumber[inst[i]]); // erase cloumn
                            changingTendencyGraph[j].erase(changingTendencyGraph[j].begin()+stringToNumber[inst[i]]); // erase cloumn
                        }
                        changingTimeGraph.erase(changingTimeGraph.begin() + stringToNumber[inst[i]]);
                        changingTendencyGraph.erase(changingTendencyGraph.begin()+stringToNumber[inst[i]]); // erase cloumn
                        
                        changingNumberToString.erase(stringToNumber[inst[i]]);
                        changingStringToNumber.erase(inst[i]);
                        
                        totalPlaces = totalPlaces - 1;
                        for (int a = 0; a < totalPlaces; a++)
                        {
                            for (int b = 0; b < totalPlaces; b++)
                            {
                                cout << changingTimeGraph[a][b] << " \t ";
                            }
                            cout << endl;
                        }
                        for (int a = 0; a < totalPlaces; a++)
                        {
                            for (int b = 0; b < totalPlaces; b++)
                            {
                                cout << changingTendencyGraph[a][b] << " \t ";
                            }
                            cout << endl;
                        }
                        
                    }
                    else if (inst[1] == "OPEN")
                    {
                        cout << "valid open instruction" << endl;
                        state[inst[i]] = true;
                        
                        for (int j = 0; j < totalPlaces; j++)
                        {
                            if (!state[inst[j]])
                            {
                                changingTimeGraph[stringToNumber[inst[i]]][j] = timeGraph[stringToNumber[inst[i]]][j];
                                changingTimeGraph[j][stringToNumber[inst[i]]] = timeGraph[j][stringToNumber[inst[i]]];
                                changingTendencyGraph[j][stringToNumber[inst[i]]] = tendencyGraph[j][stringToNumber[inst[i]]];
                                changingTendencyGraph[stringToNumber[inst[i]]][j] = tendencyGraph[stringToNumber[inst[i]]][j];
                            }
                        }
                        // for (int a = 0; a < totalPlaces; a++)
                        // {
                        //     for (int b = 0; b < totalPlaces; b++)
                        //     {
                        //         cout << changingTimeGraph[a][b] << " \t ";
                        //     }
                        //     cout << endl;
                        // }
                        // for (int a = 0; a < totalPlaces; a++)
                        // {
                        //     for (int b = 0; b < totalPlaces; b++)
                        //     {
                        //         cout << changingTendencyGraph[a][b] << " \t ";
                        //     }
                        //     cout << endl;
                        // }
                    }
                }
            }
        }
        else if (inst[0] == "OPTIMAL_PATH")
        {
            if (inst[2] == "TIME")
            {
                cout << "origin: " << stringToNumber[origin] << endl;
                cout << "destination: " << stringToNumber[inst[1]] << endl;
                path = Dijkstra(changingTimeGraph, stringToNumber[origin], stringToNumber[inst[1]], totalPlaces);
                cout << "Optimal TIME : ";
                for (int j = 0; j < path.size(); j++)
                {
                    if (j == path.size() - 1)
                    {
                        cout << numberToString[path[j]] << endl;
                    }
                    else
                    {
                        cout << numberToString[path[j]] << " -> ";
                    }
                }
            }
            else if (inst[2] == "FLOW")
            {
                // cout << "origin: " << stringToNumber[origin] << endl; // check origin
                cout << "origin: " << changingStringToNumber[origin] << endl;
                cout << "destination: " <<  changingStringToNumber[inst[1]] << endl;
                path = maxProductDijkstra(changingTendencyGraph, changingStringToNumber[origin], changingStringToNumber[inst[1]], totalPlaces);
                cout << "Optimal FLOW : ";
                for (int j = 0; j < path.size(); j++)
                {
                    if (j == path.size() - 1)
                    {
                        cout << numberToString[path[j]] << endl;
                    }
                    else
                    {
                        cout << numberToString[path[j]] << " -> ";
                    }
                }
            }
        }
        else if (inst[0] == "LIMITED_PATH")
        {
            int limit = stoi(inst[3]);
            if (inst[2] == "TIME")
            {
            }
            else if (inst[2] == "FLOW ")
            {
            }
        }
        else if (inst[0] == "END_OF_INSTRUCTION")
        {
            cout << "Stop receiving instructions" << endl;
        }
    }

    /* check read file state consistency */

    // cout<<count<<endl;
    // for(int i=0; i<totalPlaces; i++){
    //     cout<<infos[i]<<endl;
    // }
    // check place timeGraph double vector status
    // for(int i=0; i<totalPlaces; i++){
    //     for(int j=0; j<totalPlaces; j++){
    //         cout<<timeGraph[i][j]<<" ";
    //     }
    //     cout << endl;
    // }
    // check place tendencyGraph double vector status
    // for(int i=0; i<totalPlaces; i++){
    //     for(int j=0; j<totalPlaces; j++){
    //         cout<<tendencyGraph[i][j]<<" ";
    //     }
    //     cout << endl;
    // }
    // for(int i=0; i<instructions.size(); i++){
    //     cout<<instructions[i]<<endl;
    // }
    // check state map status
    // for(stateIter = state.begin(); stateIter != state.end(); stateIter++){
    // 	cout<<stateIter->first<<" "<<stateIter->second<<endl;
    // }
    // check place number
    // for(stringToNumberIter = placeNumber.begin(); placeNumberIter != placeNumber.end(); placeNumberIter++){
    // 	cout<<stringToNumberIter->first<<" "<<stringToNumberIter->second<<endl;
    // }
}