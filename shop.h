#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <math.h>
#include <unordered_set>
#include "bst.h"
#include "person.h"
#include "auxiliary.h"

struct Product
{
    Product() {}
    Product(const string &name , const string &category, const float &price, const int &n_orders) {this->name = name; this->category = category; this->price = price; this->n_orders = n_orders;}
    string name;
    string category;
    float price;
    int n_orders = 0;
    bool operator==(const Product &p) const {return name == p.name;}
    bool operator<(const Product &p) const {return n_orders < p.n_orders || (n_orders == p.n_orders && category < p.category) || (n_orders == p.n_orders && category == p.category && name < p.name);}
};

/**
 * @brief Class to make orders. Has a BST of products, employee to deliver, client to receive, a possibility of discount and a price to pay.
 */
class Order {
    int id;
    map<struct Product, int> products;
    Employee *employee;
    bool alreadyDel;
    Client *client;
    bool discount;
    float price;
public:
    /**
     * @brief Construct a new Order object.
     * @param client a pointer Client object argument.
     * @param emp a pointer Employee object argument.
     * @param alreadyDel true if the order has been delivered
     */
    Order(Client *client, Employee *emp);

    /**
     * @brief Adds a product and its quantity to 'products' map.
     * @param product a struct Product argument passed by reference.
     * @param quantity a constant integer argument passed by reference.
     */
    void addProduct(const struct Product &product, const int &quantity);

    /**
     * @brief Gets the Products object.
     * @return map<struct Product, int> of the products in said shop.
     */
    map<struct Product, int> getProducts() const;

    /**
     * @brief Gets the Id of the order.
     * @return int - the id of said order. 
     */
    int getId() const;

    /**
     * @brief Gets wether the order was delivered or not.
     * @return Wether the order was delivered or not.
     */
    bool getAlreadyDel()const;

    /**
     * @brief Gets the employee who does the deliver
     * @return employee who does the deliver.
     */
    Employee* getEmployee() const;

    /**
     * @brief Sets if it is to be applied a discount.
     * @param discount boolean argument passed by reference.
     */
    void setDiscount(const bool &discount);

    /**
     * @brief Sets the price.
     * @param price a float argument passed by reference.
     */
    void setPrice(const float &price);

    /**
     * @brief Sets the boolean variable if orders were delivered.
     * @param aDel boolean argument to be set to.
     */
    void setAlreadyDel(const bool &aDel);

    /**
     * @brief Ends the order... Calculates the price and the employee to do the job, if specified.
     */
    void endOrder();

    /**
     * @brief saves class information in a savefile.
     * @param out output file.
     */
    void saveFile(ofstream &out) const;

    /**
     * @brief overload of << operator to help print information from class.
     * @param out ostream to print.
     * @param c Client object argument.
     * @return ostream& info about said client.
     */
    friend ostream& operator<<(ostream &out, const Order &o);

    /**
     * @brief overload of < operator to implement priority queue.
     * @param o the order to be compared by.
     * @return wether the order is prioritized or not, following criteria established.
     */
    bool operator<(const Order &o) const;
    
    /**
     * @brief overload of "==" operator to enable comparisons.
     * @param o Order object to be compared by.
     * @return wether the order is identical to the argument, by the criteria implemented.
     */
    bool operator==(const Order &o) const;
};


struct EmployeeHash {
    int operator()(Employee *emp) const {
        return (emp->getNIF()*13)%11;
    }

    bool operator()(Employee *emp1, Employee *emp2) const {
        return *emp1 == *emp2;
    }
};

typedef unordered_set<Employee*, EmployeeHash, EmployeeHash> HashTableEmployees;

/**
 * @brief Class representing a shop. Has its location, vector of employees, BST of products, a vector of orders, a priority queue of the deliveries and a Hash table of employees.
 */
class Shop
{
    string location;
    //vector<Employee*> employees;
    BST<struct Product> products;
    int n_prod;
    vector<Order> orders;
    priority_queue<Order> deliveries;
    HashTableEmployees employees;
public:
    /**
     * @brief Construct a new Shop object with a location specified.
     * @param location string argument passed by reference.
     */
    Shop(const string &location);

    /**
     * @brief Get the shop's location.
     * @return string location.
     */
    string getLocation() const;

    /**
     * @brief Adds a new product. Throws exception if the product already exists in the bst of available products.
     * @param product Product object argument.
     */
    void addProduct(const struct Product &product);

    /**
    * @brief Removes a product from the shop. Throws exception if the product does not exist in the bst of available products.
    * @param name string argument passed by reference.
    */
    void removeProduct(const string &name);

    /**
     * @brief Get the Product object. Throws exception if product is non-existent in shop.
     * @param name string argument passed by reference.
     * @return struct Product. 
     */
    struct Product getProduct(const string &name) const;

    /**
     * @brief Increments the number of orders of a product.
     * @param name string argument passed by reference.
     */
    void incrementNOrders(const string &name);

    /**
     * @brief Adds a new order to 'orders' and, if not already delievered, to the priority queue
     * @param o Order object argument passed by reference.
     */
    void addOrder(const Order &o);
    
    /**
     * @brief Prints the next order to be delivered by an employee.
     * @param e Pointer employee object argument.
     */
    void printDel(Employee *e) const;

    /**
     * @brief Removes order from priority queue and changes status of the order in the vector orders.
     * @param e Employee object argument passed by reference.
     * @return true in case the order has been succesfully delivered, and false otherwise
     */
    bool removeDel(Employee *e);

    /**
     * @brief Gets the Orders from a shop.
     * @return vector<Order> which contains all of the orders made.
     */
    vector<Order> getOrders() const;

    /**
     * @brief 
     * @param name string argument passed by reference.
     * @param NIF integer argument passed by reference.
     * @param salary constant float argument passed by reference.
     * @return Employee* that was required.
     */
    Employee* addEmp(const string &name, const int &NIF, const float &salary, const string post);

    /**
     * @brief Returns a employee. Throws an exception if the employee is not registered.
     * @param name string argument passed by reference.
     * @param NIF integer argument passed by reference.
     * @return Employee* that was required.
     */
    Employee* getEmployee(const string &name, const int &NIF);

    /**
     * @brief Chenges the salary of all employees that work at a certain post by a certain percentage.
     * @param percentage const integer argument passed by reference.
     * @param post const string argument passed by reference.
     */
    void changeSalaryByPost(const string &post, const int &percentage);

    /**
     * @brief Returns the employee with the fewest number of orders.
     * @return Employee* that was required.
     */
    Employee* getMinDelEmployee();

    /**
     * @brief Removes a employee from 'employees'. Throws an exception if the employee is not registered.
     * @param name string argument passed by reference.
     * @param NIF integer argument passed by reference.
     */
    void removeEmp(const string &name, const int &NIF);

    /**
     * @brief Prints the sales volume for the shop.
     */
    void printSalesVolume(ostream& out) const;

    /**
     * @brief Prints all the orders made in the shop.
     * @param out ostream to print.
     */
    void printOrders(ostream& out) const;

    /**
     * @brief Prints all the employees.
     * @param out ostream to print.
     */
    void printEmployees(ostream& out) const;

    /**
     * @brief Prints all employees by a certain post.
     * @param out Ostream to print.
     * @param post String argument by reference - the post to find.
     */
    void printEmpByPost(ostream &out, const string &post) const;

    /**
     * @brief Prints all available post for hiring.
     * @param out Ostream to print.
     */
    void printAvailablePosts(ostream &out) const;

    /**
     * @brief Removes all available products.
     * @param out ostream to print.
     */
    void printProducts(ostream& out) const;

    /**
     * @brief saves class information in a savefile.
     * @param out output file. 
     */
    void saveFile(ofstream &out) const;

    /**
     * @brief overload of << operator to help print information from class.
     * @param out ostream to print.
     * @param c Client object argument.
     * @return ostream& info about said client.
     */
    friend ostream& operator<<(ostream &out, const Shop &s);

    /**
     * @brief Deletes the Employee* vector
     */
    ~Shop();
};


/**
 * @brief Exception when an employee is not registered.
 */
class EmployeeIsNotRegistered
{
    string name;
public:
    /**
     * @brief Exception constructor. Initializes with the name that caused the exception.
     * @param n string argument.
     */
    EmployeeIsNotRegistered(string n): name(n) {}

    /**
     * @brief Get the name object that has thrown the exception.
     * @return string name.
     */
    string getName() const {return name;}
};

/**
 * @brief Exception when a product is not present in the products list.
 */
class ProductDoesNotExist
{
    string name;
public:
    /**
     * @brief Exception constructor. Initializes with the product's name that caused the exception.
     * @param n string argument.
     */
    ProductDoesNotExist(string n): name(n) {}

    /**
     * @brief Get the name object that has thrown the exception.
     * @return string name.
     */
    string getName() const {return name;}
};

/**
 * @brief Exception when an employee is already registered.
 */
class EmployeeAlreadyExists
{
    int NIF;
public:
    /**
     * @brief Exception constructor. Initializes with the NIF that caused the exception.
     * @param n integer argument.
     */
    EmployeeAlreadyExists(int n): NIF(n) {}

    /**
     * @brief Get the NIF object that has thrown the exception.
     * @return integer NIF.
     */
    int getNIF() const {return NIF;}
};

/**
 * @brief Exception when a product was already added to the list.
 */
class ProductAlreadyAdded
{
    string prodName;
public:
    /**
     * @brief Exception constructor. Initializes with the product's name that caused the exception.
     * @param pn string argument.
     */
    ProductAlreadyAdded(string pn): prodName(pn) {}
    
    /**
     * @brief Get the name object that has thrown the exception.
     * @return string name.
     */
    string getProdName() const {return prodName;}
};

#endif //SHOP_H
