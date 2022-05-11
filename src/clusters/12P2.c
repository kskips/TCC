#include <globals.h>
#include <tools.h>
#include "10P2.h"
#include "7T.h"
#include "8P.h"
#include "9P.h"
#include "12P2.h"
//!  A 11P is a 10P with an additional particle
/*!
* A 10P cluster contains two 6Z clusters at the top and bottom of the cluster. 
* A 11P takes these two 6Z clusters and tries to make a 7T from the cluster and an extra particle.
*  Cluster output: BBBBBBBBBB
*  Storage order: original 10P particles x 9, new 5A spindle)
*/

    void Clusters_Get12P2() {
    for (int old_11P2_id = 0; old_11P2_id < n11P2; ++old_11P2_id) {
        int *old_11P2_cluster = hc11P2[old_11P2_id];
        int clust_11P2[11];
        clust_11P2[0] = old_11P2_cluster[8];
        clust_11P2[1] = old_11P2_cluster[2];
        clust_11P2[2] = old_11P2_cluster[1];
        clust_11P2[3] = old_11P2_cluster[9];
        clust_11P2[4] = old_11P2_cluster[7];
        clust_11P2[5] = old_11P2_cluster[6];
        clust_11P2[6] = old_11P2_cluster[5];
        clust_11P2[7] = old_11P2_cluster[4];
        clust_11P2[8] = old_11P2_cluster[0];
        clust_11P2[9] = old_11P2_cluster[3];
        clust_11P2[10] = old_11P2_cluster[10];


    for(int g = 0; g<2; ++g){
        int spindle_id_2 = clust_11P2[5];
        int spindle_id = clust_11P2[4];
        int nbonded_id = clust_11P2[3];
        int bonded_id = clust_11P2[0]; 
        int nbonded_id_2 = clust_11P2[1];
        int bonded_id_2 = clust_11P2[2]; 
        int final_part1 = clust_11P2[6]; 
        int final_part2 = clust_11P2[7]; 
        int final_part3 = clust_11P2[8]; 
        int final_part4 = clust_11P2[9]; 
        int final_part5 = clust_11P2[10]; 

        int arr_6Z[6] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2};
        int arr_9P[9] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2, final_part1, final_part2, final_part3};
        for (int new_3_id = 0; new_3_id < nsp3a; ++new_3_id ){ //iterate over all sp3a rings
            int *new_3_cluster = hcsp3a[new_3_id];
            if(nring_in_cluster(old_11P2_cluster, new_3_cluster, 12) == 2){
                if(nring_bonded_nbonded(bonded_id, nbonded_id, new_3_cluster) == 2){ //two particles in ring are in 6Z
                   int bond_counter = check_ring_bonds(new_3_cluster, arr_6Z);
                    if (bond_counter == 9){
                        int new_part = get_new_particle_P2(new_3_cluster, bonded_id, nbonded_id);
                        if (check_unique9P(arr_9P, final_part4, 9) == 0){
                        if (check_unique12P2(old_11P2_cluster, new_part, 12) == 0){
                            add_12P2(bonded_id, nbonded_id_2, bonded_id_2, nbonded_id,spindle_id, spindle_id_2, final_part1, final_part2, final_part3, final_part4, final_part5, new_part);
                            }
                        }
                    }
                    }
                }
            }
        }
    } 
} 

void add_12P2(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int final_part3, int final_part4, int final_part5, int new_particle) {
    int clusSize = 12;
    //printf("new_particle %i\n", new_particle);
    if (n12P2 == m12P2) {
        hc12P2 = resize_2D_int(hc12P2, m12P2, m12P2 + incrStatic, clusSize, -1);
        m12P2 = m12P2 + incrStatic;
    }
    hc12P2[n12P2][0] = bonded_id;
    hc12P2[n12P2][1] = nbonded_id_2;
    hc12P2[n12P2][2] = bonded_id_2;
    hc12P2[n12P2][3] = nbonded_id;
    hc12P2[n12P2][4] = spindle_id;
    hc12P2[n12P2][5] = spindle_id_2;
    hc12P2[n12P2][6] = final_part1;
    hc12P2[n12P2][7] = final_part2;
    hc12P2[n12P2][8] = final_part3;
    hc12P2[n12P2][9] = final_part4;
    hc12P2[n12P2][10] = final_part5;
    hc12P2[n12P2][11] = new_particle;

    for (int i = 0; i < 12; ++i) {
        s12P2[hc12P2[n12P2][i]] = 'B';
    }
    ++n12P2;
}

int check_unique12P2(const int *old_clust, int new_particle, int new_clust_size){
    int u;
    for (int old_12P2_id = 0; old_12P2_id < n12P2; ++old_12P2_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<11; ++r){
                //printf("%i %i\n", hc11P[old_11P_id][q],old_clust[r]);
                if(hc12P2[old_12P2_id][q] == old_clust[r]){
                    u += 1;
                }
            }

        }
        for (int p = 0; p<new_clust_size; ++p){
            if(hc12P2[old_12P2_id][p] == new_particle){
                    u += 1;
                }
        }
    if(u == new_clust_size){
        return 1;            
    }
    }

    for (int old_12P_id = 0; old_12P_id < n12P; ++old_12P_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<11; ++r){
                //printf("%i %i\n", hc11P[old_11P_id][q],old_clust[r]);
                if(hc12P[old_12P_id][q] == old_clust[r]){
                    u += 1;
                }
            }

        }
        for (int p = 0; p<new_clust_size; ++p){
            if(hc12P[old_12P_id][p] == new_particle){
                    u += 1;
                }
        }
    if(u == new_clust_size){
        return 1;            
    }
    }
    return 0;
}