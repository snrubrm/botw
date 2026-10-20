#include <gsys/gsysG3dResMaterialEx.h>

namespace gsys {

s32 G3dResMaterialEx::calcRequiredMemorySize(const nn::g3d::ResMaterial*) {
    return 0x440;
}

}  // namespace gsys
