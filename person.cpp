#include "shop.h"

using namespace std;

bool Person::validNIF(const int &NIF) const
{
   if (!(NIF/1e8 >= 1 && NIF/1e8 <= 9)) {return false;}

   int sum_mod_11 = 0, nif_aux = NIF/10;
   
   for(int i = 1; i < 9; i++)
   {
       sum_mod_11 +=  nif_aux%10 * (i + 1);
       nif_aux /= 10;
   }

   if(sum_mod_11%11 == 0 || sum_mod_11%11 == 1)
   {
       return (NIF%10 == 0);
   }

   return (NIF%10 == (11 - sum_mod_11%11));
}

Person::Person(const string &name, const int &NIF): name(name), NIF(NIF)
{
    if (!validNIF(NIF))
        throw(NonValidNIF(NIF));
}

string Person::getName() const{return name;}

int Person::getNIF() const {return NIF;}

bool Person::operator==(const Person &right) const {return name == right.getName() && NIF == right.getNIF();}


Employee::Employee(const string &name, const int &NIF, const float &salary, const string &post) : Person(name, NIF) {this->salary = salary; nOrders = 0; this->post = post;}

bool Employee::operator<(const Employee &right) const {return nOrders < right.getnOrders();}

void Employee::addOrder(){nOrders++;}

string Employee::getPost() const {return post;}

float Employee::getSalary() const {return salary;}

int Employee::getnOrders() const {return nOrders;}

void Employee::setOrders(const int &nOrders) {this->nOrders = nOrders;}

void Employee::setSalary(const float &salary) {this->salary = salary;}

void Employee::setPost(const string &post) {this->post = post;}

void Employee::saveFile(ofstream &out) const {out << getName() << endl << getNIF() << endl << post << endl << salary << endl << nOrders << endl;}

ostream& operator<<(ostream &out, const Employee &e)
{
    setColor(15);
    out << "Name: ";
    setColor(7);
    out << e.getName() << endl;
    setColor(15);
    out << "NIF: ";
    setColor(7);
    out << e.getNIF() << endl;
    setColor(15);
    out << "Post: ";
    setColor(7);
    out << e.getPost() << endl;
    setColor(15);
    out << "Salary: ";
    setColor(7);
    out << e.salary << endl;
    setColor(15);
    out << "Number of Orders to be delivered: ";
    setColor(7);
    out << e.nOrders << endl << endl;
    return out;
}


Client::Client(const string &name, const int &NIF, const string &shop_location, const bool &premium) : Person(name, NIF) {this->premium = premium; this->shop_location = shop_location; points = 0; avr_opinion = 0; n_opinions = 0;}

void Client::changeStat() {premium = !premium;}

void Client::changeShopLocation(const string &shopLocation) {shop_location = shopLocation;}

void Client::addOpinion(const float &opinion)
{
    avr_opinion = (avr_opinion*n_opinions + opinion) / (n_opinions + 1);
    n_opinions++;
}

void Client::setAvrOpinion(const float &avr_opinion) {this->avr_opinion = avr_opinion;}

void Client::setNumberOpinion(const int &n_opinions) {this->n_opinions = n_opinions;}

float Client::getOpinion() {return avr_opinion;}

void Client::addPoints(const int &points) {this->points += points;}

int Client::getPoints() const {return this->points;}

void Client::setPoints(const int &points) {this->points = points;}

string Client::getShopLocation() const {return this->shop_location;}

bool Client::getPremium() const {return this->premium;}

float Client::getDiscount()
{
    if (premium && (points >= 100)) {
        points -= 100;
        return 0.95;
    }
    else if (!premium && (points >= 200)) {
        points -= 200;
        return 0.98;
    }

    return 1;
}

void Client::saveFile(ofstream &out) const {out << getName() << endl << getNIF() << endl << premium << endl << points << endl << shop_location << endl << avr_opinion << endl << n_opinions << endl;}

ostream& operator<<(ostream &out, const Client &c)
{
    setColor(15);
    out << "Name: ";
    setColor(7);
    out << c.getName() << endl;
    setColor(15);
    out << "NIF: ";
    setColor(7);
    out << c.getNIF() << endl;
    setColor(15);
    out << "Premium: ";
    setColor(7);

    if (c.premium)
        out << "True\n";
    else
        out << "False\n";
    
    setColor(15);
    out << "Points: ";
    setColor(7);
    out << c.points << endl;
    setColor(15);
    out << "Main Shop Location: ";
    setColor(7);
    out << c.shop_location << endl;
    setColor(15);
    out << "Opinion: ";
    setColor(7);
    out << c.avr_opinion << endl << endl;
    return out;
}