#ifndef TCC_12S_H
#define TCC_12S_H

void Clusters_Get12S();
int check_unique_12S(int *old_11S_cluster2, int final_part);
void add_12S(int *old_11S_cluster2, int final_part);
int get_final_part12S(int *old_11S_cluster1, int *old_11S_cluster2);
int check_rings_11A(int *old_11S_cluster1, int *old_11S_cluster2);
int check_central_7A(int *old_11S_cluster1, int *old_11S_cluster2);
#endif