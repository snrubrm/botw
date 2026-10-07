#include "KingSystem/Event/evtS7.h"

namespace ksys::evt {

// 0x71008b84e0 (CSV evt::S7EventFlow::isPlaying)
bool S7EventFlow::isPlaying() {
    return mState == 3;
}

// 0x71008b6f20 (CSV evt::S7EventFlow::getStatusStr)
const char* S7EventFlow::m7() {
    return mStatus.cstr();
}

}  // namespace ksys::evt
