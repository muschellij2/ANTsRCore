#ifndef __RCPPANTSR_H
#define __RCPPANTSR_H

#include "itkMacro.h"
#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkVector.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "vnl/vnl_vector_ref.h"
#include "itkTransform.h"
#include "itkAffineTransform.h"

#include <RcppCommon.h>

// From advice @ http://dirk.eddelbuettel.com/code/rcpp/Rcpp-extending.pdf

inline SEXP exception_to_r_condition( const itk::ExceptionObject & ex )
{
  //std::string ex_class = demangle( typeid(ex).name() ) ;
  std::string ex_msg   = ex.what() ;
  std::string ex_class = "ITK";

  Rcpp::Shield<SEXP> cppstack( rcpp_get_stack_trace() );
  Rcpp::Shield<SEXP> call( get_last_call() );
  Rcpp::Shield<SEXP> classes( get_exception_classes(ex_class) );
  Rcpp::Shield<SEXP> condition( make_condition( ex_msg, call, cppstack, classes) );
  rcpp_set_stack_trace( R_NilValue ) ;
  return condition ;
}

inline void forward_exception_to_r( const itk::ExceptionObject & ex )
{
  SEXP stop_sym  = Rf_install( "stop" ) ;
  Rcpp::Shield<SEXP> condition( exception_to_r_condition(ex) );
  Rcpp::Shield<SEXP> expr( Rf_lang2( stop_sym , condition ) ) ;
  Rf_eval( expr, R_GlobalEnv ) ;
}

inline std::string pixeltype_highest_precision( std::string p1, std::string p2 )
{
  if ( (p1=="double") || (p2=="double")) {
    return "double";
  }
  else if ( (p1=="float") || (p2=="float")) {
    return "float";
  }
  else if ( (p1=="unsigned int") || (p2=="unsigned int")) {
    return "unsigned int";
  }
  else if ( (p1=="unsigned char") || (p2=="unsigned char")) {
    return "unsigned char";
  }

  Rcpp::Rcout << "Both pixeltypes are invalid" << std::endl;
  return "NA";

}



// itk::Image to antsImage
#include <RcppANTsR/RcppANTsR_ImageBaseDef.h>
#include <RcppANTsR/RcppANTsR_ImageDef.h>
#include <RcppANTsR/RcppANTsR_VectorImageDef.h>
#include <RcppANTsR/RcppANTsR_ImageIteratorDef.h>
#include <RcppANTsR/RcppANTsR_TransformDef.h>
#include <RcppANTsR/RcppANTsR_MetricDef.h>

// This needs to go after wrap declarations and before implementations
#include <Rcpp.h>

#include <RcppANTsR/RcppANTsR_ImageBaseImp.h>
#include <RcppANTsR/RcppANTsR_ImageImp.h>
#include <RcppANTsR/RcppANTsR_VectorImageImp.h>
#include <RcppANTsR/RcppANTsR_ImageIteratorImp.h>
#include <RcppANTsR/RcppANTsR_TransformImp.h>
#include <RcppANTsR/RcppANTsR_MetricImp.h>


#endif
