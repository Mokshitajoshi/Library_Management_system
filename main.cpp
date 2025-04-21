#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
class library{ // for management
    private:
        stack<int> returned_books;
        queue<int> requested_books;
        

};
class book{ // class for the book catalog
    private:
        int book_id; //unique id for each book
        string book_name;
        string author;
        string genre;
        bool is_issued; //to find if the book is issued or not
        int issued_to; //to find to which user book is issued
    public:
        book(int id,string name,string author,string genre){
            book_id=id;
            book_name=name;
            this->author=author;
            this->genre=genre;
            is_issued=false;
            issued_to=-1;
        }

};

class user{
    private:
        int user_id;
        string name;
    public:
        user(int id,string name){
            user_id=id;
            this->name=name;
        } 
};

class student : public user{
    private:

    public:
        student(int id,string name) : user(id,name){}
};
 
class admin : public user,public library{
    private:
        
    public:
        admin(int id,string name) : user(id,name){}
        void add_book(int id,string name,string author,string genre){
            book b(id,name,author,genre);
            
        }
        void del_book(int id){
            
        }
};



