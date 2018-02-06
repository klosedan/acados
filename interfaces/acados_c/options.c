/*
 *    This file is part of acados.
 *
 *    acados is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    acados is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with acados; if not, write to the Free Software Foundation,
 *    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "acados_c/options.h"

#include <string.h>

#include "acados_c/dense_qp/dense_qp_qpoases.h"
#include "acados_c/dense_qp/dense_qp_hpipm.h"
#include "acados_c/ocp_qp/ocp_qp_hpipm.h"
#include "acados_c/ocp_qp/ocp_qp_hpmpc.h"
#include "acados_c/ocp_qp/ocp_qp_full_condensing_solver.h"

int get_option_int(const void *args_, const char *option)
{
    return 0;
}



bool set_option_int(void *args_, const char *option, const int value)
{
    char *option_cpy, *token;
    option_cpy = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    strcpy(option_cpy, option);
    token = strsep(&option_cpy, ".");
    while (token) {
        // Linear search since the number of options is small.
        if (!strcmp(token, "sparse_hpipm")) {
            token = strsep(&option_cpy, ".");
            ocp_qp_hpipm_args *args = (ocp_qp_hpipm_args *) args_;
            if (!strcmp(token, "max_iter"))
                args->hpipm_args->iter_max = value;
            else if (!strcmp(token, "max_stat"))
                args->hpipm_args->stat_max = value;
            else return false;
        } else if (!strcmp(token, "condensing_hpipm")) {
            token = strsep(&option_cpy, ".");
            dense_qp_hpipm_args *args = (dense_qp_hpipm_args *) args_;
            if (!strcmp(token, "max_iter"))
                args->hpipm_args->iter_max = value;
            else if (!strcmp(token, "max_stat"))
                args->hpipm_args->stat_max = value;
            else return false;
        } else if (!strcmp(token, "hpmpc")) {
            token = strsep(&option_cpy, ".");
            ocp_qp_hpmpc_args *args = (ocp_qp_hpmpc_args *) args_;
            if (!strcmp(token, "max_iter"))
                args->max_iter = value;
            else if (!strcmp(token, "warm_start"))
                args->warm_start = value;
            else if (!strcmp(token, "out_iter"))
                args->out_iter = value;
            else if (!strcmp(option, "N2"))
                args->N2 = value;
            // partial tightening
            else if (!strcmp(token, "N"))
                args->N = value;
            else if (!strcmp(token, "M"))
                args->M = value;
            else return false;
        } else if (!strcmp(token, "qpoases")) {
            token = strsep(&option_cpy, ".");
            ocp_qp_full_condensing_solver_args *cond_args = (ocp_qp_full_condensing_solver_args *) args_;
            dense_qp_qpoases_args *args = (dense_qp_qpoases_args *) cond_args->solver_args;
            if (!strcmp(token, "max_nwsr"))
                args->max_nwsr = value;
            else if (!strcmp(token, "warm_start"))
                args->warm_start = value;
            else return false;
        } else {
            return false;
        }
        token = strsep(&option_cpy, ".");
    }
    return true;
}



const int *get_option_int_array(const void *args_, const char *option)
{
    return NULL;
}



bool set_option_int_array(void *args_, const char *option, const int *value)
{
    bool return_value = true;

    return return_value;
}



double get_option_double(const void *args_, const char *option)
{
    return 0;
}



bool set_option_double(void *args_, const char *option, const double value)
{
    char *option_cpy, *token;
    option_cpy = (char *) malloc(sizeof(char) * MAX_STR_LEN);
    strcpy(option_cpy, option);
    while ((token = strsep(&option_cpy, "."))) {
        // Linear search since the number of options is small.
        if (!strcmp(token, "sparse_qp") || !strcmp(token, "condensing_qp")) {
            set_option_double(args_, option_cpy, value);
        } else if (!strcmp(token, "hpipm")) {
            ocp_qp_hpipm_args *args = (ocp_qp_hpipm_args *) args_;
            if (!strcmp(option, "res_g_max"))
                args->hpipm_args->res_g_max = value;
            else if (!strcmp(option, "res_b_max"))
                args->hpipm_args->res_b_max = value;
            else if (!strcmp(option, "res_d_max"))
                args->hpipm_args->res_d_max = value;
            else if (!strcmp(option, "res_m_max"))
                args->hpipm_args->res_m_max = value;
            else if (!strcmp(option, "alpha_min"))
                args->hpipm_args->alpha_min = value;
            else if (!strcmp(option, "mu0"))
                args->hpipm_args->mu0 = value;
            else return false;
        } else if (!strcmp(token, "hpmpc")) {
            ocp_qp_hpmpc_args *args = (ocp_qp_hpmpc_args *) args_;
            if (!strcmp(option, "tol"))
                args->tol = value;
            else if (!strcmp(option, "mu0"))
                args->mu0 = value;
            // partial tightening
            else if (!strcmp(option, "sigma_mu"))
                args->sigma_mu = value;
            else return false;
        } else if (!strcmp(token, "qpoases")) {
            ocp_qp_full_condensing_solver_args *cond_args = (ocp_qp_full_condensing_solver_args *) args_;
            dense_qp_qpoases_args *args = (dense_qp_qpoases_args *) cond_args->solver_args;
            if (!strcmp(option, "max_cputime"))
                args->max_cputime = value;
            else return false;
        }
    }
    return true;
}



const double *get_option_double_array(const void *args_, const char *option)
{
    return NULL;
}



bool set_option_double_array(void *args_, const char *option, const double *value)
{
    bool return_value = true;

    return return_value;
}
