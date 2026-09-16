% TETWILD_REFINE Refine an existing tetrahedral mesh (e.g. the output of
% TetGen or CDT) using TetWild's mesh-improvement passes (edge
% splitting/collapsing/swapping, vertex smoothing), instead of building a
% new tet mesh from scratch via Delaunay tetrahedralization + BSP
% subdivision.
%
% [V,T,A] = tetwild_refine(VI,TI)
%
% Inputs:
%   VI  #VI by 3 list of input tet mesh vertex positions
%   TI  #TI by 4 list of input tet mesh tetrahedra indices into VI. TI is
%     assumed to already be exactly the region to keep: TI's own boundary
%     facets (those incident to exactly one tet) are treated as the
%     surface to stay within envelope of, and every tet enclosed by that
%     boundary (which, since TI encloses it by construction, should be
%     every tet of TI) is kept in the output.
% Outputs:
%   V  #V by 3 list of output tet mesh vertex positions
%   T  #T by 4 list of output tet mesh tetrahedra indices into V
%   A  #T list of per-tetrahedron "energy" values
%
% See also: tetwild, tetgen
