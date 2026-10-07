#include "Game/AI/Action/actionAreaFireObserve.h"

#include <cstring>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AreaFireObserve::AreaFireObserve(const InitArg& arg) : AreaFireObserveBase(arg) {
    _50 = false;
}

void AreaFireObserve::m2() {
    _50 = false;
}

bool AreaFireObserve::m15(const void* data) {
    if (!data)
        return false;
    const auto* bytes = static_cast<const char*>(data);
    const void* linked;
    std::memcpy(&linked, bytes + 8, sizeof(linked));
    if (!linked)
        return false;
    u32 flag;
    std::memcpy(&flag, static_cast<const char*>(linked) + 0x270, sizeof(flag));
    if (flag != 0)
        return false;
    if (bytes[0x1a] == 0)
        return false;
    _50 = true;
    return true;
}

void AreaFireObserve::m5() {
    if (_50)
        mActor->emitBasicSigOn();
    else
        mActor->emitBasicSigOff();
}

}  // namespace uking::action
