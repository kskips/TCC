#include <globals.h>
#include <tools.h>
#include "8P.h"
#include "7T.h"
//!  A 7T is made of a 7T cluster with an additional particle.
/*!
*  Find 7Ta and 7Ts clusters
*  7T is made made of a 7T cluster and a 5A. Depending on where the location of the new 5A spindle,
*  the cluster is either asymmetric (7Ta) or symmetric (7Ts)
*  7T:
*  - The 5A has one spindle common with the common ring particles of the 6A
*  - For 7Ts the other 5A spindle is bonded to both 7T bonded spindles
*  - For 7TA the other 5A spindle is bonded to one bonded 7T spindle and one unbonded 7T spindle
*
*  Cluster output: BBBBBBB
*  Storage order: original 7T particles x 6, new 5A spindle)
*/

void Clusters_Get8P() {
    for (int old_7T_id = 0; old_7T_id < n7T_a; ++old_7T_id) {
        int *old_7T_cluster = hc7T_a[old_7T_id];
        int get_6Z[2][6];
        get_6Z[0][0] = 0;
        get_6Z[0][1] = 1;
        get_6Z[0][2] = 2;
        get_6Z[0][3] = 3;
        get_6Z[0][4] = 4;
        get_6Z[0][5] = 5;

        get_6Z[1][0] = 3;
        get_6Z[1][1] = 2;
        get_6Z[1][2] = 4;
        get_6Z[1][3] = 6;
        get_6Z[1][4] = 5;
        get_6Z[1][5] = 0;
        int clust_6Z[6];
        for (int spindle_iter = 0; spindle_iter <2; ++spindle_iter){
            clust_6Z[0] = old_7T_cluster[get_6Z[spindle_iter][0]];
            clust_6Z[1] = old_7T_cluster[get_6Z[spindle_iter][1]];
            clust_6Z[2] = old_7T_cluster[get_6Z[spindle_iter][2]];
            clust_6Z[3] = old_7T_cluster[get_6Z[spindle_iter][3]];
            clust_6Z[4] = old_7T_cluster[get_6Z[spindle_iter][4]];
            clust_6Z[5] = old_7T_cluster[get_6Z[spindle_iter][5]];
        for (int spindle_pointer = 4; spindle_pointer < 6; ++spindle_pointer) {
            int spindle_id = clust_6Z[spindle_pointer];
           // printf("%i %i %i \n", spindles_7T[spindle_iter][spindle_pointer],spindle_id, mem_sp3c[spindle_id]);
            for (int new_5A_pointer = 0; new_5A_pointer < nmem_sp3c[spindle_id]; ++new_5A_pointer) {
                int new_5A_id = mem_sp3c[spindle_id][new_5A_pointer];
                int *new_5A_cluster = hcsp3c[new_5A_id];
                if (is_particle_spindle_of_5A(spindle_id, new_5A_cluster) == 1) {
                    int new_particle_id = get_new_particle(new_5A_cluster, spindle_id);
                    if(crossover_part_8P(old_7T_cluster, new_particle_id) == 0){
                        //if(check_ring_bonds_8P(new_5A_cluster, old_7T_cluster)== 22|| check_ring_bonds_8P(new_5A_cluster, old_7T_cluster)== 25){

                        int bond_counter = check_ring_bonds8P(new_5A_cluster, clust_6Z);
                        if (bond_counter == 22|| bond_counter ==25){
                            if (check_unique(old_7T_cluster, new_particle_id) == 0){
                                //printf("bo0op %i %i %i\n", spindle_iter,spindle_pointer, spindle_id);
                                //printf("8P %i %i %i %i %i %i %i %i \n",old_7T_cluster[0], old_7T_cluster[1],old_7T_cluster[2],old_7T_cluster[3],old_7T_cluster[4],old_7T_cluster[5],old_7T_cluster[6],new_particle_id );
                            add_8P(old_7T_cluster, new_particle_id);
                            }
                        }
                        
                        //}
                        
                    }
                    }
                }
            }            
        }

        }
    }
int crossover_spiral(const int *clust_1, const int *clust_2){
    int s1 = sizeof(clust_1);
    int cross_count =0; 
    for(int m=0; m<6; ++m){
        for(int n=0; n<s1; ++n){
        if(clust_1[n]==clust_2[m]){
            cross_count += 1;
        }
    }
    }
    printf("cross count %i \n", cross_count);
    return cross_count;
}

int crossover_part_8P(const int *clust_1, int particle){
    int s1 = 7;
    int cross_count =0; 
    printf("crossover %i \n", s1);
    for(int n=0; n<s1; ++n){
        if(clust_1[n]==particle){
            cross_count += 1;
        }
    }
    return cross_count;
}

void add_8P(const int *old_7T, int new_particle) {
    int clusSize = 8;
    if (n8P == m8P) {
        hc8P = resize_2D_int(hc8P, m8P, m8P + incrStatic, clusSize, -1);
        m8P = m8P + incrStatic;
    }
    hc8P[n8P][0] = old_7T[0];
    hc8P[n8P][1] = old_7T[1];
    hc8P[n8P][2] = old_7T[2];
    hc8P[n8P][3] = old_7T[3];
    hc8P[n8P][4] = old_7T[4];
    hc8P[n8P][5] = old_7T[5];
    hc8P[n8P][6] = old_7T[6];
    hc8P[n8P][7] = new_particle;

    for (int i = 0; i < 8; ++i) {
        s8P[hc8P[n8P][i]] = 'B';
    }
    ++n8P;
}

int check_ring_bonds_8P(const int *new_5A_cluster, const int *old_7T_cluster) {
    int bond_counter = 0;

    for (int ring_pointer = 0; ring_pointer < 3; ++ring_pointer) {
        printf("ring bonds %i %i %i %i %i %i %i %i %i\n",ring_pointer, new_5A_cluster[ring_pointer],old_7T_cluster[0],old_7T_cluster[1],old_7T_cluster[2],old_7T_cluster[3],old_7T_cluster[4],old_7T_cluster[5],old_7T_cluster[6]);
        if (new_5A_cluster[ring_pointer] == old_7T_cluster[0]) {
            if (new_5A_cluster[ring_pointer] == old_7T_cluster[1]) {
                if (new_5A_cluster[ring_pointer] == old_7T_cluster[6]) {
                   return 1; 
                }
            }
        
        }
        if (new_5A_cluster[ring_pointer] == old_7T_cluster[2]) {
            if (new_5A_cluster[ring_pointer] == old_7T_cluster[3]) {
                if (new_5A_cluster[ring_pointer] == old_7T_cluster[6]) {
                    return 1;
                }
            }  
        }
    }
    return 0;
}

int get_new_particle_8P(const int *new_5A_cluster, int spindle_id) {
    if (new_5A_cluster[3] == spindle_id) {
        //printf("5A %i\n", new_5A_cluster[3]);
        return new_5A_cluster[4];
    }
    else if (new_5A_cluster[4] == spindle_id) {
        return new_5A_cluster[3];
    }
    else {
        Error("New spindle not found.");
        return 0;
    }
}

int check_ring_bonds8P(const int *new_5A_cluster, const int *old_6Z_cluster) {
    int bond_counter = 0;

    for (int ring_pointer = 0; ring_pointer < 3; ++ring_pointer) {
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

int check_ring_bonds8P_2(const int *new_5A_cluster, const int *old_6Z_cluster) {
    int bond_counter = 0;

    for (int ring_pointer = 0; ring_pointer < 3; ++ring_pointer) {
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

int check_unique(const int *old_7T, int new_particle){
    int u;
    for (int old_8P_id = 0; old_8P_id < n8P; ++old_8P_id) {
        u = 0;
        for (int q = 0; q<8; ++q){
            for (int r = 0; r<7; ++r){
                if(hc8P[old_8P_id][q] == old_7T[r]){
                    //printf(" i %i %i %i %i\n",q, r,hc8P[old_8P_id][q],old_7T[r]);
                    u += 1;
                }
            }

        }
        for (int p = 0; p<8; ++p){
            if(hc8P[old_8P_id][p] == new_particle){
                    u += 1;
                }
        }
   // if(hc8P[old_8P_id][7] == new_particle){
          //      u += 1;
           // }
    if(u == 8){
        return 1;            
    }
    }
    return 0;
}