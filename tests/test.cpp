// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/HashTree.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////




std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////
TEST_F(test_x,key_hash){
HashTree myHashTree;
unsigned int h = myHashTree.key_hash("test");
ASSERT_EQ(h,2090756197);
}

TEST_F(test_x,internal_hash){

}

TEST_F(test_x,init_tree_node){
HashTree myHashTree;
shared_ptr<hash_tree_node> n = myHashTree.init_tree_node("test");
ASSERT_EQ(n->key,"test");
ASSERT_EQ(n->hashcode,2090756197);
}

TEST_F(test_x, init_data_set){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
ASSERT_TRUE(data_set.empty());
}

TEST_F(test_x,insert){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("apples",data_set);
ASSERT_FALSE(data_set.empty());
ASSERT_EQ(data_set.size(),1);
}

TEST_F(test_x,create_internal_node){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("apples",data_set);
myHashTree.Insert("bananas",data_set);
shared_ptr<hash_tree_node> internal_node = myHashTree.create_internal_node(data_set[0],data_set[1]);
ASSERT_EQ(internal_node->hashcode,2271817439);
}

TEST_F(test_x,internal_node_order){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("bananas",data_set);	
myHashTree.Insert("apples",data_set);
shared_ptr<hash_tree_node> internal_node = myHashTree.create_internal_node(data_set[0],data_set[1]);
ASSERT_EQ(internal_node->hashcode,2271817439);
}

TEST_F(test_x,create_parent_nodes){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("bananas",data_set);	
myHashTree.Insert("apples",data_set);
myHashTree.Insert("chocolate",data_set);
myHashTree.Insert("ice cream",data_set);
myHashTree.Insert("hockey",data_set);
vector<shared_ptr<hash_tree_node>> parent_nodes = myHashTree.hash_nodes_together(data_set);

ASSERT_EQ(parent_nodes.size(),3);
ASSERT_EQ(parent_nodes[0]->hashcode,2271817439);
ASSERT_EQ(parent_nodes[0]->key,"applesbananas");
ASSERT_EQ(parent_nodes[0]->left->key,"apples");
ASSERT_EQ(parent_nodes[0]->right->key,"bananas");
ASSERT_EQ(parent_nodes[0]->is_leaf,false);
ASSERT_EQ(parent_nodes[1]->hashcode,2618300579);
ASSERT_EQ(parent_nodes[1]->key,"chocolatehockey");
ASSERT_EQ(parent_nodes[1]->left->key,"chocolate");
ASSERT_EQ(parent_nodes[1]->right->key,"hockey");
ASSERT_EQ(parent_nodes[1]->is_leaf,false);
ASSERT_EQ(parent_nodes[2]->key,"ice cream");
ASSERT_EQ(parent_nodes[2]->hashcode,3342531326);
ASSERT_EQ(parent_nodes[2]->is_leaf,true);
ASSERT_EQ(parent_nodes[2]->left,nullptr);
ASSERT_EQ(parent_nodes[2]->right,nullptr);
}

TEST_F(test_x,make_tree){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("bananas",data_set);	
myHashTree.Insert("apples",data_set);
myHashTree.Insert("chocolate",data_set);
myHashTree.Insert("ice cream",data_set);
myHashTree.Insert("hockey",data_set);
shared_ptr<hash_tree_node> top_node = myHashTree.create_hash_tree(data_set);

ASSERT_EQ(top_node->hashcode,351600701);
ASSERT_EQ(top_node->key,"applesbananaschocolatehockeyice cream");
ASSERT_EQ(top_node->is_leaf,false);
ASSERT_EQ(top_node->left->key,"applesbananaschocolatehockey");
ASSERT_EQ(top_node->right->key,"ice cream");
}

TEST_F(test_x,root_hash){
HashTree myHashTree;
vector<shared_ptr<hash_tree_node>> data_set = myHashTree.init_data_set();
myHashTree.Insert("bananas",data_set);	
myHashTree.Insert("apples",data_set);
myHashTree.Insert("chocolate",data_set);
myHashTree.Insert("ice cream",data_set);
myHashTree.Insert("hockey",data_set);
shared_ptr<hash_tree_node> top_node = myHashTree.create_hash_tree(data_set);
unsigned int root_hash = myHashTree.Top_Hash(top_node);

ASSERT_EQ(root_hash,351600701);
ASSERT_EQ(root_hash,top_node->hashcode);
}

TEST_F(test_x,full_stack){
vector<string> data_set_animals = {"dog","cat","cow","pig","horse"};
HashTree animalHashTree;
vector<shared_ptr<hash_tree_node>> animal_data_set_nodes = animalHashTree.init_data_set();

for (int i = 0; i < data_set_animals.size(); i++)
{
	animalHashTree.Insert(data_set_animals[i],animal_data_set_nodes);
}
unsigned int animal_root_hash = animalHashTree.create_hash_tree(animal_data_set_nodes)->hashcode;


vector<string> data_set_animals_same = {"dog","cat","cow","horse","pig"};
HashTree animalHashTree_same;
vector<shared_ptr<hash_tree_node>> animal_data_set_same_nodes = animalHashTree.init_data_set();
for (int i = 0; i < data_set_animals_same.size(); i++)
{
	animalHashTree_same.Insert(data_set_animals_same[i],animal_data_set_same_nodes);
}
unsigned int animal_root_hash_same = animalHashTree_same.create_hash_tree(animal_data_set_same_nodes)->hashcode;


vector<string> data_set_sports = {"hockey","football","australian football","basketball","yoga"};
HashTree sportsHashTree;
vector<shared_ptr<hash_tree_node>> sports_nodes = sportsHashTree.init_data_set();
for (int i = 0; i < data_set_sports.size(); i++)
{
	sportsHashTree.Insert(data_set_sports[i],sports_nodes);
}
unsigned int sports_root_hash = sportsHashTree.create_hash_tree(sports_nodes)->hashcode;


ASSERT_EQ(animalHashTree.create_hash_tree(animal_data_set_nodes)->key,"catcowdoghorsepig");
ASSERT_EQ(animal_root_hash,animal_root_hash_same);
ASSERT_NE(sports_root_hash,animal_root_hash);
}

TEST_F(test_x,Create_Top_Hash){
	HashTree myHashTree;
	unsigned int func_val = myHashTree.Build_Hash_Tree({"hockey","football","australian football","basketball","yoga"});
	vector<string> data_set_sports = {"hockey","football","australian football","basketball","yoga"};
	HashTree sportsHashTree;
	vector<shared_ptr<hash_tree_node>> sports_nodes = sportsHashTree.init_data_set();
	for (int i = 0; i < data_set_sports.size(); i++)
	{
		sportsHashTree.Insert(data_set_sports[i],sports_nodes);
	}
	unsigned int sports_root_hash = sportsHashTree.create_hash_tree(sports_nodes)->hashcode;

	ASSERT_EQ(func_val,sports_root_hash);

}

TEST_F(test_x,Is_Identical){
	HashTree myHashTree;
	vector<string> sports = {"hockey", "football","soccer", "yoga"};
	vector<string> sports_2 = {"hockey", "yoga", "soccer", "football"};
	vector<string> prem_league_teams {"Brentford","The rest don't matter"};
	vector<string> empty_vec = {};
	bool test_1 = myHashTree.Identical_Data(sports,sports_2);
	bool test_2 = myHashTree.Identical_Data(sports, prem_league_teams);
	bool test_3 = myHashTree.Identical_Data(prem_league_teams,prem_league_teams);
	bool test_4 = myHashTree.Identical_Data(sports,empty_vec);
	bool test_5 = myHashTree.Identical_Data(empty_vec,empty_vec);

	ASSERT_TRUE(test_1);
	ASSERT_FALSE(test_2);
	ASSERT_TRUE(test_3);
	ASSERT_FALSE(test_4);
	ASSERT_TRUE(test_5);
}

TEST_F(test_x,Add_Data_To_Tree){
	HashTree myHashTree;
	vector<string> data_set = {"apples"};
	string new_data = "bananas";
	unsigned int hash_val_apples = myHashTree.key_hash("apples");
	unsigned int hash_val_bananas = myHashTree.key_hash("bananas");
	unsigned int hash_val_combined = myHashTree.key_hash(to_string(hash_val_apples) + to_string(hash_val_bananas));
	ASSERT_EQ(hash_val_combined,myHashTree.Add_Data_To_Tree(new_data,data_set));
}


// apples hash = 4065158538
// bananas hash = 1707924825
// chocolate hash = 1216302135
// ice cream hash = 3342531326
// hockey hash = 42484808

//apples + bananas hash = 2271817439
// chocolate + hockey = 2618300579

//applesbananas + chocolatehockey = 1899416666

//applesbananaschocolatehockey + ice cream = 351600701
