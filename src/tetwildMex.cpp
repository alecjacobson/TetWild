#include "mex.h"

#include <tetwild/tetwild.h>
#include <tetwild/Logger.h>

#include <igl/matlab/parse_rhs.h>
#include <igl/matlab/prepare_lhs.h>
#include <igl/matlab/validate_arg.h>
#include <igl/matlab/MexStream.h>
#include <igl/matlab/mexErrMsgTxt.h>

#include <Eigen/Core>
#include <Eigen/Sparse>

void mexFunction(
  int          nlhs,
  mxArray      *plhs[],
  int          nrhs,
  const mxArray *prhs[])
{
  int log_level = 6;
  using namespace igl;
  using namespace igl::matlab;
  using namespace Eigen;
  igl::matlab::MexStream mout;        
  std::streambuf *outbuf = std::cout.rdbuf(&mout);

  Eigen::MatrixXd VI;
  Eigen::MatrixXi FI;
  mexErrMsgTxt(nrhs>=2,"nrhs should be >= 2");
  parse_rhs_double(prhs+0,VI);
  parse_rhs_index(prhs+1,FI);

  Eigen::MatrixXd VO;
  Eigen::MatrixXi TO;
  Eigen::VectorXd AO;

  tetwild::Args args;
  std::string log_filename = "tetwild.log";
  tetwild::Logger::init(false, log_filename);

  log_level = std::max(0, std::min(6, log_level));
  spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
  spdlog::flush_every(std::chrono::seconds(3));

  // This is essential. Otherwise GEO::initialize() will crash matlab (only when
  // run in gui?!)
  ::setenv("GEO_NO_SIGNAL_HANDLER", "1", 1);
  ////std::cout<<"tetrahedralization start"<<std::endl;
  ////std::cout<<"|VI| = "<<VI.rows()<<std::endl;
  ////std::cout<<"|FI| = "<<FI.rows()<<std::endl;
  tetwild::tetrahedralization(VI, FI, VO, TO, AO, args);
  ////std::cout<<"tetrahedralization done"<<std::endl;
  ////std::cout<<"|VO| = "<<VO.rows()<<std::endl;
  ////std::cout<<"|TO| = "<<TO.rows()<<std::endl;
  ////std::cout<<"|AO| = "<<AO.rows()<<std::endl;
  spdlog::shutdown();

  switch(nlhs)
  {
    case 3:
      prepare_lhs_double(AO,plhs+2);
    case 2:
      prepare_lhs_index(TO,plhs+1);
    case 1:
      prepare_lhs_double(VO,plhs+0);
    default:break;
  }
  

  std::cout.rdbuf(outbuf);
  return;
}
