#ifndef GLOBALS_H
#define GLOBALS_H

#define EPS 0.000001

#include <stdio.h>
#include <stdlib.h>

int box_type;                    //if the system in non-cubic or NPT, get box size info from a datafile
int frames_to_analyse;           // frames to read from input xmol file
int num_cluster_types;           // The number of items in the cluster names array

extern int cluster_size[];        // A list of the number of particles in each cluster type
extern char* cluster_names[];     // A list of strings of cluster names
extern int* do_cluster_list[];    // A list of pointers to the do_clusts variables
extern int* num_cluster_list[];   // A list of pointers to the nclusts variables
extern char** raw_list[];         // A list of pointers to the "s" raw storage variables
extern int*** cluster_list[];     // A list of pointers to the "hc" cluster storage variables
extern int* cluster_list_width[]; // A list of pointers to the "m" storage width variables


struct xyz_info {
    long total_frames;
    long max_frames;
    long *num_particles;
    long *frame_offsets;
};

char *fXmolName, *fBoxSizeName; //Name of xyz file, name of file which contains info on box
long box_offsets[1000];          // Offsets of each line in the box file
double *x, *y, *z;              // positions in x y and z directions of N particles
int *particle_type;             // species of particle, index is particle number

double rcutAA,rcutAA2,rcutAB,rcutAB2,rcutBB,rcutBB2;    // diameters of AB and BB interactions for binary interactions
double min_cutAA, min_cutAA2;
double fc;                  // Voronoi adjustment parameter
int use_voronoi_bonds;      // 0 use simple bond length method build_bond_network(), 1 use Voronoi method Get_Bonds_With_Voronoi()
int PBCs;                   // 0 do not impliment periodic boundary conditions, 1 implement periodic boundary conditions
int max_num_bonds;          // max number of bonds per particle
int use_cell_list;          // 0  do not use cell list, 1 use cell list
int analyse_all_clusters;   // 0 Read clusters to analyse from file, 1 analyse all clusters

int doWriteBonds;   // write bonds files out
int doWriteClus;    // write out indices of each detected cluster
int doWriteRaw; // write raw_*** cluster xmol files out
int do11AcenXyz; // write centres of 11A
int do13AcenXyz; // write centres of 13A
int eleven_A_number; // The location of the 11A cluster in the cluster list
int thirteen_A_number;
int doWritePopPerFrame; // write pop_per_frame file
int doWriteXYZ; // Write clusters as XYZ file

int incrStatic; // when full, increment cluster arrays by this amount

// Lists of particle population of each cluster type in each frame, index i is the frame number,
// index j is the cluster type
double **pop_per_frame;

// The average population of each cluster type over all frames, index i is cluster type
double *mean_pop_per_frame;

// Gross number of particles in the specified cluster type accumulated over all frames
int *num_gross_particles;

// Total number of clusters of the specified type accumulated over all frames
int *total_clusters;

// Per frame variables

// Box and bond variables

double sidex, sidey, sidez, half_sidex, half_sidey, half_sidez;
double tiltxy,tiltxz,tiltyz;
long particles_in_current_frame;

int *num_bonds;                                       // Current Number of Bonds for particles {1,...,N}
int **bond_list;                                      // list of particles (indices j) bonded to particle at index i
double **squared_bondlengths;                         // length of bonds in the bond network and squared
int maxnb;                                            // max number of bonds to one particle
int correctedBonds;                                   // bonds adjusted due to voronoi assymetry

int num_sort_columns;                                 // Number of columns to iterate over with quicksort

int n_cells_x, n_cells_y, n_cells_z, n_cells_total;   // number of cells per box length, total number of cells
int *head;                                            // head of cell array
int *linked_list;                                     // linked list array
double cell_len_x, cell_len_y, cell_len_z;

// Cluster variables

// Whether to perform analysis of this type of cluster
int dosp3, dosp3a, dosp3b, dosp3c;
int dosp4, dosp4a, dosp4b, dosp4c;
int dosp5, dosp5a, dosp5b, dosp5c;
int do6A, do6Z, do7K, do7T_a, do7T_s, do7PAB;
int do8PAA, do8A, do8B, do8K, do8PAB, do8PBB, do8O, do8MW;
int do9A, do9B, do9K, do9PAA, do9PAB, do9PBB, do9S;
int do10A, do10B, do10K, do10W, do10PAA, do10PAB, do10PBB, do10S, do10O;
int do11A, do11B, do11C, do11E, do11F, do11W, do11PAA, do11PAB, do11PBB, do11S, do11SB, do11O;
int do12A, do12B, do12D, do12E, do12K, do12PAA, do12PAB, do12PBB, do12S, do12SB,do12O;
int do13A, do13B, do13K, do13PAA, do13PAB, do13PBB, do13S, do13SB;
int do14O, doFCC, doHCP, doBCC9;

// number of clusters of particlar type in current frame
int nsp3a, nsp3b, nsp3c;
int nsp4a, nsp4b, nsp4c;
int nsp5a, nsp5b, nsp5c;
int n6A, n6Z, n7K, n7T_a, n7T_s, n7PAB;
int n8PAA, n8A, n8B, n8K, n8PBB, n8PAB, n8O, n8MW;
int n9A, n9B, n9K, n9PAA, n9PBB, n9PAB, n9S;
int n10A, n10B, n10K, n10W,n10PAA, n10PAB, n10PBB, n10S, n10O;
int n11A, n11B, n11C, n11E, n11F, n11W,n11PAA, n11PAB, n11PBB, n11S, n11SB, n11O;
int n12A, n12B, n12D, n12E, n12K, n12PAA, n12PBB, n12PAB, n12S, n12SB, n12O;
int n13A, n13B, n13K, n13PBB, n13PAB, n13PAA, n13S, n13SB;
int n14O,nFCC, nHCP, nBCC_9;

// max size of cluster storage arrays in dimension i
int msp3a, msp3b, msp3c;
int msp4a, msp4b, msp4c;
int msp5a, msp5b, msp5c;
int m6A, m6Z, m7K, m7T_a, m7T_s, m7PAB;
int m8PAA, m8A, m8B, m8K, m8PBB, m8PAB, m8O, m8MW;
int m9A, m9B, m9K, m9PAA, m9PBB, m9PAB, m9S;
int m10A, m10B, m10K, m10W, m10PAA, m10PAB, m10PBB, m10S, m10O;
int m11A, m11B, m11C, m11E, m11F, m11W, m11PAA, m11PAB, m11PBB, m11S, m11SB, m11O;
int m12A, m12B, m12D, m12E, m12K, m12PAA, m12PBB, m12PAB, m12S, m12SB,m12O;
int m13A, m13B, m13K, m13PBB, m13PAB, m13PAA, m13S, m13SB;
int m14O,mFCC, mHCP, mBCC_9;

// cluster storage arrays (index i denotes number/identifier of cluster, j lists particles in cluster)
int **hcsp3a, **hcsp3b, **hcsp3c;
int **hcsp4a, **hcsp4b, **hcsp4c;
int **hcsp5a, **hcsp5b, **hcsp5c;
int **hc6A, **hc6Z, **hc7K, **hc7T_a, **hc7T_s, **hc7PAB;
int **hc8PAA, **hc8A, **hc8B, **hc8K, **hc8PBB, **hc8PAB, **hc8O, **hc8MW;
int **hc9A, **hc9B, **hc9K, **hc9PAA, **hc9PBB, **hc9PAB, **hc9S;
int **hc10A, **hc10B, **hc10K, **hc10W, **hc10PAA, **hc10PAB, **hc10PBB, **hc10S, **hc10O;
int **hc11A, **hc11B, **hc11C, **hc11E, **hc11F, **hc11W, **hc11PAA, **hc11PAB, **hc11PBB, **hc11S, **hc11SB, **hc11O;
int **hc12A, **hc12B, **hc12D, **hc12E, **hc12K, **hc12PAA, **hc12PBB, **hc12PAB, **hc12S, **hc12SB,**hc12O;
int **hc13A, **hc13B, **hc13K, **hc13PBB, **hc13PAB, **hc13PAA, **hc13S, **hc13SB;
int **hc14O,**hcFCC, **hcHCP, **hcBCC_9;

// Raw lists of particle identity, output to RAW_clust files and reset each frame
char *ssp3a, *ssp3b, *ssp3c;
char *ssp4a, *ssp4b, *ssp4c;
char *ssp5a, *ssp5b, *ssp5c;
char *s6A, *s6Z, *s7K, *s7T_a, *s7T_s, *s7PAB;
char *s8PAA, *s8A, *s8B, *s8K, *s8PBB, *s8PAB, *s8O, *s8MW;
char *s9A, *s9B, *s9K,*s9PAA, *s9PBB, *s9PAB, *s9S;
char *s10A, *s10B, *s10K, *s10W, *s10PAA, *s10PAB, *s10PBB, *s10S, *s10O;
char *s11A, *s11B, *s11C, *s11E, *s11F, *s11W, *s11PAA, *s11PAB, *s11PBB, *s11S, *s11SB, *s11O;
char *s12A, *s12B, *s12D, *s12E, *s12K, *s12PAA, *s12PBB, *s12PAB, *s12S, *s12SB,*s12O;
char *s13A, *s13B, *s13K, *s13PBB, *s13PAB, *s13PAA, *s13S, *s13SB;
char *s14O, *sFCC, *sHCP, *sBCC_9;

// mem lists the clusters of that type each particle is in, index i is the particle index, j is the cluster id
// nmem lists the number of clusters of that type each particle is in, index i is the number of particles
// mmem lists the width of mem, the maximum number of clusters of the specified type associated with a single particle (the largest value in nmem)
int **mem_sp3b, *nmem_sp3b, mmem_sp3b;
int **mem_sp3c, *nmem_sp3c, mmem_sp3c;
int **mem_sp4b, *nmem_sp4b, mmem_sp4b;
int **mem_sp4c, *nmem_sp4c, mmem_sp4c;
int **mem_sp5b, *nmem_sp5b, mmem_sp5b;
int **mem_sp5c, *nmem_sp5c, mmem_sp5c;

#endif
