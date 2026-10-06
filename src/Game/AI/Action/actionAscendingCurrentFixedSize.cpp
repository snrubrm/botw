#include "Game/AI/Action/actionAscendingCurrentFixedSize.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AscendingCurrentFixedSize::AscendingCurrentFixedSize(const InitArg& arg) : AscendingCurrent(arg) {}

AscendingCurrentFixedSize::~AscendingCurrentFixedSize() = default;

bool AscendingCurrentFixedSize::init_(sead::Heap* heap) {
    if (!AscendingCurrent::init_(heap))
        return false;
    if (*mDisableInDemo_s)
        _28._2c = true;
    return true;
}

void AscendingCurrentFixedSize::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
    mFlags.set(Flag::Changeable);
}

void AscendingCurrentFixedSize::leave_() {
    AscendingCurrent::leave_();
}

void AscendingCurrentFixedSize::loadParams_() {
    AscendingCurrent::loadParams_();
    getStaticParam(&mDisableInDemo_s, "DisableInDemo");
    getStaticParam(&mSize_s, "Size");
}

void AscendingCurrentFixedSize::calc_() {
    AscendingCurrent::calc_();
}

void AscendingCurrentFixedSize::m33(sead::Vector3f* size) {
    size->set(*mSize_s);
}

void AscendingCurrentFixedSize::m34(sead::Matrix34f* mtx) {
    *mtx = mActor->getMtx();
}

}  // namespace uking::action
