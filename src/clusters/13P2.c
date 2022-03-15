#include <globals.h>
#include <tools.h>
#include "10P2.h"
#include "7T.h"
#include "8P.h"
#include "9P.h"
#include "12P.h"
#include "13P2.h"
//!  A 13P2 cluster is made of a 12P cluster with one extra particle which forms a 3 ring
/*!
*  13P2 is made up of a 12P cluster and a sp3a cluster
*  The sp3a cluster shares two particles with the 13P2 cluster
*  One particle of the sp3a is a bonded spindle of the 12P, and one is a non- bonded spindle
*
*  Cluster output: BBBBBBBBBBBBB
*  Storage order: original 12P particles x 12, new sp3a particle)
*/

    void Clusters_Get13P2() {
    for (int old_12P_id = 0; old_12P_id < n12P; ++old_12P_id) {
        int *old_12P_cluster = hc12P[old_12P_id];
        int clust_12P[12][2]; 
        clust_12P[0][0] = old_12P_cluster[3];
        clust_12P[1][0] = old_12P_cluster[2];
        clust_12P[2][0] = old_12P_cluster[5];
        clust_12P[3][0] = old_12P_cluster[11];
        clust_12P[4][0] = old_12P_cluster[0];
        clust_12P[5][0] = old_12P_cluster[4];
        clust_12P[6][0] = old_12P_cluster[1];
        clust_12P[7][0] = old_12P_cluster[6];
        clust_12P[8][0] = old_12P_cluster[7];
        clust_12P[9][0] = old_12P_cluster[8];
        clust_12P[10][0] = old_12P_cluster[9];
        clust_12P[11][0] = old_12P_cluster[10];
        
        clust_12P[0][1] = old_12P_cluster[9];
        clust_12P[1][1] = old_12P_cluster[1];
        clust_12P[2][1] = old_12P_cluster[6];
        clust_12P[3][1] = old_12P_cluster[10];
        clust_12P[4][1] = old_12P_cluster[8];
        clust_12P[5][1] = old_12P_cluster[7];
        clust_12P[6][1] = old_12P_cluster[2];
        clust_12P[7][1] = old_12P_cluster[5];
        clust_12P[8][1] = old_12P_cluster[4];
        clust_12P[9][1] = old_12P_cluster[0];
        clust_12P[10][0] = old_12P_cluster[3];
        clust_12P[11][0] = old_12P_cluster[11];

    for(int g = 0; g<2; ++g){
        int spindle_id_2 = clust_12P[5][g];
        int spindle_id = clust_12P[4][g];
        int nbonded_id = clust_12P[3][g];
        int bonded_id = clust_12P[0][g]; 
        int nbonded_id_2 = clust_12P[1][g];
        int bonded_id_2 = clust_12P[2][g]; 
        int final_part1 = clust_12P[6][g]; 
        int final_part2 = clust_12P[7][g]; 
        int final_part3 = clust_12P[8][g]; 
        int final_part4 = clust_12P[9][g]; 
        int final_part5 = clust_12P[10][g]; 
        int final_part6 = clust_12P[11][g]; 

        int arr_6Z[6] = {bonded_id, nbonded_id_2, bonded_id_2, nbonded_id, spindle_id, spindle_id_2};
        for (int new_3_id = 0; new_3_id < nsp3a; ++new_3_id ){ //iterate over all sp3a rings
            int *new_3_cluster = hcsp3a[new_3_id];
            //printf("12P %i %i \n",bonded_id,nbonded_id);
            //printf("3 ring %i %i %i\n",new_3_cluster[0], new_3_cluster[1], new_3_cluster[2]);
            int rinc = nring_in_cluster(old_12P_cluster, new_3_cluster, 12);
            //printf("n ring in cluster %i \n", rinc);
            if(nring_in_cluster(old_12P_cluster, new_3_cluster, 12) == 2){
                if(nring_bonded_nbonded(bonded_id, nbonded_id, new_3_cluster) == 2){ //two particles in ring are in 6Z
                   int bond_counter = check_ring_bonds(new_3_cluster, arr_6Z);
                    if (bond_counter == 9){
                        int new_part = get_new_particle_P2(new_3_cluster, bonded_id, nbonded_id);
                        if (check_unique13P2(old_12P_cluster, new_part, 13) == 0){
                            add_13P2(bonded_id, nbonded_id_2, bonded_id_2, nbonded_id,spindle_id, spindle_id_2, final_part1, final_part2, final_part3, final_part4, final_part5, final_part6, new_part);
                            }
                        }
                    }
                }
            }
        }
    } 
} 


void add_13P2(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int final_part3, int final_part4, int final_part5, int final_part6, int new_particle) {
    int clusSize = 13;
    if (n13P2 == m13P2) {
        hc13P2 = resize_2D_int(hc13P2, m13P2, m13P2 + incrStatic, clusSize, -1);
        m13P2 = m13P2 + incrStatic;
    }
    hc13P2[n13P2][0] = bonded_id;
    hc13P2[n13P2][1] = nbonded_id_2;
    hc13P2[n13P2][2] = bonded_id_2;
    hc13P2[n13P2][3] = nbonded_id_2;
    hc13P2[n13P2][4] = spindle_id;
    hc13P2[n13P2][5] = spindle_id_2;
    hc13P2[n13P2][6] = final_part1;
    hc13P2[n13P2][7] = final_part2;
    hc13P2[n13P2][8] = final_part3;
    hc13P2[n13P2][9] = final_part4;
    hc13P2[n13P2][10] = final_part5;
    hc13P2[n13P2][11] = final_part6;
    hc13P2[n13P2][12] = new_particle;

    for (int i = 0; i < 12; ++i) {
       s13P2[hc13P2[n13P2][i]] = 'B';
    }
    ++n13P2;
}

int check_unique13P2(const int *old_clust, int new_particle, int new_clust_size){
    int u;
    for (int old_13P2_id = 0; old_13P2_id < n13P2; ++old_13P2_id) {
        u = 0;
        for (int q = 0; q<new_clust_size; ++q){
            for (int r = 0; r<12; ++r){
                if(hc13P2[old_13P2_id][q] == old_clust[r]){
                    u += 1;
                }
            }

        }
        for (int p = 0; p<new_clust_size; ++p){
            if(hc13P2[old_13P2_id][p] == new_particle){
                    u += 1;
                }
        }
    if(u == new_clust_size){
        return 1;            
    }
    }
    return 0;
}