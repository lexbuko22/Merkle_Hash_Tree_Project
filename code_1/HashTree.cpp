#include "HashTree.h"

// constructor, initialize class variables and pointers here if need.
HashTree::HashTree(){
  // your code here
}

//deconstructor,
HashTree::~HashTree(){
}

unsigned int HashTree :: Build_Hash_Tree(vector<string> data){

    if (data.empty())
    {
        cout << "Please enter data to create the Hash Tree" << endl;
        return 0;
    }

    vector<shared_ptr<hash_tree_node>> hash_data = init_data_set();

    for (int i = 0; i < data.size(); i++)
    {
	   Insert(data[i],hash_data);
    }

    unsigned int top_hash = create_hash_tree(hash_data)->hashcode;
    
    return top_hash;
}

bool HashTree :: Identical_Data(vector <string> data_1, vector<string> data_2){

    if (data_1.empty() && data_2.empty())
    {
        return true;
    }
    
    else if (data_1.empty() || data_2.empty())
    {
        return false;
    }
    
    unsigned int hash_data_1 = Build_Hash_Tree(data_1);
    unsigned int hash_data_2 = Build_Hash_Tree(data_2);

    if (hash_data_1 == hash_data_2)
    {
        return true;
    }
    return false;
}


unsigned int HashTree:: Add_Data_To_Tree(string new_data, vector<string> &old_data){
    old_data.push_back(new_data);
    return Build_Hash_Tree(old_data);
}

//Creates hash value from sting key input. DJB2 hash funciton is used. This
//can be changed by changing DJB2 call below to another hash function.
unsigned int HashTree :: key_hash(std::string key){
    return DJB2(key);
}





/////////////////////////////////////////////////////////////////////////////////
//BELOW ARE PRIVATE MEMBER FUNCTIONS THAT ARE LEFT PUBLIC FOR THE PURPOSE OF UNIT
//TESTING AND DEMONSTRATING FUNCTIONALITY
/////////////////////////////////////////////////////////////////////////////////






//Initializes new hash tree node. This node can be added to the data_set
shared_ptr<hash_tree_node> HashTree :: init_tree_node(std::string key){
    shared_ptr<hash_tree_node> new_node(new hash_tree_node);
    new_node->key = key;
    new_node->hashcode = key_hash(key);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->is_leaf = true;
    return new_node;
}

//Initializes data set
vector<shared_ptr<hash_tree_node>> HashTree :: init_data_set(){
    vector<shared_ptr<hash_tree_node>> data_set;
    return data_set;
}

//Helper function to store node in data set in ascending order so that data set of a,b = b,a
void HashTree :: add_to_data_set(shared_ptr<hash_tree_node> new_data, vector<shared_ptr<hash_tree_node>> &data_set){
    int data_len = data_set.size();
    for (int i = 0; i < data_len; i++)
    {
        if (new_data->key <= data_set[i]->key)
        {
            data_set.insert(data_set.begin() + i,new_data);
            return;
        } 
    }
    data_set.push_back(new_data);
}

// Hash the two children together to create new internal node
shared_ptr<hash_tree_node> HashTree :: create_internal_node(shared_ptr<hash_tree_node> a, shared_ptr<hash_tree_node> b){
    string combined_val = to_string(a->hashcode) + to_string(b->hashcode);
    unsigned int new_hash_val = key_hash(combined_val);
    shared_ptr<hash_tree_node> internal_node = init_tree_node(a->key + b->key);
    internal_node->hashcode = new_hash_val;
    internal_node->left = a;
    internal_node->right = b;
    internal_node ->is_leaf = false;
    return internal_node;
}


//Insert a string key value into the data set. Data is input as a string and helper functions
//create a tree node and add the tree node to the data set.
void HashTree :: Insert(std::string key, vector<shared_ptr<hash_tree_node>> &data_set){
    shared_ptr<hash_tree_node> new_node = init_tree_node(key);
    add_to_data_set(new_node,data_set);
}

//Helper function to hash together internal nodes or leaves
 vector<shared_ptr<hash_tree_node>> HashTree::hash_nodes_together(vector<shared_ptr<hash_tree_node>> data){
    vector<shared_ptr<hash_tree_node>> new_parents;
    int i = 0; //index of new_parent vector
    while (data.size() > 1)
    {
        shared_ptr<hash_tree_node> temp = create_internal_node(data[0], data[1]);
        new_parents.insert(new_parents.begin()+ i,temp);
        data.erase(data.begin());
        data.erase(data.begin());
        i = i + 1;   
    }

    if (data.size() == 1)
    {
        new_parents.push_back(data[0]);
    }
    
    return new_parents;
 }

//Hash all nodes together to create root hash node
shared_ptr<hash_tree_node> HashTree::create_hash_tree(vector<shared_ptr<hash_tree_node>> data_set){
   
    vector<shared_ptr<hash_tree_node>> next_parents;
    next_parents = hash_nodes_together(data_set);
    vector<shared_ptr<hash_tree_node>> next_parents_copy = next_parents;
    while (next_parents.size() > 1)
    {
        next_parents.clear();
        next_parents = hash_nodes_together(next_parents_copy);
        next_parents_copy = next_parents;
    }
    return next_parents[0];
}

unsigned int HashTree :: Top_Hash(shared_ptr<hash_tree_node> top_hash){
    return top_hash->hashcode;
}



unsigned int DJB2(std::string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}






