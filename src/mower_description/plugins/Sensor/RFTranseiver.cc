#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

struct rparams
  {
    double d_x;
    double d_y;
    double r_1;
    double r_2;
    double r_3;
  };


int rosenbrock_f (const gsl_vector * p, void *params, 
              gsl_vector * f)
{
  double d_x = ((struct rparams *) params)->d_x;
  double d_y = ((struct rparams *) params)->d_y;

  double r_1 = ((struct rparams *) params)->r_1;
  double r_2 = ((struct rparams *) params)->r_2;
  double r_3 = ((struct rparams *) params)->r_3;

  const double x = gsl_vector_get (p, 0);
  const double y = gsl_vector_get (p, 1);
  const double z = gsl_vector_get (p, 2);

  const double f0 = x*x + y*y + z*z - r_1*r_1;
  const double f1 = x*x - 2*d_x*x + d_x*d_x + y*y + z*z - r_2*r_2;
  const double f2 = x*x + y*y - 2*d_y*y + d_y*d_y + z*z - r_3*r_3;

  gsl_vector_set (f, 0, f0);
  gsl_vector_set (f, 1, f1);
  gsl_vector_set (f, 2, f2);

  return GSL_SUCCESS;
}

//USING DERIVATIVE FOR FAST CONVERGENCE

int
rosenbrock_df (const gsl_vector * p, void *params, 
               gsl_matrix * J)
{
  const double d_x = ((struct rparams *) params)->d_x;
  const double d_y = ((struct rparams *) params)->d_y;


  const double x = gsl_vector_get (p, 0);
  const double y = gsl_vector_get (p, 1);
  const double z = gsl_vector_get (p, 2);

  const double df00 = 2*x;
  const double df10 = 2*y;
  const double df20 = 2*z;

  const double df01 = 2*x - 2*d_x;
  const double df11 = 2*y;
  const double df21 = 2*z;

  const double df02 = 2*x;
  const double df12 = 2*y - 2*d_y;
  const double df22 = 2*z;

  gsl_matrix_set (J, 0, 0, df00);
  gsl_matrix_set (J, 1, 0, df10);
  gsl_matrix_set (J, 2, 0, df20);

  gsl_matrix_set (J, 0, 1, df01);
  gsl_matrix_set (J, 1, 1, df11);
  gsl_matrix_set (J, 2, 1, df21);

  gsl_matrix_set (J, 0, 2, df02);
  gsl_matrix_set (J, 1, 2, df12);
  gsl_matrix_set (J, 2, 2, df22);


  return GSL_SUCCESS;
}

int
rosenbrock_fdf (const gsl_vector * p, void *params,
                gsl_vector * f, gsl_matrix * J)
{
  rosenbrock_f (p, params, f);
  rosenbrock_df (p, params, J);

  return GSL_SUCCESS;
}


int
main (void)
{
  const gsl_multiroot_fdfsolver_type *T;
  gsl_multiroot_fdfsolver *s;

  int status;
  size_t i, iter = 0;

  const size_t n = 3;
  struct rparams d = {0.05, 0.05};
  gsl_multiroot_function_fdf f = {&rosenbrock_f, 
                                  &rosenbrock_df, 
                                  &rosenbrock_fdf, 
                                  n, &d};

  double p_init[2] = {5.0, -5.0, 5.0};
  gsl_vector *p = gsl_vector_alloc (n);

  gsl_vector_set (p, 0, p_init[0]);
  gsl_vector_set (p, 1, p_init[1]);
  gsl_vector_set (p, 2, p_init[2]);

  T = gsl_multiroot_fdfsolver_gnewton;
  s = gsl_multiroot_fdfsolver_alloc (T, n);
  gsl_multiroot_fdfsolver_set (s, &f, p);

  print_state (iter, s);

  do
    {
      iter++;

      status = gsl_multiroot_fdfsolver_iterate (s);

      print_state (iter, s);

      if (status)
        break;

      status = gsl_multiroot_test_residual (s->f, 1e-7);
    }
  while (status == GSL_CONTINUE && iter < 1000);

  printf ("status = %s\n", gsl_strerror (status));

  gsl_multiroot_fdfsolver_free (s);
  gsl_vector_free (p);
  return 0;
}

