#include "LETS.h"

VVI VC_adj;//VN: 0 ~ n-1; CN: n ~ n+m-1

//��� 
SI setXorVec (const SI &st, const VI &vec){
	SI res = st;
	for (int i = 0; i < vec.size(); ++ i){
		if (res.find (vec[i]) != res.end()){//�����res(set)���ҵ�vec[i],�����res�е�vec[i] 
			res.erase (vec[i]);
		}
		else{								//���û��res(set)�ҵ�vec[i],����res�в���vec[i] 
			res.insert (vec[i]);
		}
	}
	return	res;//res��ֻʣ��vec���е�Ԫ�� 
} 

//�ҳ�set������vector��������ͬ�Ľڵ�
SI SetXnorVec (const SI &st, const VI &vec){
	SI res;
	for (int i = 0; i < vec.size(); ++ i){
		if (st.find (vec[i]) != st.end()){//�����res(set)���ҵ�vec[i],�����res 
			res.insert (vec[i]);
		}
	}
	return	res;
} 

SSI ssinsertss (const SSI &set1, const SSI &set2){
	SSI res(set1);
	for (SSI :: const_iterator it = set2.begin(); it != set2.end(); ++ it){
		res.insert(*it); 
	}
	return res;
} 

//�����弯vn���ҵ���Ϊ1��У��ڵ� 
SI degree1CN (const SI &setVN){
	SI res;
	SI commonCN;
	for (set <int> :: iterator it = setVN.begin(); it != setVN.end(); ++ it){//VC_adj[*it]
		for (int i = 0; i < VC_adj[*it].size(); ++ i){
			if (res.find (VC_adj[*it][i]) != res.end()){//�����res(set)���ҵ�vec[i],�����res�е�vec[i] 
			commonCN.insert (VC_adj[*it][i]);
			}
		else{								//���û��res(set)�ҵ�vec[i],����res�в���vec[i] 
			res.insert (VC_adj[*it][i]);
			}
		}
	}
	for (set <int> :: iterator it = commonCN.begin(); it != commonCN.end(); ++ it){
		res.erase(*it) ;
	}
	return	res;//res��ֻʣ��vec���е�Ԫ�� 
}

//�����弯vn���ҵ��ȴ���2��У��ڵ�
SI greater_than2CN (const SI &setVN){
	SI res;
	SI commonCN;
	for (set <int> :: iterator it = setVN.begin(); it != setVN.end(); ++ it){//VC_adj[*it]
		for (int i = 0; i < VC_adj[*it].size(); ++ i){
			if (res.find (VC_adj[*it][i]) != res.end()){//�����res(set)���ҵ�vec[i],�����commonCN 
			commonCN.insert (VC_adj[*it][i]);
			}
			res.insert(VC_adj[*it][i]);
		}
	}
	return commonCN; 
} 
 
//ͨ���ҵ������ڵ��ҵ����е�У��ڵ�
SI Findall_CN (const SI &setVN){
	SI res;
	for (set <int> :: iterator it = setVN.begin(); it != setVN.end(); ++ it){
		for (int i = 0; i < VC_adj[*it].size(); ++ i){
			res.insert(VC_adj[*it][i]); 
		}
	}
	return res;
} 

//find unsatisfied CNs of TS vn�����弯vn���ҵ��������У��ڵ� 
SI unsatCN (const SI &setVN){
	SI res;
	for (set <int> :: iterator it = setVN.begin(); it != setVN.end(); ++ it){
		res = setXorVec (res, VC_adj[*it]);//VC_adj�е�Ԫ����һ��res����xor 
	}
	return	res;//res��ֻʣ��VC_adj�ж��е�Ԫ�� 
}

//�ҵ������У��ڵ�
SI satisfiedCN (const SI &setVN){
	SI res= Findall_CN(setVN);
	SI unsaCN = unsatCN(setVN);
	for (set <int> :: iterator it = unsaCN.begin(); it != unsaCN.end(); ++ it){
		res.erase(*it); 
	}
	return res;
} 

//�ҵ���u��root����̵�·�� 
void dfsAllPaths (int depth, int u, const VVI &pre, VI &path, VVI &allPaths){
	path[depth] = u;
	
	if (depth == 0){
		allPaths.push_back(path);
		return;
	}
	
	for (int i = 0; i < pre[u].size(); ++ i){
		dfsAllPaths (depth - 1, pre[u][i], pre, path, allPaths);
	}
}

void prints (SI &res){//��ӡset���� 
	for (set<int> ::iterator it = res.begin(); it != res.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;
}

void printss (SSI &res){
	for (SSI :: iterator it = res.begin(); it != res.end(); ++it){
		for (SI :: iterator sit = (*it).begin(); sit != (*it).end(); ++sit){
			cout<<*sit<<" ";
		}
		cout<<endl;
	}
}

//�ҵ�LDPC���е�simple cycle
SSI bfsSimpleCycles (int dv, int g){
	int scy_num = 0;
	SSI res;
	VVI pre (VC_adj.size());
	VI  dist (VC_adj.size(),2);
	int startNode = n;
	for (int root = startNode; root < VC_adj.size(); ++ root){
		for (int i = 0; i < VC_adj.size(); ++ i){
			pre[i].clear();
			dist[i] = INF;
		}
		dist[root] = 0;
		queue <int> que;
		que.push(root); //��root�Ž�����que 
		
		while (!que.empty()){//��ǰ���ʽڵ�Ϊu 
			int u = que.front();
			que.pop();
			
			for (int i = 0; i < VC_adj[u].size(); ++ i){//u����һ���ڵ�Ϊv 
				int v = VC_adj[u][i];
				
				if (v < root){
					if (dist[v] > dist[u] + 1){//��v�ڵ�δ�����ʹ���������� 
						dist[v] = dist[u] + 1;
						if (dist[v] < g+1)	que.push(v);
					}
					
					if (dist[v] == dist[u] + 1){//��v�ڵ���ʽ�������u����Ϊv��ǰһ�ڵ� 
						pre[v].push_back (u);
					}
				}
			}
		}
		
		for (int u = 0; u < root; ++ u){
			if (pre[u].size() < 2)	continue;//��u�Ķ�С��2������ѭ�� 
			
			int	d = dist[u];
			VI	path (d + 1);//����Ԫ��path��Ԫ�ظ���Ϊu�ڵ�����1
			VVI	allPaths;//����u��root������·�� 
			dfsAllPaths (d, u, pre, path, allPaths);
			
			for (int i = 0; i < allPaths.size(); ++ i){
				for (int j = 0; j < i; ++ j){
					int num = 0;
					for (int k = 1; k < d; k++){
						if (allPaths[i][k] == allPaths[j][k]){
							num = 1;
						}
					}
					if (num == 0){
						SI setVN;
						for (int l = (allPaths[i][0] >= n); l <= d; l += 2){
							setVN.insert(allPaths[i][l]);
							setVN.insert(allPaths[j][l]);
						}
					
						SI unscn;
						unscn = degree1CN(setVN);

						if (unscn.size() == setVN.size()*(dv-2) && setVN.size() == g){
							res.insert (setVN);
						}
					}	
				}
			}	
		}
	}
//	for (set<set<int> > ::iterator it = res.begin(); it != res.end(); it++){
//			for (set<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++){
//			cout << *vit <<" ";
//			}
//			cout<< endl;
//		}
//		scy_num = res.size() ;
//		cout<<"������ĿΪ�� "<<scy_num<<endl;
		return res;

} 
 
void DotExpand (int dv, const SSI &origTS){
	for (SSI :: iterator all = origTS.begin(); all != origTS.end(); ++ all){
		SI setVN(*all);//ԭtannerͼ�����ڵ�
		SI setVN2;//�ܹ���չ�ı����ڵ� 
		SI setVN3;//���������ı����ڵ� 
		SI setVNtoCN;//��������У��ڵ����������б����ڵ� 
		SI setCN1 = degree1CN (*all);//��Ϊ1У��ڵ� 
		SI setCN2 = satisfiedCN(setVN);//ż����У��ڵ�
		int b2 = setCN2.size(); 	
		int b1 = setCN1.size();
		
		for (SI :: iterator it = setCN1.begin(); it != setCN1.end(); ++ it){//�ҳ�������������������У��ڵ�ı����ڵ�  
			SI setVN4 = SetXnorVec(setVNtoCN,VC_adj[*it]);//
				for (SI :: iterator sit = setVN4.begin(); sit != setVN4.end(); ++ sit){
					setVN2.insert(*sit); 
				}
				for (int i = 0; i < VC_adj[*it].size(); ++i){
				setVNtoCN.insert(VC_adj[*it][i]); 	
				}
		}
		
		for (SI :: iterator it = setVN2.begin(); it != setVN2.end(); ++ it){//�ų�����ż����У��ڵ�ı����ڵ㣬���������ı����ڵ����setVN3�� 
			int num = 0; 
				for (int i = 0; i < VC_adj[*it].size(); ++i){
					if (setCN2.find(VC_adj[*it][i]) != setCN2.end()){
					 num++;
					}
				}
				if (num == 0){
				setVN3.insert(*it);								
				}	
		}
		
		for  (SI :: iterator it = setVN3.begin(); it != setVN3.end(); ++ it){//���γɵ�ͼ�����res�� 
			SI newsetVN(setVN);
			newsetVN.insert(*it); 
			SI newsetCN = degree1CN(newsetVN);
			SI newsetCN2 = satisfiedCN(newsetVN);
			int da = newsetVN.size();
			int db = newsetCN.size();
			LETS[da][db].insert(newsetVN); 
			}
		}
	} 	
 
void PathExpand (int p, int dv, const SSI &origTS){
	for (SSI :: iterator all = origTS.begin(); all != origTS.end(); ++ all){
		VVVI satPath(VC_adj.size());//����Ϊp�ĵ㹹�ɵ�·�� 
		VVI pre (VC_adj.size());//ǰһ�ڵ� 
		VI  dist (VC_adj.size(),2);//���� 
		SI unsat_CN = degree1CN(*all);//ԭLETS������У��ڵ� 
		SI sat_CN = satisfiedCN(*all);
		int b2 = sat_CN.size(); 
		int a1 = (*all).size(); //ԭLETS�Ĵ�С
	
		for (SI :: iterator it = unsat_CN.begin(); it != unsat_CN.end(); ++it){//��һ��������������У��ڵ� 
			for (int i = 0; i < VC_adj.size(); ++ i){
				pre[i].clear();
				dist[i] = INF;
			}
			SI expansileNode;
			dist[*it] = 0;
			queue <int> que;
			que.push(*it); //�����ڵ�Ž�����que 
			
			while (!que.empty()){//��ǰ���ʽڵ�Ϊu 
				int u = que.front();
				if (dist[u] == p){
					expansileNode.insert(u); 
				} 
				que.pop();
				
				for (int i = 0; i < VC_adj[u].size(); ++ i){//u����һ���ڵ�Ϊv 
					int v = VC_adj[u][i];
					
						if (dist[v] > dist[u] + 1){//��v�ڵ�δ�����ʹ���������� 
							dist[v] = dist[u] + 1;
							if (dist[v] <= p)	que.push(v);
						}
						
						if (dist[v] == dist[u] + 1){//��v�ڵ���ʽ�������u����Ϊv��ǰһ�ڵ� 
							pre[v].push_back(u);
						}
						
				}
			}
	
			for (SI :: iterator sit = expansileNode.begin(); sit != expansileNode.end(); ++sit){
				int u = *sit;
//				int	d = dist[u];
				VI	path (p + 1);//����Ԫ��path��Ԫ�ظ���Ϊu�ڵ�����1
				VVI	allPaths;//����u��root������·�� 
				dfsAllPaths (p, u, pre, path, allPaths);
	
				for (int i = 0; i < allPaths.size(); ++ i){					
					satPath[u].push_back(allPaths[i]); 
				}				
			}	
		}
		
		for (int u = 0; u <satPath.size(); u++){//satPath[u].
//		cout<<"u="<<u<<endl;
//		output(satPath[u],"nnnn");
			if (satPath[u].size() >= 2){//����С��2��ֱ������ 
				for (int i = 1; i < satPath[u].size(); ++i){//�����Ƚ�������ͬ�����е�Ԫ�� 
					for (int j = 0; j < i; ++j){
						int temp1 = 0;
//						SI paVN1;
//						SI paVN2;
//						for (int l = 1; l < p; l += 2){
//							paVN1.insert(satPath[u][i][l]);
//							paVN2.insert(satPath[u][j][l]);
//						}
//						SI paCN1 = Findall_CN(paVN1);
//						SI paCN2 = Findall_CN(paVN2);
//						paCN1.erase(satPath[u][i][p]);
//
//						
//						for (SI :: iterator sit2 = paCN1.begin(); sit2 != paCN1.end(); ++sit2){
//							if (paCN2.find(*sit2) != paCN2.end() ){
//								++temp1;
//							}
//						}
//						
						for (int k1 = 0; k1 < p; ++k1){//��p+1���ڵ㣬�������һ���ڵ��������ͬ 
							for (int k2 = 0; k2 < p; ++ k2){
								if (satPath[u][i][k1] == satPath[u][j][k2]){
								++temp1;
								}
							}
						}
						 
						SI setVN;
						if (temp1 == 0){//��·���޽��� ����setVN 
							for (int l = 1; l <= p; l += 2){
								setVN.insert(satPath[u][i][l]);
								setVN.insert(satPath[u][j][l]);
							}	
							
							int temp2 = 0;//�ж�path�е�У��ڵ��Ƿ���ԭͼ�� 
							SI newsetCN2 = satisfiedCN(*all);
							SI allsetCN1 = Findall_CN(*all);
							SI allsetCN2 = Findall_CN(setVN);
							allsetCN2.erase(satPath[u][i][0]);
							allsetCN2.erase(satPath[u][j][0]);
							for (SI :: iterator sit2 = allsetCN1.begin(); sit2 != allsetCN1.end(); ++sit2){
								if (allsetCN2.find(*sit2) != allsetCN2.end() ){
									++temp2;
								}
							}
							if (temp2 == 0){
								SI newsetVN(*all);
								for  (SI :: iterator sit1 = setVN.begin(); sit1 != setVN.end(); ++ sit1){
									newsetVN.insert(*sit1);  
								}
								SI newsetCN1 = degree1CN(newsetVN);
								SI newsetCN2 = satisfiedCN(newsetVN);
								int da = newsetVN.size();
								int db = newsetCN1.size();
								
								if ((newsetVN.size() == a1 + p)&&(newsetCN1.size() == unsat_CN.size()-2+p*(dv-2))&&(newsetCN2.size() == b2+p+1 )){//�ж϶�Ϊ1��У��ڵ�������Ƿ���ȷ 
									LETS[da][db].insert(newsetVN);
								}

							}
								
						}
						
						
					}
				}	
			}	
		}
	}	
}  
 
void LoExpand (int p, int c, int dv, const SSI &origTS){
	for (SSI :: iterator all = origTS.begin(); all != origTS.end(); ++ all){
		int d = p + 1 - c; 
		int dis = 2*(d-1);
		VVVI satPath(VC_adj.size());//����Ϊdis�ĵ㹹�ɵ�·�� 
		VSSI satCycles(VC_adj.size());//ĳ���ڵ�����Щ���� 
		VVI pre (VC_adj.size());//ǰһ�ڵ� 
		VI  dist (VC_adj.size(),2);//���� 
		SI unsat_CN = degree1CN(*all);//ԭLETS��Ϊ1У��ڵ� 
		int b1 = unsat_CN.size(); //��Ϊ1У��ڵ����� 
		SI sat_CN = satisfiedCN(*all);//ԭLETSż����У��ڵ� 
		int b2 = sat_CN.size();//ԭLETSż����У��ڵ�����  
		 
		int a1 = (*all).size(); //ԭLETS��С
		
		for (SSI :: iterator it = LETS[c][c].begin(); it != LETS[c][c].end(); ++it){
			SI setCN1 = unsatCN(*it);//���в������У��ڵ� 
			for (SI :: iterator sit = setCN1.begin(); sit != setCN1.end(); ++sit){//���ڵ�*sit���ڵĻ��ļ��ϷŽ� satCycles[*sit]
				satCycles[*sit].insert(*it); 
			}
		}  
		
		for (SI :: iterator it = unsat_CN.begin(); it != unsat_CN.end(); ++it){//��һ�������ж�Ϊ1��У��ڵ� 
			for (int i = 0; i < VC_adj.size(); ++ i){
				pre[i].clear();
				dist[i] = INF;
			}
			SI expansileNode;
			dist[*it] = 0;
			queue <int> que;
			que.push(*it); //�����ڵ�Ž�����que 
			
			while (!que.empty()){//��ǰ���ʽڵ�Ϊu 
				int u = que.front();
				if (dist[u] == dis){
					expansileNode.insert(u); 
				} 
				que.pop();
				
				for (int i = 0; i < VC_adj[u].size(); ++ i){//u����һ���ڵ�Ϊv 
					int v = VC_adj[u][i];
	
					if (dist[v] > dist[u] + 1){//��v�ڵ�δ�����ʹ���������� 
						dist[v] = dist[u] + 1;
						if (dist[v] <= dis)	que.push(v);
					}
					
					if (dist[v] == dist[u] + 1){//��v�ڵ���ʽ�������u����Ϊv��ǰһ�ڵ� 
						pre[v].push_back (u);
					}					
				}
			}
	
			for (SI :: iterator sit = expansileNode.begin(); sit != expansileNode.end(); ++sit){
				int u = *sit;
				VI	path (dis + 1);//����Ԫ��path��Ԫ�ظ���Ϊu�ڵ�����1
				VVI	allPaths;//����u��root������·�� 
				dfsAllPaths (dis, u, pre, path, allPaths);
	
				for (int i = 0; i < allPaths.size(); ++ i){					
					satPath[u].push_back(allPaths[i]); 
				}				
			}	
		}
	
		for (int u = 0; u <satPath.size(); u++){//��ǰ���ʽڵ�Ϊu 
			if ((satPath[u].size() >= 1)&&(satCycles[u].size() >= 1)){//����Ϊ0��ֱ������ 
				for (int i = 0; i < satPath[u].size(); ++i){//�����Ƚ�������ͬ�����е�Ԫ�� 
					for (SSI :: iterator it = satCycles[u].begin(); it != satCycles[u].end(); ++it){
						SI setVN;
						SI allorigCN = Findall_CN(*all);
						allorigCN.erase(satPath[u][i][0]); 
						SI allcyCN = Findall_CN(*it);
						allcyCN.erase(u); 
						int temp = 0;
						for (int l = 1; l < satPath[u][i].size(); l += 2){
							if ((*all).find(satPath[u][i][l]) != (*all).end() || (*it).find(satPath[u][i][l]) != (*it).end()){
								++ temp;
							}
							setVN.insert(satPath[u][i][l]);
						}	
						for (SI :: iterator sit = (*it).begin(); sit != (*it).end(); ++sit){
							if((*all).find(*sit) != (*all).end()){
								++ temp;
							}
						}
						
						SI allpaCN = Findall_CN(setVN);	
						for (SI :: iterator sit = allpaCN.begin(); sit != allpaCN.end(); ++sit){
							if(allorigCN.find(*sit) != allorigCN.end() ||allcyCN.find(*sit) != allcyCN.end() ){
								++ temp;
							}
						}
						
						for (SI :: iterator sit = allcyCN.begin(); sit != allcyCN.end(); ++sit){
							if(allorigCN.find(*sit) != allorigCN.end() ){
								++ temp;
							}
						}
						SI setVN1;
						if (temp == 0){
							for (SI :: iterator sit = (*it).begin(); sit != (*it).end(); ++sit){//��������setVN1�� 
								setVN1.insert(*sit);
							}
							for (int l = 1; l < satPath[u][i].size(); l += 2){//��ֱ�߲���setVN1�� 
								setVN1.insert(satPath[u][i][l]);
							}
							
							SI newsetVN(*all);
							for (SI :: iterator sit = setVN1.begin(); sit != setVN1.end(); ++sit){//����չ���Ĳ��ֲ���newsetVN 
								newsetVN.insert(*sit);
							}
							SI newsetCN1 = degree1CN(newsetVN);//�½ṹ��Ϊ1��У��ڵ�
							SI newsetCN2 = satisfiedCN(newsetVN);// �½ṹ�������У��ڵ�
							if((newsetVN.size() == a1+p)&&(newsetCN1.size() == b1-2+p*(dv-2))&&(newsetCN2.size() == b2+d+c)){//�������ڵ����������У��ڵ������������У��ڵ������������� 
								int da = newsetVN.size();
								int db = newsetCN1.size();
								LETS[da][db].insert(newsetVN);
							}
							
						}						
					
						
					}	
				}		
			}	
		}
		
	}
} 
 
//dot��չ
SSI DotExpand_one (int p, int dv, const SI &origTS){
	SSI res;
	SI setVN(origTS);//ԭtannerͼ�����ڵ�
	SI setVN2;//�ܹ���չ�ı����ڵ� 
	SI setVN3;//���������ı����ڵ� 
	SI setVNtoCN;//��������У��ڵ����������б����ڵ� 
	SI setCN1 = degree1CN (origTS);//��Ϊ1У��ڵ� 
	SI setCN2 = satisfiedCN(setVN);//ż����У��ڵ�
	int b2 = setCN2.size(); 

	int b1 = setCN1.size();
	
	for (SI :: iterator it = setCN1.begin(); it != setCN1.end(); ++ it){//�ҳ�������������������У��ڵ�ı����ڵ�  
		SI setVN4 = SetXnorVec(setVNtoCN,VC_adj[*it]);//
			for (SI :: iterator sit = setVN4.begin(); sit != setVN4.end(); ++ sit){
				setVN2.insert(*sit); 
			}
			for (int i = 0; i < VC_adj[*it].size(); ++i){
			setVNtoCN.insert(VC_adj[*it][i]); 	
			}
	}
	
	for (SI :: iterator it = setVN2.begin(); it != setVN2.end(); ++ it){//�ų�����ż����У��ڵ�ı����ڵ㣬���������ı����ڵ����setVN3�� 
		int num = 0; 
			for (int i = 0; i < VC_adj[*it].size(); ++i){
				if (setCN2.find(VC_adj[*it][i]) != setCN2.end()){
				 num++;
				}
			}
			if (num == 0){
			setVN3.insert(*it);								
			}	
	}
	
	for  (SI :: iterator it = setVN3.begin(); it != setVN3.end(); ++ it){//���γɵ�ͼ�����res�� 
		SI newsetVN(setVN);
		newsetVN.insert(*it); 
		SI newsetCN = degree1CN(newsetVN);
		SI newsetCN2 = satisfiedCN(newsetVN);
		if((newsetCN.size() == b1 + dv -2*p)&&(newsetCN2.size() == b2+p)){//�ж����γɵĽڵ�����ԭͼ�����ı��� 
		res.insert(newsetVN); 	
		}
	} 	 
	return res;
} 

//lollipop��չ 
SSI LoExpand1 (int p, int c, int dv, const SI &origTS){
	int d = p + 1 - c; 
	int dis = 2*(d-1);
	SSI res;
	VVVI satPath(VC_adj.size());//����Ϊp�ĵ㹹�ɵ�·�� 
	VSSI satCycles(VC_adj.size());//ĳ���ڵ�����Щ���� 
	VVI pre (VC_adj.size());//ǰһ�ڵ� 
	VI  dist (VC_adj.size(),2);//���� 
	SI unsat_CN = degree1CN(origTS);//ԭLETS��Ϊ1У��ڵ� 
	int b1 = unsat_CN.size(); //��Ϊ1У��ڵ����� 
	SI sat_CN = satisfiedCN(origTS);//ԭLETSż����У��ڵ� 
	int b2 = sat_CN.size();//ԭLETSż����У��ڵ�����  
	
	int a1 = origTS.size(); //ԭLETS��С
	
	for (SSI :: iterator it = LETS[c][c].begin(); it != LETS[c][c].end(); ++it){
		SI setCN1 = unsatCN(*it);//���в������У��ڵ� 
		for (SI :: iterator sit = setCN1.begin(); sit != setCN1.end(); ++sit){//���ڵ�*sit���ڵĻ��ļ��ϷŽ� satCycles[*sit]
			satCycles[*sit].insert(*it); 
		}
	}  
	
	for (SI :: iterator it = unsat_CN.begin(); it != unsat_CN.end(); ++it){//��һ��������������У��ڵ� 
		for (int i = 0; i < VC_adj.size(); ++ i){
			pre[i].clear();
			dist[i] = INF;
		}
		SI expansileNode;
		dist[*it] = 0;
		queue <int> que;
		que.push(*it); //�����ڵ�Ž�����que 
		
		while (!que.empty()){//��ǰ���ʽڵ�Ϊu 
			int u = que.front();
			que.pop();
			
			for (int i = 0; i < VC_adj[u].size(); ++ i){//u����һ���ڵ�Ϊv 
				int v = VC_adj[u][i];

				if (dist[v] > dist[u] + 1){//��v�ڵ�δ�����ʹ���������� 
					dist[v] = dist[u] + 1;
					if (dist[v] <= dis)	que.push(v);
				}
				
				if (dist[v] == dist[u] + 1){//��v�ڵ���ʽ�������u����Ϊv��ǰһ�ڵ� 
					pre[v].push_back (u);
				}
				if (dist[v] == dis){
					expansileNode.insert(v); 
				} 
			}
		}

		for (SI :: iterator sit = expansileNode.begin(); sit != expansileNode.end(); ++sit){
			int u = *sit;
			int	d = dist[u];
			VI	path (d + 1);//����Ԫ��path��Ԫ�ظ���Ϊu�ڵ�����1
			VVI	allPaths;//����u��root������·�� 
			dfsAllPaths (d, u, pre, path, allPaths);

			for (int i = 0; i < allPaths.size(); ++ i){					
				satPath[u].push_back(allPaths[i]); 
			}				
		}	
	}

	for (int u = 0; u <satPath.size(); u++){//��ǰ���ʽڵ�Ϊu 
		if ((satPath[u].size() >= 1)&&(satCycles[u].size() >= 1)){//����Ϊ0��ֱ������ 
			for (int i = 0; i < satPath[u].size(); ++i){//�����Ƚ�������ͬ�����е�Ԫ�� 
				for (SSI :: iterator it = satCycles[u].begin(); it != satCycles[u].end(); ++it){
					SI setVN;
					for (int l = 1; l < satPath[u][i].size(); l += 2){//��ֱ�߲���setVN�� 
						setVN.insert(satPath[u][i][l]);
					}		
					
					for (SI :: iterator sit = (*it).begin(); sit != (*it).end(); ++sit){//��������setVN�� 
						setVN.insert(*sit);
					}
					
					SI newsetVN(origTS);
					for (SI :: iterator sit = setVN.begin(); sit != setVN.end(); ++sit){//����չ���Ĳ��ֲ���newsetVN 
						newsetVN.insert(*sit);
					}
					SI newsetCN1 = degree1CN(newsetVN);//�½ṹ��Ϊ1��У��ڵ�
					SI newsetCN2 = satisfiedCN(newsetVN);// �½ṹ�������У��ڵ�
					if((newsetVN.size() == a1+p)&&(newsetCN1.size() == b1-2+p*(dv-2))&&(newsetCN2.size() == b2+d+c)){//�������ڵ����������У��ڵ������������У��ڵ������������� 
						res.insert(newsetVN);
					}
				}
				
			}	
		}	
	}
	return res;	
}

//path��չ
SSI pathExpand1 (int p, int dv, const SI &origTS){
	SSI res;
	VVVI satPath(VC_adj.size());//����Ϊp�ĵ㹹�ɵ�·�� 
	VVI pre (VC_adj.size());//ǰһ�ڵ� 
	VI  dist (VC_adj.size(),2);//���� 
	SI unsat_CN = degree1CN(origTS);//ԭLETS������У��ڵ� 
	SI sat_CN = satisfiedCN(origTS);
	int b2 = sat_CN.size(); 
	int a1 = origTS.size(); //ԭLETS�Ĵ�С

	for (SI :: iterator it = unsat_CN.begin(); it != unsat_CN.end(); ++it){//��һ��������������У��ڵ� 
		for (int i = 0; i < VC_adj.size(); ++ i){
			pre[i].clear();
			dist[i] = INF;
		}
		SI expansileNode;
		dist[*it] = 0;
		queue <int> que;
		que.push(*it); //�����ڵ�Ž�����que 
		
		while (!que.empty()){//��ǰ���ʽڵ�Ϊu 
			int u = que.front();
			que.pop();
			
			for (int i = 0; i < VC_adj[u].size(); ++ i){//u����һ���ڵ�Ϊv 
				int v = VC_adj[u][i];
				
					if (dist[v] > dist[u] + 1){//��v�ڵ�δ�����ʹ���������� 
						dist[v] = dist[u] + 1;
						if (dist[v] <= p)	que.push(v);
					}
					
					if (dist[v] == dist[u] + 1){//��v�ڵ���ʽ�������u����Ϊv��ǰһ�ڵ� 
						pre[v].push_back (u);
					}
					if (dist[v] == p){
						expansileNode.insert(v); 
					} 
			}
		}

		for (SI :: iterator sit = expansileNode.begin(); sit != expansileNode.end(); ++sit){
			int u = *sit;
			int	d = dist[u];
			VI	path (d + 1);//����Ԫ��path��Ԫ�ظ���Ϊu�ڵ�����1
			VVI	allPaths;//����u��root������·�� 
			dfsAllPaths (d, u, pre, path, allPaths);

			for (int i = 0; i < allPaths.size(); ++ i){					
				satPath[u].push_back(allPaths[i]); 
			}				
		}	
	}
	
	for (int u = 0; u <satPath.size(); u++){//satPath[u].
		if (satPath[u].size() >= 2){//����Ϊ0��ֱ������ 
			for (int i = 1; i < satPath[u].size(); ++i){//�����Ƚ�������ͬ�����е�Ԫ�� 
				for (int j = 0; j < i; ++j){
					int temp1 = 0;
					for (int k = 0; k < p; ++k){//��p+1���ڵ㣬�������һ���ڵ��������ͬ 
						if (satPath[u][i][k] == satPath[u][j][k]){
							++temp1;
						}
					}
					 
					SI setVN;
					if (temp1 == 0){//��·���޽��� ����setVN 
						for (int l = 1; l <= p; l += 2){
							setVN.insert(satPath[u][i][l]);
							setVN.insert(satPath[u][j][l]);
						}		
					}
					
					int temp2 = 0;//�ж�path�е�У��ڵ��Ƿ���ԭͼ�� 
				//	SI newsetCN2 = satisfiedCN(origTS);
					SI allsetCN1 = Findall_CN(origTS);
					SI allsetCN2 = Findall_CN(setVN);
					allsetCN2.erase(satPath[u][i][0]);
					allsetCN2.erase(satPath[u][j][0]);
					for (SI :: iterator sit2 = allsetCN1.begin(); sit2 != allsetCN1.end(); ++sit2){
						if (allsetCN2.find(*sit2) != allsetCN2.end() ){
							++temp2;
						}
					}
					if (temp2 == 0){
						SI newsetVN(origTS);
						for  (SI :: iterator sit1 = setVN.begin(); sit1 != setVN.end(); ++ sit1){
							newsetVN.insert(*sit1);  
						}
						SI newsetCN1 = degree1CN(newsetVN);
						SI newsetCN2 = satisfiedCN(newsetVN);
						if ((newsetVN.size() == a1 + p)&&(newsetCN1.size() == unsat_CN.size()-2+p*(dv-2))/*&&(newsetCN2.size() == b2+p+1 )*/){//�ж϶�Ϊ1��У��ڵ�������Ƿ���ȷ 
							res.insert(newsetVN);
						}
					}
				}
			}	
		}	
	}

	return res;
} 
 
//expand original TS through adding VN with degree no more than maxDeg
//return expanded TSs with sizes <= a and number of unsatisfied CNs <= b
VVI expandTS (int a, int b, int maxDeg, const SSI &origTS){
	VVI	res;
	VMSS mapTS (a + 1);
	int minCycle = a;
	 
	for (SSI :: iterator it = origTS.begin(); it != origTS.end(); ++ it){
		if (it->size() > 1 && it->size() < minCycle){
			minCycle = it->size();
		}
		mapTS[it->size()][*it] = unsatCN (*it);
	}
	
	for (int da = 1; da <= a; ++ da){
//		cerr << "expandTS has completed " << (da - 1.0) / a * 100 << "%" << "\n";
		  
		mapTS[da - 1].clear();
		
		for (MSS :: iterator mit = mapTS[da].begin(); mit != mapTS[da].end(); ++ mit){
			SI setVN = mit->first;
			SI setCN = mit->second;
			//expand TS by add a VN to unsatisfied CN
			for (SI :: iterator it = setCN.begin(); da < a && it != setCN.end(); ++ it){
				int c = *it;
				//maximum number of unsatisfied CNs
				int maxUCN = a + b - da + (da + 1 < a ? maxDeg - 1 : 0);
				for (int j = 0; j < VC_adj[c].size(); ++ j){
					int v = VC_adj[c][j];
					if (setVN.find(v) != setVN.end() || VC_adj[v].size() > maxDeg){
						continue;
					}
					SI newSetCN = setXorVec (setCN, VC_adj[v]);
					if (newSetCN.size() < maxUCN){
						setVN.insert(v);
						mapTS[setVN.size()][setVN] = newSetCN;//���������� 
						setVN.erase(v);
					}
				}
			}
			
			if (setVN.size() >= minCycle && setCN.size() <= b){
				VI vn (setVN.begin(), setVN.end());
				vn.insert(vn.begin(), setCN.size());
				vn.insert(vn.begin(), setVN.size());
				res.push_back(vn);
			}
		}
	}
	
	return	res;
}

//each element of ts is a TS: a, b, v1, v2, ..., va
//file format: "TSidx" i "a" a "b" b v1, v2, ..., va
void writeTStoFile (const VVI &ts, const char *fileName){
	FILE *fp = fopen (fileName, "w");
	
	fprintf(fp, "a\tb\tv1~va\n");
	for (int i = 0; i < ts.size(); ++ i){
		fprintf (fp, "%d\t%d\t", ts[i][0], ts[i][1]);
		for (int j = 2; j < ts[i].size(); ++ j){
			fprintf (fp, "%d\t", ts[i][j]);
		}
		fprintf (fp, "\n");
	}
	
	fclose (fp);
}

//each element of ts is a TS: a, b, v1, v2, ..., va
void writeTSsummaryToFile (const VVI &ts, const char *fileName){
	FILE *fp = fopen (fileName, "w");
	
	int maxa = 0, maxb = 0;
	for (int i = 0; i < ts.size(); ++ i){
		maxa = max (maxa, ts[i][0]);
		maxb = max (maxb, ts[i][1]);
	}
	
	VVI cntTS (maxa + 1, VI (maxb + 1, 0));
	for (int i = 0; i < ts.size(); ++ i){
		++ cntTS[ts[i][0]][ts[i][1]];
	}
	
	fprintf (fp, "total number of TS:  %u\n\n", ts.size());
	fprintf (fp, "a\tb\tcnt\n");
	for (int i = 1; i <= maxa; ++ i){
		for (int j = 0; j <= maxb; ++ j){
			if (cntTS[i][j] > 0){
				fprintf (fp, "%d\t%d\t%d\n", i, j, cntTS[i][j]);
			}	
		}
	}
		
	fclose (fp);
}

//file format: "TSidx" i "a" a "b" b v1, v2, ..., va
//each TS format: a, b, v1, v2, ..., va
VVI readFiletoTS (const char *fileName){
	FILE *fp = fopen (fileName, "r");
	if (fp == NULL){
		cerr << "<readFiletoTS>: fail to open " << fileName << "." << "\r\n";
		assert (false);
	}
	
	VVI res;
	char str[10];
	VI vn (2);
	FILE *pre = fp;
	while (fscanf (fp, "%s", str) != EOF){
		fscanf (fp, "%d %s %d %s %d", &vn[0], str, &vn[0], str, &vn[1]);
		vn.resize(vn[0] + 2);
		for (int i = 2; i < vn.size(); ++ i){
			fscanf (fp, "%d", &vn[i]);
		}
		res.push_back(vn);
	}
	
	fclose (fp);
	
	return	res;
}

//SSI de (int m, int dv, const SSI &origTS){
//	SSI lets(origTS);
//	SSI res;	
//	for (set<set<int> > ::iterator it = lets.begin(); it != lets.end(); it++){
//		SSI lets1 = DotExpand_one (m,dv,*it);
//		for (set<set<int> > ::iterator mit = lets1.begin(); mit != lets1.end(); mit++){
//			res.insert(*mit);
//		}
//	}	
//	return res;
//}
//
//SSI pe (int m, int dv, const SSI &origTS){
//	SSI lets(origTS);
//	SSI res;	
//	for (set<set<int> > ::iterator it = lets.begin(); it != lets.end(); it++){
//		SSI lets1 = pathExpand1 (m,dv,*it);
//		for (set<set<int> > ::iterator mit = lets1.begin(); mit != lets1.end(); mit++){
//			res.insert(*mit);
//		}
//	}	
//	return res;
//}
//
//SSI le (int m, int c, int dv, const SSI &origTS){
//	SSI lets(origTS);
//	SSI res;	
//	for (set<set<int> > ::iterator it = lets.begin(); it != lets.end(); it++){
//		SSI lets1 = LoExpand (m,c,dv,*it);
//		for (set<set<int> > ::iterator mit = lets1.begin(); mit != lets1.end(); mit++){
//			res.insert(*mit);
//		}
//	}	
//	return res;
//}

//Find all LETS (a', b') <= (a, b)
//An LETS is denoted by a VI: a, b, v1, v2, ...,va
VVI find_LETS (int a, int b){
	
	if (a < 2 || b < 0){
		cerr << "<findTS>: parameters have errors." << "\n";
		assert (false);
	}
	
	int start = clock();
	
	VC_adj = CN_adj_to_VN_adj (CN_adj);
	for (int j = 0; j < n; ++ j){
		for (int i = 0; i < VC_adj[j].size(); ++ i){
			VC_adj[j][i] += n;
		}
	}
	VC_adj.insert(VC_adj.end(), CN_adj.begin(), CN_adj.end());
//	cout<<"�ڽӾ������£�"<<endl; 
//	output(VC_adj, "VC_adj");
	int dv = VC_adj[0].size();	
	SSI cycles4 = bfsSimpleCycles (dv,4);	
	for (set<set<int> > ::iterator it = cycles4.begin(); it != cycles4.end(); it++){
		LETS[4][4].insert(*it);
	}
//	LoExpand(5,4,dv,LETS[4][4]);
//	printss(LETS[9][7]);
//	while(1);

	
	SSI cycles5 = bfsSimpleCycles (dv,5);
	for (set<set<int> > ::iterator it = cycles5.begin(); it != cycles5.end(); it++){
		LETS[5][5].insert(*it);
	}
	
	SSI cycles6 = bfsSimpleCycles (dv,6);
	for (set<set<int> > ::iterator it = cycles6.begin(); it != cycles6.end(); it++){
		LETS[6][6].insert(*it);
	}
	
		for (int i = 0; i <= a; ++ i){
		for (int j = 0; j <= b; ++j){
			if (LETS[i][j].empty()){
				continue;
			}
			if ((i == 12 && j == 5)||(i==12 && j == 6)){
				continue;
			}
			if (j <= 4){
				cout<<"LETS["<<i<<"]"<<"["<<j<<"]"<<"����Ϊ��"<<LETS[i][j].size()<<endl;
			}
			
			DotExpand(dv,LETS[i][j]);
			
			for (int k1 = 2; (k1 + i <= a) && (k1 + j - 2 <= b); ++ k1){
				PathExpand(k1,dv,LETS[i][j]);
			}
			
			for (int k1 = 3; (k1 + i <= a) && (k1 + j - 2 <= b); ++ k1){
				for (int k2 =3; k2 <= k1; ++ k2){
					LoExpand(k1,k2,dv,LETS[i][j]);
				}	
			}
			
		}
	}

//	for (int i = 0; i <= a; ++ i){
//		for (int j = 0; j <= b; ++j){
//			if (LETS[i][j].empty()){
//				continue;
//			}
//			if (dot[i][j] == 1){
//				DotExpand(dv,LETS[i][j]);
//			}
//			
//			for (int k = 0; k < 2; ++ k ){
//				if (path[i][j][k] != 0){
//					PathExpand(path[i][j][k], dv, LETS[i][j]);
//				}
//			}
//			
//			for (int k = 0; k < 2; ++ k ){
//				if (lo[i][j][k].first != 0){
//					LoExpand(lo[i][j][k].first, lo[i][j][k].second, dv, LETS[i][j]);
//				}
//			}
//			if (j <= 4){
//				cout<<"LETS["<<i<<"]"<<"["<<j<<"]"<<"����Ϊ��"<<LETS[i][j].size()<<endl; 
//			}			
//			
//		}
//	}
	

	VVI ts = expandTS (a, b, 2, cycles4);

	sort (ts.begin(), ts.end());
	
	writeTStoFile (ts, "TS.txt");
	writeTSsummaryToFile (ts, "TS summary.txt");
	
	outputClock ("running time (sec.) of find_LETS: ", (clock() - start)/1000);
	
	return	ts;
}


