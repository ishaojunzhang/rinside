// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4;  tab-width: 8; -*-
//
// Showing off some of the templated as<>() conversion from Rcpp
//
// Copyright (C) 2010 - 2011  Dirk Eddelbuettel and Romain Francois

#include <RInside.h>                    // for the embedded R via RInside

int main(int argc, char *argv[]) {

    try {

        RInside R(argc, argv);          // create an embedded R instance 
        std::string txt;

        txt = "m <- 1.23";
        //double d1 = Rcpp::as< double >(R.parseEval(txt));
        double d1 = R.parseEval(txt);
        std::cout << "d1 " << d1 << std::endl;

        txt = "M <- 1.0 * 1:6";
        //std::vector<double> d2 = Rcpp::as< std::vector< double > >(R.parseEval(txt));
        std::vector<double> d2 = R.parseEval(txt);
        std::cout << "d2[0] " << d2[0] << " d2[1] " << d2[1] << std::endl;
 
        txt = "l <- matrix(1:6, 3, 2)";
        Rcpp::NumericMatrix nmat((SEXP) R.parseEval(txt));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << nmat(i, j) << " ";
            }
            std::cout<<std::endl;
        }
        
        txt = "n <- 1:5";
        Rcpp::NumericVector nv((SEXP) R.parseEval(txt));
        for (int i = 0; i < nv.size(); i++) {
            std::cout << nv[i] << " ";
        }
        std::cout << std::endl;
        
        txt = "k <- list(a = c(1, 2), b = \"a\")";
        Rcpp::List lst((SEXP) R.parseEval(txt));
        std::vector<double> x = lst["a"];
        std::string s = lst["b"];
        std::cout << x[0] << " "<< s << std::endl;
        
        
    } catch(std::exception& ex) {
        std::cerr << "Exception caught: " << ex.what() << std::endl;
    } catch(...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }

    exit(0);
}

