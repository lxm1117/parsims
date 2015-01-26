#ifndef _NR_H_
#define _NR_H_

#define NR_END 1

/*
static double nr_sqrarg;
#define SQR_NR(a) ((nr_sqrarg=(a)) == 0.0 ? 0.0 : nr_sqrarg*nr_sqrarg)
*/

double betacf( double a, double b, double x );
double betai( double a, double b, double x );
void crank( int n, double w[], double *s );
double *dvector( int nl, int nh );
double erfcc( double x );
void free_dvector(double *v, long nl, long nh);
double gammln(double xx);
void nrerror( char error_text[] );
void pearsn( double x[], double y[], int n, double *r, double *prob, double *z );
double nr_select( int k, int n, double arr[] );
void shell2( int n, double a[], double b[] );
void shell2_i( int n, double a[], int b[] );
void spear( double data1[], double data2[], int n, 
	    double *d, double *zd, double *probd, double *rs, double *probrs );

#endif /* _NR_H_ */

