/* ========================================================================
   pDE: Parallel version of Storn and Price's Differential evolution 
   applied to NEURON modeling

   c2005 Jose Ambros-Ingerson jose@kiubo.net
   
   $Date: 2007/10/01 20:57:57 $ $Log: jString.c,v $
   $Date: 2007/10/01 20:57:57 $ Revision 1.4  2007/10/01 20:57:57  jose
   $Date: 2007/10/01 20:57:57 $ changed default alloc for jString to avoid reallocs (the cause trouble in BALE cluster)
   $Date: 2007/10/01 20:57:57 $
   $Date: 2007/10/01 20:57:57 $ Revision 1.3  2006/09/22 23:11:47  jose
   $Date: 2007/10/01 20:57:57 $ Changed so that returns NULL tok when no more tokens
   $Date: 2007/10/01 20:57:57 $
   $Date: 2007/10/01 20:57:57 $ Revision 1.2  2005/06/01 20:54:31  jose
   $Date: 2007/10/01 20:57:57 $ worked out most warnings in biowulf.biosci.ohiou.edu
   $Date: 2007/10/01 20:57:57 $
   $Date: 2007/10/01 20:57:57 $ Revision 1.1.1.1  2005/05/20 19:49:14  jose
   $Date: 2007/10/01 20:57:57 $ Parallel Differential Evolution
   $Date: 2007/10/01 20:57:57 $

   ======================================================================== */

/* ================================================================================
   String related utilities
   ================================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jLib.h"

/* ================================================================================
   return pointer to freshly allocated jString
   ================================================================================ */
jString* jString_new(){
  jString* jS;
  jS = (jString *) xmalloc( sizeof( jString ));
  jS->s = (char *) xmalloc( 2048 * sizeof( char ));
  jS->sz = 2048;	/* large to avoid reallocs; bale cluster crashes */

  return jS;
}

/* ================================================================================
   free jString
   ================================================================================ */
void jString_free( jString* jS ){
  xfree( (char*) jS->s );
  xfree( (char*) jS );
}

/* ================================================================================
   Read a line (up to \n) from file fd and return as a jString
   return EOF upon end of file.
   Assumes jS has been allocated using jString_new
   ================================================================================ */
int jLine_read( FILE *fp, jString *jS )
{
  int		i, c;

  i = 0;
  while( EOF!=(c=getc(fp)) && c!='\n' ) {
    if( i >= jS->sz+1 ) {
      if( jS->sz == 0 ){
	jS->s = NULL;
	jS->sz = 2048;	/* large to avoid reallocs; bale cluster crashes */
      }
      jS->sz *= 2;
      jS->s = (char *) xrealloc( jS->s, jS->sz*sizeof( char ) );
    }
    jS->s[i++] = (char) c;
  }
  if( c==EOF && i==0 ) return( EOF );

  jS->s[i] = '\0';
  return( i );
}

/* ================================================================================
   str2TYPE converts the string to a number of the given TYPE if possible using the
   strtoTYPE routines in the c-library. 
   Returns 1 on success; -1 on error
   ================================================================================ */

int str2int( char *s, int *i )
{
  char		*ptr;

  *i = (int) strtol( s, &ptr, 10 );
  if( strEQ( ptr, "" )) 
    return 1;
  else
    return -1;
}

/* ================================================================================ */
int str2short( char *s, short *si )
{
  int		i;
  
  if( 1 == str2int( s, &i )){
    *si = (short) i;
    return 1;
  }
  else
    return -1;
}

/* ================================================================================ */
int str2double( char *s, double *d )
{
  char		*ptr;

  *d = strtod( s, &ptr );
  if( strEQ( ptr, "" )) 
    return 1;
  else
    return -1;
}

/* ================================================================================ */
int str2float( char *s, float *f )
{
  double	d;
  
  if( 1 == str2double( s, &d )){
    *f = (float) d;
    return 1;
  }
  else
    return -1;
}

/* =========================================================================
   return tokens in str separated by any char in delims.
   A token is defined as any non-empty string delimited by any char in delims.
   The token is searched starting at position s and placed in tok (NULL 
     terminated) which should be large enough to contain it
     and the position to start search for next token is returned.
   -1 is returned when no tokens remain.
   Typical use is:

   s = 0; while( -1 != (s=strtoken(str," \t",s,tok)) ) foo( tok );
   
   ================================================================================ */   
int strtoken( char *str, char *delims, int s, char *tok )
{
  char	*fs, *d;

  fs = str;
  
  /* find begining of token */
  for( str=str+s; *str; ++str ){
    for( d=delims; *d; ++d )
      if( *d == *str ) break;
    if( ! *d ) break;
  }

  if(! *str ){
    *tok = (char) NULL;    
    return -1;
  }

  /* find end of token */
  for( ; *str; *tok++ = *str++ ){
    for( d=delims; *d; ++d )
      if( *d == *str ) break;
    if( *d ) break;
  }
  *tok = (char) NULL;
  return( str - fs );
}

/* ================================================================================
   return tokens on repeated calls reading from file fd.
   A token is defined as any non-empty string delimited by any char in delims.
   The token is placed in tok (NULL terminated) which should be large enough to
   contain it.
   The char that delimits the token on the right is returned as end_del.
   returns 1 on success; EOF on end-of-file.

   ================================================================================ */
int fp_token( FILE *fp, char *delims, char *tok, int *end_del )
{
  char	*d;
  int	c;

  while( EOF != ( c = getc( fp )) ){
    for( d=delims; *d; ++d )
      if( *d == (char)c ) break;
    if( ! *d ) break;
  }
  if( c == EOF ) return EOF;

  *tok++ = (char) c;	
  while( EOF != ( c= getc( fp )) ){
    for( d=delims; *d; ++d )
      if( *d == (char) c ) break;
    if( *d ) break;
    else    *tok++ = (char) c;
  }
  *tok = (char) NULL;
  *end_del = (int) *d;
  return 1;
}

/* ================================================================================
   return tokens on repeated calls reading from file fd.
   A token is defined as any non-empty string delimited by any char in delims.
   The token is placed in tok (NULL terminated). 
   tok is allocated inside xfp_token and should be freed by the calling routine
   when done using xfree.
   The char that delimits the token on the right is returned as end_del.
   returns 1 on success; EOF on end-of-file.

   See below for usage example
   ================================================================================ */
int xfp_token( FILE *fp, char *delims, char **tokp, int *end_del )
{
  char	*d, *tok;
  int	c, sz;
  static int tok_sz;

  if( *tokp == NULL ) {
    tok_sz = 32;
    *tokp = (char *) xmalloc( tok_sz * sizeof( char ) );
  }
  tok = *tokp;

  while( EOF != ( c = getc( fp )) ){
    for( d=delims; *d; ++d )
      if( *d == (char)c ) break;
    if( ! *d ) break;
  }
  if( c == EOF ) return EOF;

  sz = 1;
  *tok++ = (char) c;
  while( EOF != ( c= getc( fp )) ){
    for( d=delims; *d; ++d )
      if( *d == (char) c ) break;
    if( *d ) break;
    else {
      if( sz >= tok_sz -1 ) {	/* Make sure there's space for NULL termination */
	tok_sz *= 2;
	*tokp = (char *) xrealloc( *tokp, tok_sz * sizeof( char ) );
	tok = *tokp + sz;	/* Advance tok pointer to position before realloc */
      }
      *tok++ = (char) c;
      sz++;
    }
  }
  *tok = (char) NULL;
  *end_del = (int) *d;
  return 1;
}

/* ================================================================================ */
#ifdef Test_xfp_token

main( int argc, char* argv[] ){
  char *tok;
  int end_tok;
  FILE *fd;

  tok = NULL;
  fd = fopen( argv[1], "r" );

  while( -1 != xfp_token( fd, " \t\n\r", &tok, &end_tok ) ) 	/* \r is carriage return*/
    printf( "RETURNED_TOK '%s'\n'%x'\n", tok, end_tok );
  
  xfree( tok );
}

#endif
