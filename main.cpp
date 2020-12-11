// Task 7
// Создать массив списков, содержащий n =10 элементов многочлена Лукаса
// определяемого формулами:
// K0(x)=2
// K1(x)=x
// K_n(x)=xK_{n-1}(x) +K_{n-2}(x)

#include <iostream>
#include <list>
#include <iterator>
#include <utility>

using namespace std;
list < pair <int,int> >::iterator it,it_1;
// first  - степень переменной
// second - коэффициент

void print(list < pair <int,int> > lst)
{
    for (it = lst.begin(); it != lst.end(); it++) {
        if( it->first==0) {
            if( it->second<0)
                cout << " " << it->second;
            else
                cout <<" +" << it->second;
        } else {
            if( it->second==1)
                cout << " +x^" << it->first;
            else if( it->second<0)
                cout << " " << it->second << "x^" << it->first;
            else
                cout <<" +" << it->second << "x^" << it->first;
        }
    }
}

void lst_add(list < pair <int,int> > &lst, int a, int k) // lst += a*x^k
{
    pair <int,int> p(k, a);
    lst.push_front(p);
}


pair <int,int> operator * (int n, pair <int,int> p)
{
    p.second *=n; return p;
}

list < pair <int,int> > operator * (list < pair <int,int> > lst, int a)
{
    for (it = lst.begin(); it != lst.end(); it++) *it = a*(*it);
    return lst;
}

list < pair <int,int> > operator * (list < pair <int,int> > lst, pair <int,int> p)
{
    for (it = lst.begin(); it != lst.end(); it++)
        it->first = it->first + p.first;
    lst = lst * p.second;
    return lst;
}

list < pair <int,int> > operator + (list < pair <int,int> > lst1, list < pair <int,int> > lst2)
{
    list < pair <int,int> > lst3;
    it = lst1.begin();
    it_1 = lst2.begin();

    while(it != lst1.end() && it_1 != lst2.end()) {
        if (it->first > it_1->first) lst3.push_back(*it++);
        if (it->first < it_1->first) lst3.push_back(*it_1++);
        if (it->first == it_1->first) {
            it->second = it->second + it_1->second;
            lst3.push_back(*it);
            it++;
            it_1++;
        }
    }
    while (it != lst1.end()) {
        lst3.push_back(*it);
        it++;
    }

    while (it_1 != lst2.end()) {
        lst3.push_back(*it_1);
        it_1++;
    }
    return lst3;
}

list < pair <int,int> > operator - (list < pair <int,int> > lst1, list < pair <int,int> > lst2) {
    lst2 = lst2*(-1);
    lst1 = lst1 + lst2;
    return lst1;
}

int main()
{
    int i;
    list < pair <int,int> > T[10];
    list < pair <int,int> > T1, T2, T3;
    // first  - степень переменной
    // second - коэффициент
    lst_add(T[0], 2, 0);        // 2
    lst_add(T[1], 1, 1);        // x
    pair <int,int> X(1,1);      // x

    for(i = 2; i < 10; i++)
    {
        T[i] = T[i-1]*X + T[i-2];
    }

    for(i = 0; i < 10; i++)
    {
        cout << i << ": ";
        print(T[i]);
        cout << endl;
    }
    cout << "\nIndex: ";  cin >> i;
    cout << "Lucas[" << i << "]=" ;
    print(T[i]);
    cout << endl;

    return 0;
}
