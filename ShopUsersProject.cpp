#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

char Main_menu(){
    char temp = '0';
    system("CLS");
    cout <<"1.Log in \n"
         <<"2.View the store \n"
         <<"q.Exit \n"
         <<">>";
    cin >> temp;
    return temp;         
}
char User_logged_in_menu(){ 
    char temp = '0';
    system("CLS");
    cout <<"1.Show wallet credit.\n"
         <<"2.Increase wallet credit.\n"
         <<"3.Change password \n"
         <<"4.Buy products \n"
         <<"q.Log out \n"
         <<">>";
    cin >> temp;
    return temp;      
}
char Admin_Logged_in_menu(){
    char temp = '0';
    system("CLS");
    cout <<"1.Show wallet credit.\n"
         <<"2.Increase wallet credit.\n"
         <<"3.Change password \n"
         <<"4.Buy products \n"
         <<"5.Add a discount_code \n"
         <<"6.Edit product list \n"
         <<"q.Log out \n"
         <<">>";
    cin >> temp;
    return temp;  
}
char Product_menu(){ 
    char temp = '0';
    system("CLS");
    cout <<"1.Add a new product \n"
         <<"2.Edit an existing product \n"
         <<">>";
    cin >> temp;
    return temp;      
}
char Edit_product_menu(){ 
    char temp = '0';
    system("CLS");  
    cout <<"Which one you want to edit? \n"
         <<"1.product's name \n 2.product's cost \n"
         <<">>";
    cin >> temp;
    return temp;     
}

struct discount_code{
    string text;
    float precentage;
    string start_date;
    string end_date;
    long long int code;
};
struct product{
    long long int product_code = 0;
    string name;
    double cost;
};
class User{
    protected:
        string user_id;
        string password;
        double wallet_credit = 0;

    public:
        vector<discount_code> user_discount_codes;
        User(){
            user_id = ""; password = ""; wallet_credit = 0;
        }
        User(string user_id_, string password_){
            user_id = user_id_;
            password = password_;
            wallet_credit = 0; 
            }
        User(string user_id_, string password_, double wallet_credit_){
            user_id = user_id_;
            password = password_;
            wallet_credit = wallet_credit; 
        }

        void set_user_id(string temp) { user_id = temp; }
        void set_password(string temp) { password = temp; }
        void set_wallet_credit(double temp) { wallet_credit = temp; }
        string get_user_id(){ return user_id; }
        string get_password(){ return password; }
        double get_wallet_credit(){ return wallet_credit; }

        bool wallet_credit_update(double change) {
            if (change >=0 || (abs(change) <= wallet_credit)){
                wallet_credit += change;    
                return true;
            }
            return false;
        }
        bool compare_discount_codes(discount_code* first_code, discount_code* second_code){
            if (first_code->code == second_code->code){ return false; }
            if (first_code->text != second_code->text){ return false; }
            if (first_code->precentage != second_code->precentage){ return false; }
            if (first_code->start_date != second_code->start_date){ return false; }
            if (first_code->end_date != second_code->end_date){ return false; }
            return true;
        }
        void delete_discount_code(discount_code* discount_code){
            int i;
            struct discount_code temp_code;
            for (i=0 ; i <size(user_discount_codes); i++){
                if (compare_discount_codes(&user_discount_codes[i], discount_code)){ break; }
            }
            for (i ; i < size(user_discount_codes)-1; i++){
                temp_code = discount_code[i];
                discount_code[i] = discount_code[i+1];
                discount_code[i+1] = temp_code;
            }
        }
};
class Admin : public User{
    public:
    Admin():User("Admin", "Admin@123456") {}
    void Edit_product(vector<product>* products){
        product temp;
        switch(Product_menu()){
            case '1':{
            cout <<"Enter product name: ";
            cin >>temp.name;
            cout <<"Enter product's cost: ";
            cin >>temp.cost;
            if(size(*products) == 0){ temp.product_code = 0;}
            else{temp.product_code = ((*products)[size(*products)-1].product_code)+1;}
            (*products).push_back(temp);
            cout <<"Product " <<(*products)[size(*products)-1].name <<" with the code " << (*products)[size(*products)-1].product_code <<" have been saved successfully." << endl;
            break;
            }
            case '2':{
            int i;
            cout <<"Enter product's code: ";
            long long int temp_code;
            cin >> temp_code;

            for(i=0; i<size(*products); i++){
                if((*products)[i].product_code == temp_code){
                    break;
                }
            }
            switch(Edit_product_menu()){
                case '1':{
                cout <<"Enter product's name: ";
                cin >>(*products)[i].name;
                break;
                }
                case '2':{
                cout <<"Enter product's cost: ";
                cin >> (*products)[i].cost; 
                break;
                }
            }
            }
        }
    }
    void Add_discount_code(vector<discount_code>* discount_list){
        discount_code temp;
        if (size(*discount_list) == 0){ temp.code = 0; }
        else { temp.code = ((*discount_list)[size(*discount_list)-1].code)+1; }
        cout <<"Enter discount presentage: ";
        cin >> temp.precentage;
        cout <<"Enter discount start date: ";
        cin >> temp.start_date;
        cout <<"Enter discount end date: ";
        cin >> temp.end_date;
        cout <<"Enter discount discription text: ";
        cin >> temp.text;
        (*discount_list).push_back(temp);
    }
    
};

void Signup(vector<User>* users_list){
    User temp;
    string temp_data;
    cout <<"Enter your username: ";
    cin >> temp_data;
    temp.set_user_id(temp_data);
   cout <<"Enter your password: ";
    cin >> temp_data;
    temp.set_password(temp_data);
    users_list->push_back(temp);
    cout <<"User name: " << temp.get_user_id() <<" with password: " << temp.get_password() <<" have been saved.\n";
}
bool login(vector<User>* users_list, Admin* admin, string username){
    string temp;
    if(admin->get_user_id() == username){
        Repeat_admin_pass:
        cout <<"Enter password: ";
        cin >>temp;
        if (admin->get_password() == temp){
            cout <<"Logged in. \n";
            return true;
        }else{
            cout <<"Password is incorrect.\n";
            goto Repeat_admin_pass;
    }
    }
    for (int i = 0; i < size(*users_list); i++){
        if ((*users_list)[i].get_user_id() == username){
            Repeat_pass:
            cout <<"Enter password: ";
            cin >>temp;
            if ((*users_list)[i].get_password() == temp){
                cout <<"Logged in. \n";
                return true;
            }else{
                cout <<"Password is incorrect.\n";
                goto Repeat_pass;
            }
        }
    }
    cout <<"There isn't a user with this user name. Add the user:\n";
    Signup(users_list); 
    return true;
}
void Show_products(vector<product>* products_list){
    if(size(*products_list) == 0){
        cout <<"there is no product available. \n";
        return;
    }else{    
        cout <<"***************************************************\n";
        for (int i = 0; i <size(*products_list); i++){
        cout <<i+1 <<".name: " <<(*products_list)[i].name <<" ,cost: " <<(*products_list)[i].cost <<endl;
        }
        cout <<"***************************************************\n";
    }
}
void Print_recipt(vector<product>* products_list, vector<long long int>* choices, vector<long long int>* counts){
    time_t my_time = time(NULL);
    cout <<"||Product name||  cost  ||  count  ||\n";
    for (int i = 0; i < choices->size(); i++){
        cout <<"||" <<setw(13) <<(*products_list)[(*choices)[i]].name <<"||" <<setw(8) <<(*products_list)[(*choices)[i]].cost <<"||" <<setw(7) <<(*counts)[i] <<"||\n"; 
    }    
    cout <<"********************************************\nDate and Time: ";
    printf("%s", ctime(&my_time));
    cout <<"Action Exepted.";
}
void save_Products_infile(vector<product>* products_list){
    ofstream output_file("products.txt");
    ostream_iterator<std::string> output_iterator(output_file, "\n");
    copy(example.begin(), example.end(), output_iterator);
}

int main(){
    Admin shop_admin;
    bool flag = true, login_flag = true;
    vector<product> products_list;
    vector<User> users_list;
    vector<discount_code> discount_codes;

    while(flag){
    switch (Main_menu()){
        case '1':{
        login_flag = true;    
        string username;
        cout <<"Enter user name: ";
        cin >> username;    
        if(login(&users_list, &shop_admin, username)){
        if(username == shop_admin.get_user_id()){
        while(login_flag){
        switch(Admin_Logged_in_menu()){
            case '1':{
            cout <<"Wallet credit: " <<shop_admin.get_wallet_credit() <<" R\n";
            system("pause");
            break;
            }
            case '2':{
            long long int credit_amount;
            cout <<"How much credit do you want to charge: ";
            cin >>credit_amount;
            if (shop_admin.wallet_credit_update(credit_amount)){
                cout <<"Your credit now has been updated to " <<shop_admin.get_wallet_credit() <<endl;
            }else{
                cout <<"Your credit failed to update. \n";
            }
            system("pause");
            break;
            }
            case '3':{
            string password;
            cout <<"Enter current password: ";
            cin >>password;
            if(password == shop_admin.get_password()){
                cout <<"Enter new password: ";
                cin >>password;
                shop_admin.set_password(password);
            }else{
                cout <<"password is incorrect.\n";
            }
            system("pause");
            break;
            }
            case '4':{
            long long int credit = 0;
            Show_products(&products_list);
            long long int choice, count, discount_code; 
            vector<long long int> choices, counts;
            do{
            cout <<"Enter the number related to the product: ";
            cin >>choice;
            cout <<"Number of this product you want to buy: ";
            cin >>count;
            cout <<"Enter discount code: ";
            cin >>discount_code;
            int index = 0;
            for (int index = 0; index <size(shop_admin.user_discount_codes); index++){
                if (discount_code == shop_admin.user_discount_codes[index].code){
                credit -= credit*shop_admin.user_discount_codes[index].precentage;
                shop_admin.delete_discount_code(&shop_admin.user_discount_codes[index]);
                }
            }
            if(choice > 0 && count > 0){ 
                credit += products_list[choice-1].cost * count;
                choices.push_back(choice);
                counts.push_back(count);
            }
            }while(choice > 0);

            if (credit < shop_admin.get_wallet_credit()){
                cout <<"you don't have the credit required for this purchase. \n";
            }else{
                shop_admin.wallet_credit_update(-1* credit);
                Print_recipt(&products_list, &choices, &counts);
            }
            system("pause");
            break;
            }
            case '5':{
            shop_admin.Add_discount_code(&discount_codes); break;
            }
            case '6':{
            shop_admin.Edit_product(&products_list); break;
            }
            case 'q':
            case 'Q':{
            login_flag = false; break;
            }
            default:{
            cout <<"Unknown choice, please try again.. \n";
            system("pause");
            }
        }
        }
        }else{
            int index = 0;
            for (index; index < size(users_list); index++){
                if (username == users_list[index].get_user_id()){
                    break;
                }
            }
            switch(User_logged_in_menu()){
            case '1':{
            cout <<"Wallet credit: " <<users_list[index].get_wallet_credit() <<" R\n";
            system("pause");
            break;
            }
            case '2':{
            long long int credit_amount;
            cout <<"How much credit do you want to charge: ";
            cin >>credit_amount;
            if (users_list[index].wallet_credit_update(credit_amount)){
                cout <<"Your credit now has been updated to " <<users_list[index].get_wallet_credit() <<endl;
            }else{
                cout <<"Your credit failed to update. \n";
            }
            system("pause");
            break;
            }
            case '3':{
            string password;
            cout <<"Enter current password: ";
            cin >>password;
            if(password == users_list[index].get_password()){
                cout <<"Enter new password: ";
                cin >>password;
                users_list[index].set_password(password);
            }else{
                cout <<"password is incorrect.\n";
            }
            system("pause");
            break;
            }
            case '4':{
            long long int credit = 0;
            Show_products(&products_list);
            long long int choice, count, discount_code; 
            vector<long long int> choices, counts;
            do{
            cout <<"Enter the number related to the product: ";
            cin >>choice;
            cout <<"Number of this product you want to buy: ";
            cin >>count;
            cout <<"Enter discount code: ";
            cin >>discount_code;
            int index = 0;
            for (int index = 0; index <size(shop_admin.user_discount_codes); index++){
                if (discount_code == shop_admin.user_discount_codes[index].code){
                credit -= credit*shop_admin.user_discount_codes[index].precentage;
                shop_admin.delete_discount_code(&shop_admin.user_discount_codes[index]);
                }
            }
            if(choice > 0 && count > 0){ 
                credit += products_list[choice-1].cost * count;
                choices.push_back(choice);
                counts.push_back(count);
            }
            }while(choice > 0);

            if (credit < shop_admin.get_wallet_credit()){
                cout <<"you don't have the credit required for this purchase. \n";
            }else{
                shop_admin.wallet_credit_update(-1* credit);
                Print_recipt(&products_list, &choices, &counts);
            }
            system("pause");
            break;
            }
            case 'q':
            case 'Q':{
            login_flag = false; break;
            }
            default:{
            cout <<"Unknown choice, please try again.. \n";
            system("pause");
            }
        }
        }
        }
        break;
        }
        case '2':{
        Show_products(&products_list);
        system("pause");
        break;
        }
        case 'q':
        case 'Q':{
            flag = false; break;
        }
        default:{
        cout <<"Unknown choice, please try again.. \n";
        system("pause");
        }
    }
    }
    cout <<"Thank you for choosing this online shop. \n";
    return 0;
}
