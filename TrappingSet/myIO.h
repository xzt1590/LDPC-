#ifndef __myIO_h__
#define __myIO_h__

#include "globalFile.h"

void output(const VB  &A, const string &name);
void output(const VI  &A, const string &name);
void output(const VD  &A, const string &name);
void output(const VVB &A, const string &name);
void output(const VVI &A, const string &name);
void output(const VVD &A, const string &name);
void outputClock(const char *clockTitle, clock_t start);
void outputLength(const string &str, int L);
void outputLength(const LL &val, int L);

void writeFile(FILE *fp, const VB  &A);//write A at fp
void writeFile(FILE *fp, const VI  &A);
void writeFile(FILE *fp, const VD  &A);
void writeFile(FILE *fp, const VVB &A);
void writeFile(FILE *fp, const VVI &A);
void writeFile(FILE *fp, const VVD &A);

VB	read_VB (FILE *fp);
VI	read_VI (FILE *fp);
VD	read_VD (FILE *fp);
VVB	read_VVB(FILE *fp, int max_row);//read at most [max_row] rows
VVI	read_VVI(FILE *fp, int max_row);
VVD	read_VVD(FILE *fp, int max_row);
VVB	read_VVB(const char *fileName);
VVI	read_VVI(const char *fileName);
VVD	read_VVD(const char *fileName);

//write VVB PCM into file; first row is "format: boolMat"
void write_PCM (const VVB &H, const char *fileName);
//write VVI PCM into file; first row is "format: XX",
//where XX = "CN_adj" or "VN_adj" is the form of adj
void write_PCM (const VVI &adj, const char *fileName, const char *format);
//write base matrix into file; first row is "liftingSize: XX"
void write_PCM (const VVI &BM, int liftingSize, const char *fileName);
//write CN_adj into file; first row is "format: CN_adj"; then: m, n, k
void write_PCM (int m, int n, int k, const VVI &CN_adj, const char *fileName);

//return CN_adj
VVI  read_CN_adj(const char *fileName);
//return true/false: read all parameters successfully/unsuccessfully
bool read_CN_adj (int &m, int &n, int &k, VVI &CN_adj, const char *fileName);

//output degree distribution of PCM (CN_adj)
void output_PCM_degree(const VVI &CN_adj);

//true for existing file
bool	fileExist (const char *fileName);
//make a copy of a file
void	makeCopy (const char *fileName);
//return the smallest positive number satisfying "prefix (num).txt" doesn't exist
int		creatNewFileNum (const char *prefix);
//return the last number in a file's name, such as the "10" in log_01_xx (10).txt
int		getFileNum (const char *fileName);
//creat a new file named "prefix (num).txt"
string	creatNewFile (const char *prefix, int num);
//creat a new file named "prefix (num).txt"
string 	creatNewFile (const char *prefix);

#endif
