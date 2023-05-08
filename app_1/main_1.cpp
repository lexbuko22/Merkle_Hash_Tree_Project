#include <iostream>
#include <fstream>
#include "/Users/lexbukowski/Documents/CSPB-2270/term-project-lexbuko22/code_1/HashTree.h"
using namespace std;

int main()
{

HashTree myHashTree;

cout << myHashTree.key_hash("car") << endl;


vector<string> data_1 = {"car","bike","train"};
vector<string> data_2 = {"hockey","formula 1","volleyball"};
vector<string> data_3 = {"hockey","volleyball","formula 1"};
vector<string> data_4 = {"car","bike","train","truck"};


cout<< myHashTree.Build_Hash_Tree(data_1) << endl;
cout << myHashTree.Add_Data_To_Tree("truck",data_1) << endl;
cout << myHashTree.Build_Hash_Tree(data_4) << endl;

if (myHashTree.Identical_Data(data_1,data_4))
{
    cout << "Data sets are identical" << endl;
}

else cout << "Data sets are not identical" << endl;


cout << myHashTree.Build_Hash_Tree(data_3) << endl;

if (myHashTree.Identical_Data(data_1,data_2))
{
    cout<< "Data sets are identical" << endl;
}

else cout << "Data sets are not identical" << endl;

if (myHashTree.Identical_Data(data_2,data_3))
{
    cout<< "Data sets are identical" << endl;
}

else cout << "Data sets are not identical" << endl;

return 0;
}
