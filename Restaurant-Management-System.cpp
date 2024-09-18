// Restaurant Management System

#include <iostream>
#include <string>
using namespace std;

// Constants for maximum menu and order items
const int MAX_MENU_ITEMS = 10;
const int MAX_ORDER_ITEMS = 10;

// Base class for menu items
class MenuItem {
private:
	string name;
	string description;
	double price;

public:
	MenuItem() {}
	MenuItem(const string& name, const string& description, double price)
		: name(name), description(description), price(price) {}

	string getName() const {
		return name;
	}

	string getDescription() const {
		return description;
	}

	double getPrice() const {
		return price;
	}

	// Overloading << operator for convenient display
	friend ostream& operator<<(ostream& os, const MenuItem& item) {
		os << item.name << " - $" << item.price << " - " << item.description;
		return os;
	}
};

// Derived class for order items, Composition
class OrderItem {
private:
	const MenuItem* item;

public:
	int quantity;
	OrderItem() {}
	OrderItem(const MenuItem* item, int quantity) : item(item), quantity(quantity) {}

	double calculateTotal() const {
		return item->getPrice() * quantity;
	}

	void display() const {
		cout << *item << " - Quantity: " << quantity << " - Total: $" << calculateTotal() << "\n";
	}
};

// Menu class manages the restaurant's menu (using aggregation)
class Menu {
public:
	MenuItem items[MAX_MENU_ITEMS];
	int itemCount;
	Menu() : itemCount(0) {}

	void addItem(const MenuItem& item) {
		if (itemCount < MAX_MENU_ITEMS) {
			items[itemCount++] = item;
		}
		else {
			cout << "Menu is full. Cannot add more items.\n";
		}
	}

	void display() const {
		cout << "Menu:\n";
		for (int i = 0; i < itemCount; ++i) {
			cout << items[i] << "\n";
		}
	}

	const MenuItem* findItem(const string& name) const {
		for (int i = 0; i < itemCount; ++i) {
			if (items[i].getName() == name) {
				return &items[i];
			}
		}
		return nullptr;
	}
};

// Base class for customers (using inheritance)
class Customer {
protected:
	string name;
	string phoneNumber;
	string address;
	OrderItem orders[MAX_ORDER_ITEMS];
	int orderCount;

public:
	Customer(const string& name, const string& phoneNumber, const string& address)
		: name(name), phoneNumber(phoneNumber), address(address), orderCount(0) {}

	// Virtual function for placing orders (polymorphism)
	virtual void placeOrder(const Menu& menu) = 0;

	void viewOrders() const {
		cout << "Orders for " << name << ":\n";
		for (int i = 0; i < orderCount; ++i) {
			orders[i].display();
		}
	}

	void deleteOrder(int orderIndex) {
		if (orderIndex >= 0 && orderIndex < orderCount) {
			for (int i = orderIndex; i < orderCount - 1; ++i) {
				orders[i] = orders[i + 1];
			}
			orderCount--;
			cout << "Order deleted successfully.\n";
		}
		else {
			cout << "Invalid order index. Cannot delete.\n";
		}
	}

	void editOrder(int orderIndex, int newQuantity) {
		if (orderIndex >= 0 && orderIndex < orderCount) {
			if (newQuantity > 0) {
				orders[orderIndex].quantity = newQuantity;
				cout << "Order quantity updated successfully.\n";
			}
			else {
				cout << "Invalid quantity. Quantity must be greater than 0.\n";
			}
		}
		else {
			cout << "Invalid order index. Cannot edit.\n";
		}
	}
};

// Derived class for restaurant customers
class RestaurantCustomer : public Customer {
public:
	RestaurantCustomer(const string& name, const string& phoneNumber, const string& address)
		: Customer(name, phoneNumber, address) {}

	// Implementing the virtual function for placing orders (polymorphism)
	void placeOrder(const Menu& menu) override {
		cout << "Welcome, " << name << "!\n";
		menu.display();
		OrderItem newOrders[MAX_ORDER_ITEMS];
		int newOrderCount = 0;

		while (true) {
			string itemName;
			int quantity;

			cout << "Enter an item name to order (or 'done' to finish): ";
			cin >> itemName;

			if (itemName == "done") {
				break;
			}

			const MenuItem* item = menu.findItem(itemName);

			if (item == nullptr) {
				cout << "Item not found in the menu.\n";
				continue;
			}

			cout << "Enter the quantity: ";
			cin >> quantity;

			newOrders[newOrderCount++] = OrderItem(item, quantity);
		}

		for (int i = 0; i < newOrderCount; ++i) {
			orders[orderCount++] = newOrders[i];
		}

		cout << "Order placed successfully!\n";
	}
};

// Admin class manages restaurant administration (using encapsulation)
class Admin {
private:
	string username;
	string password;

public:
	Admin(const string& username, const string& password)
		: username(username), password(password) {}

	bool authenticate(const string& inputUsername, const string& inputPassword) const {
		return username == inputUsername && password == inputPassword;
	}

	void viewCash() const {
		// Implement cash viewing logic here
		double cashAmount = 1000.0; // Replace with your actual cash amount retrieval logic
		cout << "Cash: $" << cashAmount << "\n";
	}

	void viewMenu(const Menu& menu) const {
		menu.display();
	}

	void addItemToMenu(Menu& menu, const MenuItem& item) {
		menu.addItem(item);
		cout << "Item added to the menu.\n";
	}

	void deleteItemFromMenu(Menu& menu, const string& itemName) {
		for (int i = 0; i < menu.itemCount; ++i) {
			if (menu.items[i].getName() == itemName) {
				// Shift all items after the deleted item one position to the left
				for (int j = i; j < menu.itemCount - 1; ++j) {
					menu.items[j] = menu.items[j + 1];
				}
				menu.itemCount--;
				cout << "Item '" << itemName << "' deleted from the menu.\n";
				return;
			}
		}
		cout << "Item '" << itemName << "' not found in the menu.\n";
	}
};

int main() {
	Menu restaurantMenu;
	restaurantMenu.addItem(MenuItem("Burger", "A delicious burger.", 8.99));
	restaurantMenu.addItem(MenuItem("Pizza", "A classic pizza.", 10.99));
	restaurantMenu.addItem(MenuItem("Pasta", "Delicious pasta.", 12.49));
	restaurantMenu.addItem(MenuItem("Wings", "Crispy wings.", 18.49));
	restaurantMenu.addItem(MenuItem("Shawarma", "Chicken shawarma.", 18.49));

	while (true) {
		cout << "Welcome to the Restaurant Management System!\n";
		cout << "1. Admin Login\n";
		cout << "2. Customer Login\n";
		cout << "3. Exit\n";
		int choice;
		cin >> choice;

		if (choice == 1) {
			// Admin login and menu handling
			string adminUsername, adminPassword;
			cout << "Enter Admin Username: ";
			cin >> adminUsername;
			cout << "Enter Admin Password: ";
			cin >> adminPassword;

			Admin admin("admin", "admin123"); // Replace with your actual admin username and password

			if (admin.authenticate(adminUsername, adminPassword)) {
				while (true) {
					cout << "\nAdmin Menu:\n";
					cout << "1. View Cash\n";
					cout << "2. View Menu\n";
					cout << "3. Add Item to Menu\n";
					cout << "4. Delete Item from Menu\n";
					cout << "5. Log Out\n";
					int adminChoice;
					cin >> adminChoice;
					string itemName, itemDescription;
					double itemPrice;
					string itemToDelete, itemToEdit;
					int orderIndex, newQuantity;
					switch (adminChoice) {
					case 1:
						admin.viewCash();
						break;
					case 2:
						admin.viewMenu(restaurantMenu);
						break;
					case 3:
						cout << "Enter Item Name: ";
						cin >> itemName;
						cout << "Enter Item Description: ";
						cin.ignore(); // Clear newline character
						getline(cin, itemDescription);
						cout << "Enter Item Price: ";
						cin >> itemPrice;
						admin.addItemToMenu(restaurantMenu, MenuItem(itemName, itemDescription, itemPrice));
						break;
					case 4:
						cout << "Enter the name of the item to delete: ";
						cin >> itemToDelete;
						admin.deleteItemFromMenu(restaurantMenu, itemToDelete);
						break;
					case 5:
						cout << "Admin logged out.\n";
						return 0;
					default:
						cout << "Invalid choice. Please try again.\n";
					}
				}
			}
			else {
				cout << "Authentication failed. Please try again.\n";
			}
		}
		else if (choice == 2) {
			// Customer login and menu handling
			string customerName, customerPhoneNumber, customerAddress;
			cout << "Enter Your Name: ";
			cin.ignore();
			getline(cin, customerName);
			cout << "Enter Your Phone Number: ";
			cin >> customerPhoneNumber;
			cout << "Enter Your Address: ";
			cin.ignore();
			getline(cin, customerAddress);

			Customer* customer = new RestaurantCustomer(customerName, customerPhoneNumber, customerAddress);

			while (true) {
				cout << "\nCustomer Menu:\n";
				cout << "1. View Menu\n";
				cout << "2. Place Order\n";
				cout << "3. View Orders\n";
				cout << "4. Delete Order\n";
				cout << "5. Edit Order\n";
				cout << "6. Exit\n";
				int customerChoice;
				cin >> customerChoice;
				int orderIndex, newQuantity;
				switch (customerChoice) {
				case 1:
					restaurantMenu.display();
					break;
				case 2:
					customer->placeOrder(restaurantMenu);
					break;
				case 3:
					customer->viewOrders();
					break;
				case 4:
					cout << "Enter the order index to delete: ";
					cin >> orderIndex;
					customer->deleteOrder(orderIndex);
					break;
				case 5:
					cout << "Enter the order index to edit: ";
					cin >> orderIndex;
					cout << "Enter the new quantity: ";
					cin >> newQuantity;
					customer->editOrder(orderIndex, newQuantity);
					break;
				case 6:
					delete customer; // Free memory allocated for customer
					cout << "Thank you for dining with us!\n";
					return 0;
				default:
					cout << "Invalid choice. Please try again.\n";
				}
			}
		}
		else if (choice == 3) {
			cout << "Goodbye! Have a great day.\n";
			return 0;
		}
		else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}