#include "globalFile.h"
#include "myIO.h"
#include "LETS.h"

int	m;//#CNs
int	n;//#VNs
int k;//#information bits; last k bits; code rate = k/n
VVI	CN_adj;//neighbors of CNs
VVI	VN_adj;//neighbors of VNs
VVSSI LETS(15,VSSI(10));
VVB dot(13,VB(7));
VVVI path(13,VVI(7,VI(2)));
VVVPII lo(13,VVPII(7,VPII(2))); 

int main(){	
	CN_adj = read_CN_adj("H.txt");
	m = CN_adj.size();
	n = max_value_VVI(CN_adj) + 1;
	
//dot特征表 
//	dot[4][4] = 1;
//	dot[5][3] = 1;
//	dot[6][2] = 1;
//	dot[6][4] = 1;
//	dot[7][3] = 1;
//	dot[7][5] = 1;
//	dot[8][2] = 1;
//	dot[8][4] = 1;
//	dot[8][6] = 1;
//	dot[9][3] = 1;
//	dot[9][5] = 1;
//	dot[10][2] = 1;
//	dot[10][4] = 1;
//	dot[10][6] = 1;
//	dot[11][3] = 1;
//	dot[11][5] = 1;
//	for (int i = 0; i < dot.size(); ++ i){
//		for (int j = 0; j <dot[i].size(); ++ j){
//			if (dot[i][j] != 1){
//				dot[i][j] = 0;
//			} 
//		}
//	}
	
//path特征表
//	for (int i = 0; i < path.size(); ++ i){
//		for (int j = 0; j < path[i].size(); ++ j){
//			for (int t = 0; t < path[i][j].size(); ++ t){				
//				path[i][j][t] = 0;
//			}			
//		}
//	}
//	path[4][4][0] = 2;
//	path[4][4][1] = 3;
//	path[5][3][0] = 4;
//	path[5][5][0] = 2;
//	path[6][2][0] = 3;
//	path[6][2][1] = 4;
//	path[6][4][0] = 2;
//	path[6][4][1] = 3;
//	path[6][6][0] = 2;
//	path[7][3][0] = 4;
//	path[7][5][0] = 2;
//	path[7][5][1] = 3;
//	path[8][2][0] = 3;
//	path[8][2][1] = 4;
//	path[8][4][0] = 2;
//	path[8][6][0] = 2;
//	path[9][3][0] = 3;
//	path[9][5][0] = 2;
//	path[10][4][0] = 2;
//	for (int i = 0; i < path.size(); ++ i){
//		for (int j = 0; j < path[i].size(); ++ j){
//			for (int t = 0; t < path[i][j].size(); ++ t){				
//				cout<<path[i][j][t]<<" ";
//			}	
//			cout<<"	";		
//		}
//		cout<<endl;
//	}

//lollipop扩展
//	for (int i = 0; i < lo.size(); ++ i){
//		for (int j = 0; j < lo[i].size(); ++ j){
//			for (int t = 0; t < lo[i][j].size(); ++ t){				
//				lo[i][j][t].first = 0;
//				lo[i][j][t].second = 0;
//			}			
//		}
//	}
//	lo[5][3][0].first = 4;
//	lo[5][3][0].second = 4;
//	lo[5][3][1].first = 5;
//	lo[5][3][1].second = 4;
//	lo[6][4][0].first = 4;
//	lo[6][4][0].second = 4;
//	lo[6][1][0].first = 5;
//	lo[6][1][0].second = 4;
//	lo[6][1][1].first = 5;
//	lo[6][1][1].second = 5;
//	lo[8][2][0].first = 4;
//	lo[8][2][0].second = 4;
	
	
	find_LETS(8,6);

	return 0;	
}


