#include "Game/AI/Action/actionHorseSaddleDefaultAction.h"
#include "Game/AI/aiUnk_7101ec1800.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseSaddleDefaultAction::HorseSaddleDefaultAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

HorseSaddleDefaultAction::~HorseSaddleDefaultAction() = default;

bool HorseSaddleDefaultAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseSaddleDefaultAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->sub_71011DA824(&_20);
    _1a38 = 0x10;
}

void HorseSaddleDefaultAction::leave_() {
    mActor->sub_71011DA834(&_20);
    for (s32 i = 0; i < 36; ++i)
        _20.getEntry(i).reset();
}

void HorseSaddleDefaultAction::loadParams_() {}

void HorseSaddleDefaultAction::calc_() {
    ksys::act::ai::Action::calc_();
}

const sead::Vector3f* HorseSaddleDefaultAction::m32() {
    return &sUnk_7101ec1818;
}

const sead::Vector3f* HorseSaddleDefaultAction::m33() {
    return &sUnk_7101ec1824;
}

}  // namespace uking::action
