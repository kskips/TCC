#ifndef TCC_10P_H
#define TCC_10P_H

void Clusters_Get10P();
int check_unique10P(const int *old_9P, int new_particle); //Check that we don't already have the cluster stored
void add_10P(const int *old_9P, int new_particle) ;
int check_ring_bonds10P(const int *new_5A_cluster, const int *old_6Z_cluster);
int crossover_part_10P(const int *old_9P_clust, int new_part);
#endif