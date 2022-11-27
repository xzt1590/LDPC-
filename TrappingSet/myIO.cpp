#include "myIO.h"


void output(const VB &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i){
		cout << A[i] << " ";
	}
	cout << endl << endl;
}

void output(const VI &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i){
		cout << A[i] << " ";
	}
	cout << endl << endl;
}


void output(const VD &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i){
		cout << A[i] << " ";
	}
	cout << endl << endl;
}



void output(const VVB &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i, cout << endl){
		for (int j = 0; j < A[i].size(); ++ j){
			cout << A[i][j] << " ";
		}
	}
	cout << endl << endl;
}

void output(const VVI &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i, cout << endl){
		for (int j = 0; j < A[i].size(); ++ j){
			cout << A[i][j] << " ";
		}
	}
	cout << endl << endl;
}


void output(const VVD &A, const string &name){
	cout << name << endl;
	for (int i = 0; i < A.size(); ++ i, cout << endl){
		for (int j = 0; j < A[i].size(); ++ j){
			cout << A[i][j] << " ";
		}
	}
	cout << endl << endl;
}

void outputClock(const char *clockTitle, clock_t start)
{
	double DIV = CLOCKS_PER_SEC;
	printf ("\n%s:  %f s (%f h)\n", clockTitle, (clock() - start) / DIV, (clock() - start) / DIV / 3600);
}

void outputLength(const string &str, int L)
{
	cout << str;
	for (int i = str.size(); i <= L; ++ i){
		putchar(' ');
	}
	putchar('\t');
}

void outputLength(const LL &val, int L)
{
	sprintf(data_buff, "%lld", val);
	outputLength(data_buff, L);
}

void writeFile(FILE *fp, const VB  &A){
	for (int i = 0; i < A.size(); ++ i){
		fprintf(fp, "%d ", A[i]);
	}
	fprintf(fp, ";\n\n");
}

void writeFile(FILE *fp, const VI  &A){
	for (int i = 0; i < A.size(); ++ i){
		fprintf(fp, "%d ", A[i]);
	}
	fprintf(fp, ";\n\n");
}

void writeFile(FILE *fp, const VD  &A){
	for (int i = 0; i < A.size(); ++ i){
		fprintf(fp, "%f ", A[i]);
	}
	fprintf(fp, ";\n\n");
}

void writeFile(FILE *fp, const VVB &A){
	for (int i = 0; i < A.size(); ++ i){
		for (int j = 0; j < A[i].size(); ++ j){
			fprintf(fp, "%d ", A[i][j]);
		}
		fprintf(fp, ";\n");
	}
	fprintf(fp, "\n");
}

void writeFile(FILE *fp, const VVI &A){
	for (int i = 0; i < A.size(); ++ i){
		for (int j = 0; j < A[i].size(); ++ j){
			fprintf(fp, "%d ", A[i][j]);
		}
		fprintf(fp, ";\n");
	}
	fprintf(fp, "\n");
}

void writeFile(FILE *fp, const VVD &A){
	for (int i = 0; i < A.size(); ++ i){
		for (int j = 0; j < A[i].size(); ++ j){
			fprintf(fp, "%f ", A[i][j]);
		}
		fprintf(fp, ";\n");
	}
	fprintf(fp, "\n");
}

bool first_be_number(char str[]){
	for (int i = 0; str[i] != '\0'; ++ i){
		if (str[i] != '\t' && str[i] != ' '){
			return	be_digit(str[i]) || (be_digit(str[i+1]) &&\
					(str[i] == '-' || str[i] == '+' || str[i] == '.'));
		}
	}
	return	false;
}

VB read_VB(FILE *fp){
	VB res;
	bool tmp; 
	while(fgets(data_buff, DATA_LEN, fp) != NULL){
		if (!first_be_number(data_buff)){
			continue;
		}
		
		int L = strlen(data_buff);
		while (-- L >= 0 && !be_digit(data_buff[L]));//remove the non-digits at the tail 
		data_buff[++ L] = '\0';
		
		if (L == 0)	continue;
		
		istringstream iss(data_buff);
		while (iss >> tmp){
			res.push_back(tmp);
		}
		break;
	}
	return	res;
}

VI read_VI(FILE *fp){
	VI res;
	int tmp; 
	while(fgets(data_buff, DATA_LEN, fp) != NULL){
		if (!first_be_number(data_buff)){
			continue;
		}
		
		int L = strlen(data_buff);
		while (-- L >= 0 && !be_digit(data_buff[L]));//remove the non-digits at the tail 
		data_buff[++ L] = '\0';
		
		if (L == 0)	continue;
		
		istringstream iss(data_buff);
		while (iss >> tmp){
			res.push_back(tmp);
		}
		break;
	}
	return	res;
}

//read the VD in the current row 
VD read_VD(FILE *fp){
	VD res;
	double tmp; 
	while(fgets(data_buff, DATA_LEN, fp) != NULL){
		if (!first_be_number(data_buff)){
			continue;
		}
		
		int L = strlen(data_buff);
		while (-- L >= 0 && !be_digit(data_buff[L]));//remove the non-digits at the tail 
		data_buff[++ L] = '\0';
		
		if (L == 0)	continue;
		
		istringstream iss(data_buff);
		while (iss >> tmp){
			res.push_back(tmp);
		}
		break;
	}
	return	res;
}

VVB read_VVB(FILE *fp, int max_row){
	VVB res;
	for (int i = 0; i < max_row; ++ i){
		VB tmp = read_VB(fp);
		if (tmp.empty()){
			break;
		}
		else{
			res.push_back(tmp);
		}
	}
	return	res;
}

VVI read_VVI(FILE *fp, int max_row){
	VVI res;
	for (int i = 0; i < max_row; ++ i){
		VI tmp = read_VI(fp);
		if (tmp.empty()){
			break;
		}
		else{
			res.push_back(tmp);
		}
	}
	return	res;
}

VVD read_VVD(FILE *fp, int max_row){
	VVD res;
	for (int i = 0; i < max_row; ++ i){
		VD tmp = read_VD(fp);
		if (tmp.empty()){
			break;
		}
		else{
			res.push_back(tmp);
		}
	}
	return	res;
}

VVB	read_VVB(const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<read_VVB>: fail to open " << fileName << "." << "\n";
		assert(false);	
	}
	return	read_VVB(fp, INF);
}

VVI	read_VVI(const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<read_VVI>: fail to open " << fileName << "." << "\n";
		assert(false);	
	}
	return	read_VVI(fp, INF);
}

VVD	read_VVD(const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<read_VVD>: fail to open " << fileName << "." << "\n";
		assert(false);	
	}
	return	read_VVD(fp, INF);
}

void write_PCM (const VVB &H, const char *fileName){
	FILE *fp = fopen (fileName, "w");
	fprintf (fp, "format:\tboolMat\n\n");
	writeFile(fp, H);
	fclose (fp);
}

void write_PCM (const VVI &BM, int liftingSize, const char *fileName){
	FILE *fp = fopen (fileName, "w");
	fprintf (fp, "liftingSize:\t%d\n\n", liftingSize);
	writeFile(fp, BM);
	fclose (fp);
}

void write_PCM (const VVI &adj, const char *fileName, const char *format){
	if (strcmp(format, "CN_adj") != 0 && strcmp(format, "VN_adj") != 0){
		cerr << "<write_PCM>: format must be CN_adj or VN_adj." << endl;
		assert(false);
	}
	
	FILE *fp = fopen (fileName, "w");
	fprintf (fp, "format:\t%s\n\n", format);
	writeFile(fp, adj);
	fclose (fp);
}

void write_PCM (int m, int n, int k, const VVI &CN_adj, const char *fileName){
	FILE *fp = fopen (fileName, "w");
	fprintf (fp, "format:\tCN_adj\n\n");
	
	fprintf (fp, "m:\t%d\n", m);
	fprintf (fp, "n:\t%d\n", n);
	fprintf (fp, "k:\t%d\n\n", k);
	
	writeFile(fp, CN_adj);
	fclose (fp);
}

VVI read_CN_adj (const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<read_CN_adj>: fail to open " << fileName << "." << "\n";
		assert(false);	
	}
	
	char format[20] = "boolMat";//default
	int liftingSize = -1;
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "format:") == 0){
		fscanf(fp, "%s", format);
	}
	else if (strcmp(data_buff, "liftingSize:") == 0){
		fscanf(fp, "%d", &liftingSize);
	}
	fclose(fp);
	
	if (liftingSize > 0){
		return	baseMat_to_CN_adj(read_VVI(fileName), liftingSize);
	}
	else if (strcmp(format, "boolMat") == 0){
		return	boolMat_to_CN_adj(read_VVB(fileName));
	}
	else if (strcmp(format, "CN_adj") == 0){
		return	read_VVI(fileName);
	}
	else if (strcmp(format, "VN_adj") == 0){
		return	VN_adj_to_CN_adj(read_VVI(fileName));
	}
	else{
		cerr << "<read_CN_adj>: data format in " << fileName << " is incorrect." << "\n";
		assert (false);
	}
}

bool read_CN_adj (int &m, int &n, int &k, VVI &CN_adj, const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<read_CN_adj>: fail to open " << fileName << "." << "\n";
		assert(false);	
	}
	
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "format:") != 0){
		fclose(fp);
		return	false;
	}
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "CN_adj") != 0){
		fclose(fp);
		return	false;
	}
	
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "m:") != 0){
		fclose(fp);
		return	false;
	}
	fscanf(fp, "%d", &m);
	
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "n:") != 0){
		fclose(fp);
		return	false;
	}
	fscanf(fp, "%d", &n);
	
	fscanf(fp, "%s", data_buff);
	if (strcmp(data_buff, "k:") != 0){
		fclose(fp);
		return	false;
	}
	fscanf(fp, "%d", &k);
	
	CN_adj = read_VVI(fp, INF);
	fclose(fp);
	if (CN_adj.size() != m || max_value_VVI(CN_adj) + 1 != n ||\
		n <= 0 || k <= 0 || k + m < n){
		return	false;
	}
	
	return	true;
}

void output_PCM_degree(const VVI &CN_adj){
	VI degCN(CN_adj.size(), 0);
	VI degVN(max_value_VVI(CN_adj) + 1, 0);
	int sum = 0;
	for (int i = 0; i < CN_adj.size(); ++ i){
		degCN[i] = CN_adj[i].size();
		sum += degCN[i];
		for (int j = 0; j < CN_adj[i].size(); ++ j){
			++ degVN[CN_adj[i][j]];
		}
	}
	
	VI cnt(max(degCN.size(), degVN.size()) + 1, 0);
	for (int i = 0; i < degCN.size(); ++ i){
		++ cnt[degCN[i]];
	}
	assert(cnt[0] == 0);
	cerr << "CN degree distribution" << endl;
	cerr << "m = " << degCN.size() << endl;
	cerr << "deg\t#CN\tfraction_node\tfraction_edge" << endl;
	for (int d = 1; d < cnt.size(); ++ d){
		if (cnt[d] > 0){
			cerr << d << "\t" << cnt[d] << "\t" << 1.0*cnt[d]/degCN.size() \
			<< "\t\t" << 1.0*cnt[d]*d/sum << endl;
		}
	}
	
	fill(cnt.begin(), cnt.end(), 0);
	for (int i = 0; i < degVN.size(); ++ i){
		++ cnt[degVN[i]];
	}
	assert(cnt[0] == 0);
	cerr << endl << "VN degree distribution" << endl;
	cerr << "n = " << degVN.size() << endl;
	cerr << "deg\t#VN\tfraction_node\tfraction_edge" << endl;
	for (int d = 1; d < cnt.size(); ++ d){
		if (cnt[d] > 0){
			cerr << d << "\t" << cnt[d] << "\t" << 1.0*cnt[d]/degVN.size() \
			<< "\t\t" << 1.0*cnt[d]*d/sum << endl;
		}
	}
}

bool	fileExist (const char *fileName){
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL){
		return	false;
	}
	else{
		fclose(fp);
		return	true;
	}
}


void makeCopy (const char *fileName){
	FILE *fin = fopen (fileName, "r");
	if (fin == NULL){
		cerr << "<makeCopy>: fail to open " << fileName << "." << "\n";
		assert (false);	
	}
	
	string copyFile = fileName;
	for (int i = copyFile.size() - 1; ; -- i){
		if (i == -1 || copyFile[i] == '\\'){//in case of having directory
			copyFile.insert(i + 1, "copy_");
			break;
		}
	}
	
	FILE *fout = fopen (copyFile.c_str(), "w");
	int ch = fgetc (fin);
	while (ch != EOF){
		fputc (ch, fout);
		ch = fgetc (fin);
	}
	
	fclose (fin);
	fclose (fout);
}

//return the smallest positive number satisfying "prefix (num).txt" doesn't exist
int creatNewFileNum (const char *prefix){
	for (int num = 1; ; ++ num){
		sprintf (data_buff, "%s (%d).txt", prefix, num);
		if (!fileExist(data_buff)){
			return	num;
		}
	}
}

//return the last number in a file's name, such as the "10" in log_01_xx (10).txt
int getFileNum (const char *fileName){
	int res = 0, p10 = 1;
	int L = strlen(fileName);
	while(-- L >= 0 && fileName[L] != ')');
	while(-- L >= 0 && fileName[L] != '('){
		res += (fileName[L] - '0') * p10;
		p10 *= 10;
	}
	return	res;
}

//creat a new file named "prefix (num).txt"
string creatNewFile (const char *prefix, int num){
	sprintf (data_buff, "%s (%d).txt", prefix, num);
	fclose (fopen (data_buff, "w"));
	return	(string)data_buff;
}

//creat a new file named "prefix (num).txt"
string creatNewFile (const char *prefix){
	return	creatNewFile (prefix, creatNewFileNum (prefix));
}
