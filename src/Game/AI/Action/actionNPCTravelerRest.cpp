#include "Game/AI/Action/actionNPCTravelerRest.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

NPCTravelerRest::NPCTravelerRest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTravelerRest::~NPCTravelerRest() = default;

void NPCTravelerRest::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTravelerRest::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTravelerRest::loadParams_() {
    getDynamicParam(&mIsWarpHorse_d, "IsWarpHorse");
}

void NPCTravelerRest::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
}

}  // namespace uking::action
