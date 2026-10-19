#include <Havok/Ai/Pathfinding/NavMesh/Query/hkaiPathSearchParams.h>

namespace
{
// The unset value the two constructors splat into their three vectors (0x7f7fffee).
constexpr hkReal cRealMax = 3.402820018375656e+38f;
}  // namespace

// 0x7101549660
Unk_7101549660::Unk_7101549660() {
    mVector0.setAll(cRealMax);
    mVector10.setAll(cRealMax);
    mVector30.set(-1.0f, cRealMax, 0.0f, 0.0f);
    mVector50.setAll(cRealMax);
}

// 0x71015496c4
Unk_71015496C4::Unk_71015496C4() {
    mVector0.setAll(cRealMax);
    mVector10.setAll(cRealMax);
    mVector30.set(-1.0f, cRealMax, 0.0f, 0.0f);
    mVector50.setAll(cRealMax);
}
