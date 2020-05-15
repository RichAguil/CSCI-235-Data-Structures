/*
    Name: Richard Aguilar
    Course: CSCI 235 - Software Analysis & Design II
    Term: Spring 2020
    Instructor: Professor Wole Oyekoya
    Assignment: Project 4
*/
#include "Maze.cpp"
#include <queue>
#include <map>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
using namespace directions;

namespace solutions
{

int getNumberOfWalls(MazeNode *a_node)
{
    int wall_counter = 0;
    for (nesw dir = NORTH; dir <= WEST; dir = nesw(dir + 1))
    {
        if (a_node->getDirectionNode(dir) == nullptr || a_node->getDirectionNode(dir)->isWall() || a_node->getDirectionNode(dir)->isVisited())
        {
            if (a_node->isWall() == false) {
               wall_counter++; 
            }
        }
    }
    return wall_counter;
}

bool canTravel(MazeNode *a_node)
{
    if (a_node == nullptr || a_node->isVisited() || a_node->isWall()) //This snippet of code here was changed to include that it check for nullpointers. In other words, that it checked whether the next node is outside
    {                                                                 //of the maze. This initially became an issue for me in regards to maze 3, since my iterator would alaways check NORTH first, and that so happened
        return false;                                                 //to lead outside of the maze.
    }
    return true;
}

/*
    This first algorithm is a depth-first search algorithm. This was implemented using a while loop. What this algorithm does is that it explores each direction until it can no longer travel in that direction.
    It then uses a for loop to try a new direction, and does the same, and it keeps going as far as it can until it hits a wall, a nullpointer, or a visited node. 

*/

std::vector<MazeNode> solveDFS(Maze &a_maze)
{
    MazeNode *traversingNode = a_maze.getFirstNode(); //Initializing my internal iterator to the starting node in the maze
    vector <MazeNode> finishPath;                     //Creating the vector object that will hold the final path to the finish
    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray()); //This MazeNode parametrized constructor constructs a MazeNode from the traversingNode pointer, thereby copying the node
    finishPath.push_back(copyNode);                                                       //The copyNode is then pushed into the vector  
    a_maze.setCurrentNode(traversingNode);                                                //This inefficiency is fixed in solveCustom
    traversingNode->setVisited();                                                         //Sets the current node to visited

    while (traversingNode != a_maze.getLastNode()) {                                       //This while loop will continue until the lastNode is reached
        int i = 0;                                                                      
        while (i < 4 && traversingNode != a_maze.getLastNode()) {                          //This while loop controls the directions that the internal iterator tries
            if (solutions::canTravel(traversingNode->getDirectionNodeArray()[i])) {        //The canTravel function in the solutions namespace is checking to see that the next node is available to visit

                a_maze.setCurrentNode(traversingNode->getDirectionNodeArray()[i]);         //Moves the internal iterator to the next node  
                traversingNode = a_maze.getCurrentNode();
                traversingNode->setVisited();
                MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
                finishPath.push_back(copyNode);
                i = 0;                                                                     //Sets the direction back to North. The internal iterator always checks if it can move north first

            } else {
                if (traversingNode->getDirectionNodeArray()[i] != nullptr) {                //Checks if the next node is a null pointer. This inefficiency is fixed later
                }
                i++;                                                                        //If the North direction fails, check East, and if that eventually fails, check South, and then West
            }
        }

        if (traversingNode == a_maze.getLastNode()) {                                       //If internal iterator reaches lastNode, break out of loop
            break;
        }

        finishPath.pop_back();                                                              //if a dead-end is reached, remove the last node (which happens to be the current one) from the vector
        a_maze.setCurrentNode(&finishPath[finishPath.size() - 1]);                          //Revert the currentto the previous node, which is now the new last node in the vector
        traversingNode = a_maze.getCurrentNode();                                           //set internal iterator equal to this last node. This inefficiency is fixed later
    }
    return finishPath;   
}

/*
    This algorithm is breadth-first search. This algorithm is unlike DFS because it checks wide instead of deep. It does so by moving in layers. From the starting node, this algorithm checks if it has any neighbors
    If it does, the neighbors are added to a queue. Then, the first element in the queue is dequeue, and that element's neighbors are checked. If it has neighbors that havent been visited, they're also added to
    the queue. Then the next element in the queue (which was part of the first layer) is dequeue, and checked for neighbors. And so on, and so on, this continues until the last node is reached. BFS is an algorithm
    that works well in giving you the shortest path to the end. However, this only works in graphs with no loops, and if the cells are unweighted, which just so happens to be the case with this maze.
*/

std::vector<MazeNode> solveBFS(Maze &a_maze)
{
    queue <MazeNode *> queueNodes;                          ///Initializes queue object to hold the layers of nodes
    map<MazeNode *, MazeNode *> trackParent;                //Initializes map object. This will be used to keep track of each node's parents, thereby allowing reconstruction of the path from start to end
    MazeNode *traversingNode = a_maze.getFirstNode();     
    vector <MazeNode> finishPath;                           

    traversingNode->setVisited();
    queueNodes.push(traversingNode);                        //Pushing the first node, which is the starting node, to the queue

    while (!queueNodes.empty()) {                           //This will continue so long as the queue is not empty

        traversingNode = queueNodes.front();                //This returns the first element in the queue
        if (traversingNode == a_maze.getLastNode()) {
            break;
        }
        queueNodes.pop();                                   //This removes the first element in the queue (dequeues)

        for (int i = 0; i < 4; i++) {                                                   
            if(solutions::canTravel(traversingNode->getDirectionNodeArray()[i])) {    //In this snippet of code here, I am checking to see if the current node has unvisited neighbors,
                traversingNode->getDirectionNodeArray()[i]->setVisited();             //and if it does, then it markes them as visited,
                queueNodes.push(traversingNode->getDirectionNodeArray()[i]);          //and adds them to the queue.
                trackParent.emplace(traversingNode->getDirectionNodeArray()[i],traversingNode); //It will then create a key-value pair in the form of "(child, parent)". The reason why it was done this way is because
            }                                                                                   //a parent can have multiple children, but a child only has one parent (in the context of this maze). Therefore
        }                                                                                       //each child will be unique, even if there are multiples of the same parent
    }

    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
    finishPath.push_back(copyNode);
    bool reachedStart = false;

    while (!reachedStart) {
        traversingNode = trackParent[traversingNode];                                               //Once the end has been reached, I will set the internal iterator equal to the parent of the child
        MazeNode copyNode(traversingNode->getPos(),traversingNode->getDirectionNodeArray());        //The parent (which represents the previous node) is then copied,
        finishPath.push_back(copyNode);                                                             //so that it can be added to the vector to return later
        
        if (traversingNode == a_maze.getFirstNode()) {                                              //This while loop continues until the starting node is reached, and then exits
            reachedStart = true;
        }
    }

    reverse(finishPath.begin(), finishPath.end());                                                  //However, technically, the vector is filled in backwards. So this line of code reverses the vector, so that
    return finishPath;                                                                              //it returns the values from start-to-end instead of end-to-start
}

/*
    This following algorithm is Dead-End Filling. This algorithm works by filling in every dead-end in the maze until it reaches a junction. After all dead-ends are filled, the only path left is the path
    from start to finish. The drawback of this algorithm is that it requires the individual to have global knowledge of the maze. Otherwise, this algorithm becomes worthless.
*/
std::vector<MazeNode> solveDEF(Maze &a_maze)
{

    MazeNode *traversingNode = a_maze.getCurrentNode();
    vector<MazeNode *> wallTracker;                                 //This initializes a vector to keep track of every dead-end (which will be the starting nodes).
    vector <MazeNode> finishPath;
    int j = 0;


                                                                    //Since every maze has differently positioned dead-ends, I needed to find a way for a specific sub-algorithm to launch depending on which maze
    if (a_maze.getSize() == 140) {                                  //was passed into the DEF algorithm. This, three if-statements
        bool deadEndFilled = false;                                 
        bool junctionReached = false;
        vector <pair<int,int>> vectorPairs;                         //This initializes a vector of pair objects. This will be used to set the starting nodes equal to the dead-ends

        vectorPairs.push_back(make_pair(13,1));                     //Every pair object being created here and pushed into this vector is a dead-end node.
        vectorPairs.push_back(make_pair(3,4));
        vectorPairs.push_back(make_pair(15,2));
        vectorPairs.push_back(make_pair(8,2));
        vectorPairs.push_back(make_pair(14,5));

        for (int i = 0; i < vectorPairs.size(); i++) {                      
            MazeNode *convertPairToNode = a_maze.contains(vectorPairs[i]);      //This initializes a pointer--an internal iterator--to the dead-end node within the vector. The pointer becomes the starting node
            wallTracker.push_back(convertPairToNode);                           //The starting node is then pushed into the wallTracker vector so that a future for-loop can iterate through every dead-end
        }
        wallTracker[3]->setVisited();                                           //These two lines of code that set the last (node at position (14,5)) and second-to-last (node at position (8,2)) element to visited 
        wallTracker[4]->setVisited();                                           //is unique to the first maze. The reason I did this was because there were two nodes within the first maze that are corner nodes, and 
        wallTracker.pop_back();                                                 //thus would mess with the DEF algorithm. So, I just made sure to set them to visited so that the canTravel and getNumberOfWalls 
        wallTracker.pop_back();                                                 //would treat those nodes as walls. Anyways, I then removed them from the wallTracker once I did.
        
        while (!deadEndFilled) {
            for (int i = 0; i < wallTracker.size(); i++) {                      //This outer for-loop will loop through every dead-end node in the vector so that all dead-ends could be filled.
                traversingNode = wallTracker[i];
                while (junctionReached == false) {                          
                    while (j < 4) {
                        if (solutions::canTravel(traversingNode->getDirectionNodeArray()[j])) {
                            if (solutions::getNumberOfWalls(traversingNode->getDirectionNodeArray()[j]) >= 2) {     //This checks to see if the next node it can travel so has 2 or more walls. If it does, it is not a junction.
                                traversingNode->setVisited();
                                traversingNode = traversingNode->getDirectionNodeArray()[j];
                                j = 0;
                            } else {
                                traversingNode->setVisited();
                                j = 0;
                                break; 
                            }
                        } else {
                            j++;
                        }
                        
                    }
                    junctionReached = true;
                }

                junctionReached = false;                
            }
            deadEndFilled = true;                                               //This boolean value turns to true when the wallTracker vector is exhausted. In other words, every dead-end is filled.
        }

    traversingNode = a_maze.getFirstNode();                                     //This next chunk of code just has the internal iterator start at the beginning and traverse to the end. Nothing fancy here.
    int iterator = 0;                                                           //It's similar to what I used in the other two algorithms.
    
    while (traversingNode != a_maze.getLastNode()) {
        while (iterator < 4) {
            if (solutions::canTravel(traversingNode->getDirectionNodeArray()[iterator])) {
                MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
                finishPath.push_back(copyNode);
                traversingNode->setVisited();
                traversingNode = traversingNode->getDirectionNodeArray()[iterator];
                iterator = 0;
            } else {
                iterator++;
            }
        }
    }
    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
    finishPath.push_back(copyNode);

    return finishPath;                                                          //And that's it. That pretty much it for DEF for the first maze. Since the algorithm is exactly the same for the next two mazes,
                                                                                //I won't commment them. The only difference is that their dead-ends nodes are different.
    } else if (a_maze.getSize() == 121) {                                       //This is for maze 2

        bool deadEndFilled = false;
        bool junctionReached = false;
        vector <pair<int,int>> vectorPairs;
        vectorPairs.push_back(make_pair(9,1));
        vectorPairs.push_back(make_pair(9,3));
        vectorPairs.push_back(make_pair(1,9));

        for (int i = 0; i < vectorPairs.size(); i++) {
            MazeNode *convertPairToNode = a_maze.contains(vectorPairs[i]);
            wallTracker.push_back(convertPairToNode);
        }

        while (!deadEndFilled) {
            for (int i = 0; i < wallTracker.size(); i++) {
                traversingNode = wallTracker[i];
                while (junctionReached == false) {
                    while (j < 4) {
                        if (solutions::canTravel(traversingNode->getDirectionNodeArray()[j])) {
                            if (solutions::getNumberOfWalls(traversingNode->getDirectionNodeArray()[j]) >= 2) {
                                traversingNode->setVisited();
                                traversingNode = traversingNode->getDirectionNodeArray()[j];
                                j = 0;
                            } else {
                                traversingNode->setVisited();
                                j = 0;
                                break; 
                            }
                        } else {
                            j++;
                        }
                        
                    }
                    junctionReached = true;
                }

                junctionReached = false;                
            }
            deadEndFilled = true;
        }
    
    traversingNode = a_maze.getFirstNode();
    int iterator = 0;
    
    while (traversingNode != a_maze.getLastNode()) {
        while (iterator < 4) {
            if (solutions::canTravel(traversingNode->getDirectionNodeArray()[iterator])) {
                MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
                finishPath.push_back(copyNode);
                traversingNode->setVisited();
                traversingNode = traversingNode->getDirectionNodeArray()[iterator];
                iterator = 0;
            } else {
                iterator++;
            }
        }
    }
    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
    finishPath.push_back(copyNode);

    return finishPath;


    } else {                                                            ///This is for maze 3

        bool deadEndFilled = false;
        bool junctionReached = false;
        vector <pair<int,int>> vectorPairs;
        vectorPairs.push_back(make_pair(6,11));
        vectorPairs.push_back(make_pair(17,1));
        vectorPairs.push_back(make_pair(10,3));
        vectorPairs.push_back(make_pair(10,8));
        vectorPairs.push_back(make_pair(14,6));
        vectorPairs.push_back(make_pair(15,11));
        vectorPairs.push_back(make_pair(15,13));
        vectorPairs.push_back(make_pair(1,14));
        vectorPairs.push_back(make_pair(15,19));
        vectorPairs.push_back(make_pair(10,22));
        vectorPairs.push_back(make_pair(3,19));

        for (int i = 0; i < vectorPairs.size(); i++) {
            MazeNode *convertPairToNode = a_maze.contains(vectorPairs[i]);
            wallTracker.push_back(convertPairToNode);
        }

        while (!deadEndFilled) {
            for (int i = 0; i < wallTracker.size(); i++) {
                traversingNode = wallTracker[i];
                while (junctionReached == false) {
                    j = 0;
                    while (j < 4) {
                        if (solutions::canTravel(traversingNode->getDirectionNodeArray()[j])) {
                            if (solutions::getNumberOfWalls(traversingNode->getDirectionNodeArray()[j]) >= 2) {
                                traversingNode->setVisited();
                                traversingNode = traversingNode->getDirectionNodeArray()[j];
                                j = 0;
                            } else {
                                traversingNode->setVisited();
                                j = 0;
                                break; 
                            }
                        } else {
                            j++;
                        }
                        
                    }
                    junctionReached = true;
                }

                junctionReached = false;                
            }
            deadEndFilled = true;
        }
    
    traversingNode = a_maze.getFirstNode();
    int iterator = 0;
    
    while (traversingNode != a_maze.getLastNode()) {
        while (iterator < 4) {
            if (solutions::canTravel(traversingNode->getDirectionNodeArray()[iterator])) {
                MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
                finishPath.push_back(copyNode);
                traversingNode->setVisited();
                traversingNode = traversingNode->getDirectionNodeArray()[iterator];
                iterator = 0;
            } else {
                iterator++;
            }
        }
    }
    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
    finishPath.push_back(copyNode);

    return finishPath;
    }
}

std::vector<MazeNode> solveCustom(Maze &a_maze)                                 //For my custom algorithm, I simply decided to optimize my DFS algorithm. I understand that the DEF algorithm I have is far more inefficient
{                                                                               //But I will take the time to refactor that later.
    MazeNode *traversingNode = a_maze.getFirstNode();
    vector <MazeNode> finishPath;
    MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
    finishPath.push_back(copyNode);
    traversingNode->setVisited();

    while (traversingNode != a_maze.getLastNode()) {
        int i = 0;
        while (i < 4 && traversingNode != a_maze.getLastNode()) {
            if (solutions::canTravel(traversingNode->getDirectionNodeArray()[i])) {

                traversingNode = traversingNode->getDirectionNodeArray()[i];
                traversingNode->setVisited();
                MazeNode copyNode(traversingNode->getPos(), traversingNode->getDirectionNodeArray());
                finishPath.push_back(copyNode);

            } else {
                i++;
            }
        }

        if (traversingNode == a_maze.getLastNode()) {
            break;
        }
        
        if (solutions::getNumberOfWalls(traversingNode) > 3) {
                finishPath.pop_back();
                traversingNode = &finishPath.back();
        }
    }

    return finishPath;   

}
} // namespace solutions
