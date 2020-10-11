#include <stdexcept>
#include "rational.h"
#include <cmath>
using namespace std;

Rational::Rational(){
    n = 0;
    d = 1;
}

Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    n = num;
    d = denom;
    if(d < 0) {
        d *= -1;
        n *= -1;
    }
    this->reduce();
    this->normalize0();
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()


}

void Rational::reduce() {
        int gcf = gcd(n, d);
        n /= gcf;
        d /= gcf;
}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

//source: https://en.wikipedia.org/wiki/Greatest_common_divisor
int Rational::gcd(int a, int b) {
        int remainder = -1;

        while(remainder != 0) {
            remainder = a % b;
            a = b;
            if(remainder != 0) {
                b = remainder;
            }  
        }
        if(b < 0) {
            return -b;
        }
        return b;
}

//source: https://en.wikipedia.org/wiki/Least_common_multiple
int Rational::lcm(int a, int b) {

	return (a*b)/gcd(a,b);
} 

ostream& operator<<(ostream& ostr, const Rational& r){
    Rational temp(r.n, r.d);
	ostr << temp.n << '/' << temp.d;
	return ostr;
}

istream& operator>>(std::istream& istr, Rational& r) {
    char dash;
    istr >> r.n >> dash >> r.d;
    if(r.d < 0) {
        r.d *= -1;
        r.n *= -1;
    }
    r.reduce();
    return istr;
}

Rational Rational::operator+(const Rational &rhs) {

    Rational temp;
    if(d == rhs.d) {
        temp.n = n + rhs.n;
        temp.d = d; 
        this->reduce();
    } else {
        int num = rhs.n;
        int con = n;
        temp.d = lcm(d, rhs.d);
        con *= temp.d/d;
        num *= temp.d/rhs.d;
        temp.n = con + num;
        this->reduce();
    }
    return temp;
    
}

Rational operator+(const int& x, const Rational &rhs) {
    Rational temp(x,1);
    Rational final;
    if(temp.d == rhs.d) {
        final.n = temp.n + rhs.n;
        final.d = rhs.d;
        final.reduce();
    } else {
        int num = rhs.n;
        final.d = temp.lcm(temp.d, rhs.d);
        temp.n *= final.d/temp.d;
        num *= final.d/rhs.d;
        final.n = temp.n + num;
        final.reduce();
    }
    return final;

}

//rational plus int
Rational Rational::operator+(const int rhs) {
    Rational temp(rhs,1);
    if(d == temp.d) {
        temp.n = n + temp.n;
        temp.d = d; 
        this->reduce();
    } else {
        int num = temp.n;
        temp.d = lcm(d, temp.d);
        n *= temp.d/d;
        num *= temp.d;
        temp.n = n + num;
        this->reduce();
    }
    return temp;
}


//multiplying two rationals
Rational Rational::operator*(const Rational& rhs) {
    Rational temp;
    temp.n = n * rhs.n;
    temp.d = d * rhs.d;
    temp.reduce();
    return temp;
}

//multiplying rational by int
Rational Rational::operator*(const int rhs) {

    Rational temp;
    temp.n = n * rhs;
    temp.d = d;
    temp.reduce();
    return temp;

}

//multiplying int by rational
Rational operator*(const int& x, const Rational &rhs) {

    Rational temp;
    temp.n = x * rhs.n;
    temp.d = rhs.d;
    temp.reduce();
    return temp;
}

//exponents;
Rational Rational::operator^(const int rhs) {
    Rational temp;
    
    if (rhs == 0){
        temp.n = 1;
        temp.d = 1;
    } else if(rhs < 0) {
        temp.n = pow(d, -rhs);
        temp.d = pow(n, -rhs);
    } else {
        temp.n = pow(n, rhs);
        temp.d = pow(d, rhs);
    }
    return temp;
}


//for equal checks
bool Rational::operator==(const Rational& rhs) {
    return (n == rhs.n && d == rhs.d);
}

bool Rational::operator!=(const Rational& rhs) {
    return !(n == rhs.n && d == rhs.d);
}

//for less  than checks
bool Rational::operator<(const Rational& rhs) {
    return (((double)n/d) < ((double)rhs.n/rhs.d));
}

//+= adding rational plus rational
Rational Rational::operator+=(const Rational& rhs) {

    Rational temp;
    if(d == rhs.d) {
        temp.n = n + rhs.n;
        temp.d = d; 
        this->reduce();
    } else {
        int num = rhs.n;
        temp.d = lcm(d, rhs.d);
        n *= temp.d/d;
        num *= temp.d/rhs.d;
        temp.n = n + num;
        this->reduce();
    }
    n = temp.n;
    d = temp.d;
    return temp;
}

//rational plus int
Rational Rational::operator+=(const int rhs) {
    Rational temp(rhs,1);
    if(d == temp.d) {
        temp.n = n + temp.n;
        temp.d = d; 
        this->reduce();
    } else {
        int num = temp.n;
        temp.d = lcm(d, temp.d);
        n *= temp.d/d;
        num *= temp.d;
        temp.n = n + num;
        this->reduce();
    }
    n = temp.n;
    d = temp.d;
    return temp;
}

//*= multiplying two rationals
Rational Rational::operator*=(const Rational& rhs) {
    Rational temp;
    temp.n = n * rhs.n;
    temp.d = d * rhs.d;
    temp.reduce();
    n = temp.n;
    d = temp.d;
    return temp;
}

//*= multiplying rational by int
Rational Rational::operator*=(const int rhs) {
    Rational temp;
    temp.n = n * rhs;
    temp.d = d;
    temp.reduce();
    n = temp.n;
    d = temp.d;
    return temp;

}