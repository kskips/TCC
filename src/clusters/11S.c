#include <globals.h>
#include <tools.h>
#include "11S.h"
#include "8PAB.h"
#include "7PAB.h"
#include "9S.h"
#include "7T.h"
//!  A 11S is a made of three intersectiing 7A clusters
/*!
* The central 7A shares a spindle particle with each of the other two: s1, s2
* The other spindle of each outer 7A is a ring if the central 7A: s3, s4
* There is one common ring cr1 shared between the three 7As
* each outer 7A shares one ring with the central one: cr2, cr3
* the outer 7As have two ring particles not shared by the other 7As: r1, r2, r3, r4
* storage order: s1, s2, s3, s4, cr1, cr2, cr3, r1, r2, r3, r4
*/

void Clusters_Get11S() {
    int new_part;
    for (int first_7A_id = 0; first_7A_id < nsp5c; ++first_7A_id) {
        int *first_7A_cluster = hcsp5c[first_7A_id];
            for (int second_7A_id = 0; second_7A_id < nsp5c; ++second_7A_id) {
                if(second_7A_id != first_7A_id){
                    int *second_7A_cluster = hcsp5c[second_7A_id];
                        for (int third_7A_id = 0; third_7A_id < nsp5c; ++third_7A_id) {
                            if(third_7A_id != second_7A_id && third_7A_id != first_7A_id){
                                int *third_7A_cluster = hcsp5c[third_7A_id];
                                //int *array;
                                int *array = malloc(11 * sizeof(int));
                                printf("%i %i \n", first_7A_cluster[5], first_7A_cluster[6]);
                                printf("%i %i \n", second_7A_cluster[5], second_7A_cluster[6]);
                                printf("%i %i \n", third_7A_cluster[5], third_7A_cluster[6]);
                                printf("\n");
                                if(spindles_11S(&array, first_7A_cluster, second_7A_cluster, third_7A_cluster) == 1){
                                    if(shared_ring(&array, first_7A_cluster, second_7A_cluster, third_7A_cluster) == 1){
                                        if(shared_ring12(&array, first_7A_cluster, second_7A_cluster, third_7A_cluster) == 1){
                                            if(get_final_rings(&array, first_7A_cluster, second_7A_cluster, third_7A_cluster) == 1){
                                                if(check_unique_11S(&array)== 0){
                                                    //printf("%i %i %i %i %i\n",array[0], array[1], array[2], array[3], array[4]);
                                                    add_11S(&array);
                                                    free(array);
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

int spindles_11S(int **array, const int *clust1, const int *clust2, const int *clust3){ //check that the 6 spindles have the right overlaps
    int spindles_1[2] = {clust1[5], clust1[6]};
    int spindles_2[2] = {clust2[5], clust2[6]};
    int spindles_3[2] = {clust3[5], clust3[6]};
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 2; ++j){
            if(spindles_1[i] == spindles_2[j]){
                for(int k = 0; k < 2; ++k){
                    int idx = abs(i-1);
                    if(spindles_3[k] == spindles_1[idx]){
                        int idx2 = abs(k-1); 
                        printf("ij %i %i\n", i, j);
                            if(spindles_2[abs(j-1)] != spindles_3[abs(k-1)]){
                                (*array)[0] = spindles_1[0];
                                (*array)[1] = spindles_1[1];
                                (*array)[2] = spindles_2[abs(j-1)];
                                (*array)[3] = spindles_3[abs(k-1)]; 
                                return 1;                           
                        }
                    }
                }
            }
        }
        
    }
    return 0;
}

int shared_ring(int **array, const int *clust1, const int *clust2, const int *clust3){
    //*array = malloc(11 * sizeof(int));
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            for(int k = 0; k < 5; ++k){
                if(clust1[i] == clust2[j] && clust1[i] == clust3[k]){
                    for( int m = 0; m < 4; ++m){
                        if ((*array)[m] == clust1[i]){
                            return 0;
                        }
                    }
                    (*array)[4] = clust1[i];
                    return 1;    
                }
            }
        }
    }
    return 0;
}

int shared_ring12(int **array, const int *clust1, const int *clust2, const int *clust3){
    //*array = malloc(11 * sizeof(int));
    int count = 0;
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j){
            if(clust1[i] == clust2[j]){
                if(clust2[j] != (*array)[4]){
                    (*array)[5] = clust1[i];
                    count +=1;
                }
            }
        }
    }
    if(count == 1){
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 4; ++j){
                if(clust1[i] == clust3[j]){
                    if(clust2[j] != (*array)[4]){
                        (*array)[6] = clust1[i];
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int get_final_rings(int **array, const int *clust1, const int *clust2, const int *clust3){
    //*array = malloc(11 * sizeof(int));
    int index = 7;
    int count;
    for(int i = 0; i < 5; ++i){
        count = 0;
        for(int j = 0; j < index; ++j){
            if(clust2[i] == (*array)[j]){
                count +=1;
            }
        }
        if(count == 0){
            (*array)[index] = clust2[i];
            index += 1;
        }
    }
    if (index == 9){
        for(int i = 0; i < 5; ++i){
            count = 0;
            for(int j = 0; j < index; ++j){
                if(clust3[i] == (*array)[j]){
                    count +=1;
                }
            }
            if(count == 0){
                (*array)[index] = clust3[i];
                index += 1;
            }
        }
    }
    if(index == 11){
        return 1;
    }
    else{
        return 0;
    }
}

void change(int **array, const int *clust1, const int *clust2, const int *clust3)
{
    int count;
    //*array = malloc(11 * sizeof(int));
    if (*array == NULL){
        return;
    }
    for (int i = 0 ; i < 7 ; i++){
        (*array)[i] = clust1[i];
        }
    for (int i = 7 ; i < 11 ; i++){
        (*array)[i] = 0;
        }
    int index = 7;
    for(int j = 0; j < 7; ++j){
        count = 0;
        for(int k = 0; k < 7; ++ k){
            if((*array)[k] == clust2[j]){
                count += 1;
            }
        }
        if(count == 0){
                (*array)[index] = clust2[j];
                index += 1;
            }
    }
    int index2 = index;
    for(int j = 0; j < 7; ++j){
        count = 0;
        for(int k = 0; k < index; ++ k){
            if((*array)[k] == clust3[j]){
                count += 1;
            }
        }
            if(count == 0){
                (*array)[index2] = clust3[j];
                index2 += 1;
            }
    }
}

void add_11S(int **clust) {
    int clusSize = 11;
    //printf("new_particle %i\n", new_particle);
    if (n11S == m11S) {
        hc11S = resize_2D_int(hc11S, m11S, m11S + incrStatic, clusSize, -1);
        m11S = m11S + incrStatic;
    }
    hc11S[n11S][0] = (*clust)[0];
    hc11S[n11S][1] = (*clust)[1];
    hc11S[n11S][2] = (*clust)[2];
    hc11S[n11S][3] = (*clust)[3];
    hc11S[n11S][4] = (*clust)[4];
    hc11S[n11S][5] = (*clust)[5];
    hc11S[n11S][6] = (*clust)[6];
    hc11S[n11S][7] = (*clust)[7];
    hc11S[n11S][8] = (*clust)[8];
    hc11S[n11S][9] = (*clust)[9];
    hc11S[n11S][10] = (*clust)[10];

    for (int i = 0; i < 10; ++i) {
        s11S[hc11S[n11S][i]] = 'B';
    }
    ++n11S;
}

int common_spindle(const int *clust1, const int *clust2, int r1, int r2){
    int count = 0;
    for(int i = r1; i < r1 + 2; ++i){
        for(int j = r2; j < r2 + 2; ++j){
            if(clust1[i] == clust2[j]){
                count += 1;
            }
        }
    }
    return count;
}

int common_ring(const int *clust1, const int *clust2, int r1, int r2){
    int count = 0;
    for(int i = 0; i < r1; ++i){
        for(int j = 0; j < r2; ++j){
            if(clust1[i] == clust2[j]){
                count += 1;
            }
        }
    }
    return count;
}

int common_rs(const int *clust1, const int *clust2, int r1, int r2){
    int count = 0;
    for(int i = r1; i < r1+2; ++i){
        for(int j = 0; j < r2; ++j){
            if(clust1[i] == clust2[j]){
                count += 1;
            }
        }
    }
    return count;
}

int check_unique_11S(int **clust){
    int u;
    for (int old_11S_id = 0; old_11S_id < n11S; ++old_11S_id) {
        u = 0;
        for (int q = 0; q < 11; ++q){
            for (int r = 0; r < 11; ++r){
                if(hc11S[old_11S_id][r] == (*clust)[q]){
                    u += 1;
                }
            }

        }
    if(u == 11){
        return 1;            
    }
    }
    return 0;
}