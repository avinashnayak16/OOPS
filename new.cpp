#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Exception;
class Customer;
class RoomCustomer;
class Employee;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;

class Exception {
public:
    int errNo;
    string msg;

    Exception(int errNo, string msg) {
        this->errNo = errNo;
        this->msg = msg;
    }

    void what() {
        cout << "\t\t" << errNo << " :: " << msg << endl;
    }
};

class Room {
public:
    string roomType;
    int noOfBeds;
    double rent;
    int roomNo;
    int status;

    Room(string roomType, int noOfBeds, double rent, int roomNo) {
        this->roomType = roomType;
        this->noOfBeds = noOfBeds;
        this->rent = rent;
        this->roomNo = roomNo;
        this->status = 0;
    }

    Room() {}

    bool isVacant() {
        return status == 0;
    }

   void displayDetail() const {
    cout << "Room Type :: " << this->roomType << endl;
    cout << "Number of Beds :: " << this->noOfBeds << endl;
    cout << "Rent :: " << this->rent << endl;
    cout << "Room Number :: " << this->roomNo << endl;
    cout << (status == 1 ? "Occupied" : "Vacant") << endl;
}


    void vacateRoom() {
        status = 0;
    }

    static void displayAvailable(const vector<Room>& rooms) {
        for (const auto& room : rooms) {
            if (room.status == 0) {
                room.displayDetail();
            }
        }
    }
};

class Dish {
public:
    string dishName;
    double price;
    string dishType;

    Dish(string dishName, double price, string dishType) {
        this->dishName = dishName;
        this->price = price;
        this->dishType = dishType;
    }

    Dish() {}
};

class Customer {
public:
    string custName;
    string custAddress;
    string custID;
    long int custPhone;
    string custEmail;
    string checkInTime;
    int status;

    Customer() {
        time_t c = time(0);
        string dt = ctime(&c);
        this->custName = " ";
        this->custAddress = " ";
        this->custID = " ";
        this->custPhone = 0L;
        this->custEmail = " ";
        this->checkInTime = dt;
        status = 0;
    }

    void setData() {
        time_t now = time(0);
        string dt = ctime(&now);
        this->checkInTime = dt;
        ofstream customer;
        customer.open("Customer.txt", ios::ate);
        cout << "Enter your Name :\n";
        cin >> this->custName;
        customer << "Name ::" << this->custName << "\n";

        cout << "Enter your Address :\n";
        cin >> this->custAddress;
        customer << "Address ::" << this->custAddress << "\n";

        cout << "Enter your Phone number :\n";
        cin >> this->custPhone;
        customer << "Phone ::" << this->custPhone << "\n";

        cout << "Enter your Email :\n";
        cin >> this->custEmail;
        customer << "Email ::" << this->custEmail << "\n\n";
        customer.close();
    }

    int selectChoice() {
        int ch;
        cout << " Hello!\n";
        cout << "Enter \n1. Accommodation \n 2. Dine\n ";
        cin >> ch;
        return ch;
    }

    virtual void printCustomer() {
        cout << "Name :: " << this->custName << endl;
        cout << "Address :: " << this->custAddress << endl;
        cout << "ID :: " << custID << endl;
        cout << "Phone Number :: " << custPhone << endl;
        cout << "Email :: " << custEmail << endl;
        cout << "Check-In Time ::" << this->checkInTime << endl;
    }

    virtual void viewTotalBill() {}
    virtual void allocateRoom(Room r1) {}
    virtual void allocateDish(Dish d1) {}
    virtual void checkOut() {}
};

class RoomCustomer : public Customer {
public:
    double rbill;
    Room r;
    int bookStatus;

    void viewTotalbill() {
        cout << "Bill =" << rbill;
    }

    void allocateRoom(Room r1) {
        this->r = r1;
    }

    void printCustomer() {
        Customer::printCustomer();
        if (r.status == 1 && bookStatus == 1) {
            cout << "Check-In Time :: " << checkInTime << endl;
            cout << "Room type :: " << r.roomType << endl;
            cout << "Room Number :: " << r.roomNo << endl;
        }
    }

    void viewTotalBill() {
        this->rbill = r.rent;
        cout << "Bill :: " << this->rbill << endl;
    }

    void checkOut() {
        cout << "Your bill is " << this->rbill << "/-" << endl;
        this->rbill = 0;
        this->r.status = 0;
        cout << "Thank You! Visit Again.\n" << endl;
    }
};

class RestaurantCustomer : public Customer {
public:
    double dbill;
    Dish d;
    int orderStatus;

    void viewTotalbill() {
        cout << "Bill =" << dbill;
    }

    void allocateDish(Dish d1) {
        this->d = d1;
    }

    void printCustomer() {
        Customer::printCustomer();
        if (orderStatus) {
            cout << "Dish Name :: " << d.dishName << endl;
            cout << "Dish Type :: " << d.dishType << endl;
        }
    }

    void viewTotalBill() {
        this->dbill = d.price;
        cout << "Bill :: " << this->dbill << endl;
    }
};

class Employee {
public:
    virtual void performDuty() = 0;
    virtual ~Employee() {}
};

class RoomService : public Employee {
public:
    void performDuty() {
        cout << "Employee XYZ arriving at your doorstep...\n\n";
    }

    virtual ~RoomService() {}
};

class Waiter : public Employee {
public:
    void performDuty() {
        cout << "\n\nEmployee ABC arriving at your table to take your Order\n\n";
    }

    virtual ~Waiter() {}
};

class SelectEmployee {
    Employee* e;

public:
    SelectEmployee(Employee* e1) {
        e = e1;
    }

    void performDuty() {
        e->performDuty();
    }
};

class Restaurant {
public:
    map<string, Dish> dishMap;

    void addDishes() {
        ofstream menu;
        menu.open("Menu.txt", ios::ate);
        for (int i = 0; i < 8; ++i) {
            string dishName, dishType;
            double price;
            cout << i + 1 << "] Enter Dish Name Price and Type\n";
            cin >> dishName >> price >> dishType;
            dishMap[dishName] = Dish(dishName, price, dishType);
            menu << dishName << "\t" << price << "\t" << dishType << "\n";
        }
        menu.close();
    }

    Dish getDish(const string& dnam) {
        return dishMap[dnam];
    }

    void displayDish(const Dish& d) {
        cout << " Dish Name :: " << d.dishName << endl;
        cout << " Price :: " << d.price << endl;
        cout << " Dish Type :: " << d.dishType << endl;
    }

    void displayMenu() {
        for (const auto& pair : dishMap) {
            displayDish(pair.second);
        }
    }
};

class Hotel {
private:
    static Hotel* instanceHotel;
    string hotelName;
    string hotelAddress;
    vector<Employee*> employees;
    Restaurant restaurant;
    vector<Room> rooms;
    vector<Customer*> customers;

    Hotel(string hname, string add) {
        this->hotelName = hname;
        this->hotelAddress = add;
    }

public:
    static Hotel* getHotel() {
        if (!instanceHotel)
            instanceHotel = new Hotel("RENNAISSANCE", "HUBLI");
        return instanceHotel;
    }

    void setHotel(Restaurant r, const vector<Room>& rs) {
        this->rooms = rs;
        this->restaurant = r;
    }

    void generateID(Customer* c) {
        static const char m[] = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < 6; ++i) {
            c->custID += m[rand() % 26];
        }
    }

    void checkIn(Customer* c1, Room r) {
        c1->allocateRoom(r);
        r.status = 1;
        c1->status = 1;
        c1->custName = "Customer"; // This should be properly initialized
        cout << c1->custName << " checked in at Room No." << r.roomNo << endl;
        customers.push_back(c1);
    }

    void dineIn(Customer* c1, Dish d) {
        c1->allocateDish(d);
        c1->status = 1;
        c1->custName = "Customer"; // This should be properly initialized
        cout << c1->custName << " ordered " << d.dishName << endl;
        customers.push_back(c1);
    }

    Room searchRoom(int roomNo) {
        auto it = find_if(rooms.begin(), rooms.end(), [roomNo](const Room& r) {
            return r.roomNo == roomNo;
        });
        if (it != rooms.end()) {
            return *it;
        } else {
            throw Exception(404, "Room not found");
        }
    }

    Customer* searchCustomer(const string& id) {
        auto it = find_if(customers.begin(), customers.end(), [&id](Customer* c) {
            return c->custID == id;
        });
        if (it != customers.end()) {
            return *it;
        } else {
            throw Exception(404, "Customer not found");
        }
    }

    void listCustomers() {
        for (Customer* c : customers) {
            c->printCustomer();
        }
    }

    void displayMenu() {
        restaurant.displayMenu();
    }

    Dish getDish(const string& name) {
        return restaurant.getDish(name);
    }

    void checkOutCustomer(const string& id) {
        Customer* customer = searchCustomer(id);
        customer->viewTotalBill();
        customer->checkOut();
    }
};

Hotel* Hotel::instanceHotel = nullptr;

int main() {
    srand(time(0));
    Hotel* h = Hotel::getHotel();

    vector<Room> rooms = {
        Room("AC", 2, 3000, 101),
        Room("Non-AC", 2, 2000, 102),
        Room("AC", 3, 4000, 103),
        Room("Non-AC", 3, 3000, 104),
        Room("AC", 1, 2000, 105),
        Room("Non-AC", 1, 1500, 106),
        Room("AC", 4, 5000, 107),
        Room("Non-AC", 4, 4000, 108)
    };
vector <Dish> d={
		Dish("Chocolate_Fondue",140,"Desert"),
		Dish("Manchow_Soup",110,"Soup"),
		Dish("Shahi_Paneer",220,"Main Course"),
		Dish("Arizona_Tea",100,"Beverage"),
		Dish("Grilled_Romaine Salad",180,"Salad"),
		Dish("Mushroom_Manchurian",170,"Starter"),
		Dish("Pina_Colada",210,"Cocktail"),
		Dish("Raspberry_Ripple",120,"Ice Cream")
			};
    Restaurant r;
    r.addDishes();

    h->setHotel(r, rooms);

    int choice;
    while (true) {
        cout << "Welcome to the Hotel Management System\n";
        cout << "1. Check In\n2. Dine In\n3. Check Out\n4. List Customers\n5. Display Menu\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Customer* c = new RoomCustomer();
            c->setData();
            h->generateID(c);
            int roomNo;
            cout << "Enter room number to check in: ";
            cin >> roomNo;
            Room r = h->searchRoom(roomNo);
            h->checkIn(c, r);
        } else if (choice == 2) {
            Customer* c = new RestaurantCustomer();
            c->setData();
            h->generateID(c);
            string dishName;
            cout << "Enter dish name to order: ";
            cin >> dishName;
            Dish d = h->getDish(dishName);
            h->dineIn(c, d);
        } else if (choice == 3) {
            string id;
            cout << "Enter customer ID to check out: ";
            cin >> id;
            h->checkOutCustomer(id);
        } else if (choice == 4) {
            h->listCustomers();
        } else if (choice == 5) {
            h->displayMenu();
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
