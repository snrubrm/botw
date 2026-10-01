#include "KingSystem/System/OverlayArenaSystemS2.h"

namespace ksys {

OverlayArenaSystemS2::OverlayArenaSystemS2() = default;

void OverlayArenaSystemS2::init(const InitArg& arg) {
    _30 = arg.s1;
    _38 = arg.system_pause_mgr;
}

bool OverlayArenaSystemS2::x_a() const {
    return _28 != 0;
}

}  // namespace ksys
