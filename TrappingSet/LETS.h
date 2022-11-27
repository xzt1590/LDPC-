#ifndef __LETS_h__
#define __LETS_h__

#include "globalFile.h"
#include "myIO.h"


typedef set <int> SI;
typedef vector <SI> VSI;
typedef set <SI> SSI;
typedef vector <SSI> VSSI;
typedef vector <VSSI> VVSSI; 
typedef map <SI, SI> MSS;
typedef vector <MSS> VMSS;

extern int	m;//#CNs
extern int	n;//#VNs
extern VVI	CN_adj;//neighbors of CNs
extern VVSSI LETS;
extern VVB dot;
extern VVVI path;
extern VVVPII lo; 

VVI find_LETS (int a, int b);

#endif
