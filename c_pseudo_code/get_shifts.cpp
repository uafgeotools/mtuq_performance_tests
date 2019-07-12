
void get_shifts_bw(double corr[], double corr_sum[], int shifts[], double mt[]) {
    int i,j,k;
    int j0;
    double corr_max;

    for (j=0 ; j<NS*NP; j++) {
        corr_sum[j] = 0.;
    }

    for (i=0; i<NG; i++) {
        for (j=0; j<2; j++) {
            for (k=0; k<NS*NP; k++) {
                corr_sum[k] += corr[i*NC*NS*NP + j*NC*NS + k] * mt[i];
            }
        }
    }

    for (i=0; i<NS; i++) {
        for (j=0; j<NP; j++) {
            if (corr_max < corr_sum[i*NP + j]) {
                corr_max = corr_sum[i*NP + j];
                j0 = j;
            }
            shifts[i] = j0;
            shifts[i+NS] = j0;
        }
    }
}



void get_shifts_sw(double corr[], double corr_sum[], int shifts[], double mt[]) {
    int i,j,k;
    int j0;
    double corr_max;

    for (j=0 ; j<2*NS*NP; j++) {
        corr_sum[j] = 0.;
    }

    for (i=0; i<NG; i++) {
        // component Z,R
        for (j=0; j<2; j++) {
            for (k=0; k<NS*NP; k++) {
                corr_sum[k] += corr[i*NC*NS*NP j*NS*NP + k] * mt[i];
            }
        }
        // component T
        j = 3
        for (k=2*NS*NP; k<3*NS*NP; k++) {
            corr_sum[j*NS*NP + k] += corr[i*NC*NS*NP + k] * mt[i];
        }
    }

    for (i=0; i<2*NS; i++) {
        for (j=0; j<NP; j++) {
            if (corr_max < corr_sum[i*NP + j]) {
                corr_max = corr_sum[i*NP + j];
                j0 = j;
            }
            shifts[i] = j0;
        }
    }
}

