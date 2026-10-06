#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// NON_MATCHING: the original stores `lane_id = 2` / `flags = 4` as one `stp w8, w9` (ours: two `str`, scheduled around
// the SafeString name stores)
bool CameraSystem::finishLoad() {
    if (_8 == 1) {
        bool all_ready = true;
        for (s32 i = 0; i < _30; ++i)
            all_ready &= _10[i].isReadyOrNeedsParse();
        if (all_ready) {
            _8 = 2;
            util::LowPrioThreadMgr::Request request;
            request.lane_id = 2;
            request.flags.setDirect(4);
            request.delegate = &_2c8;
            submitLowPriorityRequest(request);
        }
    }
    return u32(_8 - 1) > 1;
}

}  // namespace ksys::evt
