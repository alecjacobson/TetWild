% TETWILD_REFINE Refine an existing tetrahedral mesh (e.g. the output of
% TetGen or CDT) using TetWild's mesh-improvement passes (edge
% splitting/collapsing/swapping, vertex smoothing), instead of building a
% new tet mesh from scratch via Delaunay tetrahedralization + BSP
% subdivision.
%
% [V,T,A] = tetwild_refine(VI,TI)
% [V,T,A] = tetwild_refine(VI,TI,'ParameterName',ParameterValue, ...)
%
% Inputs:
%   VI  #VI by 3 list of input tet mesh vertex positions
%   TI  #TI by 4 list of input tet mesh tetrahedra indices into VI. TI is
%     assumed to already be exactly the region to keep: TI's own boundary
%     facets (those incident to exactly one tet) are treated as the
%     surface to stay within envelope of, and every tet enclosed by that
%     boundary (which, since TI encloses it by construction, should be
%     every tet of TI) is kept in the output.
%   Optional:
%     'EdgeLength'  followed by the target edge length, as a fraction of the
%       bounding box diagonal. Controls the output resolution: smaller means
%       a finer (higher resolution, more tets) output mesh {0.05}. Requesting
%       a target far coarser than TI's own resolution can, for some inputs,
%       make quality-driven refinement fail to converge and produce a much
%       larger mesh than requested (bounded by 'MaxPasses', not unbounded);
%       this is a property of refining an unprepared input mesh under a tight
%       envelope, not specific to any one parameter value. Prefer a target
%       close to TI's native resolution, and loosen 'Epsilon' if coarsening
%       substantially.
%     'AbsoluteEdgeLength'  followed by the target edge length in absolute
%       units, instead of relative to the bounding box diagonal. Cannot be
%       given together with 'EdgeLength'.
%     'Epsilon'  followed by the envelope size (maximum surface deviation),
%       as a fraction of the bounding box diagonal. Smaller means the output
%       surface must track TI's own boundary more closely {1e-3}.
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
%     'Quiet'  followed by whether to mute console output {false}.
% Outputs:
%   V  #V by 3 list of output tet mesh vertex positions
%   T  #T by 4 list of output tet mesh tetrahedra indices into V
%   A  #T list of per-tetrahedron "energy" values
%
% See also: tetwild, tetgen
