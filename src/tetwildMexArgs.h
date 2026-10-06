#pragma once

#include "mex.h"

#include <tetwild/Args.h>

#include <igl/C_STR.h>
#include <igl/matlab/mexErrMsgTxt.h>
#include <igl/matlab/validate_arg.h>

#include <cstring>

// Parse `Name,Value` pairs (as used throughout gptoolbox/libigl mex functions) starting at
// prhs[i_start] into a tetwild::Args, shared between tetwildMex.cpp and tetwildRefineMex.cpp.
//
// `allow_voxel_stuffing_and_smooth_open_boundary` gates 'VoxelStuffing' and
// 'SmoothOpenBoundary': tetwildRefineMex.cpp passes false, since neither one does what its name
// implies for tetwild::tetrahedralizeFromTetmesh() -- there's no fresh Delaunay tetrahedralization
// for 'VoxelStuffing' to seed, and tetrahedralizeFromTetmesh() deliberately leaves
// args.smooth_open_boundary at its default (false) so output extraction goes through
// InoutFiltering rather than MeshRefinement::postProcess, which has no fallback for the
// globally-reversed surface orientation that can arise from a boundary derived purely from the
// input tetmesh's own topology (see tetwild.cpp). Honoring an explicit 'SmoothOpenBoundary',true
// there would silently reintroduce that failure mode, so it's rejected instead.
inline void parse_tetwild_args(
  const int i_start,
  const int nrhs,
  const mxArray *prhs[],
  tetwild::Args &args,
  const bool allow_voxel_stuffing_and_smooth_open_boundary = true)
{
  using namespace igl::matlab;
  bool has_edge_length = false;
  bool has_absolute_edge_length = false;
  int i = i_start;
  while(i < nrhs)
  {
    mexErrMsgTxt(mxIsChar(prhs[i]), "Parameter names should be strings");
    const char * name = mxArrayToString(prhs[i]);
    if(strcmp("EdgeLength", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.initial_edge_len_rel = (double)*mxGetPr(prhs[++i]);
      has_edge_length = true;
    }else if(strcmp("AbsoluteEdgeLength", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.initial_edge_len_abs = (double)*mxGetPr(prhs[++i]);
      has_absolute_edge_length = true;
    }else if(strcmp("Epsilon", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.eps_rel = (double)*mxGetPr(prhs[++i]);
    }else if(strcmp("TargetNumVertices", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.target_num_vertices = (int)*mxGetPr(prhs[++i]);
    }else if(strcmp("MaxPasses", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.max_num_passes = (int)*mxGetPr(prhs[++i]);
    }else if(strcmp("FilterEnergy", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.filter_energy_thres = (double)*mxGetPr(prhs[++i]);
    }else if(strcmp("Stage", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_double(i, nrhs, prhs, name);
      args.stage = (int)*mxGetPr(prhs[++i]);
    }else if(strcmp("BackgroundMesh", name) == 0)
    {
      validate_arg_char(i, nrhs, prhs, name);
      args.background_mesh = mxArrayToString(prhs[++i]);
    }else if(allow_voxel_stuffing_and_smooth_open_boundary && strcmp("VoxelStuffing", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_logical(i, nrhs, prhs, name);
      args.not_use_voxel_stuffing = !(bool)*mxGetLogicals(prhs[++i]);
    }else if(allow_voxel_stuffing_and_smooth_open_boundary && strcmp("SmoothOpenBoundary", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_logical(i, nrhs, prhs, name);
      args.smooth_open_boundary = (bool)*mxGetLogicals(prhs[++i]);
    }else if(strcmp("Quiet", name) == 0)
    {
      validate_arg_scalar(i, nrhs, prhs, name);
      validate_arg_logical(i, nrhs, prhs, name);
      args.is_quiet = (bool)*mxGetLogicals(prhs[++i]);
    }else
    {
      mexErrMsgTxt(false, C_STR("Unknown parameter: "<<name));
    }
    i++;
  }
  mexErrMsgTxt(!(has_edge_length && has_absolute_edge_length),
    "EdgeLength and AbsoluteEdgeLength cannot both be given as arguments.");
}
