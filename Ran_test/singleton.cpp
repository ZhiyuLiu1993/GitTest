#include <iostream>

class Singleton
{
public:
    static Singleton* GetInstance();
protected:
    Singleton(){};
private:
    static Singleton * m_pInstance;
    class Garbo
    {
    public:
        ~Garbo()
        {
            std::cout<<"in"<<std::endl;
            delete Singleton::m_pInstance;
        }
    };
    static Garbo m_garbo;
};
//void access(void)
//{
//    Singleton * Singleton::m_pInstance = NULL;
//    Singleton::Garbo Singleton::m_garbo; // 不要忘记此处的定义
//} // invalid use
Singleton * Singleton::m_pInstance = NULL;
Singleton::Garbo Singleton::m_garbo; // 不要忘记此处的定义
Singleton * Singleton::GetInstance()
{
    if(m_pInstance == NULL)
    {
//        Lock();
        if(m_pInstance == NULL)
            m_pInstance = new Singleton;
//        Unlock();
    }
    return m_pInstance;
}

int main() {
    Singleton::GetInstance();
    return 0;
}