#include "Game/AI/Action/actionAnmTimingBackWalk.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

AnmTimingBackWalk::AnmTimingBackWalk(const InitArg& arg) : BackWalkWithAS(arg) {}

AnmTimingBackWalk::~AnmTimingBackWalk() = default;

bool AnmTimingBackWalk::init_(sead::Heap* heap) {
    return BackWalkWithAS::init_(heap);
}

void AnmTimingBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkWithAS::enter_(params);
}

void AnmTimingBackWalk::leave_() {
    BackWalkWithAS::leave_();
}

void AnmTimingBackWalk::loadParams_() {
    BackWalkWithAS::loadParams_();
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
}

void AnmTimingBackWalk::calc_() {
    if (sub_71005DD798(mActor, 0x2f, nullptr, 0, 0)) {
        BackWalkWithAS::calc_();
        return;
    }
    sub_71000B6D2C();
    auto* actor = mActor;
    const sead::Vector3f gravity = getGravity(actor) * 0.0011111111f;
    sub_7100738488(actor, *mPosReduceRatio_s, gravity);
    sub_7100738AA8(actor, *mAngReduceRatio_s);
}

}  // namespace uking::action
