
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;


// number of components
static int NC = 2;

// number of stations
static int NS = 20;

// number of time samples
static int NT = 950;

// number of Green's functions per component
static int NF = 6;

// number of time shift groups
static int NG = 2;

// number of depths
static int ND = 1;

// number of moment tensors
static int NM = 50000;


static int min_shift = -100;
static int max_shift =  100;

// length of padding
int NP = max_shift - min_shift + 1;

// length of padded records
int NTP = NT + max_shift - min_shift + 1;



void get_synthetics(double greens[], double synthetics[], double mt[]) {
    int i,j;
    // computes synthetics through linear combination of Green's functions

    for (j=0 ; j<NC*NS*NTP; j++) { 
        synthetics[j] = 0.;
    }

    for (i=0 ; i<NF; i++) {
        for (j=0 ; j<NC*NS*NTP; j++) {
            synthetics[j] += greens[i*NC*NS*NTP + j] * mt[i];
        }
    }
}



void get_shifts(double corr[], double corr_sum[], double corr_max[], int corr_argmax[], double mt[], int shifts[], int is_component_in_group[], int component_to_group[]) {
    // gets time shifts between the given data and synthetics corresponding to 
    // the given source

    // this implementation is very flexible with regard to whether 
    // time shifts are fixed or vary


    int i,j,k,l;
    int i0;

    for (j=0 ; j<NG*NS*NP; j++) {
        corr_sum[j] = 0.;
    }

    for (j=0 ; j<NG*NS; j++) {
        corr_max[j] = 0.;
    }

    // compute cross correlations
    for (i=0; i<NF; i++) {
        for (j=0; j<NG; j++) {
            for (k=0; k<NC; k++) {
                if (is_component_in_group[j*NC + k]==1) {
                    continue;
                }
                for (l=0; l<NS*NP; l++) {
                    corr_sum[i*NC*NS*NP + j*NC*NS + l] +=
                        corr[i*NC*NS*NP + k*NC*NS + l] * mt[i];
                }
            }
        }
    }

    // which offset has the largest correlation?
    for (i=0; i<NG*NS; i++) {
        for (j=0; j<NP; j++) {
            if (corr_max[i] < corr_sum[i*NP + j]) {
                corr_max[i] = corr_sum[i*NP + j];
                corr_argmax[i] = i*NP + j;
            }
        }
    }

    // fill in components
    for (i=0; i<NC; i++) {
        i0 = component_to_group[i];
        for (j=0; j<NS; j++) {
            shifts[i*NS + j] = corr_argmax[i0*NS + j];
        }
    }

}



double L1(double data[], double synthetics[], int mask[], int shifts[]) {
    // evaluates L1 misfit between data and shifted synthetics

    int i,j;
    int j0;
    double sum_misfit = 0.;

    for (i=0 ; i<NC*NS; i++) {
        // skip missing components
        if (mask[i]==0) {
            continue;
        }
        j0 = shifts[i];
        for (j=0 ; j<NT; j++) {
            sum_misfit += mask[i*NT + j] * abs(
                data[i*NT + j] - synthetics[i*NT + j+j0]);
        }
    }
}


int main() {

    double *data;
    double *synthetics;

    int *mask;

    double *greens;
    double *corr;
    double *corr_sum;
    double *corr_max;
    int *corr_argmax;

    double *mt;
    double *results;

    int *component_to_group;
    int *is_component_in_group;
    int *shifts;


    data = new double [NC*NS*NT];
    synthetics = new double [NC*NS*NTP];

    mask = new int [NC*NS];

    greens = new double [NF*NC*NS*NTP];
    corr = new double [NF*NC*NS*NP];
    corr_sum = new double [NG*NS*NP];
    corr_max = new double [NG*NS];
    corr_argmax = new int [NG*NS];

    is_component_in_group = new int [NG*NC]();
    component_to_group = new int [NC]();
    shifts = new int [NC*NS]();

    mt = new double [NF*NM];
    results = new double [NM];


    // populate arrays
    for (int i=0; i<NC*NS; i++) {
        mask[i] = 1;
    }

    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();


    for (int i=0; i<NM; i++) {
        //cout << "i: " << i << endl;

        // compute shifted synthetics
        get_synthetics(greens, synthetics, &mt[i]);

        get_shifts(corr, corr_sum, corr_max, corr_argmax, &mt[i],
            shifts, is_component_in_group, component_to_group);

        // evaluate misfit
        results[i] = L1(data, synthetics, mask, shifts);

    }

    // stop timer
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"elapsed time: "<< duration <<'\n';


    return 0; 

}

