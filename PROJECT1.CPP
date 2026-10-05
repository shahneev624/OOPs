#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;


// ============================================================
// PRODUCT CLASS
// ============================================================

class Product
{
private:
    int productId;
    string name;
    string category;
    double price;
    int stock;

public:

    Product()
    {
        productId = 0;
        name = "";
        category = "";
        price = 0;
        stock = 0;
    }

    Product(int id, string n, string c, double p, int s)
    {
        productId = id;
        name = n;
        category = c;
        price = p;
        stock = s;
    }

    int getId()
    {
        return productId;
    }

    string getName()
    {
        return name;
    }

    string getCategory()
    {
        return category;
    }

    double getPrice()
    {
        return price;
    }

    int getStock()
    {
        return stock;
    }

    void setName(string n)
    {
        name = n;
    }

    void setCategory(string c)
    {
        category = c;
    }

    void setPrice(double p)
    {
        price = p;
    }

    void setStock(int s)
    {
        stock = s;
    }

    void display()
    {
        cout << left
             << setw(8) << productId
             << setw(22) << name
             << setw(18) << category
             << setw(12) << fixed << setprecision(2) << price
             << setw(8) << stock
             << endl;
    }
};


// ============================================================
// ABSTRACT USER CLASS
// ============================================================

class User
{
protected:
    int userId;
    string name;
    string email;
    string password;

public:

    User()
    {
        userId = 0;
        name = "";
        email = "";
        password = "";
    }

    User(int id, string n, string e, string p)
    {
        userId = id;
        name = n;
        email = e;
        password = p;
    }

    virtual void display() = 0;

    int getUserId()
    {
        return userId;
    }

    string getName()
    {
        return name;
    }

    string getEmail()
    {
        return email;
    }

    string getPassword()
    {
        return password;
    }
};


// ============================================================
// CART ITEM CLASS
// ============================================================

class CartItem
{
private:
    Product product;
    int quantity;

public:

    CartItem(Product p, int q)
    {
        product = p;
        quantity = q;
    }

    Product getProduct()
    {
        return product;
    }

    int getQuantity()
    {
        return quantity;
    }

    void increaseQuantity(int q)
    {
        quantity += q;
    }

    double getTotal()
    {
        return product.getPrice() * quantity;
    }

    void display()
    {
        cout << left
             << setw(8) << product.getId()
             << setw(22) << product.getName()
             << setw(10) << quantity
             << setw(12) << fixed << setprecision(2)
             << product.getPrice()
             << setw(12) << getTotal()
             << endl;
    }
};


// ============================================================
// CART CLASS
// ============================================================

class Cart
{
private:
    vector<CartItem> items;

public:

    // Operator overloading
    Cart& operator+(Product product)
    {
        addProduct(product, 1);
        return *this;
    }

    void addProduct(Product product, int quantity)
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].getProduct().getId() == product.getId())
            {
                items[i].increaseQuantity(quantity);
                return;
            }
        }

        items.push_back(CartItem(product, quantity));
    }

    void removeProduct(int productId)
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].getProduct().getId() == productId)
            {
                items.erase(items.begin() + i);

                cout << "\nProduct removed from cart.\n";
                return;
            }
        }

        cout << "\nProduct not found in cart.\n";
    }

    bool isEmpty()
    {
        return items.empty();
    }

    vector<CartItem> getItems()
    {
        return items;
    }

    double calculateTotal()
    {
        double total = 0;

        for (int i = 0; i < items.size(); i++)
        {
            total += items[i].getTotal();
        }

        return total;
    }

    void displayCart()
    {
        if (items.empty())
        {
            cout << "\nYour cart is empty.\n";
            return;
        }

        cout << "\n============================================================\n";
        cout << "                         YOUR CART\n";
        cout << "============================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(22) << "Product"
             << setw(10) << "Qty"
             << setw(12) << "Price"
             << setw(12) << "Total"
             << endl;

        cout << "------------------------------------------------------------\n";

        for (int i = 0; i < items.size(); i++)
        {
            items[i].display();
        }

        cout << "------------------------------------------------------------\n";

        cout << "Cart Total: Rs. "
             << fixed << setprecision(2)
             << calculateTotal()
             << endl;
    }

    void clearCart()
    {
        items.clear();
    }
};


// ============================================================
// CUSTOMER CLASS
// ============================================================

class Customer : public User
{
private:
    string phone;
    string address;
    Cart cart;

public:

    Customer()
    {
        phone = "";
        address = "";
    }

    Customer(
        int id,
        string n,
        string e,
        string p,
        string ph,
        string a
    ) : User(id, n, e, p)
    {
        phone = ph;
        address = a;
    }

    void display() override
    {
        cout << "\n========================================\n";
        cout << "             CUSTOMER PROFILE\n";
        cout << "========================================\n";

        cout << "Customer ID : " << userId << endl;
        cout << "Name        : " << name << endl;
        cout << "Email       : " << email << endl;
        cout << "Phone       : " << phone << endl;
        cout << "Address     : " << address << endl;
    }

    Cart& getCart()
    {
        return cart;
    }

    string getPhone()
    {
        return phone;
    }

    string getAddress()
    {
        return address;
    }
};


// ============================================================
// ADMIN CLASS
// ============================================================

class Admin : public User
{
public:

    Admin(
        int id,
        string n,
        string e,
        string p
    ) : User(id, n, e, p)
    {
    }

    void display() override
    {
        cout << "\n========================================\n";
        cout << "              ADMIN PROFILE\n";
        cout << "========================================\n";

        cout << "Admin ID : " << userId << endl;
        cout << "Name     : " << name << endl;
        cout << "Email    : " << email << endl;
    }
};


// ============================================================
// ONLINE SHOPPING CENTRE CLASS
// ============================================================

class OnlineShoppingCentre
{
private:

    vector<Product> products;
    vector<Customer> customers;

    int nextProductId;
    int nextCustomerId;
    int nextOrderId;

public:

    OnlineShoppingCentre()
    {
        nextProductId = 101;
        nextCustomerId = 1001;
        nextOrderId = 5001;

        loadProducts();
        loadCustomers();
        findLastOrderId();
    }


    // ========================================================
    // PRODUCT FILE HANDLING
    // ========================================================

    void saveProducts()
    {
        ofstream file("products.txt");

        for (int i = 0; i < products.size(); i++)
        {
            file << products[i].getId() << "|"
                 << products[i].getName() << "|"
                 << products[i].getCategory() << "|"
                 << products[i].getPrice() << "|"
                 << products[i].getStock()
                 << endl;
        }

        file.close();
    }


    void loadProducts()
    {
        ifstream file("products.txt");

        if (!file)
        {
            products.push_back(
                Product(101, "Laptop", "Electronics", 65000, 10)
            );

            products.push_back(
                Product(102, "Smartphone", "Electronics", 25000, 15)
            );

            products.push_back(
                Product(103, "Headphones", "Electronics", 2500, 20)
            );

            products.push_back(
                Product(104, "Keyboard", "Accessories", 1500, 25)
            );

            products.push_back(
                Product(105, "Mouse", "Accessories", 800, 30)
            );

            products.push_back(
                Product(106, "T-Shirt", "Clothing", 999, 20)
            );

            products.push_back(
                Product(107, "Shoes", "Footwear", 2499, 15)
            );

            saveProducts();

            return;
        }

        string line;

        while (getline(file, line))
        {
            try
            {
                size_t p1 = line.find("|");
                size_t p2 = line.find("|", p1 + 1);
                size_t p3 = line.find("|", p2 + 1);
                size_t p4 = line.find("|", p3 + 1);

                int id =
                    stoi(line.substr(0, p1));

                string name =
                    line.substr(
                        p1 + 1,
                        p2 - p1 - 1
                    );

                string category =
                    line.substr(
                        p2 + 1,
                        p3 - p2 - 1
                    );

                double price =
                    stod(
                        line.substr(
                            p3 + 1,
                            p4 - p3 - 1
                        )
                    );

                int stock =
                    stoi(line.substr(p4 + 1));

                products.push_back(
                    Product(
                        id,
                        name,
                        category,
                        price,
                        stock
                    )
                );

                if (id >= nextProductId)
                    nextProductId = id + 1;
            }
            catch (...)
            {
                // Ignore invalid product record
            }
        }

        file.close();
    }


    // ========================================================
    // CUSTOMER FILE HANDLING
    // ========================================================

    void saveCustomers()
    {
        ofstream file("customers.txt");

        for (int i = 0; i < customers.size(); i++)
        {
            file << customers[i].getUserId() << "|"
                 << customers[i].getName() << "|"
                 << customers[i].getEmail() << "|"
                 << customers[i].getPassword() << "|"
                 << customers[i].getPhone() << "|"
                 << customers[i].getAddress()
                 << endl;
        }

        file.close();
    }


    void loadCustomers()
    {
        ifstream file("customers.txt");

        if (!file)
        {
            return;
        }

        string line;

        while (getline(file, line))
        {
            try
            {
                size_t p1 = line.find("|");
                size_t p2 = line.find("|", p1 + 1);
                size_t p3 = line.find("|", p2 + 1);
                size_t p4 = line.find("|", p3 + 1);
                size_t p5 = line.find("|", p4 + 1);

                int id =
                    stoi(line.substr(0, p1));

                string name =
                    line.substr(
                        p1 + 1,
                        p2 - p1 - 1
                    );

                string email =
                    line.substr(
                        p2 + 1,
                        p3 - p2 - 1
                    );

                string password =
                    line.substr(
                        p3 + 1,
                        p4 - p3 - 1
                    );

                string phone =
                    line.substr(
                        p4 + 1,
                        p5 - p4 - 1
                    );

                string address =
                    line.substr(p5 + 1);

                customers.push_back(
                    Customer(
                        id,
                        name,
                        email,
                        password,
                        phone,
                        address
                    )
                );

                if (id >= nextCustomerId)
                    nextCustomerId = id + 1;
            }
            catch (...)
            {
                // Ignore invalid customer record
            }
        }

        file.close();
    }


    // ========================================================
    // FIND LAST ORDER ID
    // ========================================================

    void findLastOrderId()
    {
        ifstream file("orders.txt");

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.find("Order ID:") == 0)
            {
                try
                {
                    int id =
                        stoi(line.substr(9));

                    if (id >= nextOrderId)
                        nextOrderId = id + 1;
                }
                catch (...)
                {
                }
            }
        }

        file.close();
    }


    // ========================================================
    // DISPLAY PRODUCTS
    // ========================================================

    void displayProducts()
    {
        cout << "\n====================================================================\n";
        cout << "                         ALL PRODUCTS\n";
        cout << "====================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(22) << "Product"
             << setw(18) << "Category"
             << setw(12) << "Price"
             << setw(8) << "Stock"
             << endl;

        cout << "--------------------------------------------------------------------\n";

        for (int i = 0; i < products.size(); i++)
        {
            products[i].display();
        }

        cout << "====================================================================\n";
    }


    // ========================================================
    // SEARCH PRODUCT - FUNCTION OVERLOADING
    // ========================================================

    void searchProduct(int id)
    {
        for (int i = 0; i < products.size(); i++)
        {
            if (products[i].getId() == id)
            {
                cout << "\nProduct Found:\n";

                products[i].display();

                return;
            }
        }

        cout << "\nProduct not found.\n";
    }


    void searchProduct(string name)
    {
        bool found = false;

        for (int i = 0; i < products.size(); i++)
        {
            if (products[i].getName() == name)
            {
                products[i].display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nProduct not found.\n";
        }
    }


    // ========================================================
    // FIND PRODUCT
    // ========================================================

    Product* findProduct(int id)
    {
        for (int i = 0; i < products.size(); i++)
        {
            if (products[i].getId() == id)
            {
                return &products[i];
            }
        }

        return nullptr;
    }


    // ========================================================
    // SIGN UP
    // ========================================================

    void signUp()
    {
        string name;
        string email;
        string password;
        string phone;
        string address;

        cin.ignore();

        cout << "\n========================================\n";
        cout << "              CUSTOMER SIGN UP\n";
        cout << "========================================\n";

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Email: ";
        getline(cin, email);

        // Check duplicate email
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getEmail() == email)
            {
                cout << "\nThis email is already registered.\n";
                cout << "Please use Sign In.\n";
                return;
            }
        }

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Address: ";
        getline(cin, address);

        Customer newCustomer(
            nextCustomerId,
            name,
            email,
            password,
            phone,
            address
        );

        customers.push_back(newCustomer);

        saveCustomers();

        cout << "\n========================================\n";
        cout << "       ACCOUNT CREATED SUCCESSFULLY\n";
        cout << "========================================\n";

        cout << "Customer ID: "
             << nextCustomerId
             << endl;

        cout << "\nYou can now Sign In.\n";

        nextCustomerId++;
    }


    // ========================================================
    // CUSTOMER SIGN IN
    // ========================================================

    Customer* signIn()
    {
        string email;
        string password;

        cin.ignore();

        cout << "\n========================================\n";
        cout << "             CUSTOMER SIGN IN\n";
        cout << "========================================\n";

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Password: ";
        getline(cin, password);

        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getEmail() == email)
            {
                if (customers[i].getPassword() == password)
                {
                    cout << "\nSign In Successful!\n";
                    cout << "Welcome "
                         << customers[i].getName()
                         << "!\n";

                    return &customers[i];
                }
                else
                {
                    cout << "\nIncorrect password.\n";
                    return nullptr;
                }
            }
        }

        cout << "\nNo account found with this email.\n";
        cout << "Please Sign Up first.\n";

        return nullptr;
    }


    // ========================================================
    // ADMIN SIGN IN
    // ========================================================

    bool adminSignIn()
    {
        string email;
        string password;

        cin.ignore();

        cout << "\n========================================\n";
        cout << "              ADMIN SIGN IN\n";
        cout << "========================================\n";

        cout << "Enter Admin Email: ";
        getline(cin, email);

        cout << "Enter Password: ";
        getline(cin, password);

        if (
            email == "admin@shopping.com" &&
            password == "admin123"
        )
        {
            cout << "\nAdmin Sign In Successful!\n";
            return true;
        }

        cout << "\nInvalid admin credentials.\n";

        return false;
    }


    // ========================================================
    // ADD PRODUCT
    // ========================================================

    void addProduct()
    {
        string name;
        string category;
        double price;
        int stock;

        cin.ignore();

        cout << "\nEnter Product Name: ";
        getline(cin, name);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Stock: ";
        cin >> stock;

        if (price < 0 || stock < 0)
        {
            cout << "\nInvalid price or stock.\n";
            return;
        }

        Product product(
            nextProductId,
            name,
            category,
            price,
            stock
        );

        products.push_back(product);

        saveProducts();

        cout << "\nProduct added successfully.\n";
        cout << "Product ID: "
             << nextProductId
             << endl;

        nextProductId++;
    }


    // ========================================================
    // UPDATE PRODUCT
    // ========================================================

    void updateProduct()
    {
        int id;

        cout << "\nEnter Product ID: ";
        cin >> id;

        Product* product = findProduct(id);

        if (product == nullptr)
        {
            cout << "\nProduct not found.\n";
            return;
        }

        int choice;

        cout << "\n1. Update Name";
        cout << "\n2. Update Category";
        cout << "\n3. Update Price";
        cout << "\n4. Update Stock";

        cout << "\n\nEnter choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1)
        {
            string name;

            cout << "Enter New Name: ";
            getline(cin, name);

            product->setName(name);
        }
        else if (choice == 2)
        {
            string category;

            cout << "Enter New Category: ";
            getline(cin, category);

            product->setCategory(category);
        }
        else if (choice == 3)
        {
            double price;

            cout << "Enter New Price: ";
            cin >> price;

            if (price < 0)
            {
                cout << "\nInvalid price.\n";
                return;
            }

            product->setPrice(price);
        }
        else if (choice == 4)
        {
            int stock;

            cout << "Enter New Stock: ";
            cin >> stock;

            if (stock < 0)
            {
                cout << "\nInvalid stock.\n";
                return;
            }

            product->setStock(stock);
        }
        else
        {
            cout << "\nInvalid choice.\n";
            return;
        }

        saveProducts();

        cout << "\nProduct updated successfully.\n";
    }


    // ========================================================
    // DELETE PRODUCT
    // ========================================================

    void deleteProduct()
    {
        int id;

        cout << "\nEnter Product ID: ";
        cin >> id;

        for (int i = 0; i < products.size(); i++)
        {
            if (products[i].getId() == id)
            {
                products.erase(products.begin() + i);

                saveProducts();

                cout << "\nProduct deleted successfully.\n";

                return;
            }
        }

        cout << "\nProduct not found.\n";
    }


    // ========================================================
    // ADD TO CART
    // ========================================================

    void addToCart(Customer& customer)
    {
        int id;
        int quantity;

        displayProducts();

        cout << "\nEnter Product ID: ";
        cin >> id;

        Product* product = findProduct(id);

        if (product == nullptr)
        {
            cout << "\nProduct not found.\n";
            return;
        }

        if (product->getStock() == 0)
        {
            cout << "\nProduct is out of stock.\n";
            return;
        }

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "\nInvalid quantity.\n";
            return;
        }

        if (quantity > product->getStock())
        {
            cout << "\nOnly "
                 << product->getStock()
                 << " items available.\n";

            return;
        }

        customer.getCart().addProduct(
            *product,
            quantity
        );

        cout << "\nProduct added to cart successfully.\n";
    }


    // ========================================================
    // REMOVE FROM CART
    // ========================================================

    void removeFromCart(Customer& customer)
    {
        customer.getCart().displayCart();

        if (customer.getCart().isEmpty())
            return;

        int id;

        cout << "\nEnter Product ID to remove: ";
        cin >> id;

        customer.getCart().removeProduct(id);
    }


    // ========================================================
    // PLACE ORDER
    // ========================================================

    void placeOrder(Customer& customer)
    {
        if (customer.getCart().isEmpty())
        {
            cout << "\nYour cart is empty.\n";
            return;
        }

        vector<CartItem> items =
            customer.getCart().getItems();

        // Check stock
        for (int i = 0; i < items.size(); i++)
        {
            Product* product =
                findProduct(
                    items[i].getProduct().getId()
                );

            if (product == nullptr)
            {
                cout << "\nProduct is no longer available.\n";
                return;
            }

            if (
                items[i].getQuantity()
                > product->getStock()
            )
            {
                cout << "\nNot enough stock for "
                     << product->getName()
                     << ".\n";

                return;
            }
        }

        // Reduce stock
        for (int i = 0; i < items.size(); i++)
        {
            Product* product =
                findProduct(
                    items[i].getProduct().getId()
                );

            product->setStock(
                product->getStock()
                - items[i].getQuantity()
            );
        }

        saveProducts();

        double subtotal =
            customer.getCart().calculateTotal();

        double gst =
            subtotal * 0.18;

        double total =
            subtotal + gst;


        // ====================================================
        // BILL
        // ====================================================

        cout << "\n\n";
        cout << "============================================================\n";
        cout << "                       ORDER BILL\n";
        cout << "============================================================\n";

        cout << "Order ID : "
             << nextOrderId
             << endl;

        cout << "Customer : "
             << customer.getName()
             << endl;

        cout << "Email    : "
             << customer.getEmail()
             << endl;

        cout << "------------------------------------------------------------\n";

        cout << left
             << setw(22) << "Product"
             << setw(10) << "Qty"
             << setw(12) << "Price"
             << setw(12) << "Total"
             << endl;

        cout << "------------------------------------------------------------\n";

        for (int i = 0; i < items.size(); i++)
        {
            cout << left
                 << setw(22)
                 << items[i].getProduct().getName()
                 << setw(10)
                 << items[i].getQuantity()
                 << setw(12)
                 << fixed << setprecision(2)
                 << items[i].getProduct().getPrice()
                 << setw(12)
                 << items[i].getTotal()
                 << endl;
        }

        cout << "------------------------------------------------------------\n";

        cout << "Subtotal    : Rs. "
             << subtotal
             << endl;

        cout << "GST (18%)   : Rs. "
             << gst
             << endl;

        cout << "------------------------------------------------------------\n";

        cout << "Grand Total : Rs. "
             << total
             << endl;

        cout << "============================================================\n";

        cout << "             ORDER PLACED SUCCESSFULLY\n";

        cout << "============================================================\n";


        saveOrder(
            customer,
            items,
            subtotal,
            gst,
            total
        );

        nextOrderId++;

        customer.getCart().clearCart();
    }


    // ========================================================
    // SAVE ORDER
    // ========================================================

    void saveOrder(
        Customer& customer,
        vector<CartItem> items,
        double subtotal,
        double gst,
        double total
    )
    {
        ofstream file(
            "orders.txt",
            ios::app
        );

        file << "Order ID: "
             << nextOrderId
             << endl;

        file << "Customer ID: "
             << customer.getUserId()
             << endl;

        file << "Customer: "
             << customer.getName()
             << endl;

        file << "Email: "
             << customer.getEmail()
             << endl;

        for (int i = 0; i < items.size(); i++)
        {
            file << items[i].getProduct().getName()
                 << " | Quantity: "
                 << items[i].getQuantity()
                 << " | Price: "
                 << items[i].getProduct().getPrice()
                 << endl;
        }

        file << "Subtotal: "
             << subtotal
             << endl;

        file << "GST: "
             << gst
             << endl;

        file << "Grand Total: "
             << total
             << endl;

        file << "--------------------------------------------------\n";

        file.close();
    }


    // ========================================================
    // CUSTOMER ORDER HISTORY
    // ========================================================

    void customerOrderHistory(Customer& customer)
    {
        ifstream file("orders.txt");

        if (!file)
        {
            cout << "\nNo orders found.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\n============================================================\n";
        cout << "                    MY ORDER HISTORY\n";
        cout << "============================================================\n";

        while (getline(file, line))
        {
            if (
                line == "Customer ID: "
                + to_string(customer.getUserId())
            )
            {
                found = true;

                cout << "\n";

                cout << "Order Information:\n";

                // Print the current customer ID line
                cout << line << endl;

                // Print remaining order information
                while (getline(file, line))
                {
                    if (
                        line.find("--------------------------------------------------")
                        == 0
                    )
                    {
                        cout << line << endl;
                        break;
                    }

                    cout << line << endl;
                }
            }
        }

        if (!found)
        {
            cout << "\nYou have not placed any orders yet.\n";
        }

        file.close();
    }


    // ========================================================
    // ADMIN MENU
    // ========================================================

    void adminMenu()
    {
        Admin admin(
            1,
            "Administrator",
            "admin@shopping.com",
            "admin123"
        );

        int choice;

        do
        {
            cout << "\n\n";
            cout << "========================================\n";
            cout << "               ADMIN MENU\n";
            cout << "========================================\n";

            cout << "1. View Products\n";
            cout << "2. Add Product\n";
            cout << "3. Update Product\n";
            cout << "4. Delete Product\n";
            cout << "5. Search Product\n";
            cout << "6. View All Orders\n";
            cout << "7. Admin Profile\n";
            cout << "8. Sign Out\n";

            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                displayProducts();
                break;

            case 2:
                addProduct();
                break;

            case 3:
                updateProduct();
                break;

            case 4:
                deleteProduct();
                break;

            case 5:
            {
                int id;

                cout << "\nEnter Product ID: ";
                cin >> id;

                searchProduct(id);

                break;
            }

            case 6:
            {
                ifstream file("orders.txt");

                if (!file)
                {
                    cout << "\nNo orders found.\n";
                    break;
                }

                string line;

                cout << "\n============================================================\n";
                cout << "                     ALL ORDERS\n";
                cout << "============================================================\n";

                while (getline(file, line))
                {
                    cout << line << endl;
                }

                file.close();

                break;
            }

            case 7:
                admin.display();
                break;

            case 8:
                cout << "\nAdmin signed out.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
            }

        } while (choice != 8);
    }


    // ========================================================
    // CUSTOMER MENU
    // ========================================================

    void customerMenu(Customer& customer)
    {
        int choice;

        do
        {
            cout << "\n\n";
            cout << "========================================\n";
            cout << "             CUSTOMER MENU\n";
            cout << "========================================\n";

            cout << "Welcome, "
                 << customer.getName()
                 << "!\n\n";

            cout << "1. View Products\n";
            cout << "2. Search Product\n";
            cout << "3. Add Product to Cart\n";
            cout << "4. Remove Product from Cart\n";
            cout << "5. View Cart\n";
            cout << "6. Place Order\n";
            cout << "7. My Order History\n";
            cout << "8. My Profile\n";
            cout << "9. Sign Out\n";

            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                displayProducts();
                break;

            case 2:
            {
                int id;

                cout << "\nEnter Product ID: ";
                cin >> id;

                searchProduct(id);

                break;
            }

            case 3:
                addToCart(customer);
                break;

            case 4:
                removeFromCart(customer);
                break;

            case 5:
                customer.getCart().displayCart();
                break;

            case 6:
                placeOrder(customer);
                break;

            case 7:
                customerOrderHistory(customer);
                break;

            case 8:
                customer.display();
                break;

            case 9:
                cout << "\nSigned out successfully.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
            }

        } while (choice != 9);
    }


    // ========================================================
    // MAIN MENU
    // ========================================================

    void start()
    {
        int choice;

        do
        {
            cout << "\n\n";
            cout << "====================================================\n";
            cout << "              ONLINE SHOPPING CENTRE\n";
            cout << "====================================================\n";

            cout << "1. Sign Up\n";
            cout << "2. Sign In\n";
            cout << "3. Admin Sign In\n";
            cout << "4. Exit\n";

            cout << "\nEnter Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                signUp();
                break;

            case 2:
            {
                Customer* customer = signIn();

                if (customer != nullptr)
                {
                    customerMenu(*customer);
                }

                break;
            }

            case 3:
                if (adminSignIn())
                {
                    adminMenu();
                }

                break;

            case 4:
                cout << "\nThank you for using Online Shopping Centre!\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
            }

        } while (choice != 4);
    }
};


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    OnlineShoppingCentre shop;

    shop.start();

    return 0;
}