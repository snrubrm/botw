#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking {

// 0x7100e8a080 (TU of its own: its address block starts right after the HorseMgr functions, and HorseMgr's
// dtor and sub_7100E87760 call these out of line).

Unk_7100e8a080::Unk_7100e8a080() = default;

// 0x7100e8a0c4 (was sub_7100E8A0C4): ~HorseMgr calls it for HorseMgr::_270; the link reset is _8's destructor.
Unk_7100e8a080::~Unk_7100e8a080() {
    if (mQuery) {
        ksys::phys::HavokAI::instance()->destroyQuery(mQuery);
        mQuery = nullptr;
    }
}

// NON_MATCHING: horseStuff ignores `this`, so the original does not re-set x0 for the call (same-TU dead argument).
bool Unk_7100e8a080::sub_7100E8A100(HorseMgr* mgr, ksys::act::BaseProc* proc) {
    if (!_4c && !mQuery && !(_48 > 0.0f)) {
        if (!horseStuff(mgr))
            return false;
        _48 = 66.0f;
        _4c = false;
        _8.acquire(proc, false);
    }
    return true;
}

}  // namespace uking
