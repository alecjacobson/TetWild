% TETWILD Robustly tetrahedralize a triangle mesh (possibly self-intersecting,
% non-manifold, or otherwise "in the wild") using TetWild.
%
% [V,T,A] = tetwild(VI,FI)
%
% Inputs:
%   VI  #VI by 3 list of input mesh vertex positions
%   FI  #FI by 3 list of input mesh triangle indices into VI
% Outputs:
%   V  #V by 3 list of output tet mesh vertex positions
%   T  #T by 4 list of output tet mesh tetrahedra indices into V
%   A  #T list of per-tetrahedron "energy" values
%
% See also: tetgen
