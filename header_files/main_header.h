#ifndef main_header
#define main_header

#include <iostream>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
typedef unsigned u;
typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
typedef pair<string, string> pss;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <double> vd;
typedef vector <char> vc;
typedef vector <string> vs;
typedef vector <pii> vpii;
typedef vector <psi> vpsi;
typedef vector <pss> vpss;
typedef unsigned long long ull;
#define fff(itr, lim) for (int itr = 0; itr < int(lim); ++itr)
#define ffff(itr, lim) for (int itr = 1; itr <= int(lim); ++itr)
#define rrr(itr, lim) for (int itr = int(lim)-1; itr > -1; --itr)
#define wn(n) while (n--)
#define s1(n) scanf("%d", &n)
#define s2(n, m) scanf("%d %d", &n, &m)
#define s3(n, m, k) scanf("%d %d %d", &n, &m, &k)
#define sv(n, v) fff(i, n) scanf("%d", &v[i])
#define pr(n) printf("%d", n)
#define pr2(n, m) printf("%d %d", n, m)
#define prn(n) printf("%d\n", n)
#define prs(n) printf("%d ", n)
#define fast ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);


#define MENTOR_WIDTH 100

#define MAX_GRADE 10
#define MIN_GRADE 0

#define DATABASE_PATH string("./database/")
#define DATABASE_FILE_TYPE string(".txt")


#include "helper_functions.h"

struct Answer {
public:
    int _student_id = -1, _grade = -1;
    string answer{};
    bool operator<(Answer a) {
        return _student_id < a._student_id;
    }
};




struct compare_answer_by_id {
    bool operator()(const Answer& a1, const Answer& a2) const {
        return a1._student_id < a2._student_id;
    }
};



class Assignment_model;
class Assignment_controler;
class Assignment_view;


#endif