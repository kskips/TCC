#ifndef TCC_11P_H
#define TCC_11P_H

void Clusters_Get11P();
int check_unique11P(const int *old_10P, int new_particle); //Check that we don't already have the cluster stored
void add_11P(const int *old_10P, int new_particle) ;
int check_ring_bonds11P(const int *new_5A_cluster, const int *old_6Z_cluster);
int crossover_part_11P(const int *old_10P_clust, int new_part);
#endif