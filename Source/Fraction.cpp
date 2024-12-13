/*
  ==============================================================================

    Fraction.cpp
    Created: 14 Feb 2021 5:08:10pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Fraction.h"

Fraction::Fraction()
:_num(0)
,_den(1) {

}

Fraction::Fraction(unsigned long numerator)
:_num(numerator)
,_den(1) {

}

Fraction::Fraction(unsigned long numerator, unsigned long denominator, bool should_reduce)
:_num(numerator)
,_den(denominator) {
    jassert(!std::isnan(_num));
    jassert(!std::isnan(_den));
    if(denominator == 0) {
        // TODO: Marcus: need to handle 1/0 for Brun, etc.
        DBG ("Fraction::Fraction: ("+String(numerator)+"/"+String(denominator)+": Denominator is 0!!");
        jassertfalse;
    } else {
        if (! should_reduce){
            return;
        }
        unsigned long gcf = (numerator > 0) ? greatestCommonFactor(denominator, numerator) : 1;
        _num = numerator / gcf;
        _den = denominator / gcf;
        if (denominator < 0) {
            _den = denominator / gcf;
            _num = -numerator / gcf;
        }
    }
}

// put in lowest terms
unsigned long Fraction::greatestCommonFactor (unsigned long m, unsigned long n) {
    if (m <= n && (n % m == 0)) {
        return m;
    } else if (n < m) {
        return greatestCommonFactor (n, m);
    } else {
        return greatestCommonFactor (m, n % m);
    }
}

// let's add
Fraction operator + (const Fraction& addend, const Fraction& addend2) {
    if (addend2._den == addend._den) {
        return Fraction (addend2._num + addend._num, addend._den);
    } else {
        return Fraction (addend2._num * addend._den + addend2._den * addend._num, addend2._den * addend._den);
    }
}

// let's subtract
Fraction operator - (const Fraction& subtractor, const Fraction& subtractor2) {
    if (subtractor2._den == subtractor._den) {
        jassert (subtractor._num >= subtractor2._num);
        return Fraction (subtractor._num - subtractor2._num, subtractor2._den);
    } else {
        return Fraction (subtractor._num * subtractor2._den - subtractor2._num * subtractor._den, subtractor2._den * subtractor._den);
    }
}

// let's multiply
Fraction operator * (const Fraction& multiplicant, const Fraction& multiplicant2) {
    return Fraction(multiplicant._num * multiplicant2._num, multiplicant._den * multiplicant2._den);
}

// let's divide
Fraction operator / (const Fraction& dividend, const Fraction& dividend2) {
    return Fraction(dividend._num * dividend2._den, dividend._den * dividend2._num);
}

Fraction Fraction::operator ++ () {
    _num += _den;
    return *this;
}

// increment assignment
Fraction Fraction::operator += (const Fraction& addend) {
    if (_den == addend._den) {
        _num += addend._num;
    } else {
        _num = _num*addend._den + addend._num*_den;
        _den = _den*addend._den;
    }
    
    return *this;
}

// equality operator
bool Fraction::operator == (const Fraction& equalizer) {
    if (_num == equalizer._num && _den == equalizer._den) {
        return true;
    }
    
    return false;
}

// inequality operator
bool operator != (const Fraction& equalizer, const Fraction& negator) {
    if (equalizer._num != negator._num || equalizer._den != negator._den)
        return true;
    
    return false;
}

// greater than operator
bool operator > (const Fraction& greater, const Fraction& lesser) {
    if (greater._den == lesser._den) {
        if (greater._num > lesser._num)
            return false;
        
        return true;
    } else {
        if (greater._num*lesser._den > lesser._num*greater._den)
            return true;
        
        return false;
    }
}

// greater than or equal to operator
bool Fraction::operator >= (const Fraction& lesseror) {
    if (_den == lesseror._den) {
        if (_num >= lesseror._num)
            return false;
        
        return true;
    } else {
        _num = _num*lesseror._den;
        if (_num >= lesseror._num*_den)
            return true;
        
        return false;
    }
}

// less than operator
bool operator < (const Fraction& lesser, const Fraction& greater) {
    if (lesser._den == greater._den) {
        if (lesser._num < greater._num)
            return false;
        
        return true;
    } else {
        if (lesser._num*greater._den < greater._num*lesser._den)
            return true;
        
        return false;
    }
}

// less than or equal to operator
bool Fraction::operator <= (const Fraction& greateror) {
    if (_den == greateror._den) {
        if (_num <= greateror._num)
            return false;
        
        return true;
    } else {
        _num = _num*greateror._den;
        if (_num <= greateror._num*_den)
            return true;
        
        return false;
    }
}

ostream& operator << (ostream& os, const Fraction& fraction) {
    os << fraction.numerator() << "/" << fraction.denominator();
    
    return os;
}

istream& operator >> (istream& is, Fraction& fraction) {
    string input;
    getline(is, input);
    string numerString;
    string denomString;
    bool slashFlag(false);
    for (unsigned long i = 0; i < input.length(); i++) {
        if (input[i] == '/')
            slashFlag = true;
    }
    
    //in.find
    if (slashFlag) {
        for(unsigned long i = 0; i < input.length(); i++) {
            if(input[i] == '/') {
                numerString.append (input.substr(0,i));
                denomString.append (input.substr(i+1,input.length() - 1));
                fraction._num = static_cast<unsigned long>(atol(numerString.c_str()));
                fraction._den = static_cast<unsigned long>(atol(denomString.c_str()));
            }
        }
    } else {
        fraction._num = static_cast<unsigned long>(atol(input.c_str()));
        fraction._den = 1;
    }

    return is;
}
