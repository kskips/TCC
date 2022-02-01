#include <globals.h>
#include <tools.h>
#include "9P.h"
#include "7T.h"
#include "8P.h"
#include "10P.h"
//!  A 10P is a 9P with an additional particle
/*!
* A 9P cluster contains two 6Z clusters at the top and bottom of the cluster. 
* A 10P takes these two 6Z clusters and tries to make a 7T from the cluster and an extra particle.
*  Cluster output: BBBBBBBBBB
*  Storage order: original 9P particles x 9, new 5A spindle)
*/

void Clusters_Get10P() {
    for (int old_9P_id = 0; old_9P_id < n9P; ++old_9P_id) {
        int *old_9P_cluster = hc9P[old_9P_id];
        for (int old_6Z_id =0; old_6Z_id<n6Z; ++old_6Z_id){
            int *old_6Z_cluster = hc6Z[old_6Z_id];
            printf("size %li \n", sizeof(old_6Z_cluster));
            if (crossover_spiral(old_9P_cluster,old_6Z_cluster) ==6){
                for (int spindle_pointer = 4; spindle_pointer < 6; ++spindle_pointer) {
                    int spindle_id = old_6Z_cluster[spindle_pointer];
                    for (int new_5A_pointer = 0; new_5A_pointer < nmem_sp3c[spindle_id]; ++new_5A_pointer) {
                        int new_5A_id = mem_sp3c[spindle_id][new_5A_pointer];
                        int *new_5A_cluster = hcsp3c[new_5A_id];
                        if (is_particle_spindle_of_5A(spindle_id, new_5A_cluster) == 1) {
                            int new_particle_id = get_new_particle(new_5A_cluster, spindle_id);
                            if(crossover_part_10P(old_9P_cluster, new_particle_id) == 0){
                                int bond_counter = check_ring_bonds9P(new_5A_cluster, old_6Z_cluster);
                                if (bond_counter == 22|| bond_counter ==25){
                                    if (check_unique10P(old_9P_cluster, new_particle_id) == 0){
                                        
                                        add_10P(old_9P_cluster, new_particle_id);
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

int crossover_part_10P(const int *clust_1, int particle){
    int s1 = 9;
    int cross_count =0; 
    printf("crossover %i \n", s1);
    for(int n=0; n<s1; ++n){
        if(clust_1[n]==particle){
            cross_count += 1;
        }
    }
    return cross_count;
}
int check_unique10P(const int *old_9P, int new_particle){
    int u;
    for (int old_10P_id = 0; old_10P_id < n10P; ++old_10P_id) {
        u = 0;
        for (int q = 0; q<10; ++q){
            for (int r = 0; r<9; ++r){
                if(hc10P[old_10P_id][q] == old_9P[r]){
                    u += 1;
                }
            }

        }
        for (int p = 0; p<10; ++p){
            if(hc9P[old_10P_id][p] == new_particle){
                    u += 1;
                }
        }

    if(u == 10){
        return 1;            
    }
    }
    return 0;
}

void add_10P(const int *old_9P, int new_particle) {
    int clusSize = 10;
    //printf("new_particle %i\n", new_particle);
    if (n10P == m10P) {
        hc10P = resize_2D_int(hc10P, m10P, m10P + incrStatic, clusSize, -1);
        m10P = m10P + incrStatic;
    }
    hc10P[n10P][0] = old_9P[0];
    hc10P[n10P][1] = old_9P[1];
    hc10P[n10P][2] = old_9P[2];
    hc10P[n10P][3] = old_9P[3];
    hc10P[n10P][4] = old_9P[4];
    hc10P[n10P][5] = old_9P[5];
    hc10P[n10P][6] = old_9P[6];
    hc10P[n10P][7] = old_9P[7];
    hc10P[n10P][8] = old_9P[8];
    hc10P[n10P][9] = new_particle;

    for (int i = 0; i < 10; ++i) {
        s10P[hc10P[n10P][i]] = 'B';
    }
    ++n10P;
}

int check_ring_bonds10P(const int *new_5A_cluster, const int *old_6Z_cluster) {
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
