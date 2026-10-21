#include "KingSystem/System/Controller.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Utils/SafeDelete.h"

Unk_71024dd640::~Unk_71024dd640() = default;

SEAD_SINGLETON_DISPOSER_IMPL(Controller)

Controller::~Controller() {
    mControllers.clear();
    ksys::util::safeDelete(_28);
}

s32 Controller::sub_7100D9F0C8() const {
    return mSnapshot._1c;
}

bool Controller::sub_7100D9F7D4() const {
    return mSnapshot.sub_7100D9E48C();
}

// NON_MATCHING: the original zero-extends the argument with and x1, x1, #0xffffffff; ours uses mov w1, w1.
bool Controller::sub_7100D9F7C8(u32 id) {
    return mFlags.isOnBit(id);
}

Unk_71024dd5c8* Controller::sub_7100D9F7DC() {
    return &mSnapshot;
}

void Controller::sub_7100D9F7E4(ksys::SeadController* controller) {
    const auto lock = sead::makeScopedLock(mCS);
    mControllers.pushBack(controller);
}

void Controller::sub_7100D9F838(ksys::SeadController* controller) {
    const auto lock = sead::makeScopedLock(mCS);
    mControllers.erase(controller);
}
