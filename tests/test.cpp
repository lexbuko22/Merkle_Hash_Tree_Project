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

// apples hash = 4065158538
// bananas hash = 1707924825
// chocolate hash = 1216302135
// ice cream hash = 3342531326
// hockey hash = 42484808

//apples + bananas hash = 2271817439
// chocolate + hockey = 2618300579
