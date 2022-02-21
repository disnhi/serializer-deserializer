/* 
Notes to self: Need to implement...
  - text serializer
  - binary serializer
  - binary deserializer
 */

#include "bakery.hpp"
#include <fstream>
#include <sstream> //for converting string to ints
#include <iostream>
#include <cstring>
#include <unordered_map> //for the hash map of binary value conversion

void print_bakery(const Bakery& bakery) {
  std::cout << "Employees: " << std::endl;
  for (auto employee : bakery.employees) {
    std::cout << employee << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Items: " << std::endl;
  for (auto item : bakery.items) {
    std::cout << item.name << ", " << item.price << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Orders: " << std::endl;
  for (auto order : bakery.orders) {
    std::cout << order.employee << ": ";
    auto j = 0;
    for (auto item : order.items) {
      std::cout << item.second << " " << item.first;
      j++;
      if (size_t(j) < order.items.size())
        std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

// You shouldn't need to edit this function (unless you want!)
Bakery text_deserializer(std::string file_path) {
  std::ifstream infile(file_path);
  std::string line;
  Bakery bakery;

  while (!infile.eof()) {
    // Employees section
    if (line.compare("@employees") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        bakery.employees.push_back(line);
        std::getline(infile, line);
      }
    }

    // Items section
    if (line.compare("@items") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        auto end = line.find(", ");
        Item item;
        item.name = line.substr(0, end);
        item.price = line.substr(end + 2);
        bakery.items.push_back(item);
        std::getline(infile, line);
      }
    }

    // Orders section
    if (line.compare("@orders") == 0) {
      std::getline(infile, line);
      auto e = bakery.employees;
      while (line.size() > 0) {
        Order order;
        auto end = line.find(": ");
        order.employee = line.substr(0, end);

        // Find all the orders
        auto rest = line.substr(end + 2);
        size_t pos = 0;
        std::string token;
        while ((pos = rest.find(", ")) != std::string::npos) {
          token = rest.substr(0, pos);
          end = token.find(" ");
          auto quantity = token.substr(0, end);
          auto item_name = token.substr(end + 1);
          order.items.push_back(std::make_pair(item_name, quantity));
          rest.erase(0, pos + 2);
        }
        end = rest.find(" ");
        auto quantity = rest.substr(0, end);
        auto item_name = rest.substr(end + 1);
        order.items.push_back(std::make_pair(item_name, quantity));
        bakery.orders.push_back(order);

        // no more lines to read
        if (infile.eof())
          break;

        std::getline(infile, line);
      }
    }

    std::getline(infile, line);
  }

  return bakery;
}

// Implement these 3 functions!
// Hint: use print_bakery to help think about the text serializer
void text_serializer(const Bakery& bakery, std::string file_path) { 
  
  std::ofstream file(file_path); 

  // Initializing strings for serialization
  std::string employeeNames = "@employees\n";
  std::string listOfItems = "@items\n";
  std::string listOfOrders = "@orders\n";

  // Concatenating the employees instance from the bakery class
  // into a string
  for (int i = 0; i<(bakery.employees).size(); i++) {

    employeeNames.append(bakery.employees[i] + "\n"); // Adding employee's name to dictionary string

  }
  employeeNames.append("\n"); // to replicate layout of original text files
  file << employeeNames; // Adding serialized employees to output file


  // Concatenating the item struct into a string by adding name of
  // item and price in format given by original text files
  for (int i=0; i<(bakery.items).size(); i++) {

    listOfItems.append(bakery.items[i].name + ", " + bakery.items[i].price + "\n");

  }
  listOfItems.append("\n"); // to replicate layout of original text files
  file << listOfItems; // Adding serialized Items to output file

  // Concatenating the order struct into a string
  for (int i=0; i<(bakery.orders).size(); i++) {
    
    // Starting a new array for each employee order combo
    listOfOrders.append(bakery.orders[i].employee + ":");

    // Adding the actual order by iterating through the item pair
    // which tells us what items and how many of it are in each order
    for (const std::pair<std::string,std::string>& x: bakery.orders[i].items){
      
      // adding the order pairs to the corresponding employee's name
      listOfOrders.append(x.second + " " + x.first + ","); 

    }
    listOfOrders.pop_back(); //getting rid of last ',' 
    listOfOrders.append("\n");
  }
  listOfOrders.append("\n"); // to replicate layout of the original text files
  std::cout<<listOfOrders;

  // Adding serialized orders to output file
  file << listOfOrders;

  return;
}

// Format doesn't matter, just need to get back to that format after serialization
Bakery binary_deserializer(std::string file_path) {

  // Hash map to go from serialized to text
  std::unordered_map<short int, std::string> umap;

  // Employees     
  umap[0] =  "Brad";
  umap[1] = "Claudia";
  umap[2] = "Simone";

  // Item names
  umap[3] = "Biscuit";
  umap[4] = "Bun";
  umap[5] = "Brownie";
  umap[6] = "White Loaf";
  umap[7] = "Wheat Loaf";

  // Item prices
  umap[8] = "3.50";
  umap[9] = "0.99";
  umap[10] = "4.75";
  umap[11] = "7.50";
  umap[12] = "8.25";

  // Quantity 
  umap[13] = "1"; 
  umap[14] = "2";
  umap[15] = "3";
  umap[16] = "4";
  umap[17] = "5";
  umap[18] = "6";
  umap[19] = "7";
  umap[20] = "8";
  umap[21] = "9";
  
  // Reading in from binary file 
  std::ifstream infile;

  //Initializing variables
  short int curr;
  Bakery bakery;

  std::vector<std::string> employeeList; 
  std::vector<Item> itemList;
  std::vector<Order> orderList;

  // Opening file
  infile.open(file_path, std::ios::binary);

  // Reading employee names (since number of employees are constant
  // across all 3 files)

  // std::cout << "@employees\n";
  // Deserializing employee names
  for (int i = 0; i<3; i++) {
    infile.read((char *)&curr, sizeof(curr));
    
    // Decoding the serialized employee name and putting it inside
    // the bakery object under employee vector
    std::string temp = umap[curr];

    // std::cout << temp << std::endl;
    
    // Adding employee names to a vector
    employeeList.push_back(temp);
  }

  // Making that vector the employee object for the bakery struct
  bakery.employees = employeeList;

  // std::cout << "\n"; // for terminal presentation


  // std::cout << "@items\n";
  // Deserializing items and prices
  for (int i = 0; i<5; i++) {

    Item itemStruct; //item struct to add name and price

    // Finding the corresponding values for the keys to deserialize
    infile.read((char *)&curr, sizeof(curr)); 
    std::string item = umap[curr];

    infile.read((char *)&curr, sizeof(curr)); 
    std::string price = umap[curr]; 

    // std::cout << item << ", " << price << std::endl;

    // Adding items to item struct
    itemStruct.name = item;
    itemStruct.price = price;

    // Adding item, price pair to list of items
    itemList.push_back(itemStruct);

  } 
  bakery.items = itemList;

  // std::cout << "@orders\n";
  // Deserializing orders by going until the end of file number is found, 
  // which I made 99 (arbitrary)
  bool innerWhileLoop = false; // inner while loop tracker
  infile.read((char *)&curr, sizeof(curr));
  while (curr != 99) {

    Order order; 
    std::vector<std::pair<std::string, std::string>> tempItem;
  

    // If the value from the file correlates to an employee name, 
    // it means it's a new order
    if ((curr == 0) || (curr == 1) || (curr == 2)) {
      std::string name = umap[curr];
      order.employee = name; //setting employee name to new order
      // std::cout << name << ": ";
      
      // Going through the actual items and quantity
      infile.read((char *)&curr, sizeof(curr));
      while ((curr != 0) && (curr != 1) && (curr != 2) && (curr != 99)) {
        std::pair<std::string, std::string> temp;

        // Mapping the quanity to the the item name
        temp.first = umap[curr];
        infile.read((char *)&curr, sizeof(curr));
        temp.second = umap[curr];

        // std::cout << temp.first << " " << temp.second << " ";
        
        infile.read((char *)&curr, sizeof(curr));
        
        innerWhileLoop = true; // tracking thi while loop to ensure
                               // that we don't skip over a line in 
                               // the outer loop

        // Adding the item and quantity amount to the list of orders per employee.
        tempItem.push_back(temp); 
      }

      // std::cout << "\n";  // for terminal representation

      // Adding the list of order items to the order struct
      order.items = tempItem; 

      // Adding each employee's orders to the master list of orders
      orderList.push_back(order); 
    }
    
    if (innerWhileLoop == false) {
      infile.read((char *)&curr, sizeof(curr)); // read in next line
      innerWhileLoop = false; // reset tracker
    }
  }

  infile.close(); 
  return bakery;

}

void binary_serializer(const Bakery& bakery, std::string file_path){
  
  // Creating the binary file
  std::ofstream file(file_path, std::ios::binary);
  
  // Initializing Variables
  std::string name; // Storing the employee's name
  std::string price; // price of items
  std::string quantity; // number of items

  // Hash map for char to binary value
  std::unordered_map<std::string, short int> umap;

  // Employees
  umap["Brad"] =  0;
  umap["Claudia"] = 1;
  umap["Simone"] = 2;

  // Item names
  umap["Biscuit"] = 3;
  umap["Bun"] = 4;
  umap["Brownie"] = 5;
  umap["White Loaf"] = 6;
  umap["Wheat Loaf"] = 7;

  // Item prices
  umap["3.50"] = 8;
  umap["0.99"] = 9;
  umap["4.75"] = 10;
  umap["7.50"] = 11;
  umap["8.25"] = 12;

  // Quantity 
  umap["1"] = 13; 
  umap["2"] = 14;
  umap["3"] = 15; 
  umap["4"] = 16;
  umap["5"] = 17; 
  umap["6"] = 18;
  umap["7"] = 19;
  umap["8"] = 20;
  umap["9"] = 21;

  // Going through the list of employee names 
  for (int i = 0; i<(bakery.employees).size(); i++) {

    name = bakery.employees[i]; // Getting individual names of employees
    short int nameValue = umap[name]; // Translating name to number value from hashmap
    
    // Writing hashed value to file in binary
    file.write((char *)&nameValue, sizeof(nameValue)); 
  }
  
  // Going through the list of items
  for (int i=0; i<(bakery.items).size(); i++) {
    
    // Translating items to decimal numbers using hash map
    name = bakery.items[i].name;
    short int nameValue = umap[name]; 

    // Translating price to decimal numbers using hash map
    price = bakery.items[i].price;
    short int priceValue = umap[price];

    // Writing items and price to binary file
    file.write((char *)&nameValue, sizeof(nameValue));
    file.write((char *)&priceValue, sizeof(priceValue));
  } 

  // Going through the orders
  for (int i=0; i<(bakery.orders).size(); i++) {
    // Getting the employee's name for each order
    name = bakery.orders[i].employee;
    short int nameValue = umap[name];
    
    // Writing to a binary file
    file.write((char *)&nameValue, sizeof(nameValue));

    // Adding the actual order by iterating through the item pair
    // which tells us what items and how many of it are in each order
    for (const std::pair<std::string,std::string>& x: bakery.orders[i].items){
      
      // adding the order pairs to the corresponding employee's name
      quantity = x.second; 
      name = x.first;

      short int quantityValue = umap[quantity]; 
      short int nameValue = umap[name];

      file.write((char *)&quantityValue, sizeof(quantityValue));
      file.write((char *)&nameValue, sizeof(nameValue));
    
    }
  }

  // To know where the end of the file is at
  short int endOfFile = 99;
  file.write((char *)&endOfFile, sizeof(endOfFile)); 
  
  file.close(); // close file

  return;
}