# Restaurant-Management-System

## Overview

This C++ project is a Restaurant Management System that simulates the operations of a restaurant. It includes functionality for managing a menu, placing and editing orders, and handling administrative tasks. The system demonstrates core Object-Oriented Programming (OOP) principles through its design.

## Features

- **Menu Management**: Add, delete, and view menu items.
- **Order Management**: Place, view, delete, and edit orders.
- **Admin and Customer Interfaces**: Separate functionalities for administrative tasks and customer interactions.

## How It Works

1. **Menu Management**:
   - Admins can add or remove items from the menu.
   - The menu items include details such as name, description, and price.

2. **Order Management**:
   - Customers can view the menu, place orders, and manage their orders (view, delete, and edit).

3. **Admin Interface**:
   - Admins can view cash, manage the menu, and log out.

4. **Customer Interface**:
   - Customers can view the menu, place orders, and manage their orders.

## OOP Principles Implemented

- **Encapsulation**: 
  - Used to protect the internal state of objects and to manage data access. For example, the `MenuItem` and `OrderItem` classes use private data members and public methods to access and modify data.

- **Inheritance**:
  - Implemented through the `Customer` and `RestaurantCustomer` classes. `RestaurantCustomer` inherits from `Customer` to extend its functionality and implement specific behavior for placing orders.

- **Polymorphism**:
  - Demonstrated via the virtual function `placeOrder` in the `Customer` class. This allows different types of customers to have different implementations of how orders are placed.

- **Composition and Aggregation**:
  - **Composition**: The `OrderItem` class uses a pointer to a `MenuItem` object, demonstrating a composition relationship where `OrderItem` relies on `MenuItem` but does not own it.
  - **Aggregation**: The `Menu` class aggregates `MenuItem` objects, managing a collection of menu items.

 
