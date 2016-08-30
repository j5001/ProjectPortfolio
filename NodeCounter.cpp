#include <vector>
#include <iostream>

using namespace std;


struct TreeNode
{
    int idNumber;
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode()
    {
        idNumber = 0;
    }

    TreeNode(int inId)
    {
        idNumber = inId;
    }

    void insertTreeNode(int childValue)
    {
        TreeNode* newChild =  new TreeNode();
        newChild->idNumber = childValue;
        newChild->parent = this;
        (this->children).push_back(newChild);

        //cout << "made: " << newChild->idNumber << endl;
       // cout << "size: " << children.size() << endl;

    }

    void cousinInsert();

    //returns the reference of the node with the specified value in the treee
    TreeNode* findNode(int idOfNode)
    {
        //cout << idNumber << endl;

        // if this is the value we want, return the node
        if(idNumber == idOfNode)
        {
            return this;
        }
        // else for each of its children, search for this number
        else
        {
            //cout << "Size of Children Vector: " << children.size() << endl;
            //if(children.empty()==false)
                for(TreeNode* child: children)
                {

                        //cout << " in LOOP" << endl;
                        TreeNode* currentChild =  child->findNode(idOfNode);
                        if(currentChild != NULL)
                            return child;



                }

        }


        // if we still haven't found it from the children, return null, notify value not found
        //cout << "Value Not Found" << endl;
        return NULL;


    }

    //in order traversal print
    void printTree()
    {
        cout << idNumber << endl;

        if(children.empty()==false)
            {
            for(TreeNode* child: children)
            {
                if(child!= NULL)
                {
                    cout << child->idNumber << endl;
                    child->printTree();
                }
            }
        }
    }

    void printNode()
    {
        if(parent!=nullptr)
        {
            cout << "id:" << idNumber << " #ofChildren:" << children.size() << " parent:" << parent->idNumber  << endl;
        }

        else
            cout << "id:" << idNumber << " #ofChildren:" << children.size() << " parent:" << "none"  << endl;



    }

};

int countCousins(int desiredNodeValue, TreeNode* inTreeNodes[], int arraySize)
{
    TreeNode* desired = nullptr;
    for(int x =0; x<arraySize;x++)
    {
        if(inTreeNodes[x]->idNumber == desiredNodeValue)
            {
                desired = inTreeNodes[x];
                break;
            }
    }

    int cousinsSum = 0;

    if(desired == nullptr ||  desired->parent == nullptr ||  desired->parent->parent == nullptr)
    {
        return 0;
    }


    else
    {

        TreeNode* grandparent = desired->parent->parent;
        TreeNode* parent = desired->parent;
        for( int x=0; x<grandparent->children.size();x++)
            {
                if(grandparent->children[x] != parent)
                {
                     cousinsSum = cousinsSum + grandparent->children[x]->children.size();

                }

               // cout << cousinsSum << endl;

            }
    }



    //cout << desired->idNumber << endl;
    //cout << desired->parent->idNumber << endl;
    //cout << desired->parent-> parent->idNumber << endl;

    return cousinsSum;


}


int main()
{
    // read in number of nodes in tree
    int numberOfNodes;
    cin >> numberOfNodes;

    // read in value of interest
    int nodeOfInterest;
    cin >> nodeOfInterest;

    // create and popu.alte array containing all read in nodes
    TreeNode* inputNodes[numberOfNodes];

    if(numberOfNodes<3)
        {
            cout << "0";
            return 0;
        }

    int x;
    for(x=0;x<numberOfNodes;x++)
    {
     int y;
     cin >> y;
     inputNodes[x] = new TreeNode(y);

    }



    // determine parent sibling relationships

    // current node index being populated with children
    int currentNodeIndex = 0;
    TreeNode* currentNode = inputNodes[currentNodeIndex];

    //values of first and last nodes ( values not indecies)
    //int lastValue=-1; // -1 because there is no last value
    //int thisValue = inputNodes[0]->idNumber;



    //go through each node via for loop and add it to the proper node
    for(int z =0; z<numberOfNodes;z++)
    {

       // lastValue= thisValue;
       // thisValue = inputNodes[z]->idNumber;
        if(z==0)
        {
            z++;
            inputNodes[0]->children.push_back(inputNodes[z]);
            inputNodes[z]->parent = inputNodes[0];

           // cout << "currentNode:" << currentNode->idNumber << " added:" <<inputNodes[z]->idNumber << " itsParent:" << inputNodes[z]->parent->idNumber<< " currentNodeIndex:" << currentNodeIndex <<  " z:" << z << endl;

            z++;
        }
           // set current node to proper index (either stays the same or moves up one if its greater than one)


        if(inputNodes[z]->idNumber != inputNodes[z-1]->idNumber+1)
        {
            currentNodeIndex++;

        }
        currentNode = inputNodes[currentNodeIndex];


        currentNode->children.push_back(inputNodes[z]);
        inputNodes[z]->parent = currentNode;
        //cout << "currentNode:" << currentNode->idNumber << " added:" <<inputNodes[z]->idNumber << " itsParent:" << inputNodes[z]->parent->idNumber << " currentNodeIndex:" << currentNodeIndex <<  " z:" << z << endl;



    }

    int finalAnswer = countCousins(nodeOfInterest, inputNodes, numberOfNodes);
    //cout <<  nodeOfInterest << "     " << numberOfNodes << endl;
    cout << finalAnswer;



}
