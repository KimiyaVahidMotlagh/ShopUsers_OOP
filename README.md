# ShopUsers_OOP
This project is object-oriented programming in C++. We needed to envision a shop with users who want to buy the shop's products and Admins who can and products as well. The focus is programming with Classes and inheritance and using everything OOP has to offer. The project is a command-line user interface program. This project was my AP final project. 

# Table of Content
- [Data Engineering](https://github.com/KimiyaVahidMotlagh/ShopUsers_OOP/tree/main#data-engineering)
- [Interface Functions](https://github.com/KimiyaVahidMotlagh/ShopUsers_OOP/blob/main/README.md#interface-functions)
- [Main Function](https://github.com/KimiyaVahidMotlagh/ShopUsers_OOP/blob/main/README.md#main-function)

# Data Engineering

We have Admin and Users as classes. With Admin being a more advanced User, we can have admin inherit the basic function and variables from the User. <br/> <br/>
Each user has user_id, password, and wallet_credit as its variable. Each user has some personal discount codes and the following functions.
- constructive functions: When a user is created we can assign a value to each variable as needed with our functions.
- set_user_id(): assigns a string value to the user_id variable.
- set_password(): assigns a string value to the password variable.
- set_wallet_credit(): assigns a double value to the wallet_credit.
- get_user_id(): returns the user_id value
- get_password(): returns the password value
- get_wallet_credit(): returns the wallet_credit's value
- wallet_credit_update(): adds a double amount to the previous value.
- compare_discount_codes(): compares two discount_codes' variables in the function input and returns true or false.
- delete_discount_code(): deletes a input discount_code in the user's list.


# Interface Functions
This functions contains the interface for a menu-driven application, designed to handle different user interactions based on their role and the context of the operation. Each function represents a different menu, corresponding to the various stages and options available within the application.
- Main_menu(): displays the main menu to all users.
- User_logged_in_menu(): presents the menu for logged-in users.
- Admin_Logged_in_menu(): provides the menu for logged-in administrators.
- Product_menu(): shown to administrators for managing products. 
- Edit_product_menu(): this menu is for editing specific details of a product, after selecting an existing product to edit.


# Main Function

