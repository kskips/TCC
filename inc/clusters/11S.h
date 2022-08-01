#ifndef TCC_11S_H
#define TCC_11S_H

void Clusters_Get11S();
void add_11S(int **clust);
int check_unique_11S(int **clust);
int spindles_11S(int **array, const int *clust1, const int *clust2, const int *clust3);
int shared_ring(int **array, const int *clust1, const int *clust2, const int *clust3);
int shared_ring12(int **array, const int *clust1, const int *clust2, const int *clust3);
int get_final_rings(int **array, const int *clust1, const int *clust2, const int *clust3);
int common_spindle(const int *clust1, const int *clust2, int r1, int r2);
int common_ring(const int *clust1, const int *clust2, int r1, int r2);
int common_rs(const int *clust1, const int *clust2, int r1, int r2);
void change(int **array, const int *clust1, const int *clust2, const int *clust3);
#endif
