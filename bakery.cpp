#include "bakery.h"

Bakery::Bakery()
{
    ifstream in("saveFile.txt");

    if (!in.is_open())
        return;
    
    // Skipping the Warning line
    string temp;
    getline(in, temp);

    // Reading Clients
    getline(in, temp);
    int numberOfReads = stoi(temp);
    for (int i = 0; i < numberOfReads; i++)
    {
        string name, shopLocation;
        int NIF, points, n_opinions;
        bool premium;
        float avr_opinion;
        getline(in, name);
        getline(in, temp);
        NIF = stoi(temp);
        getline(in, temp);
        premium = stoi(temp);
        getline(in, temp);
        points = stoi(temp);
        getline(in, shopLocation);
        getline(in, temp);
        avr_opinion = stof(temp);
        getline(in, temp);
        n_opinions = stoi(temp);
        Client *c = new Client(name, NIF, shopLocation, premium);
        c->setPoints(points);
        c->setAvrOpinion(avr_opinion);
        c->setNumberOpinion(n_opinions);
        clients.push_back(c);
    }

    // Reading Shops
    getline(in, temp);
    numberOfReads = stoi(temp);
    for (int i = 0; i < numberOfReads; i++)
    {
        string shopLocation;
        getline(in, shopLocation);
        Shop *s = new Shop(shopLocation);

        // Reading Employees
        int numberOfEmployees;
        getline(in, temp);
        numberOfEmployees = stoi(temp);
        for (int n = 0; n < numberOfEmployees; n++)
        {
            string name, post;
            int NIF, nOrders;
            float salary;
            getline(in, name);
            getline(in, temp);
            NIF = stoi(temp);
            getline(in, post);
            getline(in, temp);
            salary = stof(temp);
            getline(in, temp);
            nOrders = stoi(temp);
            Employee *e = s->addEmp(name, NIF, salary, post);
            e->setOrders(nOrders);            
        }

        // Reading Products
        int numberOfProducts;
        getline(in, temp);
        numberOfProducts = stoi(temp);
        for (int n = 0; n < numberOfProducts; n++)
        {
            Product p;
            getline(in, p.name);
            getline(in, p.category);
            getline(in, temp);
            p.price = stof(temp);
            getline(in, temp);
            p.n_orders = stof(temp);
            s->addProduct(p);
        }

        // Reading Orders
        int numberOfOrders;
        getline(in, temp);
        numberOfOrders = stoi(temp);
        for (int n = 0; n < numberOfOrders; n++)
        {
            // Reading ID
            int id;
            getline(in, temp);
            id = stoi(temp);

            // Reading Client
            string clientName;
            int clientNIF;
            bool delivery;
            getline(in, clientName);
            getline(in, temp);
            clientNIF = stoi(temp);
            Client *c = getClient(clientName, clientNIF);

            // Reading Employee
            Employee *e = NULL;
            getline(in, temp);
            delivery = stoi(temp);
            if (delivery) {
                string employeeName;
                int employeeNIF;
                getline(in, employeeName);
                getline(in, temp);
                employeeNIF = stoi(temp);
                e = s->getEmployee(employeeName, employeeNIF);
            }

            // Creating Order
            Order o(c, e);

            // Reading Products and respective quantities
            getline(in, temp);
            numberOfProducts = stoi(temp);
            for (int x = 0; x < numberOfProducts; x++)
            {
                string name;
                int quantity;
                getline(in, name);
                Product p = s->getProduct(name);
                getline(in, temp);
                quantity = stoi(temp);
                o.addProduct(p, quantity);
            }

            // Reading Discount and Price
            bool discount, alreadyDel;
            float price;
            getline(in, temp);
            discount = stoi(temp);
            getline(in, temp);
            price = stof(temp);
            getline(in, temp);
            alreadyDel = stoi(temp);
            o.setDiscount(discount);
            o.setPrice(price);
            o.setAlreadyDel(alreadyDel);

            s->addOrder(o);
        }

        shops.push_back(s);
    }

    in.close();
}

void Bakery::addShop(const string &location)
{
    for(vector<Shop *>::const_iterator it = shops.begin(); it != shops.end(); it++)
        if((*it)->getLocation()==location)
            throw(ShopIsAlreadyRegistered(location));
    Shop *temp = new Shop(location);
    shops.push_back(temp);
}

Shop* Bakery::getShop(const string &location)
{
    vector<Shop*>::iterator it = find_if(shops.begin(), shops.end(), [&](const Shop *s) {return s->getLocation() == location;});

    if (it == shops.end())
        throw(LocationDoesNotHaveShop(location));

    return *it;
}

void Bakery::removeShop(const string &location)
{
    vector<Shop*>::iterator it = find_if(shops.begin(), shops.end(), [&](const Shop *s) {return s->getLocation() == location;});

    if (it == shops.end())
        throw(LocationDoesNotHaveShop(location));

    shops.erase(it);
}

Client* Bakery::addClient(const string &name, const int &NIF, const string &shop_location, const bool &premium)
{
    vector<Client *>::iterator it = find_if(clients.begin(), clients.end(), [&](const Client *c) {return NIF == c->getNIF();});
    
    if (it != clients.end())
        throw(ClientAlreadyExists(NIF));
    
    Client *temp;

    try
    {
        getShop(shop_location);
        temp = new Client(name, NIF, shop_location, premium);

    }
    catch(LocationDoesNotHaveShop &e)
    {
        throw(e);
    }
    catch(NonValidNIF &e)
    {
        throw(e);
        //cout << "Person does not have a valid NIF(" << e.getNIF() << " [`_´])... Who are you really?!" << endl;
    }

    clients.push_back(temp);
    return temp;
}
    
Client* Bakery::getClient(const string &name, const int &NIF)
{
    vector<Client*>::iterator it = find_if(clients.begin(), clients.end(), [&](const Client *c) {return (name == c->getName()) && (NIF == c->getNIF());});

    if (it == clients.end())
        throw(ClientIsNotRegistered(name));

    return *it;
}

void Bakery::removeClient(const string &name, const int &NIF)
{
    vector<Client*>::iterator it = find_if(clients.begin(), clients.end(), [&](const Client *c) {return (name == c->getName()) && (NIF == c->getNIF());});

    if (it == clients.end())
        throw(ClientIsNotRegistered(name));
            
    clients.erase(it);
}

void Bakery::printSalesVolume(ostream& out) const
{
    map<struct Product, int> result;

    for (vector<Shop*>::const_iterator a = shops.begin(); a != shops.end(); a++)
    {
        vector<Order> temp1 = (*a)->getOrders();

        for (vector<Order>::const_iterator b = temp1.begin(); b != temp1.end(); b++)
        {
            map<struct Product, int> temp2 = b->getProducts();
            
            for (map<struct Product, int>::iterator c = temp2.begin(); c != temp2.end(); c++)
            {
                map<struct Product, int>::iterator found = find_if(result.begin(), result.end(), [&](const pair<struct Product, int> &t) {return t.first == c->first;});
                if (found == result.end())
                    result.insert(*c);
                else found->second += c->second;
            }
        }
    }

    for (map<struct Product, int>::iterator p = result.begin(); p != result.end(); p++)
    {
        setColor(15);
        out << "Product: ";
        setColor(7);
        out << p->first.name << endl;
        setColor(15);
        out << "Category: ";
        setColor(7);
        out << p->first.category << endl;
        setColor(15);
        out << "Price: ";
        setColor(7);
        out << p->first.price << endl;
        setColor(15);
        out << "Sold: ";
        setColor(7);
        out << p->second << endl;
        setColor(15);
        out << "Value: " ;
        setColor(7);
        out << p->second*p->first.price << endl << endl;
    }
}

void Bakery::printClients(ostream &out) const
{
    for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++)
        out << *(*it);
}

void Bakery::printPremiumClients(ostream &out) const
{
    for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++)
        if ((*it)->getPremium())
            out << *(*it);
}

void Bakery::printNonPremiumClients(ostream &out) const
{
    for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++)
        if (!(*it)->getPremium())
            out << *(*it);
}

void Bakery::printShopLocations(ostream &out) const
{
    setColor(15);
    out << "[Shops Available]";
    setColor(7);
    for (vector<Shop*>::const_iterator it = shops.begin(); it != shops.end(); it++)
        out << " - " << (*it)->getLocation();
    out << endl;
}

void Bakery::printPosts(ostream &out) const
{
    for (vector<Shop*>::const_iterator it = shops.begin(); it != shops.end(); it++)
        (*it)->printAvailablePosts(out);
}

void Bakery::printAllEmpByPost(ostream &out, const string &post) const
{   
    for (vector<Shop*>::const_iterator it = shops.begin(); it != shops.end(); it++)
    {
        out << "Employees in " << (*it)->getLocation() << " :" << endl;
        (*it)->printEmpByPost(out, post);
    }
}

void Bakery::changeSalaryByPost(const string &post, const int &percentage)
{
    for (vector<Shop*>::iterator it = shops.begin(); it != shops.end(); it++)
        (*it)->changeSalaryByPost(post, percentage);
}

Bakery::~Bakery()
{
    ofstream out("saveFile.txt", ofstream::trunc);
    out << "[DO NOT CHANGE ONLY IF YOU KNOW WHAT YOU'RE DOING, ELSE THE PROGRAM MAY BECOME CORRUPT]\n";

    out << clients.size() << endl;
    for (int i = 0; i < clients.size(); i++)
        clients[i]->saveFile(out);

    out << shops.size() << endl;
    for (int i = 0; i < shops.size(); i++)
    {
        shops[i]->saveFile(out);
        delete shops[i];
    }

    for (int i = 0; i < clients.size(); i++)
        delete clients[i];
    
    out.close();
}
