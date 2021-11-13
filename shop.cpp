#include "shop.h"

// Class Order

Order::Order(Client *client, Employee *emp)
{
    static int id = 0;
    this->id = id;
    id++;
    this->client = client; this->employee = emp;
    alreadyDel = false;
}

void Order::addProduct(const struct Product &product, const int &quantity)
{
    map<struct Product, int>::iterator it = find_if(products.begin(), products.end(), [&](const pair<struct Product, int> &p) {return p.first == product;});

    if (it == products.end())
        products.insert(pair<struct Product, int> (product, quantity));
    else
        it->second += quantity;
}

map<struct Product, int> Order::getProducts() const {return products;}

int Order::getId() const {return id;}

bool Order::getAlreadyDel() const {return alreadyDel;}

Employee* Order::getEmployee() const {return employee;}

void Order::setDiscount(const bool &discount) {this->discount = discount;}

void Order::setPrice(const float &price) {this->price = price;}

void Order::setAlreadyDel(const bool &aDel) {alreadyDel = aDel;}

void Order::endOrder()
{   
    float sum = 0;

    for (map<struct Product, int>::iterator it = products.begin(); it != products.end(); it++)
        sum += it->first.price * it->second;

    float disc = client->getDiscount();
    
    if (disc != 1)
        this->discount = true;

    price = ceilf(sum * disc * 100) / 100;

    client->addPoints((int) price * 10); 

    if (employee != NULL)
        employee->addOrder();
}

void Order::saveFile(ofstream &out) const
{
    out << id << endl << client->getName() << endl << client->getNIF() << endl;

    if (employee != NULL)
        out << true << endl << employee->getName() << endl << employee->getNIF() << endl;
    else
        out << false << endl;

    out << products.size() << endl;
    for (map<struct Product, int>::const_iterator it = products.begin(); it != products.end(); it++)
        out << it->first.name << endl << it->second << endl;

    out << discount << endl << price << endl << alreadyDel << endl;
}

ostream& operator<<(ostream &out, const Order &o)
{
    setColor(6);
    out << "[Client] ";
    setColor(7);
    out << o.client->getName() << " - " << o.client->getNIF() << endl;

    for (map<struct Product, int>::const_iterator it = o.products.begin(); it != o.products.end(); it++)
        out << (*it).first.name << ": " << (*it).first.price << " x " << (*it).second << " = " << (*it).first.price * (*it).second << " Euro(s)\n";
    
    out << "Final Price = " << o.price << " Euro(s)\n";

    if (o.discount)
        out << "Discount was Applied\n";

    if (o.employee != NULL)
    {
        setColor(2);
        out << "[Employee] ";
        setColor(7);
        if (!o.getAlreadyDel()) out << o.employee->getName() << " will deliver it!\n";
        else out << o.employee->getName() << " already delivered it!\n";
    }
    
    return out;
}

bool Order::operator<(const Order &o) const {return client->getOpinion() < o.client->getOpinion() || (client->getOpinion() == o.client->getOpinion() && client->getPoints() < o.client->getPoints());}

bool Order::operator==(const Order &o) const {return id == o.getId();}

// Class Shop

Shop::Shop(const string &location) : products(Product("", "", 0, 0)) {this->location = location; n_prod = 0;}

string Shop::getLocation() const {return location;}

void Shop::addProduct(const Product &product) 
{
    BSTItrIn<struct Product> it(products);

    while(!it.isAtEnd()) {
        if(it.retrieve() == product)
            throw(ProductAlreadyAdded(product.name));
        it.advance();
    }

    n_prod++;
    products.insert(product);
}

void Shop::removeProduct(const string &name)
{
    struct Product temp(name, "", 0, 0);
    BSTItrIn<struct Product> it(products); 
    while(!it.isAtEnd()){
        if(it.retrieve() == temp) {
            n_prod--;
            products.remove(it.retrieve());
            return;
        }
        it.advance();
    }   
    throw(ProductDoesNotExist(name));
}

struct Product Shop::getProduct(const string &name) const
{
    struct Product temp(name, "", 0, 0);
    BSTItrIn<struct Product> it(products);
    
    while (!it.isAtEnd()) {
        if (it.retrieve() == temp)
            return it.retrieve();
        it.advance();
    }

    throw(ProductDoesNotExist(name));
}

void Shop::incrementNOrders(const string &name)
{
    struct Product temp(name, "", 0, 0);
    BSTItrIn<struct Product> it(products);
    
    while (!it.isAtEnd()) {
        if (it.retrieve() == temp) {
            temp = it.retrieve();
            products.remove(it.retrieve());
            temp.n_orders++;
            products.insert(temp);
            return;
        }
        it.advance();
    }

    throw(ProductDoesNotExist(name));
}

void Shop::addOrder(const Order &o)
{
    orders.push_back(o);

    if (o.getEmployee() != NULL)
        deliveries.push(o);
}

void Shop::printDel(Employee *e) const
{
    if (deliveries.empty() || e->getnOrders() == 0)
    {
        cout << "You have no orders to deliver\n";
        return;
    }

    setColor(15);
    cout << "Number of orders to deliver: ";
    setColor(7);
    cout << e->getnOrders() << endl << endl;
    
    priority_queue<Order> temp = deliveries;

    while(!temp.empty()) {
        if (temp.top().getEmployee() == e)
        {
            cout << temp.top();           
            break;
        }
        temp.pop();
    }
}

bool Shop::removeDel(Employee *e)
{
    priority_queue<Order> temp;
    Order o(NULL, NULL);

    if (deliveries.empty() || e->getnOrders() == 0) {return false;}

    e->setOrders(e->getnOrders()-1);

    while(!deliveries.empty()) {
        if (deliveries.top().getEmployee() == e)
        {
            o = deliveries.top();
            deliveries.pop();
            break;
        }
        else
        {
            temp.push(deliveries.top());
            deliveries.pop();
        }
    }

    while (!temp.empty()) {deliveries.push(temp.top()); temp.pop();}

    for(vector<Order>::iterator it = orders.begin(); it != orders.end(); it++)
        if ((*it) == o)
            (*it).setAlreadyDel(true);

    return true;
}

vector<Order> Shop::getOrders() const {return orders;}

Employee* Shop::addEmp(const string &name, const int &NIF, const float &salary, const string post)
{
    HashTableEmployees::iterator it = find_if(employees.begin(), employees.end(), [&](const Employee *e) {return e->getNIF() == NIF;});

    if (it != employees.end())
        throw(EmployeeAlreadyExists(NIF));
    
    Employee *temp;

    try
    {
        temp = new Employee(name, NIF, salary, post);
    }
    catch(NonValidNIF &e)
    {
        cout << "This NIF( " << e.getNIF() << ") is not valid... Are you commiting a fraud?!" << endl;
    }
    
    employees.insert(temp);
    return temp;
}

Employee* Shop::getEmployee(const string &name, const int &NIF)
{
    HashTableEmployees::iterator it = find_if(employees.begin(), employees.end(), [&](const Employee *e) {return (e->getName() == name) && (e->getNIF() == NIF);});

    if (it == employees.end())
        throw(EmployeeIsNotRegistered(name));

    return *it;
}

void Shop::changeSalaryByPost(const string &post, const int &percentage)
{
    Employee *temp;
    vector<Employee*> changedSalary;

    for (HashTableEmployees::iterator it = employees.begin(); it != employees.end();) {
        if ((*it)->getPost() == post) {
            temp = *it;
            temp->setSalary(temp->getSalary()*((float)1+(float)percentage/100));
            changedSalary.push_back(temp);
            it = employees.erase(it);
        }
        else it++;
    }

    for (int n = 0; n != changedSalary.size(); n++) employees.insert(changedSalary[n]);
}

Employee* Shop::getMinDelEmployee(){
    if (employees.empty())
        return NULL;

    Employee *temp = NULL;
    int nOrders = 6;
    
    for (HashTableEmployees::iterator it = employees.begin(); it!= employees.end(); it++) {
        if ((*it)->getPost() == "Courier" && (*it)->getnOrders() < nOrders) {
            temp = *it;
            nOrders = (*it)->getnOrders();
        }
    }
    
    if (temp == NULL || temp->getnOrders() == 5)
        return NULL;
    
    return temp;
}

void Shop::removeEmp(const string &name, const int &NIF)
{
    HashTableEmployees::iterator it = find_if(employees.begin(), employees.end(), [&](const Employee *e) {return (e->getName() == name) && (e->getNIF() == NIF);});

    if (it == employees.end())
        throw(EmployeeIsNotRegistered(name));

    employees.erase(it);
}

void Shop::printSalesVolume(ostream& out) const
{  
    map<struct Product, int> result;
    for (vector<Order>::const_iterator it = orders.begin(); it != orders.end(); it++)
    {
        map<struct Product, int> temp = it->getProducts();
        for (map<struct Product, int>::iterator p = temp.begin(); p != temp.end(); p++)
        {
            map<struct Product, int>::iterator found = find_if(result.begin(), result.end(), [&](const pair<struct Product, int> &t) {return t.first == p->first;});
            if (found == result.end())
            {
                result.insert(*p);
            }
            else found->second += p->second;
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

void Shop::printOrders(ostream& out) const
{
    for(vector<Order>::const_iterator it = orders.begin(); it != orders.end(); it++)
        out << *it << endl;
}
    
void Shop::printEmployees(ostream& out) const
{
    for(HashTableEmployees::const_iterator it = employees.begin(); it != employees.end(); it++)
        out << *(*it);
}

void Shop::printEmpByPost(ostream &out, const string &post) const
{
    //out << "The employees that have the post " << post << " are: " << endl;
    int count = 0;

    for(HashTableEmployees::const_iterator it = employees.begin(); it != employees.end(); it++)
    {
        if ((*it)->getPost() == post)
        {
            out << *(*it) << endl;
            count ++;
        }
    }

    if (count == 0)
        out << "None. There is no employee in that post." << endl;
}

void Shop::printAvailablePosts(ostream &out) const
{
    vector<string> posts;

    setColor(15);
    out << "[Posts Available in " << location << "]";
    setColor(7);

    for (HashTableEmployees::const_iterator it = employees.begin(); it != employees.end(); it++)
    {
        if (find(posts.begin(), posts.end(), (*it)->getPost()) == posts.end())
        {
            posts.push_back((*it)->getPost());
            out << " - " << (*it)->getPost();
        }
    }

    out << endl;
}

void Shop::printProducts(ostream& out) const
{
    BSTItrIn<struct Product> it(products);
    
    while (!it.isAtEnd()) {      
        setColor(15); 
        out << "Name: ";
        setColor(7);
        out << it.retrieve().name << endl;
        setColor(15);
        out << "Category: ";
        setColor(7);
        out << it.retrieve().category << endl;
        setColor(15);
        out << "Price: ";
        setColor(7);
        out << it.retrieve().price << endl;
        setColor(15);
        out << "Number of orders in which product is present: ";
        setColor(7);
        out << it.retrieve().n_orders << endl << endl;
        it.advance();
    }        
}

void Shop::saveFile(ofstream &out) const
{
    out << location << endl;
    out << employees.size() << endl;
    for (HashTableEmployees::const_iterator it = employees.begin(); it != employees.end(); it++)
        (*it)->saveFile(out);
    
    BSTItrIn<struct Product> it(products);
    out << n_prod << endl;
    while (!it.isAtEnd()) {
        out << it.retrieve().name << endl << it.retrieve().category << endl << it.retrieve().price << endl << it.retrieve().n_orders << endl;
        it.advance();
    }
    
    out << orders.size() << endl;
    for (int i = 0; i < orders.size(); i++)
        orders[i].saveFile(out);
}

ostream& operator<<(ostream &out, const Shop &s)
{
    setColor(9);
    out << "[Orders]\n\n";
    setColor(7);
    s.printOrders(out);

    setColor(9);
    out << "[Employees]\n\n";
    setColor(7);
    s.printEmployees(out);

    setColor(9);
    out << "[Products]\n\n";
    setColor(7);
    s.printProducts(out);
    return out;
}

Shop::~Shop()
{
    for (HashTableEmployees::iterator it = employees.begin(); it != employees.end(); it++)
        delete *it;
}
