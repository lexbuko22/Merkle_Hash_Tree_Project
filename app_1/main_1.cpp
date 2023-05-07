#include <iostream>
#include <fstream>

using namespace std;


/*
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
*/
int main()
{

//cout << DJB2(to_string(1899416666)+to_string(3342531326));
return 0;
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