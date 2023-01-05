#include<iostream>
#include<vector>
#include <cstdlib>
#include<unordered_map>
using namespace std;

void rotery(int cost){
    cout<<"pick a random no from 0 to 9\n";
    
    int pick;
    cin>>pick;
    
    srand(time(0));
    
    int arr[10];
    for(int i=0;i<10;i++){
        arr[i]=rand()%10;
    }
    
    int cal=arr[pick]*10;
    
    int discount_val=(cost*cal)/100;
    
    cout<<"discount percent is "<<100-cal<<"%"<<" and value is "<<discount_val<<endl;
    
    cout<<"Pay in cash\n";
    
    int paid;
    cin>>paid;
        
    if(paid>=discount_val){
        cout<<"change "<<paid-discount_val<<endl;
        cout<<"Thank you for shopping!";
        return;
    }
        
    else{
        cout<<"due :"<<discount_val-paid<<endl;
        return;
    }
    
    // return "discount value is :- "+ to_string(discout_val) +".\n";
}

class Item;
class Cart;

class Product{
    int id;
    string prod_name;
    int price;
    
    public:
        Product(){
            
        }
        Product(int id,string prod_name,int price){
            this->id=id;
            this->prod_name=prod_name;
            this->price=price;
        }
        
        string get_print(){
            return prod_name + ": Rs" + to_string(price)+"\n";
        }
        
        string getshort_name(){
            return prod_name.substr(0,1);
        }
        
        friend class Item;
        friend class Cart;
};

class Item{
    Product product;
    int quantity;
    
    public:
        Item(){}
        Item(Product p,int q): product(p), quantity(q){}
        
        int get_itemprice(){
            return (quantity * product.price); 
        }
        
        string get_item(){
            return to_string(quantity) + " X " + product.prod_name + ": Rs "+ to_string(quantity * product.price)+'\n';
        }
        
        friend class Cart;
};

class Cart{
    unordered_map<int,Item> items;
    
    public:
        void addProduct(Product pd){
            if(items.count(pd.id)==0){
                Item newItem(pd,1);
                items[pd.id]= newItem;
            }
            
            else{
                items[pd.id].quantity+=1;
            }
        }
        
        int get_total(){
            int total=0;
            for(auto itemPair:items){
                auto item=itemPair.second;
                total+=item.get_itemprice();
            }
            return total;
        }
        
        string viewCart(){
            if(items.empty()){
                return "no element found";
            }
            
            string itemizedlist;
            
            int cart_total=get_total();
            
            for(auto itemPair:items){
                auto item=itemPair.second;
                itemizedlist.append(item.get_item());
            }
            return itemizedlist+"\n Total Amount : Rs." + to_string(cart_total)+'\n';
        }
        
        bool isEmpty(){
            return items.empty();
        }
        
};

vector<Product> all_product={
    Product(1,"apple",24),
    Product(2,"banana",30),
    Product(3,"strawberry",70),
    Product(4,"grapes",60),
    Product(5,"pineapple",30),
    Product(6,"coconut",20),
    Product(7,"Guava",40),
    Product(8,"mango",35)
};

Product* chooseproduct(){
    string p1;
    cout<<"available product"<<endl;
    for(auto pd:all_product){
        p1.append(pd.get_print());
    }
    
    cout<<p1<<endl;
    
    cout<<"---------------------"<<endl;
    
    string choice;
    cin>>choice;
    
    for(int i=0;i<all_product.size();i++){
        if(all_product[i].getshort_name()==choice){
            return &all_product[i];
        }
    }
    
    cout<<"no product found"<<endl;
    return NULL;
    
}

bool checkout(Cart &cart){
    if(cart.isEmpty()){
        return false;
    }
    
    int total=cart.get_total();
    
    cout<<"total cost:- "<<total<<endl;
    
    cout<<"do you want to play rotery :\n";
    
    cout<<"(a)YES   (b)NO \n";
    
    cout<<"choose option\n";
    
    char opt;
    cin>>opt;
    
    if(opt=='a'){
        rotery(total);
    }
    
    else{
        cout<<"your total cost is:\n";
        cout<<"Pay in cash";
    
        int paid;
        cin>>paid;
        
        if(paid>=total){
            cout<<"change "<<paid-total<<endl;
            cout<<"Thank you for shopping!";
            return true;
        }
        
        else{
            cout<<"Not enough cash!";
            return false;
        }
    }
    return true;
}

int main(){
    char choose;
    Cart cart;
    
    while(true){
        cout<<"Select an option:-  (a)dd , (v)iew , (c)heckout \n";
        cin>>choose;
        
        if(choose== 'a'){
            Product *product= chooseproduct();
            
            if(product!=NULL){
                cout<<"adding to cart: "<<product->get_print();
                cart.addProduct(*product);
            }
        }
        
        else if(choose=='v'){
            cout<<"----------------"<<endl;
            cout<<cart.viewCart();
            cout<<"----------------"<<endl;
        }
        
        else if(choose=='c'){
            cart.viewCart();
            if(checkout(cart)){
                break;
            }
        }
        
        else{
            cout<<"invalid option"<<endl;
        }
    }
    
    return 0;
}