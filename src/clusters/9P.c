#include <globals.h>
#include <tools.h>
#include "9P.h"
#include "8P.h"
#include "7T.h"
//!  A 9P is an 8P with an additional particle
/*!
* A 8P cluster contains two 6Z clusters at the top and bottom of the cluster. 
* A 9P takes these two 6Z clusters and tries to make a 7T from the cluster and an extra particle.
*  Cluster output: BBBBBBBBB
*  Storage order: original 8P particles x 8, new 5A spindle)
*/

    void Clusters_Get9P() {
    for (int old_8P_id = 0; old_8P_id < n8P; ++old_8P_id) {
        int *old_8P_cluster = hc8P[old_8P_id];
        int clust_6Z[8][2]; 
        clust_6Z[0][0] = old_8P_cluster[3];
        clust_6Z[1][0] = old_8P_cluster[2];
        clust_6Z[2][0] = old_8P_cluster[5];
        clust_6Z[3][0] = old_8P_cluster[7];
        clust_6Z[4][0] = old_8P_cluster[0];
        clust_6Z[5][0] = old_8P_cluster[4];
        clust_6Z[6][0] = old_8P_cluster[1];
        clust_6Z[7][0] = old_8P_cluster[6];
        
        clust_6Z[0][1] = old_8P_cluster[1];
        clust_6Z[1][1] = old_8P_cluster[0];
        clust_6Z[2][1] = old_8P_cluster[4];
        clust_6Z[3][1] = old_8P_cluster[6];
        clust_6Z[4][1] = old_8P_cluster[2];
        clust_6Z[5][1] = old_8P_cluster[5];
        clust_6Z[6][1] = old_8P_cluster[3];
        clust_6Z[7][1] = old_8P_cluster[7];

        for(int g = 0; g<2; ++g){
            int spindle_id_2 = clust_6Z[5][g];
            int spindle_id = clust_6Z[4][g];
            int nbonded_id = clust_6Z[3][g];
            int bonded_id = clust_6Z[0][g]; 
            int nbonded_id_2 = clust_6Z[1][g];
            int bonded_id_2 = clust_6Z[2][g]; 
            int final_part1 = clust_6Z[6][g]; 
            int final_part2 = clust_6Z[7][g]; 
            for (int new_5A_pointer = 0; new_5A_pointer < nmem_sp3c[spindle_id_2]; ++new_5A_pointer) {
                int new_5A_id = mem_sp3c[spindle_id_2][new_5A_pointer];
                int *new_5A_cluster = hcsp3c[new_5A_id];
                if (is_particle_spindle_of_5A(spindle_id_2, new_5A_cluster) == 1) {
                    if(is_particle_ring_of_5A(bonded_id,new_5A_cluster) == 1){
                        if(is_particle_ring_of_5A(nbonded_id,new_5A_cluster) == 1){
                            if(is_particle_ring_of_5A(spindle_id,new_5A_cluster) == 1){
                                int new_particle_id = get_new_particle(new_5A_cluster, spindle_id_2);
                                    if(crossover_part(old_8P_cluster, new_particle_id, 9) == 0){
                                    int arr_6Z[6] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2};
                                    int bond_counter = check_ring_bonds(new_5A_cluster, arr_6Z);
                                        if (bond_counter == 25 ){
                                            if (check_unique9P(old_8P_cluster, new_particle_id,9) == 0){
                                            add_9P(bonded_id, nbonded_id_2, bonded_id_2, nbonded_id,spindle_id, spindle_id_2, final_part1, final_part2, new_particle_id);
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


void add_9P(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int new_particle) {
    int clusSize = 9;
    //printf("new_particle %i\n", new_particle);
    if (n9P == m9P) {
        hc9P = resize_2D_int(hc9P, m9P, m9P + incrStatic, clusSize, -1);
        m9P = m9P + incrStatic;
    }
    hc9P[n9P][0] = bonded_id;
    hc9P[n9P][1] = nbonded_id_2;
    hc9P[n9P][2] = bonded_id_2;
    hc9P[n9P][3] = nbonded_id;
    hc9P[n9P][4] = spindle_id;
    hc9P[n9P][5] = spindle_id_2;
    hc9P[n9P][6] = final_part1;
    hc9P[n9P][7] = final_part2;
    hc9P[n9P][8] = new_particle;

    for (int i = 0; i < 9; ++i) {
        s9P[hc9P[n9P][i]] = 'B';
    }
    ++n9P;
}

int check_unique9P(const int *old_clust, int new_particle, int new_clust_size){
    int u;
    for (int old_9P_id = 0; old_9P_id < n9P; ++old_9P_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<8; ++r){
                //printf("%i %i\n", hc11P[old_11P_id][q],old_clust[r]);
                if(hc9P[old_9P_id][q] == old_clust[r]){
                    u += 1;
             
                }
            }

        }
        for (int p = 0; p<new_clust_size; ++p){
            if(hc9P[old_9P_id][p] == new_particle){
                    u += 1;
                }
        }

    if(u == new_clust_size){
        return 1;            
    }
    }
    return 0;
}
