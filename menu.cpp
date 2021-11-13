#include "menu.h"

// Clients

void clients(Bakery &bakery)
{
    cout << "Are you already register? (Y/N) "; 
    bool registered = getYesNo();

    if (!registered)
        registerClient(bakery);         
    else
        loginClient(bakery);
}

void loginClient(Bakery &bakery)
{
    system("cls");
    
    setColor(6);
    cout << "[Client Login]\n";
    setColor(7);
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your NIF: ";
    int NIF = getInt(1e8, 999999999);

    Client *c = NULL;

    try
    {
        c = bakery.getClient(name, NIF);
    }
    catch (ClientIsNotRegistered &e)
    {
        cout << "Client is not registered, try again...";
        Sleep(3000);
        return;
    }

    try
    {
        bakery.getShop(c->getShopLocation());
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << "We're sorry, but it appears that your main shop location has been closed! Please choose another shop that is convenient to you.";
        Sleep(3000);
        changeClientShopLocation(bakery, c);
    }

    clientPage(c, bakery);
}

void registerClient(Bakery &bakery)
{
    system("cls");
    
    setColor(6);
    cout << "[Registering client]\n"; 
    setColor(7);
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter NIF: "; 
    int NIF = getInt(1e8, 999999999);

    system("cls");

    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Choose the Shop that is more convenient to you: ";
    getline(cin, shopLocation);
    cout << "Do you want to be a premium client? (Y/N) ";
    bool premium = getYesNo();
    
    Client *c;

    try {
        c = bakery.addClient(name, NIF, shopLocation, premium);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << "There is NO shop at this location: " << e.getLocation() <<". Are you that unaware?!";
        Sleep(3000);
        return;
    }
    catch (NonValidNIF &e)
    {
        cout << "Failed to construct this person, because its NIF (" << e.getNIF() << ") is not valid... Are you commiting fraud?!" << endl;
        Sleep(3000);
        return;
    }
    catch (ClientAlreadyExists &e)
    {
        cout << "Client is already registered!";
        Sleep(3000);
        return;
    }

    clientPage(c, bakery);
}

void clientPage(Client* c, Bakery &bakery)
{
    int option;
    
    do
    {
        system("cls");
        setColor(6);
        cout << "<<Welcome " << c->getName() << ">> ";
        if (c->getPremium())
        {
            setColor(6);
            cout << "[Premium Client]\n";
        }
        else
        {
            setColor(8);
            cout << "[Non Premium Client]\n";
        }
        setColor(7);
        cout << "You have " << c->getPoints() << " points\n";
        cout << "Your current Main Shop is: " << c->getShopLocation() << endl;
        cout << "[1] Make a new order\n[2] Change my main shop location\n[3] Change my premium status\n[4] Go back to main menu page\nChoose an option: ";
        
        option = getInt(1, 4);
        
        switch (option) {
        case 1:
            makeOrder(c, bakery);
            break;
        case 2:
            changeClientShopLocation(bakery, c);
            break;
        case 3:
            c->changeStat();
            if (c->getPremium())
                cout << "You're now a premium client! Congrats on being soooooo stingy... on bread.";
            else
                cout << "You're not a premium client anymore! Wow... You're that poor?!";
            Sleep(3000);
            break;
        case 4:
            break;
        }
    } while (option != 4);
}

void makeOrder(Client* c, Bakery &bakery)
{
    Shop *shop = bakery.getShop(c->getShopLocation());

    cout << "You wish to have the products delivered directly to you? (Y/N) ";
    bool delivery = getYesNo();

    Employee *emp = NULL;
    if (delivery){
        emp = shop->getMinDelEmployee();
        if (emp == NULL)
        {
            cout << "Sorry, we have no employees available for delivery, please try again later!\n";
            Sleep(3000);
            return;
        }
    }

    system("cls");
        
    Order o(c, emp);

    setColor(6);
    cout << "[Products Available]\n\n";
    setColor(7);
    
    shop->printProducts(cout);

    bool done = false;
    int quantity;
    while (!done)
	{
        struct Product temp;

        string productName;
		cout << "Select the Product name: ";
        getline(cin, productName);

        try
        {
            temp = shop->getProduct(productName);
            shop->incrementNOrders(productName);
        }
        catch(ProductDoesNotExist &e)
        {
            cout << "Product with name: " << e.getName() << " does not exist. Can't you spell it?" << endl;
            continue;
        }

        cout << "Select the Product Quantity: ";
        quantity = getInt(1, 1000);

        o.addProduct(temp, quantity);

		cout << "End order? (Y/N) ";
        done = getYesNo();
	}

    system("cls");
    
    o.endOrder();
    shop->addOrder(o);

    setColor(6);
    cout << "[Showing Final Order]\n\n";
    setColor(7);
    cout << o;

    if (emp == NULL)
        cout << "The order will be ready to be delivered at " << shop->getLocation() << endl;

    cout << "\nLeave your opinion please (1-5): ";
    int opinion = getInt(1, 5);
    c->addOpinion(opinion);
}

void changeClientShopLocation(Bakery &bakery, Client *c)
{
    system("cls");
    setColor(6);
    cout << "[Changing Main Shop Location]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        c->changeShopLocation(bakery.getShop(shopLocation)->getLocation());
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }
}

// Manager

void manager(Bakery &bakery)
{
    int option;

    do
    {
        system("cls");
        setColor(9);
        cout << "<<Welcome to the Manager's Page>>\n";
        setColor(7);
        cout << "[1] Manage Clients\n[2] Manage Employees\n[3] Manage Shops\n[4] Go back to main menu page\nChoose an option: ";
        option = getInt(1, 4);
        switch (option) {
        case 1:
            manageClient(bakery);
            break;
        case 2:
            manageEmp(bakery);
            break;
        case 3:
            manageShops(bakery);    
            break;
        case 4:
            break;
        }
    } while (option != 4);
}

void manageClient(Bakery &bakery)
{
    int option;

    do
    {
        system("CLS");
        setColor(9);
        cout << "<<Manage Clients Menu>>\n";
        setColor(7);
        cout << "[1] Remove client\n[2] Show all clients\n[3] Show premium client\n[4] Show non premium client\n[5] Go back to the Manager's page\nChoose an option: ";
        option = getInt(1,5);
        switch (option) {
        case 1:
            removeClient(bakery);
            break;
        case 2:
            showAllClients(bakery);
            break;
        case 3:
            showPremiumClients(bakery);
            break;
        case 4:
            showNonPremiumClients(bakery);
            break;
        case 5:
            break;
        }
    } while(option != 5);
}

void removeClient(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Removing a Client]\n";
    setColor(7);
    string clientName;
    cout << "Client name: ";
    getline(cin, clientName);   
    cout << "Client NIF: ";
    int NIF = getInt(1e8, 999999999);

    try
    {
        bakery.removeClient(clientName, NIF);
    }
    catch (ClientIsNotRegistered &e)
    {
        cout << "There isn't a client with that name (" << e.getName() << ") or NIF";
        Sleep(3000);
    }
}

void showAllClients(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing All Clients]\n\n";
    setColor(7);
    bakery.printClients(cout);
    cout << "To go back to the manage clients page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void showPremiumClients(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing All Premium Clients]\n\n";
    setColor(7);
    bakery.printPremiumClients(cout);
    cout << "To go back to the manage clients page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void showNonPremiumClients(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing All Non Premium Clients]\n\n";
    setColor(7);
    bakery.printNonPremiumClients(cout);
    cout << "To go back to the manage clients page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void manageEmp(Bakery &bakery)
{
    system("cls");

    setColor(9);
    cout << "[Shop Locations Available]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Choose a Shop: ";
    getline(cin, shopLocation);

    Shop *s = NULL;

    try {
        s = bakery.getShop(shopLocation);
    }
    catch(LocationDoesNotHaveShop &e)
    {
        cout << "There is NO shop at this location: " << e.getLocation() <<". Are you that unaware?!";
        Sleep(3000);
        return;
    }

    int option = 0;

    do
    {
        system("cls");
        setColor(9);
        cout << "<<Managing Employees in " << shopLocation << ">>\n";
        setColor(7);
        cout << "[1] Hire employee\n[2] Remove employee\n[3] Change employee salary\n[4] Show employees\n[5] Go back\nChoose an option: ";
        option = getInt(1, 5);            
        switch (option) {
            case 1:
                hireEmp(bakery, s);
                break;
            case 2:
                removeEmp(bakery, s);
                break;
            case 3:
                changeSalaryMenu(bakery, s);
                break;
            case 4:
                showEmpMenu(bakery, s);
            case 5:                    
                break;
        }
    } while (option != 5); 
}

void hireEmp(Bakery &bakery, Shop *s)
{
    system("cls");

    setColor(9);
    cout << "[Hiring Employee at " << s->getLocation() << "]\n";
    setColor(7);

    string name;
    cout << "Employee name: ";
    getline(cin, name);
    cout << "Employee NIF: ";
    int NIF = getInt(1e8, 999999999);
    string post;
    cout << "Employee post: ";
    getline(cin, post);
    cout << "Employee salary: ";
    float salary = getFloat(635, 10000);

    try {
        s->addEmp(name, NIF, salary, post);
    }
    catch(NonValidNIF &e)
    {
        cout << "Failed to construct this person, because its NIF (" << e.getNIF() << ") is not valid... Are you commiting fraud?!" << endl;
        Sleep(3000);
    }
    catch (EmployeeAlreadyExists &e)
    {
        cout << "Employee is registered already!";
        Sleep(3000);
    }
}

void removeEmp(Bakery &bakery, Shop *s)
{
    system("cls");
    setColor(9);
    cout << "[Removing Employee at " << s->getLocation() << "]\n";
    setColor(7);
    string name;
    cout << "Employee name: ";
    getline(cin, name);
    cout << "Employee NIF: ";
    int NIF = getInt(1e8, 999999999);
    
    try {
        s->removeEmp(name, NIF);
    }
    catch (EmployeeIsNotRegistered &e)
    {
        cout << "Employee with name " << name << " and NIF " << NIF << " is not registered." << endl;
        Sleep(3000);
    }
}

void changeSalaryMenu(Bakery &bakery, Shop *s)
{
    int option = 0;
    do{
        system("cls");
        setColor(9);
        cout << "[Change Salary Menu]\n";  
        setColor(7);
        cout << "[1] Change by post\n[2] Especific employee\n[3] Go back\nChoose an option: ";
        option = getInt(1, 3);                  
        switch (option) {
            case 1:               
                changeSalByPost(bakery);
                break;
            case 2:
                changeEmpSal(s);
                break;
            case 3:
                break;
        }
    } while (option != 3); 
    system("cls");

    setColor(9);
    cout << "[Change Employee Salary at " << s->getLocation() << "]\n";
    setColor(7); 
}

void changeEmpSal(Shop* s){
    system("cls");
    setColor(9);
    cout << "<<Changing Employees salary in " << s->getLocation() << ">>\n";
    setColor(7);
    cout << "Employee name: ";
    string name;
    getline(cin, name);
    cout << "Employee NIF: ";
    int NIF = getInt(1e8, 999999999);
    Employee *e = NULL;             
    try{
        e = s->getEmployee(name, NIF);
        cout << "Salary: ";
        float salary = getFloat(635, 10000);
        e->setSalary(salary);
    }
    catch (EmployeeIsNotRegistered &e){
        cout << "Employee with name " << name << " and NIF " << NIF << " is not registered." << endl;
        Sleep(3000);
    }
}

void changeSalByPost(Bakery &bakery){
    system("cls");
    setColor(9);
    cout << "<<Changing Employees salary by post>>\n";
    setColor(7);
    bakery.printPosts(cout); 
    cout << "Enter Post: ";
    string post;
    getline(cin, post);
    cout << "Enter raise percentage: ";
    int percentage = getInt(-100, 200);        
    bakery.changeSalaryByPost(post, percentage);
}

void showEmpMenu(Bakery &bakery, Shop *s)
{

    int option = 0;
    do{
        system("cls");
        setColor(9);
        cout << "[Show Employees Menu]\n";  
        setColor(7);
        cout << "[1] Show all employees in " << s->getLocation()<< "\n" << "[2] Show all by post\n"; 
        cout << "[3] Show employees in " << s->getLocation()<< " by post \n" << "[4] Go back\nChoose an option: ";
        option = getInt(1, 4);                  
        switch (option) {
            case 1:               
                showAllEmps(s);
                break;
            case 2:
                showAllByPost(bakery);               
                break;
            case 3:
                showByPost(s);
                break;
            case 4:
                break;
        }
    } while (option != 4); 
    system("cls");

}

void showByPost(Shop * s){
    system("cls");
    setColor(9);
    cout << "[Showing Employees by post in "<< s->getLocation() << "]\n";  
    setColor(7);
    s->printAvailablePosts(cout); 
    cout << "Enter Post: ";
    string post;
    getline(cin, post);
    system("cls");
    setColor(9);
    cout << "[Showing all " << post << "s in "<< s->getLocation() << "]\n";
    s->printEmpByPost(cout, post);
    cout << "To go back to the manage employees page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void showAllEmps(Shop *s)
{
    system("cls");
    setColor(9);
    cout << "[Showing All Employees from " << s->getLocation() << "]\n";
    setColor(7);
    s->printEmployees(cout);
    cout << "To go back to the manage employees page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void showAllByPost(Bakery & bakery){
    system("cls");
    setColor(9);
    cout << "[Showing Employees by post]\n";  
    setColor(7);
    bakery.printPosts(cout); 
    cout << "Enter Post: ";
    string post;
    getline(cin, post);
    system("cls");
    setColor(9);
    cout << "[Showing all " << post << "s]\n"; 
    setColor(7);
    bakery.printAllEmpByPost(cout, post);
    cout << "To go back to the manage employees page press enter... ";
    string garbage;
    getline(cin, garbage);
}

void manageShops(Bakery &bakery)
{
    int option;

    do
    {
        system("cls");
        setColor(9);
        cout << "<<Manage Shops Menu>>\n";
        setColor(7);
        cout << "[1] Add Shop\n[2] Remove shop\n[3] Show shops information\n[4] Show sales volume\n[5] Show orders\n[6] Add products to shop\n[7] Remove products\n[8] Show products of shop\n[9] Go back\nChoose an option: ";
        option = getInt(1, 9);
        switch (option) {
        case 1:
            addShop(bakery);
            break;
        case 2:
            removeShop(bakery);
            break;
        case 3:
            showShopsInfo(bakery);
            break; 
        case 4:
            showSales(bakery);
            break;
        case 5:
            showOrders(bakery);
            break;
        case 6:
            addProductShop(bakery);
            break;
        case 7:
            removeProductShop(bakery);
            break;
        case 8:
            showProductShop(bakery);
            break;
        case 9:
            break;
        }
    } while (option != 9);        
}

void addShop(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Adding Shop]\n";
    setColor(7);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        bakery.addShop(shopLocation);
    }
    catch (ShopIsAlreadyRegistered &e)
    {
        cout << "There's a shop already registered at " << shopLocation;
        Sleep(3000);
    }
}

void removeShop(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Removing shop]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        bakery.removeShop(shopLocation); 
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }
}

void showShopsInfo(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Shops Information]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        Shop *s = bakery.getShop(shopLocation);
        system("cls");
        cout << *s;
        cout << "To go back to the manage shops menu press enter... ";
        string garbage;
        getline(cin, garbage);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }
}

void showSales(Bakery &bakery)
{
    int option = 0;

    do
    {
        system("cls");
        setColor(9);
        cout << "<<Show Sales Volume Menu>>\n";
        setColor(7);
        cout << "You wish to see:\n[1] Total sales\n[2] Individual Shop sales\n[3] Go back\nChoose an option: ";
        option = getInt(1, 3);
        switch(option)
        {
            case 1:
                showAllSalesVolume(bakery);
                break;
            case 2:
                showShopSalesVolume(bakery);
                break;
            case 3:
                return;
        }       
    } while (option != 3);
}

void showAllSalesVolume(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing Bakery Sales Volume]\n\n";
    setColor(7);
    bakery.printSalesVolume(cout);
    cout << "To go back to the show sales volume menu press enter... ";
    string garbage;
    getline(cin, garbage);
}

void showShopSalesVolume(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing Shops Sales Volume]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        Shop *s = bakery.getShop(shopLocation);
        system("cls");
        setColor(9);
        cout << "[Sales Volume from " << s->getLocation() << "]\n\n";
        setColor(7);
        s->printSalesVolume(cout);
        cout << "To go back to the show sales volume menu press enter... ";
        string garbage;
        getline(cin, garbage);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }
}

void showOrders(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Showing Shops Orders]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);
    try {
        Shop *s = bakery.getShop(shopLocation);
        system("cls");
        setColor(9);
        cout << "[Showing Orders from " << shopLocation << "]\n\n";
        setColor(7);
        s->printOrders(cout);
        cout << "To go back to the manage shops menu press enter... ";
        string garbage;
        getline(cin, garbage);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }
}

void addProductShop(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Choosing a Shop]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);

    Shop *s = NULL;

    try {
        s = bakery.getShop(shopLocation);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }

    system("cls");
    setColor(9);
    cout << "[Adding Product(s) to " << shopLocation << " shop]\n";
    setColor(7);

    bool done = false;
    struct Product product;

    while (!done)
    {
        cout << "New product name: ";
        getline(cin, product.name);
        cout << "New product category: ";
        getline(cin, product.category);
        cout << "New product price: ";
        product.price = getFloat(0, 10000);

        try
        {
            s->addProduct(product);
        }
        catch (ProductAlreadyAdded &e)
        {
            cout << "There's already a product with this name!\n";
        }

        cout << "Stop adding products? (Y/N) ";
        done = getYesNo();
    }
}

void removeProductShop(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Choosing a Shop]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);

    Shop *s = NULL;

    try {
        s = bakery.getShop(shopLocation);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }

    system("cls");
    setColor(9);
    cout << "[Removing a Product from " << shopLocation << "]\n";
    setColor(7);
    cout << "Product name: ";
    string prodName;
    getline(cin, prodName);

    try
    {
        s->removeProduct(prodName);
    }
    catch(ProductDoesNotExist &e)
    {
        cout << "Product does not exist in this shop!";
        Sleep(3000);
    }
}

void showProductShop(Bakery &bakery)
{
    system("cls");
    setColor(9);
    cout << "[Choosing a Shop]\n";
    setColor(7);
    bakery.printShopLocations(cout);
    string shopLocation;
    cout << "Shop location: ";
    getline(cin, shopLocation);

    Shop *s = NULL;

    try {
        s = bakery.getShop(shopLocation);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << shopLocation << " does not have a shop registered.";
        Sleep(3000);
    }

    system("cls");
    setColor(9);
    cout << "[Products from " << shopLocation << "]\n\n";
    setColor(7);
    s->printProducts(cout);
    cout << "To go back to the manage shops menu press enter... ";
    string garbage;
    getline(cin, garbage);
}

void loginEmployee(Bakery &bakery){

    system("cls");
    
    setColor(6);
    cout << "[Employee Login]\n";
    setColor(7);
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your NIF: ";
    int NIF = getInt(1e8, 999999999);
    cout << "Enter your shop: ";
    string shopName;
    getline(cin, shopName);

    Employee *e = NULL;
    Shop * s = NULL;
    try
    {
        s = bakery.getShop(shopName);
    }
    catch (LocationDoesNotHaveShop &e)
    {
        cout << "That shop doesn't exist.";
        Sleep(3000);
        return;
    }

    try{
        e = s->getEmployee(name, NIF);
    }
    catch (EmployeeIsNotRegistered &e){
        cout << "Employee is not registered, try again...";
        Sleep(3000);
        return;
    }

    employee(e, bakery, s);
}

void employee(Employee* e, Bakery &bakery, Shop* shop)
{
    int option;
    string garbage;
    
    do{
        system("cls");
        setColor(6);
        cout << "<<Welcome " << e->getName() << ">>\n";
        setColor(7);
        cout << "[1] See next order\n[2] Deliver next order\n[3] Go back to main menu page\nChoose an option: ";
        
        option = getInt(1, 3);
        
        switch (option) {
        case 1:
            system("cls");
            setColor(6);
            cout << "[Order to Deliver]\n\n";
            setColor(7);
            shop->printDel(e);
            cout << "\nTo go back to the employee menu press enter... ";
            getline(cin, garbage);
            break;
        case 2:
            if (shop->removeDel(e))
                cout << "Order is being delivered...\n";
            else
                cout << "There is no orders to deliver. Are you that distracted that you can't even remember what you have done?! \n";
            Sleep(3000);
            break;
        case 3:
            break;
        }
    } while (option != 3);
}
