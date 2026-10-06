#include "Game/AI/Action/actionNPCDyeShopReception.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"

namespace uking::action {

NPCDyeShopReception::NPCDyeShopReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCDyeShopReception::~NPCDyeShopReception() = default;

bool NPCDyeShopReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling only: the original computes the address of the "Normal" SafeString temporary (`mov x3, sp`)
// before the shop data pointer arithmetic, ours after the temporary's stores
void NPCDyeShopReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_Shop_IsDecide(false, false);
    ksys::gdt::setFlag_ColorChange_MaterialIndex(-1, false);
    if (ui::sub_7100A98514())
        return;
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        _1c = false;
        if (npc->_f88.giveItem(mActor->getParam()->getRes().mShopData, mActor->getName(), "Normal", false))
            _1c = true;
        _20 = 0;
        ui::sub_7100A984F0(&npc->_f88);
    }
}

void NPCDyeShopReception::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_1c) {
        if (_20 >= 2) {
            if (ksys::gdt::getFlag_Shop_DecideTrig()) {
                ksys::gdt::setFlag_Shop_IsDecide(true);
                ksys::gdt::setFlag_Shop_DecideTrig(false);
            }
            if (!ui::sub_7100A98514())
                setFinished();
        } else {
            _20 = _20 + 1;
        }
    } else {
        setFailed();
    }
}

}  // namespace uking::action
