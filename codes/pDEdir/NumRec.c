/* ================================================================================
   Code from numerical recipes 2.11 Modified by Jose Ambros-Ingerson jose@kiubo.net
   for use with pDE
   Oct 2006
   ================================================================================ */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "NumRec.h"

static double nr_sqrarg;
#define SQR_NR(a) ((nr_sqrarg=(a)) == 0.0 ? 0.0 : nr_sqrarg*nr_sqrarg)

/* ================================================================================
   Evaluate the continued fraction for incomplete beta function by modified
   Lentz method
   ================================================================================ */
#define MAXIT 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

double betacf( double a, double b, double x )
{
  void nrerror(char error_text[]);
  int m, m2;
  double aa,c,d,del,h,qab,qam,qap;

  qab=a+b;
  qap=a+1.0;
  qam=a-1.0;
  c=1.0;
  d=1.0-qab*x/qap;
  if (fabs(d) < FPMIN) d=FPMIN;
  d=1.0/d;
  h=d;
  for (m=1;m<=MAXIT;m++) {
    m2=2*m;
    aa=m*(b-m)*x/((qam+m2)*(a+m2));
    d=1.0+aa*d;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=1.0+aa/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    h *= d*c;
    aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
    d=1.0+aa*d;
    if (fabs(d) < FPMIN) d=FPMIN;
    c=1.0+aa/c;
    if (fabs(c) < FPMIN) c=FPMIN;
    d=1.0/d;
    del=d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) break;
  }
  if (m > MAXIT) nrerror("a or b too big, or MAXIT too small in betacf");
  return h;
}
#undef MAXIT
#undef EPS
#undef FPMIN

/* ================================================================================
   Return the incomplete beta function
   ================================================================================ */
double betai( double a, double b, double x)
{
  double betacf(double a, double b, double x);
  double gammln(double xx);
  void nrerror(char error_text[]);
  double bt;

  if (x < 0.0 || x > 1.0) nrerror("Bad x in routine betai");
  if (x == 0.0 || x == 1.0) bt=0.0;
  else
    bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
  if (x < (a+1.0)/(a+b+2.0))
    return bt*betacf(a,b,x)/a;
  else
    return 1.0-bt*betacf(b,a,1.0-x)/b;
}

/* ================================================================================
   Replace the elements in sorted array w[1..n] by their rank, including midranking 
   of ties. Return 
     s - sum of f^3-f where f is the number of elements in each tie
   ================================================================================ */
void crank( int n, double w[], double *s )
{
  int j=1,ji,jt;
  double t,rank;

  *s=0.0;
  while (j < n) {
    if (w[j+1] != w[j]) {
      w[j]=j;
      ++j;
    } 
    else {
      for (jt=j+1;jt<=n && w[jt]==w[j];jt++);
      rank=0.5*(j+jt-1);
      for (ji=j;ji<=(jt-1);ji++) w[ji]=rank;
      t=jt-j;
      *s += t*t*t-t;
      j=jt;
    }
  }
  if (j == n) w[n]=n;
}

/* allocate a double vector with subscript range v[nl..nh] */
double *dvector( int nl, int nh ){
  double *v;

  v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
  if (!v) nrerror("allocation failure in dvector()");
  return v-nl+NR_END;
}

/* ================================================================================
   Return the complementary error function
   ================================================================================ */
double erfcc( double x )
{
  double t,z,ans;

  z = fabs(x);
  t = 1.0/(1.0+0.5*z);
  ans = t*exp(-z*z-1.26551223+t*
	    (1.00002368+t*
	     (0.37409196+t*
	      (0.09678418+t*
	       (-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+t*(-0.82215223+t*0.17087277)))))))));
  return x >= 0.0 ? ans : 2.0-ans;
}

/* free a double vector allocated with dvector() */
void free_dvector(double *v, long nl, long nh)
{
        free((char *) (v+nl-NR_END));
}

/* ================================================================================
   Return the value ln[Gamma(xx)] for xx > 0
   ================================================================================ */
double gammln(double xx)
{
  double x,y,tmp,ser;
  static double cof[6]={76.18009172947146,-86.50532032941677,
			24.01409824083091,-1.231739572450155,
			0.1208650973866179e-2,-0.5395239384953e-5};
  int j;

  y=x=xx;
  tmp=x+5.5;
  tmp -= (x+0.5)*log(tmp);
  ser=1.000000000190015;
  for (j=0;j<=5;j++) ser += cof[j]/++y;
  return -tmp+log(2.5066282746310005*ser/x);
}

/* Numerical Recipes standard error handler */
void nrerror( char error_text[] ){
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  exit(1);
}


/* ================================================================================
   Given arrays x[1..n] and y[1..n] Return
     r - 	Pearson's correlation coefficient
     prob	Significance for null correlation
     z		Fisher's z
   ================================================================================ */
#define TINY 1.0e-20

void pearsn( double x[], double y[], int n, double *r, double *prob, double *z )
{
  double betai(double a, double b, double x);
  double erfcc(double x);
  int j;
  double yt,xt,t,df;
  double syy=0.0,sxy=0.0,sxx=0.0,ay=0.0,ax=0.0;
  
  for (j=1;j<=n;j++) {
    ax += x[j];
    ay += y[j];
  }
  ax /= n;
  ay /= n;
  for (j=1;j<=n;j++) {
    xt=x[j]-ax;
    yt=y[j]-ay;
    sxx += xt*xt;
    syy += yt*yt;
    sxy += xt*yt;
  }
  *r=sxy/(sqrt(sxx*syy)+TINY);
  *z=0.5*log((1.0+(*r)+TINY)/(1.0-(*r)+TINY));
  df=n-2;
  t=(*r)*sqrt(df/((1.0-(*r)+TINY)*(1.0+(*r)+TINY)));
  *prob=betai(0.5*df,0.5,df/(df+t*t));
}
#undef TINY

/* ================================================================================
   Returns the kth smallest value in the array arr[1..n].  
   (use select( ..., arr-1 ) to call with arr[0..n-1].. )
   The input array will
   be rearranged to have this value in location arr[k], with all smaller
   elements moved to arr[1..k-1] (in arbitrary order) and all larger elements in
   arr[k+1..n] (also in arbitrary order).
   ================================================================================ */
#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

double nr_select( int k, int n, double arr[] )
{
  int i,ir,j,l,mid;
  double a,temp;

  l=1;
  ir=n;
  for (;;) {
    if (ir <= l+1) {
      if (ir == l+1 && arr[ir] < arr[l]) {
	SWAP(arr[l],arr[ir])
	  }
      return arr[k];
    } else {
      mid=(l+ir) >> 1;
      SWAP(arr[mid],arr[l+1])
	if (arr[l] > arr[ir]) {
	  SWAP(arr[l],arr[ir])
	    }
      if (arr[l+1] > arr[ir]) {
	SWAP(arr[l+1],arr[ir])
	  }
      if (arr[l] > arr[l+1]) {
	SWAP(arr[l],arr[l+1])
	  }
      i=l+1;
      j=ir;
      a=arr[l+1];
      for (;;) {
	do i++; while (arr[i] < a);
	do j--; while (arr[j] > a);
	if (j < i) break;
	SWAP(arr[i],arr[j])
	  }
      arr[l+1]=arr[j];
      arr[j]=a;
      if (j >= k) ir=j-1;
      if (j <= k) l=i;
    }
  }
}
#undef SWAP

/* ================================================================================
   Shell sort (see Numerical recipes p 332 ). 
   Sort an array a[1..n] into ascending order by Shell's method.
   (use shell2( d1-1,...) to call with d1[0..n-1].. )
   a is replaced on output by its sorted rearrangement.
   If n is less than the size of the array, only the first n elements are sorted
   ================================================================================ */
void shell2( int n, double a[], double b[] )
{
  int i, j, inc;
  double v, bv;
  inc=1;
  do {
    inc *= 3;
    inc++;
  } while (inc <= n);
  do {
    inc /= 3;
    for (i=inc+1;i<=n;i++) {
      v=a[i]; bv=b[i];
      j=i;
      while (a[j-inc] > v) {
	a[j]=a[j-inc]; b[j]=b[j-inc];
	j -= inc;
	if (j <= inc) break;
      }
      a[j]=v; b[j]=bv;
    }
  } while (inc > 1);
}

/* ================================================================================
   ================================================================================ */
void shell2_i( int n, double a[], int b[] )
{
  int i, j, inc, bv;
  double v;
  inc=1;
  do {
    inc *= 3;
    inc++;
  } while (inc <= n);
  do {
    inc /= 3;
    for (i=inc+1;i<=n;i++) {
      v=a[i]; bv=b[i];
      j=i;
      while (a[j-inc] > v) {
	a[j]=a[j-inc]; b[j]=b[j-inc];
	j -= inc;
	if (j <= inc) break;
      }
      a[j]=v; b[j]=bv;
    }
  } while (inc > 1);
}

/* ================================================================================ 
   Given arrays data1[1..n] and data2[1..n] return
       (use spear( d1-1,...) to call with d1[0..n-1].. )
     d - 	sum-square difference of ranks
     zd - 	the number of SD by which d deviates from null hypothesis
     probd - 	two sided significance of zd
     rs - 	Spearman's rank correlation
     probrs - 	two sided significance pf rs
   Small value of probd or probrs indicates significant correlation (rs>0) or 
   anticorrelation (rs<0)
  ================================================================================ */
void spear( double data1[], double data2[], int n, 
	    double *d, double *zd, double *probd, double *rs, double *probrs )
{
  int j;
  double vard, t, sg, sf, fac, en3n, en, df, aved, *wksp1, *wksp2;

  wksp1 = dvector( 1, n );
  wksp2 = dvector( 1, n );
  for( j=1; j<=n; j++ ) {
    wksp1[j] = data1[j];
    wksp2[j] = data2[j];
  }
  shell2( n, wksp1, wksp2 );
  crank( n, wksp1, &sf );
  shell2( n, wksp2, wksp1 );
  crank( n, wksp2, &sg );
  *d = 0.0;
  for( j=1; j<=n; j++ )
    *d += SQR_NR( wksp1[j]-wksp2[j] );
  en = n;
  en3n = en*en*en - en;
  aved = en3n/6.0 - (sf+sg)/12.0;
  fac = (1.0-sf/en3n) * ( 1.0-sg/en3n );
  vard = ((en-1.0) *en*en* SQR_NR(en+1.0)/36.0) * fac;
  *zd = (*d-aved)/sqrt(vard);
  *probd = erfcc( fabs(*zd)/1.4142136);
  *rs = ( 1.0-(6.0/en3n)*( *d+(sf+sg)/12.0))/sqrt(fac);
  fac = (*rs+1.0)*(1.0-(*rs));
  if ( fac > 0.0 ) {
    t = (*rs)*sqrt((en-2.0)/fac);
    df = en-2.0;
    *probrs = betai(0.5*df, 0.5, df/(df+t*t));
  } else
    *probrs = 0.0;
  free_dvector( wksp2, 1, n );
  free_dvector( wksp1, 1, n );
}

#undef SQR_NR
