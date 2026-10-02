#include "Game/AI/Action/actionNPCPurchase.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

NPCPurchase::NPCPurchase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCPurchase::~NPCPurchase() = default;

bool NPCPurchase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCPurchase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCPurchase::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCPurchase::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    setFailed();
}

}  // namespace uking::action
