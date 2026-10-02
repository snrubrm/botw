#include "Game/AI/Action/actionForkPreJump.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkPreJump::ForkPreJump(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkPreJump::~ForkPreJump() = default;

bool ForkPreJump::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkPreJump::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkPreJump::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkPreJump::loadParams_() {}

void ForkPreJump::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkPreJump::isFinished() const {
    return mActor->getASList()->x(0x44, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

}  // namespace uking::action
