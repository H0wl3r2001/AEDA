#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "auxiliary.h"

using namespace std;

/**
 * @brief Class that forms persons. Has a NIF and a name.
 */
class Person{
    string name;
    int NIF;
    bool validNIF(const int &NIF) const;
public:
    /**
     * @brief Constructs a person.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference.
     * @throw when the NIF is invalid.
     */
    Person(const string &name, const int &NIF);

    /**
     * @brief Gets the name.
     * @return Returns the person's name.
     */
    string getName() const;

    /**
     * @brief Gets the NIF.
     * @return Returns the person's NIF.
     */
    int getNIF() const;

    /**
     * @brief Overload of == operator to compare two Person objects.
     * @param right Person object argument passed by reference.
     * @return Wether the two compared are equal or not.
     */
    bool operator==(const Person &right) const;
};

/**
 * @brief Class inherited from Person. Has a salary and a number of orders associated
 */
class Employee: public Person {
    float salary;
    int nOrders;
    string post;
public:
    /**
     * @brief Constructs an employee.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference.
     * @param salary a float argument passed by reference.
     */
    Employee(const string &name, const int &NIF, const float &salary, const string &post);

    /**
     * @brief Compares two employees by their number of orders.
     * @param right a class Employee argument passed by reference.
     * @return Whether the num of orders from right is bigger than the employee in which this function is called.
     */
    bool operator<(const Employee &right) const; 
    
    /**
     * @brief Sets the number of orders.
     * @param nOrders a constant integer argument passed by reference.
     */
    void setOrders(const int &nOrders);

    /**
     * @brief Increments the number of orders of an Employee object.
     */
    void addOrder();

    /**
     * @return Returns the number of orders.
     */
    int getnOrders() const;

    /**
     * @brief Gets the post of an Employee object.
     * @return string - the post of said employee.
     */
    string getPost() const;

    /**
     * @brief Gets the salary of an Employee object.
     * @return float - the salary of said employee.
     */
    float getSalary() const;

    /**
     * @brief Sets the salary of an employee.
     * @param salary a constant float argument passed by reference.
     */
    void setSalary(const float &salary);

    /**
     * @brief Sets the post of an employee.
     * @param post a constant string argument passed by reference.
     */
    void setPost(const string &post);

    /**
     * @brief Saves class information in a savefile.
     * @param out output file. 
     */
    void saveFile(ofstream &out) const;

    /**
     * @brief Overload of << operator to help print information from class.
     * @param out ostream to print.
     * @param e Employee object argument.
     * @return ostream& info about said employee.
     */
    friend ostream& operator<<(ostream &out, const Employee &e);
};

/**
 * @brief Class inherited from Person. Has an overage opinion, number of opinions, premium status, points to accumulate and a prefered shop location.
 */
class Client: public Person {
    float avr_opinion;
    int n_opinions;
    bool premium;
    int points;
    string shop_location;
public:
     /**
     * @brief Constructs a client.
     * @param name a string argument passed by reference.
     * @param NIF an integer argument passed by reference. 
     * @param shop_location a string argument passed by reference.
     * @param premium a boolean argument passed by reference. False by default.
     */
    Client(const string &name, const int &NIF, const string &shop_location, const bool &premium = false);

    /**
     * @brief Changes the premium status.
     */
    void changeStat();

    /**
     * @brief Changes the shop location from a client whose shop was eliminated.
     * @param shopLocation string argument. The new location the client is going to be moved to. 
     */
    void changeShopLocation(const string &shopLocation);

    /**
     * @brief Adds an integer opinion (1-5), relative to an order and updates the average opinion.
     * @param opinion a float argument passed by reference.
     */
    void addOpinion(const float &opinion);

    /**
     * @brief Sets the average opinion of a client of a shop.
     * @param avr_opinion a float argument passed by reference.
     */
    void setAvrOpinion(const float &avr_opinion);

    /**
     * @brief Sets the number of opinions a client submited.
     * @param n_opinions an integer argument passed by reference. 
     */
    void setNumberOpinion(const int &n_opinions);

    /**
     * @brief Gets the client's average opinion.
     * @return float - the average opinion.
     */
    float getOpinion();

    /**
     * @brief Gets the percentage of the final price.
     * @return float - the final price, taking into account the discount.
     */
    float getDiscount();

    /**
     * @brief Get the Premium object.
     * @return the premium status. 
     */
    bool getPremium() const;

    /**
     * @brief Get the Points object.
     * @return number of points the client has.
     */
    int getPoints() const;

    /**
     * @brief Adds a total number of points specified.
     * @param points an integer argument passed by reference.
     */
    void addPoints(const int &points);

    /**
     * @brief Set the Points object.
     * @param points an integer argument passed by reference.
     */
    void setPoints(const int &points);

    /**
     * @brief Get the Shop Location object.
     * @return string specifying the location of a shop.
     */
    string getShopLocation() const;

    /**
     * @brief Saves class information in a savefile.
     * @param out output file. 
     */
    void saveFile(ofstream &out) const;

    /**
     * @brief Overload of << operator to help print information from class.
     * @param out ostream to print.
     * @param c Client object argument.
     * @return ostream& info about said client.
     */
    friend ostream& operator<<(ostream &out, const Client &c);
};

/**
 * @brief Exception when a NIF is invalid.
 */
class NonValidNIF
{
    int NIF;
public:
    /**
     * @brief Exception to be thrown.
     * @param num NIF that caused problems.
     */
    NonValidNIF(int num): NIF(num) {}
    
    /**
     * @brief Gets the problematic NIF.
     * @return NIF that caused the exception.
     */
    int getNIF() const {return NIF;}
};

#endif //PERSON_H