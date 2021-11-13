#ifndef PADARIA_H
#define PADARIA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "person.h"
#include "shop.h"
#include "auxiliary.h"

using namespace std;

/**
 * @brief Main class, contains clients and all the shops
 */
class Bakery
{
    vector<Client*> clients;
    vector<Shop*> shops;
public:
    /**
     * @brief Bakery constructor. Secret... This is where the file will be read.
     */
    Bakery();

    /**
     * @brief Adds a shop to the bakery chain. Throws an exception when the location already has a shop associated.
     * @param location a string argument.
     */
    void addShop(const string &location);

    /**
     * @brief Returns a shop from the bakery chain. Throws an exception when the location does not have a shop associated.
     * @param location a string argument passed by reference.
     * @return Shop* that we require.
     */
    Shop* getShop(const string &location);

    /**
     * @brief Removes a shop from the bakery chain. Throws an exception when the location does not have a shop associated.
     * @param location a string argument passed by reference.
     */
    void removeShop(const string &location);

    /**
     * @brief Adds a client to the bakery chain. Throws exceptions when Client is already registered, when the NIF is invalid and when the location prefered does not have a shop.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference.
     * @param shop_location a string argument passed by reference. 
     * @param premium a boolean argument passed by reference.
     * @return Client* that we required.
     */
    Client* addClient(const string &name, const int &NIF, const string &shop_location, const bool &premium = false);

    /**
     * @brief Returns a client from the bakery chain. Throws an exception when client is not registered.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference.
     * @return Client* that we required.
     */
    Client* getClient(const string &name, const int &NIF);

    /**
     * @brief Removes a client from the bakery chain. Throws an exception when client is not registered.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference.
     */
    void removeClient(const string &name, const int &NIF);

    /**
     * @brief Prints the sales volume from the entire chain.
     * @param out ostream argument used to print data.
     */
    void printSalesVolume(ostream& out) const;

    /**
     * @brief Prints all the clients from all shop locations.
     * @param out ostream argument used to print data.
     */
    void printClients(ostream &out) const;

    /**
     * @brief Prints all premium clients's information
     * @param out ostream argument used to print data.
     */
    void printPremiumClients(ostream &out) const;

    /**
     * @brief Prints all non-premium clients's information
     * @param out ostream argument used to print data.
     */
    void printNonPremiumClients(ostream &out) const;

    /**
     * @brief Prints all the shops from the chain.
     * @param out ostream argument used to print data.
     */
    void printShopLocations(ostream &out) const;

    /**
     * @brief Prints available posts in the chain.
     * @param out ostream argument used to print data.
     */
    void printPosts(ostream &out) const;

    /**
     * @brief Prints all employess of the chain from a specific post.
     * @param out ostream argument used to print data.
     * @param post const string argument passed by reference.
     */
    void printAllEmpByPost(ostream &out, const string &post) const;

    /**
     * @brief Prints all employess of the chain from a specific post.
     * @param post const string argument passed by reference.
     * @param percentage const integer argument passed by reference.
     */
    void changeSalaryByPost(const string &post, const int &percentage);
    
    /**
     * @brief Destroy the Bakery object and saves the informations in a file.
     */
    ~Bakery();
};


/**
 * @brief Exception when a location does not have a shop.
 */
class LocationDoesNotHaveShop
{
    string location;
public:
    /**
     * @brief Exception constructor. Initializes with the location that caused problems.
     * @param lc string argument that caused the problems.
     */
    LocationDoesNotHaveShop(string lc): location(lc) {}

    /**
     * @brief Get the location object that has thrown the exception.
     * @return string location.
     */
    string getLocation() const {return location;}
};

/**
 * @brief Exception when a client is not registered.
 */
class ClientIsNotRegistered
{
    string name;
public:
    /**
     * @brief Exception constructor. Initializes with the name that caused problems.
     * @param n the name which caused the comotion.
     */
    ClientIsNotRegistered(string n): name(n) {}

    /**
     * @brief Get the name object that has thrown the exception.
     * @return string name.
     */
    string getName() const {return name;}
};

/**
 * @brief Exception when a client already exists.
 */
class ClientAlreadyExists
{
    int NIF;
public:
    /**
     * @brief Exception constructor. Initializes with the NIF that caused problems.
     * @param n the NIF which caused the comotion.
     */
    ClientAlreadyExists(int n): NIF(n) {}

    /**
     * @brief Get the NIF object that has thrown the exception.
     * @return int NIF.
     */
    int getNIF() const {return NIF;}
};

/**
 * @brief Exception when a shop is already registered.
 */
class ShopIsAlreadyRegistered
{
    string location;
public:
    /**
     * @brief Exception constructor. Initializes with the location that caused problems.
     * @param lc string argument that caused the problems.
     */
    ShopIsAlreadyRegistered(string lc): location(lc) {}
    
    /**
     * @brief Get the location object that has thrown the exception.
     * @return string location.
     */
    string getLocation() const {return location;}
};
#endif //PADARIA_H
