#include "Game/AI/Action/actionNPCMakeItem.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::action {

NPCMakeItem::NPCMakeItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCMakeItem::~NPCMakeItem() = default;

bool NPCMakeItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

static const char* const sShopTypeNames[] = {"Cooking", "Jewelry", "Compound", "Ancient"};

// NON_MATCHING: scheduling only: the original loads `*mIncludePorch_d` after the actor param pointer (0x570), ours
// before it
void NPCMakeItem::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ui::UI::instance() && ui::UI::instance()->sub_71010A5888())
        ui::UI::instance()->sub_71010A6B98(nullptr);
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        const bool include_porch = *mIncludePorch_d;
        if (include_porch)
            _30 = npc->_f88.sub_710091D6D8(mActor->getParam()->getRes().mShopData,
                                           sShopTypeNames[*mShopType_d], false, false);
        else
            _30 = npc->_f88.sub_710091CE98(mActor->getParam()->getRes().mShopData,
                                           sShopTypeNames[*mShopType_d]);
    }
    _31 = false;
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
