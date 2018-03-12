#include <iostream>
#include <queue>

//两个队列实现一个栈
using std::queue;
using std::cout;
using std::endl;

template <typename T>
class myStruct{
private:
    queue<T> que1;
    queue<T> que2;
    T m_back_;
public:
    myStruct();
    ~myStruct();
    void push(T a);
    T pop();
    T top();
};

template <typename T> myStruct<T>::myStruct() {}

template <typename T> myStruct<T>::~myStruct() {}

template <typename T> void myStruct<T>::push(T a){
    que1.push(a);
}

template <typename T> T myStruct<T>::pop(){
    if(que1.empty() && que2.empty())
        throw std::exception();
    while (que1.size() > 1){
        T temp = que1.front();
        que1.pop();
        que2.push(temp);
    }
    if(que1.empty() && !que2.empty()){
        while(!que2.empty()){
            T temp = que2.front();
            que2.pop();
            que1.push(temp);
        }
        while (que1.size() > 1){
            T temp = que1.front();
            que1.pop();
            que2.push(temp);
        }
    }
    T ret = que1.front();
    que1.pop();
    return ret;
}

template <typename T> T myStruct<T>::top(){
    if(que1.empty() && que2.empty())
        throw std::exception();
    if(!que1.empty())
        return que1.back();
    else
        return que2.back();
}

int main(){
    myStruct<int> mystruct;

    mystruct.push(1);
    mystruct.push(2);
    mystruct.push(3);

    int a = mystruct.pop();

    cout<<a<<endl;

    mystruct.push(5);
    mystruct.push(4);

    mystruct.pop();
    cout<<mystruct.top()<<endl;

    return 0;
}