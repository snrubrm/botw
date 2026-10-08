#include "KingSystem/Event/evtS7.h"
#include "Game/gameRoot38.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::evt {

const char* sub_71008B84F0(s32 state);

// 0x71008afb38
void S7EventFlow::m4() {
    mState = 1;
    _24 = 0;
    _28 = 0;
    mStatus.copy(sub_71008B84F0(1));
    _28 = 0;
    _2c = -1;
    _30 = 0;
    _1c = 0;
    _38 = 0;
    _3c = -1;
    _64 = -1;
    _68 = 0;
    _40 = false;
    _48 = 0;
    sub_71008AF278();
}

// 0x71008b84e0 (CSV evt::S7EventFlow::isPlaying)
bool S7EventFlow::isPlaying() {
    return mState == 3;
}

// 0x71008afcdc
bool S7EventFlow::calc() {
    const u32 result = calc_();
    if (_14 & 2)
        uking::sub_7100F41834();
    if (_3c >= 0) {
        if (_3c == 0) {
            phys::System::instance()->sub_71012167EC(false);
            _3c = -1;
        } else {
            _3c += 1;
        }
    }
    return result & 1;
}

// 0x71008b6f20 (CSV evt::S7EventFlow::getStatusStr)
const char* S7EventFlow::m7() {
    return mStatus.cstr();
}

}  // namespace ksys::evt
