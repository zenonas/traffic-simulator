#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
 
using namespace rapidxml;
using namespace std;
 
int main()
{
	cout << "Parsing my road..." << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("xmlfile.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Map");
	// Iterate over the brewerys
	for (xml_node<> * road_node = root_node->first_node("Road"); road_node; road_node =road_node->next_sibling("Road"))
	{
        printf("This is the road %s\n",road_node->first_attribute("name")->value());
        for (xml_node<> * node_node = road_node->first_node("Node"); node_node; node_node =node_node->next_sibling("Node"))
	    {  
             printf("This is node %s \n",node_node->first_attribute("name")->value());
     	      for (xml_node<> * point_node = node_node->first_node("Point"); point_node; point_node =point_node->next_sibling("Point"))
	          {
                  	printf(" %s=%s\n",point_node->first_attribute("name")->value(), point_node->value());
              }
      
       }
        for (xml_node<> * length= road_node->first_node("Length"); length; length=length->next_sibling())
	        printf("Length :%s \n",length->value());
     
      cout<<endl;
	}
	getchar();
    return 0;
}
