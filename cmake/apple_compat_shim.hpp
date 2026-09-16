// Force-included on Apple platforms (see CMakeLists.txt) to work around
// vendored third-party headers (Boost.Move, libigl) that assume <utility>
// and <cassert> are transitively included by other standard headers -- an
// assumption that no longer holds with recent libc++ versions.
#ifdef __cplusplus
#include <utility>
#include <cassert>
#endif
