#include "KingSystem/System/OverlayArenaSystemS2.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/System/OverlayArenaSystemS1.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys {

OverlayArenaSystemS2::OverlayArenaSystemS2() = default;

void OverlayArenaSystemS2::init(const InitArg& arg) {
    _30 = arg.s1;
    _38 = arg.system_pause_mgr;
}

// NON_MATCHING: request default initialization and supplied-field stores are scheduled differently.
void OverlayArenaSystemS2::sub_71012BBAF4(u32 value) {
    if (!_28)
        return;
    _0 = value;
    LowPrioThreadMgr::Request request;
    request.lane_id = 1;
    request.flags.set(1);
    request.delegate = &mDelegate;
    _28 = 0;
    evt::submitLowPriorityRequest(request);
}

u32 OverlayArenaSystemS2::sub_71012BBB70() const {
    return _0;
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
            _38->waitForStageGenFinalStep();
    } else if (_0 == 1) {
        if (_30)
            _30->m13();
        if (_38)
            _38->showMainLayerAndResumeProcJobs();
    }
    res::stubbedLogFunction();
    _28 = 1;
    return true;
}

}  // namespace ksys
