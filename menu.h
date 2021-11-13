#ifndef MENU_H
#define MENU_H

/** @file  menu header file*/
#include <iostream>
#include <windows.h>
#include <string>
#include "person.h"
#include "shop.h"
#include "bakery.h"
#include "auxiliary.h"

using namespace std;

// Client

/**
 * @brief Just asks if a client is registered or not.
 * @param bakery Bakery object argument passed by reference.
 */
void clients(Bakery &bakery);

/**
 * @brief Logs the client in.
 * @param bakery Bakery object argument passed by reference.
 */
void loginClient(Bakery &bakery);

/**
 * @brief registers a new Client.
 * @param bakery Bakery object argument passed by reference.
 */
void registerClient(Bakery &bakery);

/**
 * @brief Presents the client page and its options.
 * @param c Client object pointer argument.
 * @param bakery Bakery object argument passed by reference.
 */
void clientPage(Client* c, Bakery &bakery);

/**
 * @brief Makes an order.
 * @param c Client object pointer argument.
 * @param bakery Bakery object argument passed by reference.
 */
void makeOrder(Client* c, Bakery &bakery);

/**
 * @brief Option to change a clients shop location association, once the previous prefered location ceases to have a shop.
 * @param bakery Bakery object argument passed by reference.
 * @param c Client object pointer argument.
 */
void changeClientShopLocation(Bakery &bakery, Client *c);

// Manager

/**
 * @brief Presents manager page and its options. 
 * @param bakery Bakery object argument passed by reference.
 */
void manager(Bakery &bakery);

/**
 * @brief Page where the manager manages the clients.
 * @param bakery Bakery object argument passed by reference.
 */
void manageClient(Bakery &bakery);

/**
 * @brief Removes a client from the bakery. Catches exception when a client is not registered.
 * @param bakery Bakery object argument passed by reference.
 */
void removeClient(Bakery &bakery);

/**
 * @brief "Prints" all clients and their interactions with the bakery.
 * @param bakery Bakery object argument passed by reference. 
 */
void showAllClients(Bakery &bakery);

/**
 * @brief Option to show only premium clients.
 * @param bakery Bakery object argument passed by reference.
 */
void showPremiumClients(Bakery &bakery);

/**
 * @brief Option to show only non-premium clients.
 * @param bakery Bakery object argument passed by reference.
 */
void showNonPremiumClients(Bakery &bakery);

/**
 * @brief Sub-menu to manage the employees from all shops. Catches exception if the location input does not have a shop associated.
 * @param bakery Bakery object argument passed by reference. 
 */
void manageEmp(Bakery &bakery);

/**
 * @brief Option to hire an employee. Catches exception when the NIF is invalid.
 * @param bakery Bakery object argument passed by reference. 
 * @param s Shop object argument. 
 */
void hireEmp(Bakery &bakery, Shop *s);

/**
 * @brief Option to fire an employee. Catches exception when the employee is not registered.
 * @param bakery Bakery object argument passed by reference. 
 * @param s Shop object pointer argument. 
 */
void removeEmp(Bakery &bakery, Shop *s);

/**
 * @brief Option to change an employee's salary. Catches exception if employee is not registered in the shop.
 * @param bakery Bakery object argument passed by reference.
 * @param s Shop object pointer argument. 
 */
void changeSalaryMenu(Bakery &bakery, Shop *s);

/**
 * @brief Option to change an employee's salary  by post.
 * @param bakery Bakery object argument passed by reference. 
 */
void changeSalByPost(Bakery &bakery);

/**
 * @brief Option to change an employee's salary
 * @param s shop where the employee works. 
 */
void changeEmpSal(Shop* s);

void showEmpMenu(Bakery &bakery, Shop *s);

/**
 * @brief "Prints" all employees and their info from a shop.
 * @param s Shop object pointer argument. 
 */
void showAllEmps(Shop *s);

/**
 * @brief "Prints" all employees with a certain post.
 * @param bakery Bakery object argument passed by reference.
 */
void showAllByPost(Bakery &bakery);

/**
 * @brief "Prints" all employees with a certain post in the shop.
 * @param s Shop object pointer argument. 
 */
void showByPost(Shop *s);

/**
 * @brief Sub-menu to manage all of the shops.
 * @param bakery Bakery object argument passed by reference.
 */
void manageShops(Bakery &bakery);

/**
 * @brief Shows all sales volumes from the bakery.
 * @param bakery Bakery object argument passed by reference. 
 */
void showSales(Bakery &bakery);

/**
 * @brief Option to add a shop to the bakery chain. Catches exception when the shop is already in the location desired to add.
 * @param bakery Bakery object argument passed by reference.
 */
void addShop(Bakery &bakery);

/**
 * @brief Option to remove a shop to the bakery chain. Catches exception when the shop is not in the location desired to remove.
 * @param bakery Bakery object argument passed by reference.
 */
void removeShop(Bakery &bakery);

/**
 * @brief Prints all shop's info. Catches exception if the location inputed does not have a shop associated.
 * @param bakery Bakery object argument passed by reference.
 */
void showShopsInfo(Bakery &bakery);

/**
 * @brief Gives the option to print sales volume from a single shop, or from the bakery chain.
 * @param bakery Bakery object argument passed by reference.
 */
void showSales(Bakery &bakery);

/**
 * @brief Option to print sales volume from the bakery chain.
 * @param bakery Bakery object argument passed by reference.
 */
void showAllSalesVolume(Bakery &bakery);

/**
 * @brief Option to print sales volume from a single shop. Catches exception if the location inputed does not have a shop associated.
 * @param bakery Bakery object argument passed by reference.
 */
void showShopSalesVolume(Bakery &bakery);

/**
 * @brief Shows orders from a shop. Catches exception if the location inputed does not have a shop associated.
 * @param bakery Bakery object argument passed by reference.
 */
void showOrders(Bakery &bakery);

/**
 * @brief Adds a brand new product to the shop. Catches exception if the location input does not have a shop.
 * @param bakery Bakery object argument passed by reference.
 */
void addProductShop(Bakery &bakery);

/**
 * @brief Option to remove a product from the vector of available products from a shop. Catches exception if the product does not exist.
 * @param bakery Bakery object argument passed by reference.
 */
void removeProductShop(Bakery &bakery);

/**
 * @brief Option to show all of the available products in a shop. Catches exception if inputed location does not have a shop.
 * @param bakery Bakery object argument passed by reference.
 */
void showProductShop(Bakery &bakery);

/**
 * @brief Option that lets an employee log in.
 * @param bakery Bakery object argument passed by reference.
 */
void loginEmployee(Bakery &bakery);

/**
 * @brief Sub-menu of an employee.
 * @param e Employee object pointer argument.
 * @param bakery Bakery object argument passed by reference.
 * @param shop Shop object pointer argument.
 */
void employee(Employee* e, Bakery &bakery,Shop* shop);



#endif //MENU_H
