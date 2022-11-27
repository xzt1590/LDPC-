#include "globalFile.h"

mt19937 PRNG;//PRNG() ~ [0, 2^64); default: PRNG.seed(5489)
const double eps = 1e-9;
const double INF = 1 / eps;
const double eps2 = 1e-50;
const double INF2 = 1 / eps2;
const double PI = 3.141592653589793;
const double e = 2.71828182845904523536;
const int BWI = sizeof(int) * 8;
const int DATA_LEN = 500000;
char  data_buff[DATA_LEN]; 

const int GF_MAX_DEG = 24;
int primPoly[GF_MAX_DEG + 1] = {//i-th bit is an coefficient of x^i
	1, 3, 7, 11, 19, 
	37, 67, 131, 285, 
	529, 1033, 2053, 4249, 
	8219, 22531, 32771, 65581,
	131081, 262273, 524387, 1048585,
	2097157, 4194307, 8388641, 16777243
};

int	sgn(const double &x){
	return	x < -eps ? -1 : x > eps;
}

int	sgnPN(const double &x){
	return	x < 0 ? -1 : 1;
}

bool randb(){//return a random bit
	return	PRNG() & 1;
}

int randi(int _max){//uniformly pick {0, 1, ..., _max-1}, _max <= (1<<30)
	assert (_max > 0);
	return	PRNG() % _max;
}

int rand32(){//return a 32-bit integer
	return	PRNG();	
} 

double randu(){//creat a number x ~ uniform[0, 1)	
	static	uniform_real_distribution <double> uni_dist(0.0,1.0);
	return	uni_dist(PRNG);
}

double randn(){//creat a number x ~ normal(0, 1)	
	static	normal_distribution <double> nor_dist(0.0,1.0);
	return	nor_dist(PRNG);
}

VB	rand_VB(int len){
	VB	res(len);
	for (int i = 0; i < len; ++ i){
		res[i] = randb();
	}
	return	res;
}

VI	rand_VI(int len){
	VI	res(len);
	for (int i = 0; i < len; ++ i){
		res[i] = rand32();
	}
	return	res;
}

VVI rand_VVI(int height, int width){
	VVI	res(height, VI(width));
	for (int i = 0; i < height; ++ i){
		for (int j = 0; j < width; ++ j){
			res[i][j] = rand32();
		}
	}
	return	res;
}

VI a_choose_b(int a, int b){
	static VI perm;//permutation of {0, 1, ..., perm.size() - 1}
	if (perm.size() < a){
		int pre_size = perm.size();
		perm.resize(a);
		for (int i = pre_size; i < a; ++ i){
			perm[i] = i;
		}
	}
	
	//perm is 0, 1, ...
	for (int i = 0; i < b; ++ i){
		swap(perm[i], perm[i + randi(a - i)]);
	}
	VI	res = VI(perm.begin(), perm.begin() + b);
	
	//recover perm to be 0, 1, ...
	for (int i = 0; i < b; ++ i){
		while(perm[i] != i){
			swap(perm[i], perm[perm[i]]);
		}
	}
	
	return	res;
}

//normalize a VD
void normalize(VD &A){
	double sum = 0;
	for (int i = 0; i < A.size(); ++ i){
		sum += A[i];
	}
	assert(sgn(sum) > 0);
	for (int i = 0; i < A.size(); ++ i){
		A[i] /= sum;
	}
}

//If B is shorter than A, regarding B has a zero tail
void xorEq(VI &A, const VI &B){
	assert(A.size() >= B.size());
	for (int i = 0; i < B.size(); ++ i){
		A[i] ^= B[i];
	}
}

//If B is shorter than A, regarding B has a zero tail
void xorEq(VB &A, const VB &B){
	assert(A.size() >= B.size());
	for (int i = 0; i < B.size(); ++ i){
		A[i] = A[i] != B[i];
	}
}

int Hamming_weight(const VB &A){
	int res = 0;
	for (int i = 0; i < A.size(); ++ i){
		res += A[i];
	}
	return	res;
}

int count_diff (const VB &A, const VB &B){
	assert (A.size() == B.size());
	int sum = 0;
	for (int i = 0; i < A.size(); ++ i){
		sum += A[i] != B[i];	
	}	
	return	sum;
}

bool be_digit(char ch){
	return	ch >= '0' && ch <= '9';
}

bool be_zeros(const VI &A){
	for (int i = 0; i < A.size(); ++ i){
		if (A[i] != 0){
			return	false;
		}
	}
	return	true;
}

bool be_zeros(const VB &A){
	for (int i = 0; i < A.size(); ++ i){
		if (A[i]){
			return	false;
		}
	}
	return	true;
}

VI compress(const VB &A, int rate){
	assert(rate > 0 && rate <= BWI);
	VI res((A.size() + rate - 1) / rate, 0);
	for (int i = 0; i < A.size(); ++ i){
		if (A[i] == true){
			res[i / rate] |= (1 << i % rate);
		}
	}
	return	res;
}

VI compress(const VB &A){
	return	compress(A, BWI);
} 

VB decompress(const VI &A, int len, int rate){
	assert(rate > 0 && rate <= BWI);
	assert(len > 0 && (len - 1) / rate < A.size());
	VB res(len);
	for (int i = 0; i < len; ++ i){
		res[i] = (A[i / rate] >> i % rate) & 1;
	}
	return	res;
}

VB decompress(const VI &A, int len){
	return	decompress(A, len, BWI);
}

//check if a string is another' prefix
bool prefixMatch (const string &str1, const string &str2){
	for (int i = 0; i < str1.size() && i < str2.size(); ++ i)
		if (str1[i] != str2[i])
			return	false;
	return	true;
}

int max_value_VVI(const VVI &A){
	int res = -INF;
	for (int i = 0; i < A.size(); ++ i){
		for (int j = 0; j < A[i].size(); ++ j){
			res = max(res, A[i][j]);
		}
	}
	return	res;
}

//transpose a matrix
VVB transpose (const VVB &A){
	VVB res (A[0].size(), VB (A.size()));
	for (int i = 0; i < A.size(); ++ i){
		assert(A[i].size() == A[0].size());
		for (int j = 0; j < A[0].size(); ++ j){
			res[j][i] = A[i][j];
		}
	}
	return	res;	
}

VVI	CN_adj_to_VN_adj(const VVI &CN_adj){
	VVI res(max_value_VVI(CN_adj) + 1);
	for (int i = 0; i < CN_adj.size(); ++ i){
		for (int j = 0; j < CN_adj[i].size(); ++ j){
			res[CN_adj[i][j]].push_back(i);
		}
	}
	return	res;
}

VVI	VN_adj_to_CN_adj(const VVI &VN_adj){
	VVI res(max_value_VVI(VN_adj) + 1);
	for (int i = 0; i < VN_adj.size(); ++ i){
		for (int j = 0; j < VN_adj[i].size(); ++ j){
			res[VN_adj[i][j]].push_back(i);
		}
	}
	return	res;
}

VVB	CN_adj_to_boolMat(const VVI &CN_adj){
	VVB res(CN_adj.size(), VB(max_value_VVI(CN_adj) + 1, false));
	for (int i = 0; i < CN_adj.size(); ++ i){
		for (int j = 0; j < CN_adj[i].size(); ++ j){
			res[i][CN_adj[i][j]] = true;
		}
	}
	return	res;
}

VVI	boolMat_to_CN_adj(const VVB &H){
	VVI res(H.size());
	for (int i = 0; i < H.size(); ++ i){
		for (int j = 0; j < H[i].size(); ++ j){
			if (H[i][j]){
				res[i].push_back(j);
			}
		}
	}
	return	res;
}

VVI	CN_adj_to_baseMat(const VVI &CN_adj, int liftingSize){
	int Z = liftingSize;
	assert(CN_adj.size() % Z == 0 && (max_value_VVI(CN_adj) + 1) % Z == 0);
	VVI res(CN_adj.size() / Z, VI((max_value_VVI(CN_adj) + 1) / Z, -1));
	for (int i = 0; i < CN_adj.size(); i += Z){
		for (int t = 0; t < Z; ++ t){
			assert(CN_adj[i + t].size() == CN_adj[i].size());
			for (int j = 0; j < CN_adj[i].size(); ++ j){
				if (t == 0){
					assert(res[i / Z][CN_adj[i][j] / Z] == -1);
					res[i / Z][CN_adj[i][j] / Z] = CN_adj[i][j] % Z;
				}
				else{
					assert(CN_adj[i + t][j] % Z == (CN_adj[i][j] + t) % Z);
				}
			}
		}
	}
	return	res;
}

VVI	baseMat_to_CN_adj(const VVI &BM, int liftingSize){
	int Z = liftingSize;
	VVI res(BM.size() * Z);
	for (int i = 0; i < BM.size(); ++ i){
		for (int j = 0; j < BM[i].size(); ++ j){
			if (BM[i][j] >= 0 && BM[i][j] < Z){
				for (int t = 0; t < Z; ++ t){
					res[i * Z + t].push_back(j * Z + (BM[i][j] + t) % Z);
				}
			}
			else{
				assert(BM[i][j] == -1);
			}
		}
	}
	return	res;
}
