#include "Game/AI/Action/actionForbidTag.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForbidTag::ForbidTag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForbidTag::~ForbidTag() = default;

bool ForbidTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForbidTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForbidTag::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForbidTag::loadParams_() {}

void ForbidTag::calc_() {
    if (mActor->checkBasicSig())
        m32();
    else
        m33();
}

void ForbidTag::m32() {}

void ForbidTag::m33() {}

}  // namespace uking::action
