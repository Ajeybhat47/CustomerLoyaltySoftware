#include <bits/stdc++.h>

using namespace std;

struct PurchaseRecord
{
    string itemName;
    double price;
    int quantity;
    string date;
};

struct Product
{
    string name;
    string price;
    int quantity;
    double discount;
    int profit;
    int promotion;
};
class Customer
{
public:
    string customer, phoneNumber;
    string loyalty_badge;
    int referrals;
    int loyalty_points;

public:
    vector<PurchaseRecord> total_purchase_record;
    Customer()
    {
        customer = "";
    }
    Customer(string name, string phone) // constructor for new customer
    {
        customer = name;
        phoneNumber = phone;
        loyalty_badge = "Bronze";
        referrals = 0;
        loyalty_points = 0;
        total_purchase_record = {};
    }
    Customer(string name, string phone, string loyal, int ref, int points) // constructor for
    {
        customer = name;
        phoneNumber = phone;
        loyalty_badge = loyal;
        referrals = ref;
        loyalty_points = points;
        total_purchase_record = {};
    }

    Customer &operator+=(int x)
    {
        this->loyalty_points = (this->loyalty_points + x);
        return *this;
    }

    Customer &operator-=(int x)
    {
        this->loyalty_points = (this->loyalty_points - x);
        return *this;
    }

    // distrctor
    //  ~Customer();

    void addPurchaseInfo(PurchaseRecord x);

    // void printCustomerDetails();

    void update_points();

    string get_loyalty_badge()
    {
        return loyalty_badge;
    }
    int get_loyalty_points()
    {
        return loyalty_points;
    }

    string printCustomerDetails()
    {
        cout << "name:" << customer << endl
             << "phone:" << phoneNumber << endl
             << "loyality:" << loyalty_badge << endl
             << "referrals:" << referrals << endl
             << "loyalty points:" << loyalty_points << endl;
        for (int i = 0; i < total_purchase_record.size(); i++)
        {
            cout << "item:" << total_purchase_record[i].itemName
                 << "   price:" << total_purchase_record[i].price
                 << "   quantity:" << total_purchase_record[i].quantity
                 << "   date:" << total_purchase_record[i].date << endl;
        }
    }

    string formatCustomerDetails()
    {
        stringstream s;
        s << customer << "," << phoneNumber << "," << loyalty_badge << "," << referrals << "," << loyalty_points << ",[";
        if (total_purchase_record.size() > 0)
        {
            for (int i = 0; i < total_purchase_record.size() - 1; i++)
            {
                s << "{'Item Name':" << total_purchase_record[i].itemName
                  << ",' Price':" << total_purchase_record[i].price
                  << ",' Quantity':" << total_purchase_record[i].quantity
                  << ",' Date':" << total_purchase_record[i].date << "},";
            }

            s << "{'Item Name':" << total_purchase_record[total_purchase_record.size() - 1].itemName
              << ",' Price':" << total_purchase_record[total_purchase_record.size() - 1].price
              << ",' Quantity':" << total_purchase_record[total_purchase_record.size() - 1].quantity
              << ",' Date':" << total_purchase_record[total_purchase_record.size() - 1].date;
        }
        else
            s << "{";
        s << "}]";
        string st = s.str();
        return st;
    }
    Customer operator+(const Customer &other) const
    {
        Customer mergedCustomer;

        // Merge basic information
        mergedCustomer.customer = this->customer;
        mergedCustomer.phoneNumber = this->phoneNumber;

        // Merge loyalty badge and referrals
        mergedCustomer.loyalty_badge = this->loyalty_badge;
        mergedCustomer.referrals = this->referrals + other.referrals;

        // Merge purchase records
        mergedCustomer.total_purchase_record = this->total_purchase_record;
        mergedCustomer.total_purchase_record.insert(
            mergedCustomer.total_purchase_record.end(),
            other.total_purchase_record.begin(),
            other.total_purchase_record.end());

        // Merge loyalty points
        mergedCustomer.loyalty_points = this->loyalty_points + other.loyalty_points;

        return mergedCustomer;
    }
};

class CLS
{
private:
    vector<string> top_user;
    vector<Product> top_items;

public:
    void top_coustmers(string catg);
    // void top_items();
    void add_top_coustmer(string x)
    {
        // cout<<x<<endl;
        top_user.push_back(x);
    }

    void promotion_products(vector<Product> prd);
    void add_product(Product p)
    {
        top_items.push_back(p);
    };

    void print()
    {
        for (auto i : top_user)
        {
            cout << i << endl;
        }
    }
};

class Reward
{
private:
    int points;
    string badge;

    map<string, float> disounts;

public:
    Reward(Customer cust)
    {
        points = cust.get_loyalty_points();
        badge = cust.get_loyalty_badge();

        if (points == 0)
            cust.update_points();
        points = cust.get_loyalty_points();

        ifstream file("leaguetier.csv");
        if (!file.is_open())
        {
            cout << "Failed to open the file." << endl;
            // return 1;
        }
        string line;

        getline(file, line);
        getline(file, line);
        getline(file, line);
        istringstream iss(line);
        string field;

        getline(iss, field, ',');
        float bronze_discount = stof(field);
        getline(iss, field, ',');
        float silver_discount = stof(field);

        getline(iss, field, ',');
        float gold_discount = stof(field);
        getline(iss, field, ',');
        float diamond_discount = stof(field);

        // cout << "Silver percent:" << silver_discount;
        // cout << "Gold percent:" << gold_discount << endl;
        // cout << "Silver percent:" << silver_discount;
        // cout << "Gold percent:" << gold_discount << endl;

        disounts = {{"Bronze", bronze_discount}, {"Silver", silver_discount}, {"Gold", gold_discount}, {"Diamond", diamond_discount}};
        ;

        file.close();
    }

    int add_points();
    float get_discount(string loyalty)
    {
        for (auto i : disounts)
        {
            if (i.first == loyalty)
            {
                return i.second;
            }
        }

        return 1;
    };
};

class Admin
{
private:
    static bool loggedIn;

public:
    static Customer mergeCustomers(const Customer &customer1, const Customer &customer2)
    {
        return customer1 + customer2;
    }
    // Static member variable to track admin login status

    static bool login(const string &username, const string &password)
    {
        // Perform login authentication logic here
        // You can compare the provided username and password with the correct credentials

        if (username == "admin" && password == "password")
        {
            loggedIn = true;
            return true;
        }

        return false;
    }

    static void logout()
    {
        loggedIn = false;
    }

    static bool isLoggedIn()
    {
        return loggedIn;
    }

    void print_top_customer(CLS c)
    {
        c.print();
    }

    Customer create_customer();
};
inline void welcomeBanner()
{
    system("cls");
    cout << "**********************************************\n";
    cout << "     Welcome to Customer Loyalty Software     \n";
    cout << "**********************************************\n\n";
}
bool Admin::loggedIn = false;
namespace Ajey
{
    namespace fileHandling
    {
        Customer searchfile(string customerName)
        {
            ifstream file("data.csv");
            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                Customer c1;
                return c1;
            }
            string line;

            getline(file, line);

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (customerName == field)
                {
                    getline(iss, field, ',');
                    string phone = field;
                    cout << field;

                    getline(iss, field, ',');
                    string loyality = field;
                    cout << field;

                    getline(iss, field, ',');
                    int referral = stoi(field);
                    cout << field;

                    getline(iss, field, ',');
                    int loyalty_points = stoi(field);
                    cout << field;

                    Customer currentCustomer(customerName, phone, loyality, referral, loyalty_points);

                    PurchaseRecord rec;

                    while (getline(iss, field, ','))
                    {

                        cout << endl;

                        cout << field.substr(field.find(':') + 1);
                        rec.itemName = field.substr(field.find(':') + 1);

                        getline(iss, field, ',');
                        // string phone = field;
                        cout << field.substr(field.find(':') + 1);
                        rec.price = stoi(field.substr(field.find(':') + 1));

                        getline(iss, field, ',');
                        rec.quantity = stoi(field.substr(field.find(':') + 1));
                        cout << field.substr(field.find(':') + 1);

                        getline(iss, field, ',');
                        cout << field.substr(field.find(':') + 1, 13);
                        rec.date = field.substr(field.find(':') + 1, 13);

                        currentCustomer.addPurchaseInfo(rec);
                    }
                    return currentCustomer;
                }
            }
        }
    }
    namespace customer
    {
        Customer newcustomer()
        {
            cout << "**********************************************\n";
            cout << "     Welcome to our Loyalty Program!     \n";
            cout << "**********************************************\n\n";

            cout << "Enter Name: ";
            string name;
            cin >> name;

            cout << "Enter Phone Number: ";
            string phone;
            cin >> phone;

            Customer c(name, phone);
            return c;
        }
        Customer oldCustomer()
        {
            cout << "enter Name" << endl;
            string name;
            cin >> name;

            // Customer c;
            return Ajey::fileHandling::searchfile(name);
        }
    }

    namespace rewards
    {
        int calulatePoints(vector<PurchaseRecord> pts)
        {
            int total_points = 0;
            int total_prc = 0;
            for (auto item : pts)
            {
                if (item.price > 25)
                {
                    total_points += item.price * item.quantity;
                    total_prc += item.price;
                }
            }
            return total_points;
        }

        string updateBadge(int pts)
        {

            ifstream file("leaguetier.csv");
            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                // return 1;
            }
            string line;

            getline(file, line);

            getline(file, line);
            istringstream iss(line);
            string field;

            getline(iss, field, ',');
            int bronze_limit = stoi(field);
            getline(iss, field, ',');
            int silver_limit = stoi(field);

            getline(iss, field, ',');
            int gold_limit = stoi(field);
            getline(iss, field, ',');
            int diamond_limit = stoi(field);

            // cout << "bronze=" << bronze_limit << endl;
            // cout << "silver=" << silver_limit << endl;
            // cout << "gold=" << gold_limit << endl;
            // cout << "diamond=" << diamond_limit << endl;

            file.close();
            if (pts < bronze_limit)
            {
                return "Bronze";
            }
            else if (pts < silver_limit)
            {
                return "Silver";
            }
            else if (pts < gold_limit)
            {
                return "Gold";
            }
            else
            {
                return "Diamond";
            }
        }
    }

}

namespace Aditya
{
    namespace fileHandling
    {
        Customer readCustomerFromFile(string customerName)
        {
            ifstream file("data.csv");
            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                // return 1;
            }
            string line;

            getline(file, line);

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (customerName == field)
                {
                    getline(iss, field, ',');
                    string phone = field;
                    // cout << field;

                    getline(iss, field, ',');
                    string loyality = field;
                    // cout << field;

                    getline(iss, field, ',');
                    int referral = stoi(field);
                    // cout << field;

                    getline(iss, field, ',');
                    int loyalty_points = stoi(field);

                    Customer currentCustomer(customerName, phone, loyality, referral, loyalty_points);

                    PurchaseRecord rec;

                    while (getline(iss, field, ','))
                    {

                        if (field == "[{}]")
                            break;
                        // cout << endl;

                        // cout << field.substr(field.find(':') + 1);
                        rec.itemName = field.substr(field.find(':') + 1);

                        getline(iss, field, ',');
                        // string phone = field;
                        // cout << field.substr(field.find(':') + 1);
                        rec.price = stoi(field.substr(field.find(':') + 1));

                        getline(iss, field, ',');
                        rec.quantity = stoi(field.substr(field.find(':') + 1));
                        // cout << field.substr(field.find(':') + 1);

                        getline(iss, field, ',');
                        // cout << field.substr(field.find(':') + 1, 13);
                        rec.date = field.substr(field.find(':') + 1, 10);

                        currentCustomer.addPurchaseInfo(rec);
                    }
                    file.close();
                    return currentCustomer;
                }
            }
            file.close();
            Customer temp;
            return temp;
        }

        void NewCustomerUpdate(Customer newCustomer)
        {
            ofstream file("data.csv", ios::app);
            // ifstream file2("data.csv");

            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                // return 1;
            }
            string line;

            file << '\n';
            file << newCustomer.formatCustomerDetails();

            file.close();
        }

        void updateReferral(string customerReferred)
        {
            ifstream file("data.csv");
            ofstream file2("temp.csv");

            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                // return 1;
            }
            string line;

            getline(file, line);
            file2 << line;

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (customerReferred == field)
                {
                    file2 << endl
                          << field << ',';
                    getline(iss, field, ',');
                    file2 << field << ',';
                    getline(iss, field, ',');
                    file2 << field << ',';

                    getline(iss, field, ',');
                    file2 << stoi(field) + 1 << ",";

                    getline(iss, field, ',');
                    file2 << stoi(field) + 100;

                    while (getline(iss, field, ','))
                    {
                        // getline(iss, field, ',');
                        file2 << ',' << field;
                    }
                }
                else
                {
                    file2 << endl
                          << line;
                }
            }
            file.close();
            file2.close();

            remove("data.csv");
            rename("temp.csv", "data.csv");
        }

        void updateCurrentCustomer(Customer c)
        {
            ifstream file("data.csv");
            ofstream file2("temp.csv");

            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                // return 1;
            }
            string line;

            getline(file, line);
            file2 << line;

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (c.customer == field)
                {
                    file2 << endl
                          << c.formatCustomerDetails();
                }
                else
                {
                    file2 << endl
                          << line;
                }
            }
            file.close();
            file2.close();

            remove("data.csv");
            rename("temp.csv", "data.csv");
        }

        int deleteCurrentCustomer(Customer c)
        {
            ifstream file("data.csv");
            ofstream file2("temp.csv");

            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                return 1;
                // return 1;
            }
            string line;

            getline(file, line);
            file2 << line;

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (c.customer == field)
                {
                    cout << "deleted customer" << endl;
                }
                else
                {
                    file2 << endl
                          << line;
                }
            }
            file.close();
            file2.close();

            remove("data.csv");
            rename("temp.csv", "data.csv");
        }

        int deleteCurrentCustomer(string customerName)
        {
            ifstream file("data.csv");
            ofstream file2("temp.csv");

            if (!file.is_open())
            {
                cout << "Failed to open the file." << endl;
                return 1;
            }
            string line;

            getline(file, line);
            file2 << line;

            while (getline(file, line))
            {
                istringstream iss(line);
                string field;

                getline(iss, field, ','); // Customer ID
                if (customerName == field)
                {
                    cout << "deleted customer" << endl;
                }
                else
                {
                    file2 << endl
                          << line;
                }
            }
            file.close();
            file2.close();

            remove("data.csv");
            rename("temp.csv", "data.csv");
        }
    }
    namespace customer
    {
        Customer newcustomer()
        {
            welcomeBanner();

            cout << "Enter Name: ";
            string name;
            cin >> name;

            cout << "Enter Phone Number: ";
            string phone;
            cin >> phone;
            if (phone.length() == 10)
            {
                if (stoi(phone))
                {
                    Customer c(name, phone);
                    Aditya::fileHandling::NewCustomerUpdate(c);
                    cout << "New Customer added successfully with following details" << endl;

                    return c;
                }
            }
            else
            {
                cout << "wrong phone number" << endl;
            }
        }
        Customer oldCustomer()
        {
            welcomeBanner();

            cout << "enter Name" << endl;
            string name;
            cin >> name;

            return Aditya::fileHandling::readCustomerFromFile(name);
        }
        void isReferred()
        {
            cout << "which customer referred you?" << endl;
            string referCustomer;
            cin >> referCustomer;
            Aditya::fileHandling::updateReferral(referCustomer);
        }
    }
}

void CLS::top_coustmers(string catg)
{
    ifstream file("data.csv");
    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
    }
    string line;

    getline(file, line, ',');
    int count = 0;

    while (catg != line)
    {
        getline(file, line, ',');
        count++;
    }

    while (getline(file, line))
    {
        istringstream iss(line);
        string field;
        string id;
        getline(iss, id, ','); // Customer ID
        int i = count;
        while (i--)
        {
            getline(iss, field, ',');
        }
        // cout<<field<<endl;
        if (field == "Gold" || field == "Diamond")
        {
            // cout<<id<<endl;
            add_top_coustmer(id);
        }
    }
    file.close();
}

void Customer::update_points()
{

    int points = Ajey::rewards::calulatePoints(total_purchase_record);
    loyalty_badge = Ajey::rewards::updateBadge(points);
    loyalty_points = points + referrals * 10;
}

void Customer::addPurchaseInfo(PurchaseRecord x)
{
    total_purchase_record.push_back(x);
}

namespace Ananth
{
    vector<Product> readProductFile(const string &filename, Customer c)
    {
        vector<Product> products;
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, id, price, profit, quantityStr, discount, promotion;
                if (!getline(ss, name, ','))
                    continue;
                if (!getline(ss, id, ','))
                    continue;
                if (!getline(ss, price, ','))
                    continue;
                if (!getline(ss, profit, ','))
                    continue;
                if (!getline(ss, quantityStr, ','))
                    continue;

                if (!getline(ss, discount, ','))
                    continue;
                if (!getline(ss, promotion, ','))
                    continue;

                try
                {
                    int quantity = stoi(quantityStr);

                    Product product;
                    product.name = name;
                    product.quantity = quantity;

                    // cout << "---------" << c.loyalty_badge << endl;
                    Reward r(c);
                    cout << "-----" << r.get_discount(c.loyalty_badge);
                    product.promotion = stoi(promotion);
                    if (product.promotion == 1)
                    {
                        product.discount = round(stod(discount) + r.get_discount(c.loyalty_badge));
                    }
                    else
                    {

                        product.discount = round(stod(discount));
                    }

                    product.price = to_string(int(round(stod(price) - (stod(discount) / 100) * stod(price))));
                    products.push_back(product);
                }
                catch (const invalid_argument &e)
                {
                    // Handle invalid quantity argument
                    cout << "Invalid quantity argument: " << quantityStr << endl;
                }
            }
            file.close();
        }
        return products;
    }

    void printProductTable(const vector<Product> &products)
    {
        cout << "Product Table" << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;
        cout << setw(20) << left << "| Product Name";
        cout << setw(15) << left << "| Price";
        cout << setw(10) << left << "| Discount"
             << "|" << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;
        for (const auto &product : products)
        {
            cout << "|" << setw(20) << left << product.name;
            cout << "|" << setw(15) << left << product.price;
            cout << "|" << setw(5) << left << product.discount << "%"
                 << "|" << [product]()
            { return (product.promotion) ? "Special Offer! Upto 12% extra discout " : " "; }()
                 << endl;
        }
        cout << "----------------------------------------------------------------------------------------------" << endl;
    }
}

void CLS::promotion_products(vector<Product> products)
{
    //  vector<Product> products = Ananth::readProductFile(filename);
    for (auto i : products)
    {
        if (i.promotion)
        {
            add_product(i);
        }
    }
}
Customer Admin::create_customer()
{
    Customer cus1 = Aditya::customer::newcustomer();
    return cus1;
}
int main()
{
    string input;
    int choice;

    // Welcome statement with design

    do
    {
        // Display menu options
        welcomeBanner();
        cout << "1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        // Convert the input string to an integer
        try
        {
            choice = stoi(input);

            // Handle user's choice
            if (choice == 1)
            {
                try
                {
                    int userChoice = stoi(input);
                    if (userChoice == 1)
                    {
                        welcomeBanner();
                        cout << "Choose an option:\n";
                        cout << "1. Existing Customer\n";
                        cout << "2. New Customer\n";
                        cout << "Enter your choice: ";
                        getline(cin, input);

                        try
                        {
                            int userChoice = stoi(input);
                            if (userChoice == 1)
                            {

                                Customer currentCustomer = Aditya::customer::oldCustomer();
                                // ... perform operations for existing customer ...
                                // cout << currentCustomer.formatCustomerDetails();
                                if (currentCustomer.customer == "")
                                {
                                    cout << endl
                                         << "USER DOES NOT EXIST" << endl;
                                    break;
                                }

                                string choice1 = "-1";
                                while (choice1 != "0")
                                {

                                    // welcomeBanner();
                                    cout << endl
                                         << "Hello " << currentCustomer.customer << "!" << endl
                                         << "Your Loyalty League is " << currentCustomer.loyalty_badge << ", you have " << currentCustomer.loyalty_points << " points";
                                    cout << endl
                                         << "Press:" << endl
                                         << "1.Buy Product" << endl
                                         << "2.Redeem Loyalty Points" << endl
                                         << "3.Purchase History" << endl
                                         << "0.Back" << endl;
                                    cin >> choice1;

                                    if (choice1 == "1")
                                    {
                                        string filename = "product_dataset.csv";
                                        vector<Product> products = Ananth::readProductFile(filename, currentCustomer);
                                        // CLS prod;
                                        // prod.promotion_products(products);

                                        Ananth::printProductTable(products);

                                        cout << "Enter product Number which you want to buy." << endl;
                                        string product_index;
                                        cin >> product_index;
                                        string quantity;
                                        cout << "How many?" << endl;
                                        cin >> quantity;
                                        PurchaseRecord p;

                                        if (isdigit(product_index[0]))
                                        {
                                            try
                                            {
                                                if (stoi(quantity) >= 0 && stoi(quantity))
                                                    p.itemName = products[stoi(product_index) - 1].name;
                                                p.price = stod(products[stoi(product_index) - 1].price);
                                                p.date = "2023-07-01";
                                                p.quantity = stoi(quantity);

                                                cout << "you spent " << p.price * p.quantity << " $ "
                                                     //  << "and gained " << round(p.price * p.quantity) << " points!"
                                                     << endl;

                                                currentCustomer.addPurchaseInfo(p);
                                                // currentCustomer.loyalty_points = currentCustomer.loyalty_points + round(p.price * p.quantity);
                                                currentCustomer += round(p.price * p.quantity);
                                                // string badge = Ajey::rewards::updateBadge(currentCustomer.get_loyalty_points());
                                                Aditya::fileHandling::updateCurrentCustomer(currentCustomer);

                                                currentCustomer.update_points();

                                                Aditya::fileHandling::updateCurrentCustomer(currentCustomer);
                                            }
                                            catch (...)
                                            {
                                                cout << "wrong input" << endl;
                                            }
                                        }
                                    }
                                    else if (choice1 == "2")
                                    {
                                        cout << "redeem points, Press 1 to exchange 1000 points for 100rs . 0.Back" << endl;
                                        string choice2;
                                        cin >> choice2;
                                        if (choice2 == "1")
                                        {
                                            if (currentCustomer.loyalty_points > 1000)
                                            {
                                                currentCustomer -= 1000;
                                                Aditya::fileHandling::updateCurrentCustomer(currentCustomer);

                                                // currentCustomer.update_points();

                                                Aditya::fileHandling::updateCurrentCustomer(currentCustomer);
                                            }
                                            else
                                            {
                                                cout << "not enough points to exchange";
                                            }
                                            cout << "press any key to go back" << endl;
                                            cin >> choice2;
                                        }
                                    }
                                    else if (choice1 == "3")
                                    {
                                        currentCustomer.printCustomerDetails();
                                    }
                                }
                            }
                            else if (userChoice == 2)
                            {
                                Customer currentCustomer = Aditya::customer::newcustomer();
                                // cout << currentCustomer.customer << endl;

                                cout << currentCustomer.formatCustomerDetails();
                                cout << endl
                                     << endl
                                     << "PRESS 1 if you were referred else press 0." << endl;
                                string ref;
                                cin >> ref;
                                if (ref == "1")
                                {
                                    Aditya::customer::isReferred();
                                }
                                // ... perform operations for new customer ...
                            }
                            else
                            {
                                cout << "Invalid choice. Please try again.\n";
                                continue;
                            }
                        }
                        catch (const invalid_argument &e)
                        {
                            cout << "Invalid input. Please enter a valid choice.\n";
                            continue;
                        }
                        catch (const out_of_range &e)
                        {
                            cout << "Invalid input. The entered value is out of range.\n";
                            continue;
                        }
                    }
                    else if (userChoice == 2)
                    {
                        Customer currentCustomer = Aditya::customer::newcustomer();

                        cout << "New Customer added successfully with following details" << endl;
                        cout << currentCustomer.formatCustomerDetails();
                        cout << endl
                             << endl
                             << "PRESS 1 if you were referred else press 0." << endl;
                        string ref;
                        cin >> ref;
                        if (ref == "1")
                        {
                            Aditya::customer::isReferred();
                        }

                        // ... perform operations for new customer ...
                    }
                    else
                    {
                        cout << "Invalid choice. Please try again.\n";
                        continue;
                    }
                }
                catch (const invalid_argument &e)
                {
                    cout << "Invalid input. Please enter a valid choice.\n";
                    continue;
                }
                catch (const out_of_range &e)
                {
                    cout << "Invalid input. The entered value is out of range.\n";
                    continue;
                }
            }
            else if (choice == 2)
            {
                // Handle admin login
                cout << "Admin login\n";
                fflush(stdin);
                int ch;
                string username, password;
                do
                {
                    cout << "Enter admin username: " << endl;
                    cin >> username;

                    cout << "Enter password for the above user name: " << endl;
                    cin >> password;
                    if (Admin::login(username, password))
                    {
                        cout << "Login successful!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "Login failed!" << endl;
                        cout << "Press 1 to try again or 0 to exit" << endl;
                        cin >> ch;
                    }
                } while (ch);
                // if(Admin::isLoggedIn())
                // {

                while (Admin::isLoggedIn())
                {
                    Admin admin;
                    cout << "1.find Top customers" << endl
                         << "2.merge customer" << endl
                         << "3.delete customer" << endl
                         << "4.add new customer" << endl
                         << "5.logout" << endl;
                    fflush(stdin);
                    int choice_ad;
                    cin >> choice_ad;

                    if (choice_ad == 1)
                    {
                        CLS c;
                        c.top_coustmers("Loyalty Badge");
                        admin.print_top_customer(c);

                        // Logic for finding top customers
                    }
                    else if (choice_ad == 2)
                    {
                        // Logic for merging customers
                        Customer c1 = Aditya::customer::oldCustomer();
                        Customer c2 = Aditya::customer::oldCustomer();
                        Customer Customer3 = Admin::mergeCustomers(c1, c2);

                        Aditya::fileHandling::updateCurrentCustomer(Customer3);
                        Aditya::fileHandling::deleteCurrentCustomer(c2);
                    }
                    else if (choice_ad == 3)
                    {
                        cout << "which customer you want to delete?" << endl;
                        string deleteCustomer;
                        cin >> deleteCustomer;
                        Aditya::fileHandling::deleteCurrentCustomer(deleteCustomer);
                    }
                    else if (choice_ad == 4)
                    {
                        Customer customer = admin.create_customer();
                    }
                    else if (choice_ad == 5)
                    {
                        Admin::logout();
                    }
                    else
                    {
                        // Invalid choice
                        cout << "Invalid choice. Please select a valid option." << endl;
                    }
                }

                // ... perform admin login operations ...
            }
            else if (choice == 3)
            {
                cout << "Exiting...\n";
                // ... perform exit operations ...
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }
        catch (const out_of_range &e)
        {
            cout << "Invalid input. The entered value is out of range.\n";
            continue;
        }

        cout << "\n";
    } while (choice != 3);

    return 0;
}