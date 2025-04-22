#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<map>
using namespace std;

class book{ // class for the book catalog
    private:
        int book_id; //unique id for each book
        string book_name;
        string author;
        string genre;
    public:
        bool is_issued; //to find if the book is issued or not
        int issued_to; //to find to which user book is issued
        book(int id,string name,string author,string genre){
            book_id=id;
            book_name=name;
            this->author=author;
            this->genre=genre;
            is_issued=false;
            issued_to=-1;
        }
        void display(int id){
            cout<<book_id<<"  |  "<<book_name<<"  |  "<<author<<"  |  "<<genre<<endl;
        }

};

class user{ // Base Class for admins and students
    private:
        int user_id;
        string name;
    public:
        user(int id,string name){
            user_id=id;
            this->name=name;
        } 
};

class student : public user{ //student class for student data
    public:
        student(int id,string name) : user(id,name){}
        
};
 
class admin : public user{
    public:    
        admin(int id,string name) : user(id,name){}    
};

class transaction{
    private:
        int t_id;
        int book_id;
        int user_id;
        string type;
};

class library{ // for management
    protected:
        map<int,book> book_catalog;
        map<int,student> students;
        map<int,admin> admins;
        vector<transaction> transactions;
    public:
        void search_book(int id){
            if(book_catalog.find(id)==book_catalog.end()){
                cout<<"book not found";
            }
            for(auto i:book_catalog){
                if(i.first==id){
                    cout<<"Found";
                    i.second.display(i.first);
                    break;
                }
            }
        }
        void add_book(int id,string name,string author,string genre){
            book_catalog.insert({id, book(id, name,author,genre)});
        }
        void del_book(int id){
            auto it = book_catalog.find(id);
            if (it != book_catalog.end()) {
                book_catalog.erase(it);
            }
        }
        void show_catalog(){
            cout<<"Book Id  | Book Name  |  Author  |  Genre  "<<endl;
            for(auto i:book_catalog){
                i.second.display(i.first);
            }
        }
        
        void add_student(int id,string name){
            students.insert({id, student(id, name)});
        }

        void add_admin(int id,string name){
            admins.insert({id, admin(id, name)});
        }

        void perform(int b_id, int u_id, string t) {
            auto it = book_catalog.find(b_id);
            if (it == book_catalog.end()) {
                cout << "Book not found";
                return;
            }
            if (t == "issue") {
                if (!it->second.is_issued) {
                    it->second.is_issued = true;
                    it->second.issued_to = u_id;
                    cout << "Book issued to user " << u_id <<endl;
                } 
                else {
                    cout << "Book already issued to user " << it->second.issued_to <<endl;
                }
            } 
            else if (t == "return") {
                if (it->second.is_issued && it->second.issued_to == u_id) {
                    it->second.is_issued = false;
                    it->second.issued_to = -1; 
                    cout << "Book returned by user " << u_id <<endl;
                } 
                else {
                    cout << "This book is not issued to user " << u_id <<endl;
                }
            } 
            else {
                cout << "Invalid operation type"<<endl;
            }
        }
        bool find_student(int id){
            auto it=students.find(id);
            if(it==students.end()){
                return false;
            }
            return true;
        }
        bool find_admin(int id){
            auto it=admins.find(id);
            if(it==admins.end()){
                return false;
            }
            return true;
        }
};

int main() {
    library lib; 
    int main_choice;

    while (true) {
        cout << "\n====== Library System ======\n";
        cout << "1. Create Student\n";
        cout << "2. Create Admin\n";
        cout << "3. Login as Student\n";
        cout << "4. Login as Admin\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> main_choice;

        if (main_choice == 1) {
            int id;
            string name;
            cout << "Enter new Student ID: ";
            cin >> id;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            lib.add_student(id, name);
            cout << "Student created successfully.\n";
        }

        else if (main_choice == 2) {
            int id;
            string name;
            cout << "Enter new Admin ID: ";
            cin >> id;
            cout << "Enter Admin Name: ";
            cin.ignore();
            getline(cin, name);
            lib.add_admin(id, name);
            cout << "Admin created successfully"<<endl;
        }

        else if (main_choice == 3) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            if (!lib.find_student(id)) {
                cout << "Student not found!\n";
                continue;
            }

            int choice;
            do {
                cout << "\n--- Student Menu ---\n";
                cout << "1. Search Book\n";
                cout << "2. Issue Book\n";
                cout << "3. Return Book\n";
                cout << "4. View Catalog\n";
                cout << "5. Logout\n";
                cout << "Choice: ";
                cin >> choice;

                if (choice == 1) {
                    int book_id;
                    cout << "Enter Book ID: ";
                    cin >> book_id;
                    lib.search_book(book_id);
                } else if (choice == 2) {
                    int book_id;
                    cout << "Enter Book ID to issue: ";
                    cin >> book_id;
                    lib.perform(book_id, id,"issue");
                } else if (choice == 3) {
                    int book_id;
                    cout << "Enter Book ID to return: ";
                    cin >> book_id;
                    lib.perform(book_id, id,"return");
                } else if (choice == 4) {
                    lib.show_catalog();
                }
            } while (choice != 5);
        }

        else if (main_choice == 4) {
            int id;
            cout << "Enter Admin ID: ";
            cin >> id;
            if (!lib.find_admin(id)) {
                cout << "Admin not found!\n";
                continue;
            }

            int choice;
            do {
                cout << "\n--- Admin Menu ---\n";
                cout << "1. Add Book\n";
                cout << "2. Delete Book\n";
                cout << "3. View Catalog\n";
                cout << "4. Logout\n";
                cout << "Choice: ";
                cin >> choice;
                if (choice == 1) {
                    int book_id;
                    string name, author, genre;
                    cout << "Enter Book ID: ";
                    cin >> book_id;
                    cout << "Enter Book Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Author: ";
                    cin.ignore();
                    getline(cin, author);
                    cout << "Enter Genre: ";
                    cin.ignore();
                    getline(cin, genre);
                    lib.add_book(book_id, name, author, genre);
                } else if (choice == 2) {
                    int book_id;
                    cout << "Enter Book ID to delete: ";
                    cin >> book_id;
                    lib.del_book(book_id);
                } else if (choice == 3) {
                    lib.show_catalog();
                }
            } while (choice != 4);
        }

        else if (main_choice == 5) {
            cout << "Exiting..."<<endl;
            break;
        }

        else {
            cout << "Invalid choice, try again"<<endl;
        }
    }

    return 0;
}




