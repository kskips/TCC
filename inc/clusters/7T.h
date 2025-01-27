#ifndef TCC_7T_H
#define TCC_7T_H

void Clusters_Get7T();

int is_particle_spindle_of_5A(int particle_id, const int *new_5A_cluster);

int get_new_particle(const int *new_5A_cluster, int spindle_id_2);

int check_ring_bonds(const int *new_5A_cluster, const int *old_6Z_cluster);

void check_7T_type(int bond_counter, const int *old_6Z, int new_particle);

void add_7T_a(const int *old_6Z, int new_particle);

void add_7T_s(const int *old_6Z, int new_particle);

int check_7T_unique(const int *old_6Z_cluster, const int new_particle_id);
int is_particle_ring_of_5A(int particle_id, const int *new_5A_cluster) ;
#endif
