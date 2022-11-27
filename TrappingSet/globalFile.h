#ifndef __globalFile_h__
#define __globalFile_h__

#include <cstdio>
#include <direct.h> 
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <ctime>
#include <complex>
#include <queue>
#include <set>
#include <map>
#include <cassert>
#include <sstream>
#include <random>

using namespace std;

typedef long long  LL;
typedef vector <bool> VB;
typedef vector <VB> VVB;
typedef vector <int> VI;
typedef vector <VI> VVI;
typedef vector <VVI> VVVI;

typedef vector <LL> VLL;
typedef vector <double> VD;
typedef vector <VD> VVD;
typedef vector <string> VS;
typedef complex <double> CD;
typedef vector <CD> VCD;
typedef pair <int, int> PII;
typedef vector <PII> VPII;
typedef vector <VPII> VVPII;
typedef vector <VVPII> VVVPII;
typedef set <int> SI;
typedef vector <SI> VSI;

extern mt19937 PRNG;//PRNG() ~ [0, 2^64); default: PRNG.seed(5489)
extern const double eps;
extern const double INF;
extern const double eps2;
extern const double INF2;
extern const double PI;
extern const double e;
extern const int BWI;// = sizeof(int) * 8 = 32, bit-width of int, maximum compression rate
extern const int DATA_LEN;
extern char	 data_buff[]; 
extern const int GF_MAX_DEG;//maximum deg for GF(2^deg)
extern int   primPoly[];//primitive polynomial for generating GF(2^deg)


int		sgn(const double &x);//return x < -eps ? -1 : x > eps
int		sgnPN(const double &x);//return x < 0 ? -1 : 1;

bool	randb();//return a random bit
int		randi(int _max);//uniformly pick {0, 1, ..., _max-1}, _max > 0
int 	rand32();//return a 32-bit integer
double	randu();//creat a number x ~ uniform[0, 1)
double	randn();//creat a number x ~ normal(0, 1)

VB	rand_VB(int len);//random bool sequence
VI	rand_VI(int len);//random int32 sequence
VVI rand_VVI(int height, int width);//random int32 matrix

VI a_choose_b(int a, int b);//randomly choose b integers from {0, 1, ..., a-1}
void normalize(VD &A);//normalize a VD

void xorEq(VI &A, const VI &B);//A = A xor B
void xorEq(VB &A, const VB &B);//A = A xor B

int	 Hamming_weight(const VB &A);//#ones in A
int	 count_diff (const VB &A, const VB &B);//#ones in (A xor B)

bool be_digit(char ch);//true for ch ~ {0, 1, ..., 9}
bool be_zeros(const VI &A);//true for A = 0
bool be_zeros(const VB &A);//true for A = 0

VI 	compress(const VB &A, int rate);//compress a VB to VI with given compression rate
VI	compress(const VB &A);//compress VB to VI with maximum compression rate, i.e., BWI
VB	decompress(const VI &A, int len, int rate);//decompress the first len bits under the given compression rate 
VB	decompress(const VI &A, int len);//decompress the first len bits under the maximum compression rate 

bool prefixMatch (const string &str1, const string &str2);//check if a string is another' prefix

int max_value_VVI(const VVI &A);//return max(-INF, A)
VVB transpose (const VVB &A);//transpose a matrix
//CN_adj connect VN_adj, boolMat, baseMat
VVI	CN_adj_to_VN_adj(const VVI &CN_adj);//convert CN_adj to VN_adj
VVI	VN_adj_to_CN_adj(const VVI &VN_adj);//convert VN_adj to CN_adj
VVB	CN_adj_to_boolMat(const VVI &CN_adj);//convert CN_adj to bool matrix
VVI	boolMat_to_CN_adj(const VVB &H);//convert bool matrix to CN_adj
//base matrix has zero matrix (-1) or CPM (one's position in the first row);
//cyclically shift to the right by 1 position
VVI	CN_adj_to_baseMat(const VVI &CN_adj, int liftingSize);//convert CN_adj to base matrix
VVI	baseMat_to_CN_adj(const VVI &BM, int liftingSize);//convert base matrix to CN_adj

#endif
