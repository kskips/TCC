#ifndef TCC_9P_H
#define TCC_9P_H

void Clusters_Get9P();
int check_unique9P(const int *old_8P, int new_particle); //Check that we don't already have the cluster stored
void add_9P(const int *old_8P, int new_particle) ;
int check_ring_bonds9P(const int *new_5A_cluster, const int *old_6Z_cluster);
int crossover_part_9P(const int *old_8P_clust, int new_part);
#endif