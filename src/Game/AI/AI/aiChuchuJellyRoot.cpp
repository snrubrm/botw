#include "Game/AI/AI/aiChuchuJellyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDropData.h"

namespace uking::ai {

ChuchuJellyRoot::ChuchuJellyRoot(const InitArg& arg) : ItemRoot(arg) {}

ChuchuJellyRoot::~ChuchuJellyRoot() = default;

bool ChuchuJellyRoot::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ChuchuJellyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
    mActor->getChemicalStuff();
}

void ChuchuJellyRoot::calc_() {
    ItemRoot::calc_();
    if (isCurrentChild("リアクション"))
        return;
    auto* actor = mActor;
    if (!sub_71005D6E28(actor))
        return;
    if (auto* mgr = sead::DynamicCast<dmg::DamageManager>(actor->getDamageMgr())) {
        if (mgr->getDamageType() == 9)
            return;
    }
    if (auto* drop = sead::DynamicCast<ksys::act::DropData>(mActor->getDropData()))
        drop->clearFlags();
    changeChild("リアクション");
}

void ChuchuJellyRoot::leave_() {
    ItemRoot::leave_();
}

void ChuchuJellyRoot::loadParams_() {
    ItemRoot::loadParams_();
}

}  // namespace uking::ai
