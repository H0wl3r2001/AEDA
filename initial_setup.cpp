#include <iostream>
#include "bakery.h"

using namespace std;

int main()
{
    remove("saveFile.txt");
    
    Bakery b;

    // First test to create saveFile and test the creation of various shops, clients, employees and products
    b.addShop("Porto");
    b.addShop("Lisboa");
    b.addClient("Adriano Soares", 243351119, "Porto", true);
    b.addClient("Afonso Monteiro", 288934172, "Lisboa");
    b.addClient("Rita Ramada", 257823042, "Porto", false);
    Shop *p = b.getShop("Porto");
    p->addEmp("Manuel Fonseca", 297561154, 1000, "Cashier");
    struct Product temp;
    temp.name = "Big Bread"; temp.category = "Pastry"; temp.price = 0.5;
    p->addProduct(temp);
    temp.name = "Small Bread"; temp.category = "Pastry"; temp.price = 0.1;
    p->addProduct(temp);

    // Testing if bakery is reading from the saveFile and making changes
    //Shop *p = b.getShop("Porto");
    p->addEmp("Maria Ramada", 322235294, 1100, "Courier");

    // Testing if Orders are saved correctly and if Order adds 10 points to Afonso Monteiro
    Shop *l = b.getShop("Lisboa");
    Client *a = b.getClient("Afonso Monteiro", 288934172);
    Employee *e = l->addEmp("Ricardo Martins", 372995845, 635, "Courier");
    Employee *e1 = l->addEmp("Bruno Fernandes", 283338709, 800, "Cashier");
    temp.name = "Big Bread"; temp.category = "Pastry"; temp.price = 0.5;
    l->addProduct(temp);
    
    temp.name = "Small Bread"; temp.category = "Pastry"; temp.price = 0.1;
    l->addProduct(temp);
    Order o1(a, e);
    o1.addProduct(temp, 10);
    l->incrementNOrders(temp.name);
    o1.endOrder();
    l->addOrder(o1);

    Client *r = b.getClient("Rita Ramada", 257823042);
    Order o2(r, NULL);
    o2.addProduct(temp, 20);
    p->incrementNOrders(temp.name);
    o2.endOrder();
    p->addOrder(o2);

    // Testing if Orders are read correctly
    /*Shop *l = b.getShop("Lisboa");
    l->printOrders(cout);
    Shop *p = b.getShop("Porto");
    p->printOrders(cout);*/

    // Testing adding products
    struct Product cake;
    cake.name = "2 Layer Crunchy Cake";
    cake.category = "Cake";
    cake.price = 20;
    p->addProduct(cake);
    l->addProduct(cake);

    cake.name = "2 Layer Puff Pastry Cake";
    cake.category = "Cake";
    cake.price = 10;
    p->addProduct(cake);
    l->addProduct(cake);
    
    cake.name = "2 Layer Sponge Cake";
    cake.category = "Cake";
    cake.price = 15;
    p->addProduct(cake);
    l->addProduct(cake);

    // Testing printing clients
    //b.printClients(cout);
}
