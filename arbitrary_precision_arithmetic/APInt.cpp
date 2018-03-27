#include "APInt.h"
#include <stdexcept>
#include <exception>

APInt::APInt(int k){
	*this=k;
}

APInt::APInt(const char* str){
	*this=str;
}

APInt& APInt::operator=(int k){
	if(k<0){
		k=-k;
		negative=true;
	}
	else{
		negative=false;
	}
	do{
		digits.insert(digits.begin(),k%10);
		k/=10;
	}while(k>0);
	return *this;
}

APInt& APInt::operator=(const char* str){
	if(str[0]=='-'){
		negative=true;
		str++;
	}
	else
		negative=false;
	for(int i=0;str[i];i++) if(str[i]>='0' && str[i]<='9') digits.push_back(str[i]-'0');
	if(abs(*this)==APInt(0))
		negative=false; //-0 nem lehet
	else
		while(digits[0]==0) digits.erase(digits.begin()); //esetleges vezeto nullak levagasa
	return *this;
}

std::ostream& operator<<(std::ostream& os, const APInt& k){
	if(k.negative) os<<"-";
	for(auto d: k.digits) os<<d;
	return os;
}

unsigned APInt::getNumDigits() const{
	return digits.size();
}

bool APInt::isNegative() const{
	return negative;
}

bool APInt::operator==(const APInt& rhs) const{
	if(negative!=rhs.negative) return false;
	if(digits.size()!=rhs.digits.size()) return false;
	for(int i=0;i<digits.size();i++) if(digits[i]!=rhs.digits[i]) return false;
	return true;
}

bool APInt::operator!=(const APInt& rhs) const{
	return !(*this==rhs);
}

bool APInt::operator<(const APInt& rhs) const{
	if(*this==rhs) return false;
	if(negative && (!rhs.negative)) return true;
	if((!negative) && rhs.negative) return false;
	if((!negative) && (!rhs.negative) && (digits.size()<rhs.digits.size())) return true;
	if((!negative) && (!rhs.negative) && (digits.size()>rhs.digits.size())) return false;
	if(negative && rhs.negative && (digits.size()>rhs.digits.size())) return true;
	if(negative && rhs.negative && (digits.size()<rhs.digits.size())) return false;
	for(int i=0;i<digits.size();i++)
		if(digits[i]>rhs.digits[i])
			return negative;
		else if(digits[i]<rhs.digits[i])
			return !negative;
}

bool APInt::operator<=(const APInt& rhs) const{
	return (*this==rhs) || (*this<rhs);
}

bool APInt::operator>(const APInt& rhs) const{
	return (*this!=rhs) && (!(*this<rhs));
}

bool APInt::operator>=(const APInt& rhs) const{
	return (*this==rhs) || (*this>rhs);
}

APInt APInt::operator+() const{
	return *this;
}

APInt APInt::operator-() const{
	APInt res(*this);
	res.negative=!res.negative;
	return res;
}

APInt APInt::operator+(const APInt& rhs) const{
	if((negative && rhs.negative) || (!negative && !rhs.negative)){
		APInt res;
		if(negative) res.negative=true;
		int carry=0;
		int i=0;
		do{
			int a=(i<digits.size())?digits[digits.size()-i-1]:0;
			int b=(i<rhs.digits.size())?rhs.digits[rhs.digits.size()-i-1]:0;
			int s=a+b+carry;
			carry=s/10;
			res.digits.insert(res.digits.begin(),s%10);
			i++;
		}while((carry>0) || (i<digits.size()) || (i<rhs.digits.size()));
		return res;
	}
	if(negative && !rhs.negative)
		return rhs-(-*this);
	if(!negative && rhs.negative)
		return *this-(-rhs);
}

APInt APInt::operator-(const APInt& rhs) const{
	if(*this==rhs) return APInt(0);
	if((negative && rhs.negative) || (!negative && !rhs.negative)){
		APInt res;
		if(*this<rhs) res.negative=true;		
		const APInt& greater=((*this>rhs) ^ negative)?*this:rhs;
		const APInt& smaller=((*this>rhs) ^ negative)?rhs:*this;
		int carry=0;
		int i=0;
		do{
			int s=(i<smaller.digits.size())?smaller.digits[smaller.digits.size()-i-1]:0;
			int g=(i<greater.digits.size())?greater.digits[greater.digits.size()-i-1]:0;
			int d=g-s-carry;
			carry=0;
			while(d<0){
				d+=10;
				carry++;
			}
			res.digits.insert(res.digits.begin(),d);
			i++;
		}while((carry>0) || (i<digits.size()) || (i<rhs.digits.size()));
		while(res.digits[0]==0) res.digits.erase(res.digits.begin()); //vezeto nullak levagasa
		return res;
	}
	if(negative && !rhs.negative)
		return -((-*this)+rhs);
	if(!negative && rhs.negative)
		return *this+(-rhs);
}

APInt APInt::operator/(const APInt& rhs) const{
	APInt r(0), q(0), absRHS(rhs), absThis(*this);
	absRHS.negative=absThis.negative=false;
	if(absRHS==APInt(0))
		std::throw_with_nested(std::runtime_error("Error (/): division by zero."));
	if(absRHS>absThis) return APInt(0);
	for(int i=0;i<digits.size();i++){
		if(r==APInt(0))
			r=APInt(digits[i]);
		else
			r.digits.push_back(digits[i]);
		while(r>=absRHS){
			r-=absRHS;
			q.digits[i]++;
		}
		if(i<digits.size()-1) q.digits.push_back(0);
	}
	while(q.digits[0]==0) q.digits.erase(q.digits.begin()); //vezeto nullak levagasa
	q.negative=negative ^ rhs.negative;
	return q;
}

APInt APInt::operator%(const APInt& rhs) const{
	APInt r(0), q(0), absRHS(rhs), absThis(*this);
	absRHS.negative=absThis.negative=false;
	if(absRHS==APInt(0))
		std::throw_with_nested(std::runtime_error("Error (%): division by zero."));
	if(absRHS>absThis) return *this;
	for(int i=0;i<digits.size();i++){
		if(r==APInt(0))
			r=APInt(digits[i]);
		else
			r.digits.push_back(digits[i]);
		while(r>=absRHS){
			r-=absRHS;
			q.digits[i]++;
		}
		if(i<digits.size()-1) q.digits.push_back(0);
	}
	if(r!=APInt(0)) r.negative=negative;
	return r;
}

APInt APInt::operator*(const APInt& rhs) const{
	APInt res(0);
	int carry=0;
	for(int i=0;i<digits.size();i++){
		for(int j=0 ; j<rhs.digits.size() ; j++){
		APInt temp;
			int p=digits[digits.size()-i-1]*rhs.digits[rhs.digits.size()-j-1]+carry;
			temp.digits.push_back(p%10);
			carry=p/10;
		while(carry>0){
			temp.digits.insert(temp.digits.begin(),carry%10);
			carry=carry/10;
		}
		for(int k=0;k<i+j;k++) temp.digits.push_back(0);
		res+=temp;
		}
	}
	res.negative=negative ^ rhs.negative;
	return res;
}

APInt& APInt::operator+=(const APInt& rhs){
	*this=*this+rhs;
	return *this;
}

APInt& APInt::operator-=(const APInt& rhs){
	*this=*this-rhs;
	return *this;
}

APInt& APInt::operator/=(const APInt& rhs){
	*this=*this/rhs;
	return *this;
}

APInt& APInt::operator%=(const APInt& rhs){
	*this=*this%rhs;
	return *this;
}

APInt& APInt::operator*=(const APInt& rhs){
	*this=*this*rhs;
	return *this;
}

APInt& APInt::operator++(int){
	*this=*this+APInt(1);
	return *this;
}

APInt& APInt::operator--(int){
	*this=*this-APInt(1);
	return *this;
}

APInt& APInt::operator++(){
	(*this)++;
	return *this;
}

APInt& APInt::operator--(){
	(*this)--;
	return *this;
}

APInt APInt::abs(const APInt& k){
	APInt res(k);
	res.negative=false;
	return res;
}

APInt APInt::factorial(int k){
	APInt res(1);
	if(k<0)
		std::throw_with_nested(std::runtime_error("Error (factorial): negative argument."));
	if(k==0) return res;
	int numDigits=0;
	for(int n=1;n<=k;n++){
		int carry=0;
		for(int i=numDigits;i>=0;i--){
			int d=res.digits[i]*n+carry;
			res.digits[i]=d%10;
			carry=d/10;
		}
		while(carry>0){
			res.digits.insert(res.digits.begin(),carry%10);
			carry=carry/10;
			numDigits++;
		}
	}
	return res;
}

APInt APInt::gcd(APInt a, APInt b){
	APInt temp;
	if(a.negative || b.negative)
		std::throw_with_nested(std::runtime_error("Error (gcd): negative argument."));
	if(a==0 && b==0)
		std::throw_with_nested(std::runtime_error("Error (gcd): gcd(0,0) is undefined."));
	while(b>0){
		temp=b;
		b=a%b;
		a=temp;
	}
	return a;
}

APInt APInt::lcm(APInt a, APInt b){
	if(a.negative || b.negative)
		std::throw_with_nested(std::runtime_error("Error (lcm): negative argument."));
	if(a==0 || b==0)
		return APInt(0);
	return (a*b)/gcd(a,b);
}