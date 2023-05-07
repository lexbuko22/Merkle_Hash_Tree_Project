#include <iostream>
#include <fstream>
#include "/Users/lexbukowski/Documents/CSPB-2270/term-project-lexbuko22/code_1/HashTree.h"
using namespace std;

int main()
{

HashTree myHashTree;
vector<string> data_1 = {"car","bike","train"};
vector<string> data_2 = {"hockey","formula 1","volleyball"};
cout << myHashTree.Add_Data_To_Tree("truck",data_1) << endl;

vector<string> data_3 = {"car","bike","train","truck"};
cout << myHashTree.Build_Hash_Tree(data_3) << endl;

if (myHashTree.Identical_Data(data_1,data_2))
{
    cout<< "Data sets are identical";
}

else cout << "Data sets are not identical";


return 0;
}
