
#include <globals.h>
#include <tools.h>
#include "10P.h"
#include "10P2.h"
#include "7T.h"
//!  A 10P2 is a 9P with an additional particle
/*!
* 10P2 is a 9P cluster with an sp3a at one end. 
* Two of the sp3a particles form the bonded and nonbonded pair of one 
* of the 6Zs at either end of the 6Z.
*The other sp3a particle is the additional particle
*  Storage order: bonded, nbonded2, bonded2, nbonded, spindle1, spindle 2,
* 3 extra particles top to bottom, new particle)
*/

void Clusters_Get10P2() {
for (int old_9P_id = 0; old_9P_id < n9P; ++old_9P_id) {
    int *old_9P_cluster = hc9P[old_9P_id];
    int clust_7T[9][2]; 
    clust_7T[0][0] = old_9P_cluster[3];
    clust_7T[1][0] = old_9P_cluster[2];
    clust_7T[2][0] = old_9P_cluster[5];
    clust_7T[3][0] = old_9P_cluster[8];
    clust_7T[4][0] = old_9P_cluster[0];
    clust_7T[5][0] = old_9P_cluster[4];
    clust_7T[6][0] = old_9P_cluster[1];
    clust_7T[7][0] = old_9P_cluster[6];
    clust_7T[8][0] = old_9P_cluster[7];
    
    clust_7T[0][1] = old_9P_cluster[6];
    clust_7T[1][1] = old_9P_cluster[4];
    clust_7T[2][1] = old_9P_cluster[5];
    clust_7T[3][1] = old_9P_cluster[7];
    clust_7T[4][1] = old_9P_cluster[1];
    clust_7T[5][1] = old_9P_cluster[2];
    clust_7T[6][1] = old_9P_cluster[0];
    clust_7T[7][1] = old_9P_cluster[3];
    clust_7T[8][1] = old_9P_cluster[8];

    for(int g = 0; g<2; ++g){
        int spindle_id_2 = clust_7T[5][g];
        int spindle_id = clust_7T[4][g];
        int nbonded_id = clust_7T[3][g];
        int bonded_id = clust_7T[0][g]; 
        int nbonded_id_2 = clust_7T[1][g];
        int bonded_id_2 = clust_7T[2][g]; 
        int final_part1 = clust_7T[6][g]; 
        int final_part2 = clust_7T[7][g]; 
        int final_part3 = clust_7T[8][g]; 
        int arr_6Z[6] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2};
        for (int new_3_id = 0; new_3_id < nsp3a; ++new_3_id ){ //iterate over all sp3a rings
            int *new_3_cluster = hcsp3a[new_3_id];
            if(nring_in_cluster(old_9P_cluster, new_3_cluster, 10) == 2){
                if(nring_bonded_nbonded(bonded_id, nbonded_id, new_3_cluster) == 2){ //two particles in ring are in 6Z
                   int bond_counter = check_ring_bonds(new_3_cluster, arr_6Z);
                    if (bond_counter == 9){
                        int new_part = get_new_particle_P2(new_3_cluster, bonded_id, nbonded_id);
                        if (check_unique10P2(old_9P_cluster, new_part, 10) == 0){
                            add_10P2(bonded_id, nbonded_id_2, bonded_id_2, nbonded_id,spindle_id, spindle_id_2, final_part1, final_part2, final_part3, new_part);
                            }
                        }
                    }
                }
            }
        }
    }
}

int nring_bonded_nbonded(int bonded_id, int nbonded_id, const int *clust_2){
    int cross_count =0; 
    if(bonded_id == clust_2[0]){
        cross_count += 1;
    }
    if(bonded_id == clust_2[1]){
        cross_count += 1;
    }
    if(bonded_id == clust_2[2]){
        cross_count += 1;
    }
    
    if(nbonded_id == clust_2[0]){
        cross_count += 1;
    }
    if(nbonded_id == clust_2[1]){
        cross_count += 1;
    }
    if(nbonded_id == clust_2[2]){
        cross_count += 1;
    }
    return cross_count;
}

int nring_in_cluster(const int *clust_1, const int *clust_2, int clust_1_size){
    int s1 = clust_1_size;
    int cross_count =0; 
    for(int n=0; n<s1; ++n){
        for(int j = 0; j<3; ++j){
            if(clust_1[n]==clust_2[j]){
                cross_count += 1;
        }

        }
    }
    return cross_count;
}

void add_10P2(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int final_part3, int new_particle) {
    int clusSize = 10;
    if (n10P2 == m10P2) {
        hc10P2 = resize_2D_int(hc10P2, m10P2, m10P2 + incrStatic, clusSize, -1);
        m10P2 = m10P2 + incrStatic;
    }
    hc10P2[n10P2][0] = bonded_id;
    hc10P2[n10P2][1] = nbonded_id_2;
    hc10P2[n10P2][2] = bonded_id_2;
    hc10P2[n10P2][3] = nbonded_id;
    hc10P2[n10P2][4] = spindle_id;
    hc10P2[n10P2][5] = spindle_id_2;
    hc10P2[n10P2][6] = final_part1;
    hc10P2[n10P2][7] = final_part2;
    hc10P2[n10P2][8] = final_part3;
    hc10P2[n10P2][9] = new_particle;

    for (int i = 0; i < 10; ++i) {
        s10P2[hc10P2[n10P2][i]] = 'B';
    }
    ++n10P2;
}

int get_new_particle_P2(const int *new_3_ring, int bonded_id, int nbonded_id) {
    for(int ring_id = 0; ring_id <3; ++ring_id){
        int noverlap = 0;
        if(new_3_ring[ring_id] != bonded_id && new_3_ring[ring_id] != nbonded_id){
            return new_3_ring[ring_id];
        }
    }
}

int check_unique10P2(const int *old_clust, int new_particle, int new_clust_size){
    int u;
    for (int old_10P2_id = 0; old_10P2_id < n11P2; ++old_10P2_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<10; ++r){
                if(hc11P2[old_10P2_id][q] == old_clust[r]){
                    u += 1;
                }
            }

        }
        for (int p = 0; p<new_clust_size; ++p){
            if(hc11P2[old_10P2_id][p] == new_particle){
                    u += 1;
                }
        }
    if(u == new_clust_size){
        return 1;            
    }
    }
    return 0;
}
