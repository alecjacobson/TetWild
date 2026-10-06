% TETWILD Robustly tetrahedralize a triangle mesh (possibly self-intersecting,
% non-manifold, or otherwise "in the wild") using TetWild.
%
% [V,T,A] = tetwild(VI,FI)
% [V,T,A] = tetwild(VI,FI,'ParameterName',ParameterValue, ...)
%
% Inputs:
%   VI  #VI by 3 list of input mesh vertex positions
%   FI  #FI by 3 list of input mesh triangle indices into VI
%   Optional:
%     'EdgeLength'  followed by the target edge length, as a fraction of the
%       bounding box diagonal. Controls the output resolution: smaller means
%       a finer (higher resolution, more tets) output mesh {0.05}.
%     'AbsoluteEdgeLength'  followed by the target edge length in absolute
%       units, instead of relative to the bounding box diagonal. Cannot be
%       given together with 'EdgeLength'.
%     'Epsilon'  followed by the envelope size (maximum surface deviation),
%       as a fraction of the bounding box diagonal. Smaller means the output
%       surface must track the input surface more closely {1e-3}.
%     'TargetNumVertices'  followed by a target number of output vertices
%       (minimum, within ~5% tolerance), as an alternative way to control
%       output resolution to directly requesting an edge length {unset}.
%     'MaxPasses'  followed by the maximum number of mesh-improvement passes
%       {80}.
%     'FilterEnergy'  followed by the energy threshold below which mesh
%       improvement stops {10}.
%     'Stage'  followed by the pipeline stage to run in 1, 2, or 3 (see
%       Algorithm 1 of the TetWild paper); retry with a higher stage if a
%       lower one doesn't succeed {1}.
%     'BackgroundMesh'  followed by the path to a background tetmesh in .msh
%       format, for applying a non-uniform sizing field {unset}.
%     'VoxelStuffing'  followed by whether to seed the initial Delaunay
%       tetrahedralization with voxel-center points {true}.
%     'SmoothOpenBoundary'  followed by whether to do Laplacian smoothing on
%       the output surface covering holes in an open (non-watertight) input
%       {false}.
%     'Quiet'  followed by whether to mute console output {false}.
% Outputs:
%   V  #V by 3 list of output tet mesh vertex positions
%   T  #T by 4 list of output tet mesh tetrahedra indices into V
%   A  #T list of per-tetrahedron "energy" values
%
% See also: tetwild_refine, tetgen
