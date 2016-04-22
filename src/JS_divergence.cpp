#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double jsdiv_v(NumericVector P, NumericVector Q) {
    int n = P.size();
    if (Q.size() != n) {
        stop("P and Q must be of same length");
    }
    
    double total = 0;
    double PQ_mean;
    for (int i = 0; i < n; i++) {
        PQ_mean = (P[i] + Q[i]) / 2;
        if (P[i] != 0) {
            total += P[i] * log(P[i] / PQ_mean);
        }
        if (Q[i] != 0) {
            total += Q[i] * log(Q[i] / PQ_mean);
        }
    }
    return total / 2;
}

// [[Rcpp::export]]
NumericMatrix jsdiv_m(NumericMatrix x, NumericMatrix y) {
    int n = x.nrow();
    if (y.nrow() != n || y.ncol() != x.ncol()) {
        stop("x and y must have the same dimensions");
    }

    NumericMatrix result(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result(i, j) = jsdiv_v(x(i, _), y(j, _));
        }
    }
    return result;
}

// TODO an RcppEigen version for sparse matrices would be nice
