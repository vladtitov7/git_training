#include <iostream>
#include <string>
#include "my_vec.h"

using namespace std;

struct particle
{
  string partName;
  double mass;
  float charge;
  string type;
  int quarkNum;
};

int main()
{

  particle proton;
  proton.mass = 938.3;
  proton.charge = 1.0;
  proton.type = "hadron";
  proton.quarkNum = 3;
  proton.partName = "proton";

  particle neutron;
  neutron.mass = 939.6;
  neutron.charge = 0;
  neutron.type = "hadron";
  neutron.quarkNum = 3;
  neutron.partName = "neutron";

  MyVector<particle> part_vec;
  part_vec.push_back(neutron);
  part_vec.push_back(proton);

  cout <<"Number of particles in vector: " << part_vec.getSize() << endl;

  for(int i = 0; i < part_vec.getSize(); ++i)
    {
      cout << part_vec.at(i).partName << endl;
      cout << part_vec.at(i).charge << endl;
      cout << part_vec.at(i).mass << endl;
      cout << part_vec[i].type << endl << endl;
    }

  /*
  for(int i = 0; i < 20; i++)
    {
      vec.push_back(i);
    }
  for(int i = 0; i < vec.getSize(); i++)
    {
      cout << "i = " << i << " vec = " << vec.at(i) << endl;
    }
  cout << "number of elements is " << vec.getSize() << endl;
  //cout << "15 element is " << vec.at(15) << endl;
  //cout << "65 element is " << vec.at(65) << endl;
  cout << "19 element is " << vec[19] << endl;
  // cout << "70 element is " << vec.at(70) << endl;
   cout << "100 element is " << vec.at(100) << endl;
  //cout << "75 element is " << vec[75] << endl;
  */
  return 0;
}
