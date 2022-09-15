#include "stdio.h"

extern int dgecon_(const char *norm, const int *n, double *a, const int *lda, const double *anorm, double *rcond, double *work, int *iwork, int *info, int len);
extern int dgetrf_(const int *m, const int *n, double *a, const int *lda, int *lpiv, int *info);
extern double dlange_(const char *norm, const int *m, const int *n, const double *a, const int *lda, double *work, const int norm_len);

int main()
{
    int i, info, n, lda;
    double anorm, rcond;

    int iw[2];
    double w[8];
    //double x[4] = {7,3,-9,2 };
    double x[4] = {1,1,1,0};
    n = 2;
    lda = 2;

    /* Computes the norm of x */
    anorm = dlange_("1", &n, &n, x, &lda, w, 1);

    /* Modifies x in place with a LU decomposition */
    dgetrf_(&n, &n, x, &lda, iw, &info);
    if (info != 0) fprintf(stderr, "failure with error %d\n", info);

    /* Computes the reciprocal norm */
    dgecon_("1", &n, x, &lda, &anorm, &rcond, w, iw, &info, 1);
    if (info != 0) fprintf(stderr, "failure with error %d\n", info);

    printf("%.5e\n", rcond);
    return 0;
}
