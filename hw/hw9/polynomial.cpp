/*
Eric Cheung
polynomial.cpp
hw 9
*/ 

#include "polynomial.h"
using namespace std;

// ctors + copy control

Polynomial::Polynomial()
  : head_ptr(new Node(0)), degree(0)
{}

Polynomial::Polynomial(const vector<int>& coeffs)
  : head_ptr(nullptr), degree(0)
{
    if (coeffs.empty()) {
        head_ptr = new Node(0);
        degree = 0;
    } else {
        // build raw list
        Node* tail = nullptr;
        for (vector<int>::size_type i = 0;
             i < coeffs.size(); ++i)
        {
            Node* n = new Node(coeffs[i]);
            if (head_ptr == nullptr) {
                head_ptr = tail = n;
            } else {
                tail->next = n;
                tail = n;
            }
        }
        degree = static_cast<int>(coeffs.size()) - 1;
        cleanup();
    }
}

Polynomial::Polynomial(const Polynomial& other)
  : head_ptr(nullptr), degree(other.degree)
{
    head_ptr = other.clone();
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        clear();
        head_ptr = other.clone();
        degree  = other.degree;
    }
    return *this;
}

Polynomial::~Polynomial() {
    clear();
}

// arithmetic

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    int d1 = degree;
    int d2 = rhs.degree;
    int maxd = (d1 > d2 ? d1 : d2);

    int pad1 = maxd - d1;
    int pad2 = maxd - d2;

    Node* p1 = head_ptr;
    Node* p2 = rhs.head_ptr;
    Node* newH = nullptr;
    Node* newT = nullptr;

    for (int i = 0; i <= maxd; ++i) {
        int c1 = 0, c2 = 0;
        if (pad1 <= 0 && p1) { c1 = p1->coef; p1 = p1->next; }
        if (pad2 <= 0 && p2) { c2 = p2->coef; p2 = p2->next; }
        pad1--; pad2--;

        Node* n = new Node(c1 + c2);
        if (newH == nullptr) {
            newH = newT = n;
        } else {
            newT->next = n;
            newT = n;
        }
    }

    clear();
    head_ptr = newH;
    degree   = maxd;
    cleanup();
    return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial tmp(lhs);
    tmp += rhs;
    return tmp;
}

// comparison

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree != rhs.degree) return false;
    Polynomial::Node* p1 = lhs.head_ptr;
    Polynomial::Node* p2 = rhs.head_ptr;
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->coef != p2->coef) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return (p1 == nullptr && p2 == nullptr);
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

// evaluation

int Polynomial::evaluate(int x) const {
    int result = 0;
    for (Node* p = head_ptr; p != nullptr; p = p->next) {
        result = result * x + p->coef;
    }
    return result;
}

// output

ostream& operator<<(ostream& os, const Polynomial& poly) {
    Polynomial::Node* p = poly.head_ptr;
    int exp = poly.degree;
    bool first = true;

    while (p != nullptr) {
        int c = p->coef;
        if (c != 0) {
            // sign
            if (!first) {
                os << (c < 0 ? '-' : '+');
            } else if (c < 0) {
                os << '-';
            }
            int ac = (c < 0 ? -c : c);

            // coefficient
            if (ac != 1 || exp == 0) {
                os << ac;
            }
            // variable part
            if (exp > 0) {
                os << 'x';
                if (exp != 1) {
                    os << '^' << exp;
                }
            }
            first = false;
        }
        p = p->next;
        --exp;
    }

    if (first) {
        os << '0';
    }
    return os;
}

// helpers

void Polynomial::clear() {
    Node* p = head_ptr;
    while (p != nullptr) {
        Node* nxt = p->next;
        delete p;
        p = nxt;
    }
    head_ptr = nullptr;
    degree   = 0;
}

Polynomial::Node* Polynomial::clone() const {
    if (head_ptr == nullptr) return nullptr;
    Node* newH = new Node(head_ptr->coef);
    Node* tail = newH;
    for (Node* p = head_ptr->next; p != nullptr; p = p->next) {
        tail->next = new Node(p->coef);
        tail = tail->next;
    }
    return newH;
}

void Polynomial::cleanup() {
    // strip leading zeros
    while (head_ptr->coef == 0 && head_ptr->next != nullptr) {
        Node* tmp = head_ptr;
        head_ptr = head_ptr->next;
        delete tmp;
    }
    // recompute degree
    int d = 0;
    for (Node* p = head_ptr; p->next != nullptr; p = p->next) {
        ++d;
    }
    degree = d;
}
