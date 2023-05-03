#ifndef HASH_H__
#define HASH_H__

#include <string>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct hash_tree_node {

  // key is the key the user provides to hash
  std::string key;

  //Hashed value
  unsigned int hashcode;

  //Left child
  shared_ptr<hash_tree_node> left;

  //Right child
  shared_ptr<hash_tree_node> right;

  //Is leaf? Leafs contain the data
  bool is_leaf;

};


// DJB2 is a hash function that hashes strings and gives an unsigned
// integer hash code that could take on any value in the 32-bit
// unsigned integer range. It is the hashing function used in this implementation.
unsigned int DJB2(std::string key);


class HashTree {
public:
  HashTree();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~HashTree();

  //Creates hash value of string;
  unsigned int key_hash(std::string key);

  //Initializes hash_tree_node
  shared_ptr<hash_tree_node> init_tree_node(std::string key);

  //Initialize data_set vector
  vector<shared_ptr<hash_tree_node>> init_data_set();  
  
  //Adds node to data set vector in ascending order
  void add_to_data_set(shared_ptr<hash_tree_node> new_data,vector<shared_ptr<hash_tree_node>> &data_set);

  //Create internal hash tree node of either leaf nodes containing data, or internal nodes of data hashes
  shared_ptr<hash_tree_node> create_internal_node(shared_ptr<hash_tree_node> a, shared_ptr<hash_tree_node> b);

  //Hash the leaves of the tree together into a tree level of parent nodes
  vector<shared_ptr<hash_tree_node>> hash_nodes_together(vector<shared_ptr<hash_tree_node>> data);

  //Create hash tree from all of the data in the data_set
  shared_ptr<hash_tree_node> create_hash_tree(vector<shared_ptr<hash_tree_node>> data_set);

  //Returns the top hash of the hash tree for comprison
  unsigned int Top_Hash(shared_ptr<hash_tree_node> top_hash);

  //Inserts a string value into the data set
  void Insert(std::string key, vector<shared_ptr<hash_tree_node>> &data_set);

  //Compares to vectors of string data using the hash tree data structure to determine if the data is identical.
  //Returns truee if identical, false if not. Data is case sensitive but not order sensative
  bool Identical_Data(vector <string> data_1, vector<string> data_2);

  //Add_Key allows the user to add a key to the hash tree values and rehash the tree, creating a new
  //top hash value.
  unsigned int Build_Hash_Tree(vector<string> key);

  //Create function to see all the keys hashed


  // you can add add more public member variables and member functions here if you need

private:
  // you can add add more private member variables and member functions here if you need

};


#endif  // HASH_H__