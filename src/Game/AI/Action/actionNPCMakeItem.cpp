#include "Game/AI/Action/actionNPCMakeItem.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

NPCMakeItem::NPCMakeItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCMakeItem::~NPCMakeItem() = default;

bool NPCMakeItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCMakeItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCMakeItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCMakeItem::loadParams_() {
    getDynamicParam(&mShopType_d, "ShopType");
    getDynamicParam(&mIncludePorch_d, "IncludePorch");
}

void NPCMakeItem::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    setFailed();
}

}  // namespace uking::action
