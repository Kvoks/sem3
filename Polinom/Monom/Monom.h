#ifndef POLINOM
#define POLINOM


#include <iostream>
#include <vector>
#include "/Programming/GithubRep/sem4/Dynamic Structures/Singly linked list/Singly linked list.h"

template <typename T>
class Values {
public:
	T value;
	float degrees;

	Values(T value = 1, float degrees = 1){
		this->value = value;
		this->degrees = degrees;
	}
	Values(const Values& r){
		this->value = r.value;
		this->degrees = r.degrees;
	}

	void setValues(T value) {
		this->value = value;
	}
	void setDegrees(float degrees) {
		this->degrees = degrees;
	}

	T getValues() const { 
		return value; 
	}
	float getDegrees() const { 
		return degrees;
	}

	bool operator==(const Values& r) const {
		return ((*this == r)||(this->value == r.value && this->degrees == r.degrees));
	}
	bool operator!=(const Values& r) const {
		return !((*this == r) || (this->value == r.value && this->degrees == r.degrees));
	}
	bool operator<(const Values& r) const {
		return (this->degrees < r.degrees&& this->value == r.value) || (this->degrees == r.degrees && this->value < r.value);
	}
	bool operator<=(const Values& r) const {
		return (this->degrees <= r.degrees && this->value == r.value) || (this->degrees == r.degrees && this->value <= r.value);
	}
	bool operator>(const Values& r) const {
		return (this->degrees > r.degrees && this->value == r.value) || (this->degrees == r.degrees && this->value > r.value);
	}
	bool operator>=(const Values& r) const {
		return (this->degrees >= r.degrees && this->value == r.value) || (this->degrees == r.degrees && this->value >= r.value);
	}
};

template<typename T>
class Monom {
public:
	std::vector<Values<T>> line;
	float ldeg;

	Monom() { ldeg = 1.0; }
	Monom(const std::vector<Values<T>>& line, float ldeg = 1.0){
		this->line = line;
		this->ldeg = ldeg;
	}
	Monom(const Monom& r){
		this->line = r.line;
		this->ldeg = r.ldeg;
	}

	void addLine(const Values<T>& r) {
		this->line.push_back(r);
	}
	void setLdeg(float r) {
		this->ldeg = r;
	}
	float getLdeg() const {
		return ldeg;
	}

	std::string to_string() const {
		std::string res;
		if (ldeg == 0) {
			res = "0";
		}
		else {
			if (ldeg != 1 || line.empty()) {
				res += ldeg.to_string();
			}
			for (const auto& r : line) {
				res += "*" + r.to_string();
			}
		}
		return res;
	}
	
	Monom<T> operator+(const Monom<T> r) {
		Monom<T> res;
		res.line = line;
		res.ldeg = ldeg + r.ldeg;
		return res;
	}
	Monom<T> operator-(const Monom<T>& r)const {
		Monom<T> res;
		res.line = line;
		res.ldeg = ldeg - r.ldeg;
		return res;
	}
	//ну и получается что полином это лист мономов и халява
};

template<typename T>
class Polinom {
	Singly_linked_list<Monom<T>> list;
	float max_power;
	int count;
};
#endif // !POLINOM