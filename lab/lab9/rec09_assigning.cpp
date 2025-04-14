class Base{

};

class Derived : public Base{

};

int main()
{
    Base b;
    Derived d;
    Base* bp = nullptr;
    Derived* dp = nullptr;
    b = d;
    // d = b;
    // cannot assign base instance to derived instance
    bp = dp;
    // dp = bp;
    // cannot assign base pointer to derived pointer
    dp = &d;
    bp = &b;
    // dp = &b;
    bp = &d;
    // cannot assign base reference to derived pointer
}