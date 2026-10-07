#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

void Core::sub_7101300B4C(u32 index, const sead::Vector3f* position, bool update) {
    if (_37c & 2) {
        sub_7101300BF0();
        _37c &= ~2;
    }
    mPositions[index].mPosition = *position;
    if (update)
        sub_7101300D50(index, true, true);
}

void Core::sub_71013010D4(const Unk_71013010d4& state, s32 index) {
    mStates[index] = state;
    _37c |= 2;
}

}  // namespace ksys::tera
