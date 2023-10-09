# include <stdlib.h>
# include <stdio.h>
# include <time.h>


int main ( );
void prime_number_sweep ( int n_lo, int n_hi, int n_factor );

/******************************************************************************/

double cpu_time ( )

/******************************************************************************/
/*
  Purpose:

    CPU_TIME returns the current reading on the CPU clock.

  Discussion:

    The CPU time measurements available through this routine are often
    not very accurate.  In some cases, the accuracy is no better than
    a hundredth of a second.  

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    06 June 2005

  Author:

    John Burkardt

  Parameters:

    Output, double CPU_TIME, the current reading of the CPU clock, in seconds.
*/
{
  double value;

  value = ( double ) clock ( ) 
        / ( double ) CLOCKS_PER_SEC;

  return value;
}
/******************************************************************************/

int prime_number ( int n )

/******************************************************************************/
/*
  Purpose:

    PRIME_NUMBER returns the number of primes between 1 and N.

  Discussion:

    A naive algorithm is used.

    Mathematica can return the number of primes less than or equal to N
    by the command PrimePi[N].

                N  PRIME_NUMBER

                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    23 April 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N, the maximum number to check.

    Output, int PRIME_NUMBER, the number of prime numbers up to N.
*/
{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for ( i = 2; i <= n; i++ )
  {
    prime = 1;
    for ( j = 2; j < i; j++ )
    {
      if ( ( i % j ) == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}
/******************************************************************************/

void timestamp (  )

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

/******************************************************************************/

int main (  )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for PRIME_SERIAL_TEST.

  Discussion:

    PRIME_SERIAL_TEST tests the PRIME_SERIAL library.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    06 August 2009

  Author:

    John Burkardt
*/
{
  int n_factor;
  int n_hi;
  int n_lo;

  timestamp ( );
  printf ( "\n" );
  printf ( "PRIME_SERIAL_TEST\n" );
  printf ( "  C version\n" );
  printf ( "  Test the PRIME_SERIAL library.\n" );

  n_lo = 1;
  n_hi = 131072;
  n_factor = 2;

  prime_number_sweep ( n_lo, n_hi, n_factor );

  n_lo = 5;
  n_hi = 500000;
  n_factor = 10;

  prime_number_sweep ( n_lo, n_hi, n_factor );
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "PRIME_SERIAL_TEST\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  timestamp ( );

  return 0;
}
/******************************************************************************/

void prime_number_sweep ( int n_lo, int n_hi, int n_factor )

/******************************************************************************/
/*
  Purpose:

   PRIME_NUMBER_SWEEP does repeated calls to PRIME_NUMBER.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    06 August 2009

  Author:

    John Burkardt

  Parameters:

    Input, int N_LO, the first value of N.

    Input, int N_HI, the last value of N.

    Input, int N_FACTOR, the factor by which to increase N after
    each iteration.

*/
{
  int i;
  int n;
  int primes;
  double ctime;

  printf ( "\n" );
  printf ( "TEST01\n" );
  printf ( "  Call PRIME_NUMBER to count the primes from 1 to N.\n" );
  printf ( "\n" );
  printf ( "         N        Pi          Time\n" );
  printf ( "\n" );

  n = n_lo;

  while ( n <= n_hi )
  {
    ctime = cpu_time ( );

    primes = prime_number ( n );

    ctime = cpu_time ( ) - ctime;

    printf ( "  %8d  %8d  %14f\n", n, primes, ctime );
    n = n * n_factor;
  }
 
  return;
}

