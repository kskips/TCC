#include <globals.h>
#include <tools.h>
#include "9P.h"
#include "8P.h"
#include "7T.h"
//!  A 9P is made of a 8P cluster with an additional particle.
/*!
*  9P is made made of a 8P cluster and a 5A. Depending on where the location of the new 5A spindle,
*  - The 5A has one spindle common with the common ring particles of the 6A
*  - The other 5A spindle is bonded to one bonded 8P spindle and one unbonded 8P spindle
*
*  Cluster output: BBBBBBB
*  Storage order: original 8P particles x 8, new 5A spindle)
*/

void Clusters_Get9P() {
    for (int old_8P_id = 0; old_8P_id < n8P; ++old_8P_id) {
        int *old_8P_cluster = hc8P[old_8P_id];
        for (int old_6Z_id =0; old_6Z_id<n6Z; ++old_6Z_id){
            int *old_6Z_cluster = hc6Z[old_6Z_id];
            if (crossover_spiral(old_8P_cluster,old_6Z_cluster) ==6){
                for (int spindle_pointer = 4; spindle_pointer < 6; ++spindle_pointer) {
                    int spindle_id = old_6Z_cluster[spindle_pointer];
                    for (int new_5A_pointer = 0; new_5A_pointer < nmem_sp3c[spindle_id]; ++new_5A_pointer) {
                        int new_5A_id = mem_sp3c[spindle_id][new_5A_pointer];
                        int *new_5A_cluster = hcsp3c[new_5A_id];
                        if (is_particle_spindle_of_5A(spindle_id, new_5A_cluster) == 1) {
                            int new_particle_id = get_new_particle(new_5A_cluster, spindle_id);
                            if(crossover_part_9P(old_8P_cluster, new_particle_id) == 0){
                                int bond_counter = check_ring_bonds9P(new_5A_cluster, old_6Z_cluster);
                                if (bond_counter == 22|| bond_counter ==25){
                                    if (check_unique9P(old_8P_cluster, new_particle_id) == 0){  
                                        add_9P(old_8P_cluster, new_particle_id);
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

int crossover_part_9P(const int *clust_1, int particle){
    int s1 = 8;
    int cross_count =0; 
    printf("crossover %i \n", s1);
    for(int n=0; n<s1; ++n){
        if(clust_1[n]==particle){
            cross_count += 1;
        }
    }
    return cross_count;
}

int check_unique9P(const int *old_7T, int new_particle){
    int u;
    for (int old_9P_id = 0; old_9P_id < n9P; ++old_9P_id) {
        u = 0;
        for (int q = 0; q<9; ++q){
            for (int r = 0; r<8; ++r){
                if(hc9P[old_9P_id][q] == old_7T[r]){
                    //printf(" i %i %i %i %i\n",q, r,hc8P[old_8P_id][q],old_7T[r]);
                    u += 1;
                }
            }

        }
        for (int p = 0; p<9; ++p){
            if(hc9P[old_9P_id][p] == new_particle){
                    u += 1;
                }
        }
   // if(hc8P[old_8P_id][7] == new_particle){
          //      u += 1;
           // }
    if(u == 9){
        return 1;            
    }
    }
    return 0;
}

void add_9P(const int *old_8P, int new_particle) {
    int clusSize = 9;
    //printf("new_particle %i\n", new_particle);
    if (n9P == m9P) {
        hc9P = resize_2D_int(hc9P, m9P, m9P + incrStatic, clusSize, -1);
        m9P = m9P + incrStatic;
    }
    hc9P[n9P][0] = old_8P[0];
    hc9P[n9P][1] = old_8P[1];
    hc9P[n9P][2] = old_8P[2];
    hc9P[n9P][3] = old_8P[3];
    hc9P[n9P][4] = old_8P[4];
    hc9P[n9P][5] = old_8P[5];
    hc9P[n9P][6] = old_8P[6];
    hc9P[n9P][7] = old_8P[7];
    hc9P[n9P][8] = new_particle;

    for (int i = 0; i < 9; ++i) {
        s9P[hc9P[n9P][i]] = 'B';
    }
    ++n9P;
}

int check_ring_bonds9P(const int *new_5A_cluster, const int *old_6Z_cluster) {
    int bond_counter = 0;

    for (int ring_pointer = 0; ring_pointer < 3; ++ring_pointer) {
       // printf("ring pointer %i %i \n", ring_pointer,new_5A_cluster[ring_pointer] );
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[0]) {
            bond_counter += 1;
            continue;
        }
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[1]) {
            bond_counter += 2;
            continue;
        }
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[2]) {
            bond_counter += 4;
            continue;
        }
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[3]) {
            bond_counter += 8;
            continue;
        }
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[4]) {
            bond_counter += 16;
            continue;
        }
        if (new_5A_cluster[ring_pointer] == old_6Z_cluster[5]) {
            bond_counter += 16;
            continue;
        }
    }
    return bond_counter;
}
