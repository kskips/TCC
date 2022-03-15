#ifndef TCC_11P2_H
#define TCC_11P2_H

void Clusters_Get11P2();
void add_11P2(int bonded_id, int nbonded_id_2, int bonded_id_2, int nbonded_id, int spindle_id, int spindle_id_2, int final_part1, int final_part2, int final_part3, int final_part4, int new_particle) ;
int check_unique11P2(const int *old_clust, int new_particle, int new_clust_size);
#endif