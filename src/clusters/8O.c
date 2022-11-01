#include <globals.h>
#include <tools.h>
#include "8O.h"
#include "12O.h"

//!  A 8O is a made of two intersecting 6A clusters and 2 4A clusters
// The two 6A clusters share 2 ring particles
// two rings and one spindle of each 6A cluster are in a 4A cluster
// No 4A cluster overlaps with these two 4A clusters


void Clusters_Get8O() {
    int final_part1;
    int final_part2;
    int count1;
    int count2;
    for (int first_6A_id = 0; first_6A_id < nsp4c; ++first_6A_id) {
        int *first_6A_cluster = hcsp4c[first_6A_id];
        for(int first_4A_id = 0; first_4A_id < nsp3b; ++first_4A_id){
            int *first_4A_cluster = hcsp3b[first_4A_id];
            for(int second_4A_id = 0; second_4A_id < nsp3b; ++second_4A_id){
                int *second_4A_cluster = hcsp3b[second_4A_id];
                if(overlap_4A_4A(first_4A_cluster, second_4A_cluster) == 1){
                    if(overlap_6A_4A(first_6A_cluster, first_4A_cluster) == 3){
                        if(overlap_6A_4A(first_6A_cluster, second_4A_cluster) == 3){
                            for(int i = 0; i < 4; ++i){
                                count1 = 0;
                                for(int j = 0; j < 6; ++j){
                                    if(first_6A_cluster[j] == first_4A_cluster[i]){
                                        count1 +=1;
                                    }
                                }
                                if(count1 == 0){
                                    final_part1 = first_4A_cluster[i];
                                }
                            }

                            for(int k = 0; k < 4; ++k){
                                count2 = 0;
                                for(int l = 0; l < 6; ++l){
                                    if(first_6A_cluster[l] == second_4A_cluster[k]){
                                        count2 +=1;
                                    }
                                }
                                if(count2 == 0){
                                    final_part2 = second_4A_cluster[k];
                                }
                            }
                            if(check_unique_8O(first_6A_cluster, final_part1, final_part2) == 0){
                                add_8O(first_6A_cluster, final_part1, final_part2);
                            }
                        }
                    }
                }
            }
        }
    }
    }



int check_unique_8O(const int *old_6A, int final_part1, int final_part2){
    int u;
    for (int old_8O_id = 0; old_8O_id < n8O; ++old_8O_id) {
        u = 0;
        for (int r = 0; r < 8; ++r){
            for (int q = 0; q < 6; ++q){
                if(hc8O[old_8O_id][r] == old_6A[q]){
                    u += 1;
                }
            }

        }
        for (int i = 0; i < 8; ++i){
        if(hc8O[old_8O_id][i] == final_part1){
            u += 1;
        }
        if(hc8O[old_8O_id][i] == final_part2){
            u += 1;
        }
    }
    if(u == 8){
        return 1;           
    }
    }
    return 0;
}

void add_8O(const int *old_6A, int final_part1, int final_part2) {
    int clusSize = 8;
    //printf("new_particle %i\n", new_particle);
    if (n8O == m8O) {
        hc8O = resize_2D_int(hc8O, m8O, m8O + incrStatic, clusSize, -1);
        m8O = m8O + incrStatic;
    }
    hc8O[n8O][0] = old_6A[0];
    hc8O[n8O][1] = old_6A[1];
    hc8O[n8O][2] = old_6A[2];
    hc8O[n8O][3] = old_6A[3];
    hc8O[n8O][4] = old_6A[4];
    hc8O[n8O][5] = old_6A[5];
    hc8O[n8O][6] = final_part2;
    hc8O[n8O][7] = final_part1;

    for (int i = 0; i < 8; ++i) {
        s8O[hc8O[n8O][i]] = 'B';
    }
    ++n8O;
}
