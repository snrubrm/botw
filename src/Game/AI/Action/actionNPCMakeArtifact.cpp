#include "Game/AI/Action/actionNPCMakeArtifact.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::action {

NPCMakeArtifact::NPCMakeArtifact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCMakeArtifact::~NPCMakeArtifact() {
    _20.sub_710091BA3C();
}

bool NPCMakeArtifact::init_(sead::Heap* heap) {
    _20.initFromBshopMaybe(mActor->getParam()->getRes().mShopData, heap);
    return true;
}

void NPCMakeArtifact::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = _20.sub_710091CE98(mActor->getParam()->getRes().mShopData, "Ancient");
    _41 = false;
    ksys::gdt::setFlag_Shop_IsDecide(false, false);
}

void NPCMakeArtifact::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCMakeArtifact::loadParams_() {}

void NPCMakeArtifact::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_40) {
        const bool done = _41;
        const bool open = ui::sub_7100A9844C();
        if (done) {
            if (open) {
                if (!ksys::gdt::getFlag_Shop_DecideTrig())
                    return;
                ksys::gdt::setFlag_Shop_IsDecide(true);
                ksys::gdt::setFlag_Shop_CurrentItemState(ksys::gdt::getFlag_Shop_ItemState());
                const char* name;
                ksys::gdt::getFlag_Shop_SelectItemName(&name);
                ksys::gdt::setFlag_PlacedItemName(name);
                ksys::gdt::setFlag_Shop_SelectItemNameJpn(name);
                ksys::gdt::setFlag_Shop_DecideTrig(false);
            }
            setFinished();
        } else {
            if (open)
                ui::sub_7100A9826C();
            else
                ui::sub_7100A98428(&_20);
            _41 = true;
        }
    } else {
        setFailed();
    }
}

}  // namespace uking::action
