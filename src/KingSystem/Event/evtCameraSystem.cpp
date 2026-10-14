#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

// 0x7100da3d14
bool CameraSystem::sub_7100DA3D14(void*) {
    bool all_success = true;
    for (s32 i = 0; i < _30; ++i) {
        auto& handle = _10[i];
        handle.parseResource(nullptr);
        all_success &= handle.isSuccess();
    }
    _8 = all_success ? 3 : 4;
    return true;
}

// NON_MATCHING: the original stores `lane_id = 2` / `flags = 4` as one `stp w8, w9` (ours: two `str`, scheduled around
// the SafeString name stores)
bool CameraSystem::finishLoad() {
    if (_8 == 1) {
        bool all_ready = true;
        for (s32 i = 0; i < _30; ++i)
            all_ready &= _10[i].isReadyOrNeedsParse();
        if (all_ready) {
            _8 = 2;
            LowPrioThreadMgr::Request request;
            request.lane_id = 2;
            request.flags.setDirect(4);
            request.delegate = &_2c8;
            submitLowPriorityRequest(request);
        }
    }
    return u32(_8 - 1) > 1;
}

}  // namespace ksys::evt
