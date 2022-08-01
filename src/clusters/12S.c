#include <globals.h>
#include <tools.h>
#include "12S.h"

//!  A 12S is a made of three intersectiing 11S clusters
/*!
* One spindle of each 9B is a ring of the other 9B
* There is one common ring particle
*/

void Clusters_Get12S() {
    for (int old_11S_id1 = 0; old_11S_id1 < n11S; ++old_11S_id1) {
        int *old_11S_cluster1 = hc11S[old_11S_id1];
        for (int old_11S_id2 = 0; old_11S_id2 < n11S; ++old_11S_id2) {
            int *old_11S_cluster2 = hc11S[old_11S_id2];
            if(old_11S_id1 != old_11S_id2){
                if(check_central_7A(old_11S_cluster1, old_11S_cluster2) == 1){
                    if(check_rings_11A(old_11S_cluster1, old_11S_cluster2) == 1){
                        int final_part = get_final_part12S(old_11S_cluster1, old_11S_cluster2);
                        if (check_unique_12S(old_11S_cluster2, final_part) == 1){
                            add_12S(old_11S_cluster2, final_part);
                        }
                    }
                }
            }
        }
    }
}

int check_central_7A(int *old_11S_cluster1, int *old_11S_cluster2){
    int u = 0;
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 2; ++j){
            if(old_11S_cluster1[i] == old_11S_cluster2[j]){
                u += 1;
            }
        }       
    }

    for(int k = 2; k < 4; ++k){
        for(int l = 2; l < 4; ++l){
            if(old_11S_cluster1[k] == old_11S_cluster2[l]){
                u += 1;
            }
        }       
    }

    if(old_11S_cluster1[4] == old_11S_cluster2[4]){
        u += 1;
    }

    for(int n = 4; n < 6; ++n){
        for(int m = 4; m < 6; ++m){
            if(old_11S_cluster1[n] == old_11S_cluster2[m]){
                u += 1;
            }
        }       
    }
    if( u == 7){
        return 1;
    }
    else{
        return 0;
    }
}

int check_rings_11A(int *old_11S_cluster1, int *old_11S_cluster2){
    int u = 0;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            if(old_11S_cluster1[i] == old_11S_cluster2[j]){
                u += 1;
            }
        }       
    }
    if(u == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int get_final_part12S(int *old_11S_cluster1, int *old_11S_cluster2){
    for(int i = 0; i < 2; ++i){
        int u = 0;
        for(int j = 0; j < 2; ++j){
            if(old_11S_cluster1[i] == old_11S_cluster2[j]){
                u += 1;
            }
        } 
        if(u == 0){
            return old_11S_cluster1[i];
        }    
    }
}

int check_unique_12S(int *old_11S_cluster2, int final_part){
    int u;
    for (int old_12S_id = 0; old_12S_id < n12S; ++old_12S_id) {
        u = 0;
        for (int q = 0; q < 11; ++q){
            for (int r = 0; r < 12; ++r){
                if(hc12S[old_12S_id][r] == old_11S_cluster2[q]){
                    u += 1;
                }
            }

        }
            for (int r = 0; r < 12; ++r){
                if(hc12S[old_12S_id][r] == final_part){
                    u += 1;
                }
            }
    if(u == 12){
        return 1;            
    }
    }
    return 0;
}

void add_12S(int *old_11S_cluster2, int final_part) {
    int clusSize = 12;
    //printf("new_particle %i\n", new_particle);
    if (n12S == m12S) {
        hc12S = resize_2D_int(hc12S, m12S, m12S + incrStatic, clusSize, -1);
        m12S = m12S + incrStatic;
    }
    hc12S[n12S][0] = old_11S_cluster2[0];
    hc12S[n12S][1] = old_11S_cluster2[1];
    hc12S[n12S][2] = old_11S_cluster2[2];
    hc12S[n12S][3] = old_11S_cluster2[3];
    hc12S[n12S][4] = old_11S_cluster2[4];
    hc12S[n12S][5] = old_11S_cluster2[5];
    hc12S[n12S][6] = old_11S_cluster2[6];
    hc12S[n12S][7] = old_11S_cluster2[7];
    hc12S[n12S][8] = old_11S_cluster2[8];
    hc12S[n12S][9] = old_11S_cluster2[9];
    hc12S[n12S][10] = old_11S_cluster2[10];
    hc12S[n12S][11] = final_part;
    for (int i = 0; i < 12; ++i) {
        s12S[hc12S[n12S][i]] = 'B';
    }
    ++n12S;
}