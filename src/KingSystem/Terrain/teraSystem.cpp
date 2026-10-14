#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

u32 sub_710110B4A4(f32* out_height, const sead::Vector2f* xz, System* system) {
    if (!system->_8)
        return 0;
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return 0;
    auto* info = system->sub_710111F504();
    return sub_710110AA5C(0.0f, Terrain::instance()->_3cc, out_height, xz, &info->_20, info);
}

}  // namespace ksys::tera
