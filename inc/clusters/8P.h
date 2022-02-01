#ifndef TCC_8P_H
#define TCC_8P_H

void Clusters_Get8P();
void add_8P(const int *old_6Z, int new_particle);
int check_ring_bonds8P(const int *new_5A_cluster, const int *old_7T_cluster);
int check_ring_bonds8P_2(const int *new_5A_cluster, const int *old_7T_cluster);
int get_new_particle_8P(const int *new_5A_cluster, int spindle_id); 
int crossover_part_8P(const int *old_7T_clust, int new_part);
int crossover_spiral_8P(const int *clust_1, const int *clust_2);
int check_unique(const int *old_7T, int new_particle);
#endif
