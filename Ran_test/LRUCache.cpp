#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Node{
public:
    int key;
    int value;
    Node *pre;
    Node *next;

    Node(int key, int value){
        this->key = key;
        this->value = value;
    }

    string toString(){
        return to_string(key).append("-").append(to_string(value)).append(" ");
    }
};

class LRUCache{
public:
    int capacity;
    unordered_map<int, Node*> map;    //store key, value is just display
    Node *head = nullptr;             //head is new node
    Node *end = nullptr;              //end is to delete

    LRUCache(int capacity){
        this->capacity = capacity;
    }

    int get(int key){
        if(map.count(key)){
            Node *n = map[key];
            remove(n);
            setHead(n);
            printNode("get");
            return n->value;
        }
        printNode("get");
        return -1;
    }

    void remove(Node *n){
        if(n->pre != nullptr){
            n->pre->next = n->next;
        }else {
            head = n->next;
        }
        if(n->next != nullptr){
            n->next->pre = n->pre;
        } else{
            end = n->pre;
        }
    }

    void setHead(Node *n){
        n->next = head;
        n->pre = nullptr;
        if(head != nullptr)
            head->pre = n;
        head = n;
        if(end == nullptr)
            end = head;
    }

    void set(int key, int value){
        if(map.count(key)){
            Node *old = map[key];
            old->value = value;
            remove(old);
            setHead(old);
        } else{
            Node *temp = new Node(key, value);
            if(map.size() > capacity){
                map.erase(end->key);
                remove(end);
            }
            setHead(temp);
            map[key] = temp;
        }
        printNode("set");
    }

    void printNode(string explain){
        cout<<explain<<" "<<head->toString();
        Node *node = head->next;
        while(node){
            cout<<node->toString();
            node = node->next;
        }
        cout<<endl;
    }
public:
};

int main() {
    LRUCache lruCache(4);
    lruCache.set(1,1);
    lruCache.set(2,2);
    lruCache.set(3,3);
    lruCache.set(4,4);
    lruCache.set(5,5);
    cout<<" get(1):"<<lruCache.get(1)<<endl;
    lruCache.set(6,6);
    lruCache.set(5,10);
    cout<<" get(2):"<<lruCache.get(4)<<endl;

    return 0;
}