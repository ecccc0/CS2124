/*
Eric Cheung
polynomial.h
hw 9
*/ 
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

class Polynomial {
public:
    // default to 0
    Polynomial();

    // from coeffs 
    explicit Polynomial(const std::vector<int>& coeffs);

    // copy‐control
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    // arithmetic
    Polynomial& operator+=(const Polynomial& rhs);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

    // comparison
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

    // evaluate at x
    int evaluate(int x) const;

    // output
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

private:
    struct Node {
        int coef;
        Node* next;
        Node(int c = 0, Node* n = nullptr)
          : coef(c), next(n) {}
    };

    Node* head_ptr;  // points at highest‐degree coef
    int degree;      // highest exponent

    void clear();         // delete all nodes
    Node* clone() const;  // deep copy list
    void cleanup();       // strip leading zeros & fix degree
};

#endif // POLYNOMIAL_H
