/*
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;



int main(){

    istringstream iss("Ana YES");
    string s;
    string r = "YES";
    while ( getline( iss, s, ' ' ) ) {
        cout << s.c_str() << endl;
        if(s.c_str() == r){
            cout << "FUNCIONA" << endl;
        }
        //printf( "`%s'\n", s.c_str() );
    }

    return 0;
}

*/

#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("in.txt","r",stdin);
    string s,ans,s1;
    set<string>s_y,s_n;
    int a=0;
    while(cin >> s and s != "FIM"){
            cin  >> s1 ;
        (s1 == "YES")? s_y.insert(s):s_n.insert(s);
        if(a==0)
            a = s.size();
        else if(a < s.size() and s1 == "YES"){
            a = s.size();
            ans = s;
        }
    }
    for(set<string>::iterator it = s_y.begin(); it != s_y.end() ;it++){
        cout << *it << endl;
    }
    for(set<string>::iterator it = s_n.begin(); it != s_n.end() ;it++){
        cout << *it << endl;
    }
    cout << "nAmigo do Habay:n";
    cout << ans << endl;
    return 0;
}

//g++ pratica7.cpp
//./a.out < in.txt