#include <iostream>
#include <vector>

template <typename T>
class Values {
	T values;
	float degrees;
public:
	Values(T value, float deg): values(value), degrees(deg){}
	Values(const Values& r): values(r.values), degrees(r.degrees){}

	void setValues(T value) { values = value; }
	void setDegrees(float deg) { degrees = deg; }
	T getValues() const { return values; }
	float getDegrees() const { return degrees; }

	bool operator==(const Values& r) const {
		return (*this == r);
	}
	bool operator!=(const Values& r) const {
		return !(*this == r);
	}
	bool operator<(const Values& r) const {
		return (degrees<r.degrees && values==r.values) || (degrees == r.degrees && values < r.values)
	}
	bool operator<=(const Values& r) const {
		return (degrees <= r.degrees&& values == r.values) || (degrees == r.degrees && values <= r.values)
	}
	bool operator>(const Values& r) const {
		return (degrees > r.degrees&& values == r.values) || (degrees == r.degrees && values > r.values)
	}
	bool operator>=(const Values& r) const {
		return (degrees >= r.degrees && values == r.values) || (degrees == r.degrees && values >= r.values)
	}
	template<typename T>
	friend class Monom;
};

template<typename T>
class Monom {
public:
	std::vector<Values<T>> line;
	float ldeg;

	Monom() { ldeg = 1.0; }
	Monom(const std::vector<Values<T>>& rline, const Fraction& rldeg): line(r), ldeg(rldeg){}
	Monom(const Values& r): line(r.line), ldeg(r.ldeg){}

	void addLine(const TVarible<T>& r) {
		this->line.push_back(r);
	}
	void setLdeg(const Fraction& r) {
		this->coef = r;
	}
	float getLdeg() const {
		return coef;
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
	
	Monom operator+(const TMonom<T> r) {
		Monom<T> res;
		result.line = line;
		result.ldeg = ldeg + r.ldeg;
		return res;
	}
	Monom<T> operator-(const Monom<T>& r)const {
		Monom<T> res;
		result.line = line;
		result.ldeg = ldeg - r.ldeg;
		return res;
	}
	//ну и получается что полином это лист мономов и халява
};