#include "bigint.h"

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace ACA
{

BigInt::BigInt(std::string& s)
{
    vector<char> tmp;
    for(int i = 0; i<s.size(); i++){
        assert(s[i]>='0' || s[i] <='9');
        if(s[i]=='0' && tmp.size()==0) continue;
        tmp.push_back(s[i]);
    }
    for(int i = tmp.size()-1; i>0; i--){
        num.push_back(tmp[i]);
    }   
}

BigInt::BigInt(unsigned long long nr){
    if(nr == 0){
        num.push_back('0');
    }
    else{
        while(nr){
        char x = ((nr%10) + '0');
        num.push_back(x);
        nr/=10;
        }
    }
}

BigInt::BigInt(const BigInt& other)
{
    for(int i = 0; i<other.num.size(); i++){
        num.push_back(other.num[i]);
    }
}

BigInt& BigInt::operator()(string& s){
    num.clear();
    vector<char> tmp;
    for(int i = 0; i<s.size(); i++){
        assert(s[i]>='0' || s[i] <='9');
        if(s[i]=='0' && tmp.size()==0) continue;
        tmp.push_back(s[i]);
    }
    for(int i = tmp.size()-1; i>=0; i--){
        num.push_back(tmp[i]);
    }  
    return *this;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    // Guard self assignment
    if (this == &other)
    {
        return *this;
    }
    num.clear();
    for(int i = 0; i<other.num.size(); i++){
        num.push_back(other.num[i]);
    }
    return *this;
}

/*
BigInt& BigInt::operator=(BigInt other) noexcept
{
    // exchange resources between *this and other
    std::swap(digits, other.digits);
    return *this;
}
*/

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    if(lhs.num.size()!=rhs.num.size())return false;
    for(int i = 0; i < lhs.num.size(); i++){
        if(lhs.num[i]!=rhs.num[i]){
            return false;
        }
    }
    return true;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{   
    int n = lhs.num.size(), m = rhs.num.size();
    if(n<m) return true;
    if(n>m)return false;

	for(int i = n-1; i>=0; i--){
        if(lhs.num[i]>rhs.num[i]){
            return false;
        }
        else if(lhs.num[i]<rhs.num[i]){
            return true;
        }
    }
    return false;
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{
    int n = lhs.num.size(), m = rhs.num.size();
    if(m<n) return true;
    if(m>n)return false;

	for(int i = n-1; i>=0; i--){
        if(lhs.num[i]<rhs.num[i]){
            return false;
        }
        else if(lhs.num[i]>rhs.num[i]){
            return true;
        }
    }
    return false;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
	return !(lhs > rhs);
}

BigInt& BigInt::operator++()
{
	for(int i = 0; i<num.size(); i++){
        while(num[i]=='9'){
            num[i] = '0';
        }
        if(i==num.size()-1) num.push_back('1');
        else {
            num[i]++;
            break;
        }
    }
    return *this;
}

BigInt BigInt::operator++(int /* tmp */)
{
	BigInt old = *this;
	operator++(); // prefix increment
	return old;
}

BigInt& BigInt::operator--()
{
    if(num[0] == '0'){
        assert(num.size()!=1);
    }
	for(int i = 0; i<num.size(); i++){
        if(num[i]=='0'){
            num[i] = '9';
            continue;
        }
        num[i]-=1;
        break;
    }
    int i = num.size()-1;
    while(num[i]=='0' && i>0){
        num.pop_back();
        i--;
    }
    return *this;
}

BigInt BigInt::operator--(int /* tmp */)
{
	BigInt old = *this;
	operator--(); // prefix decrement
	return old;
}


void BigInt:: fit(){
    while(num[num.size()-1] == '0'){
        num.pop_back();
    }
}
BigInt& BigInt::operator+=(const BigInt& rhs)
{
    int tmp = 0; 
    int n =num.size(), m = rhs.num.size();
    int N = n>m?n:m;
    for(int i = 0; i<N; i++){
        if(i>=n){
            int k = tmp+rhs.num[i]-'0';
            num.push_back(k%10 +'0');
            tmp = k/10;
        }
        else{
            int y = i>=m? '0':rhs.num[i];
            int x = num[i]+y-'0'+tmp;
            num[i] = (x-'0')%10 +'0';
            tmp = (x-'0')/10;
        }
    }
    if(tmp!=0){
        num.push_back(tmp+'0');
    }
    return *this;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
    BigInt tmp = lhs;
	tmp += rhs;
	return tmp;
}

BigInt& BigInt::operator-=(const BigInt& rhs)
{
 /*   assert((*this)>=rhs);
    if(*this == rhs) {
        *this = BigInt();
        return *this;
    }
    int m = rhs.num.size();
    int tmp = 0;
    for(int i = 0; i<=m; i++){
        char x = rhs.num[i];
        char y = num[i];
        if(i==m){
            while(num[i++] == 0 ){
                num[i]='9';
            } 
            num[i]--;
        }
        if(num[i]<(x+tmp)){
            num[i] = (y-'0') + 10 - (x-'0'+tmp)+'0';
            tmp = 1;
        }
        else{
            num[i] = (y-'0') - (x-'0'+ tmp) +'0';
        }
    }
*/



    assert(*this>=rhs);
    if(*this == rhs){
        BigInt ans(0);
        *this = ans;
        return *this;
    }
    int n = num.size();
    int m =rhs.num.size();
    int tmp = 0;
    for(int i = 0; i<n; i++){
        int x = num[i];
        int y;
        if(i>=m)   y ='0';
        else y = rhs.num[i];
        if(x >= y+tmp) {
            num[i] = x-(y+tmp)+'0';
            tmp = 0;
        }
        else{
            num[i] = (x-'0')+10 - ((y-'0')+tmp) + '0';
            tmp = 1;
        }
    }
    this->fit();
    return *this;
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
	lhs -= rhs;
	return lhs;
}

BigInt& BigInt::operator*=(const BigInt& rhs)
{

    BigInt tmp1 = rhs < *this ? rhs: *this;
    BigInt tmp2 = rhs < *this ? *this: rhs;
    BigInt tmp = tmp2;
    if(tmp2.num[0] == '0' && tmp2.num.size()==1) return *this = BigInt();
    if(tmp1.num[0] == '0' && tmp1.num.size()==1) return *this = BigInt();
    tmp1--;
    BigInt a(0);
	while(tmp1 != a){
        tmp1--;
        tmp2 += tmp;
    }
    *this = tmp2;
    return *this;
}

BigInt operator*(const BigInt& lhs, const BigInt& rhs)
{
    BigInt tmp(lhs);
	tmp *= rhs;
	return tmp;
}

BigInt& BigInt::operator/=(const BigInt& rhs)
{
    if(*this < rhs){
        *this = BigInt();
        return *this; 
    }
    if(*this == rhs){
        *this = BigInt(1);
        return *this; 
    }
    BigInt k;
    int i=num.size()-1;
    vector<int> v;
    BigInt tmp;
    for(i = num.size()-1; tmp<rhs; i--){
        tmp*=10;
        BigInt f(num[i]-'0');
        tmp+=f;
        k = tmp;
        if(i==0) break;
    }
    int m = 9;
    for(; i>=0; i--){
        if(k < *this){
            k*=10;
            BigInt tmp(num[i]-'0');
            k+=tmp;
        }
        if(k<rhs){
            v.push_back(0);
            continue;
        }
        for(m = 1; m*rhs<=k; m++);
        m--;
        v.push_back(m);
        k-=m*rhs;
    }
    i=0;
    BigInt ans;
    for(int j = 0; j<v.size(); j++){
        BigInt f(v[j]);
        ans *=10;
        ans +=f;
    }
    *this = ans;
    return *this;
}

BigInt operator/(const BigInt& lhs, const BigInt& rhs)
{
    BigInt tmp = lhs;
	tmp /= rhs;
	return tmp;
}

BigInt& BigInt::operator%=(const BigInt& rhs)
{
	BigInt a = *this / rhs;
    *this = *this - a*rhs;
    return *this;
}

BigInt operator%(const BigInt& lhs, const BigInt& rhs)
{
    BigInt tmp = lhs;
	tmp%=rhs;
	return tmp;
}

BigInt& BigInt::operator^=(const BigInt& rhs)
{
    BigInt zero;
    BigInt tmp = (*this) * (*this);
    BigInt in = *this;
    if(rhs == zero){
        *this = BigInt(1);
        return *this;
    }
    if(rhs>=2){
        *this = tmp;
    }
	BigInt ex = rhs/2;
    ex--;
    while(ex != zero){
        ex--;
        *this *= tmp;
    }
    if(rhs%2 !=zero){
        *this *= in;
    }
    return *this;
}

BigInt operator^(BigInt lhs, const BigInt& rhs)
{
	lhs ^= rhs;
	return lhs;
}

istream& operator>>(istream& in, BigInt& a)
{
    char x;
    string tmp;
    getline(in, tmp, '\n');
    a(tmp);
    return in;
}

ostream& operator<<(ostream& out, const BigInt& a)
{
	for(int i = a.num.size()-1; i>=0; i--){
        out << a.num[i];
    }
    return out;
}

} // namespace ACA