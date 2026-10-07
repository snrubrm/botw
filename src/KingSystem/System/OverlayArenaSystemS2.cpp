#include "KingSystem/System/OverlayArenaSystemS2.h"
#include "KingSystem/System/OverlayArenaSystemS1.h"
#include "KingSystem/System/SystemPauseMgr.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys {

OverlayArenaSystemS2::OverlayArenaSystemS2() = default;

void OverlayArenaSystemS2::init(const InitArg& arg) {
    _30 = arg.s1;
    _38 = arg.system_pause_mgr;
}

bool OverlayArenaSystemS2::x_a() const {
    return _28 != 0;
}

bool OverlayArenaSystemS2::sub_71012BBA50(void* userdata) {
    res::stubbedLogFunction();
    if (_0 == 0) {
        if (_30)
            _30->m9();
        if (_38)
            _38->m9();
    } else if (_0 == 1) {
        if (_30)
            _30->m13();
        if (_38)
            _38->m13();
    }
    res::stubbedLogFunction();
    _28 = 1;
    return true;
}

}  // namespace ksys
