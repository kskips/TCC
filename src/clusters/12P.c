#include <globals.h>
#include <tools.h>
#include "7T.h"
#include "8P.h"
#include "12P.h"
//!  A 12P is a 11P with an additional particle
/*!
* A 11P cluster contains two 6Z clusters at the top and bottom of the cluster. 
* A 12P takes these two 6Z clusters and tries to make a 7T from the cluster and an extra particle.
*  Cluster output: BBBBBBBBBB
*  Storage order: original 11P particles x 9, new 5A spindle)
*/

    void Clusters_Get12P() {
    for (int old_11P_id = 0; old_11P_id < n11P; ++old_11P_id) {
        int *old_11P_cluster = hc11P[old_11P_id];
        int clust_11P[11][2]; 
        clust_11P[0][0] = old_11P_cluster[3];
        clust_11P[1][0] = old_11P_cluster[2];
        clust_11P[2][0] = old_11P_cluster[5];
        clust_11P[3][0] = old_11P_cluster[10];
        clust_11P[4][0] = old_11P_cluster[0];
        clust_11P[5][0] = old_11P_cluster[4];
        clust_11P[6][0] = old_11P_cluster[1];
        clust_11P[7][0] = old_11P_cluster[6];
        clust_11P[8][0] = old_11P_cluster[7];
        clust_11P[9][0] = old_11P_cluster[8];
        clust_11P[10][0] = old_11P_cluster[9];
        
        clust_11P[0][1] = old_11P_cluster[8];
        clust_11P[1][1] = old_11P_cluster[2];
        clust_11P[2][1] = old_11P_cluster[1];
        clust_11P[3][1] = old_11P_cluster[9];
        clust_11P[4][1] = old_11P_cluster[7];
        clust_11P[5][1] = old_11P_cluster[6];
        clust_11P[6][1] = old_11P_cluster[5];
        clust_11P[7][1] = old_11P_cluster[4];
        clust_11P[8][1] = old_11P_cluster[0];
        clust_11P[9][1] = old_11P_cluster[3];
        clust_11P[10][1] = old_11P_cluster[10];

        for(int g = 0; g<2; ++g){
            int spindle_id_2 = clust_11P[5][g];
            int spindle_id = clust_11P[4][g];
            int nbonded_id = clust_11P[3][g];
            int bonded_id = clust_11P[0][g]; 
            int nbonded_id_2 = clust_11P[1][g];
            int bonded_id_2 = clust_11P[2][g]; 
            int final_part1 = clust_11P[6][g]; 
            int final_part2 = clust_11P[7][g]; 
            int final_part3 = clust_11P[8][g]; 
            int final_part4 = clust_11P[9][g];
            int final_part5 = clust_11P[10][g];

            for (int new_5A_pointer = 0; new_5A_pointer < nmem_sp3c[spindle_id_2]; ++new_5A_pointer) {
                int new_5A_id = mem_sp3c[spindle_id_2][new_5A_pointer];
                int *new_5A_cluster = hcsp3c[new_5A_id];
                if (is_particle_spindle_of_5A(spindle_id_2, new_5A_cluster) == 1) {
                    if(is_particle_ring_of_5A(bonded_id,new_5A_cluster) == 1){
                        if(is_particle_ring_of_5A(nbonded_id,new_5A_cluster) == 1){
                            if(is_particle_ring_of_5A(spindle_id,new_5A_cluster) == 1){
                                int new_particle_id = get_new_particle(new_5A_cluster, spindle_id_2);
                                    if(crossover_part(old_11P_cluster, new_particle_id, 12) == 0){
                                    int arr_6Z[6] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2};
                                    int bond_counter = check_ring_bonds(new_5A_cluster, arr_6Z);
                                        if (bond_counter == 25 ){
                                            if (check_unique12P(old_11P_cluster, new_particle_id,12) == 0){
                                            add_12P(bonded_id, nbonded_id_2, bonded_id_2, nbonded_id,spindle_id, spindle_id_2, final_part1, final_part2, final_part3, final_part4, final_part5, new_particle_id);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } 
} 

void add_12P(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int final_part3, int final_part4, int final_part5, int new_particle){
    int clusSize = 12;
    if (n12P == m12P) {
        hc12P = resize_2D_int(hc12P, m12P, m12P + incrStatic, clusSize, -1);
        m12P = m12P + incrStatic;
    }
    hc12P[n12P][0] = bonded_id;
    hc12P[n12P][1] = nbonded_id_2;
    hc12P[n12P][2] = bonded_id_2;
    hc12P[n12P][3] = nbonded_id;
    hc12P[n12P][4] = spindle_id;
    hc12P[n12P][5] = spindle_id_2;
    hc12P[n12P][6] = final_part1;
    hc12P[n12P][7] = final_part2;
    hc12P[n12P][8] = final_part3;
    hc12P[n12P][9] = final_part4;
    hc12P[n12P][10] = final_part5;
    hc12P[n12P][11] = new_particle;

    for (int i = 0; i < 12; ++i) {
        s12P[hc12P[n12P][i]] = 'B';
    }
    ++n12P;
}

int check_unique12P(const int *old_clust, int new_particle, int new_clust_size){
    int u;
    for (int old_12P_id = 0; old_12P_id < n12P; ++old_12P_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<11; ++r){
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