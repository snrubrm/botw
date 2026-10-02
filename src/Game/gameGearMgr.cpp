#include "Game/gameGearMgr.h"
#include <thread/seadCriticalSection.h>

namespace uking {

bool GearMgr::sub_71006690B8(ksys::act::BaseProc* proc) {
    if (!proc)
        return false;

    mCS.lock();
    for (size_t i = 0; i < 0x80; ++i) {
        auto& link = mEntries[i].mLink;
        if (link.hasProc() && link.hasProcById(proc)) {
            mCS.unlock();
            return true;
        }
    }
    mCS.unlock();
    return false;
}

}  // namespace uking
