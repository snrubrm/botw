#include "Game/AI/AI/aiWolfLinkReaction.h"
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WolfLinkReaction::WolfLinkReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkReaction::~WolfLinkReaction() = default;

bool WolfLinkReaction::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<act::WolfLink>(mActor);
    return true;
}

void WolfLinkReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    _38 = true;
}

void WolfLinkReaction::leave_() {}

void WolfLinkReaction::loadParams_() {}

void WolfLinkReaction::m34() {
    if (m35())
        return;

    if (auto* manager = sub_710072BA90(mActor)) {
        manager->getField50();
        manager->getField54();
    }

    sead::FixedSafeString<128> message;
    message.format("%s：分岐条件が設定されていないリアクションです。", mActor->getName().cstr());
    setFailed();
    changeChild("小ダメージ");
}

// NON_MATCHING: the life guard and fallback return paths are arranged differently.
bool WolfLinkReaction::m35() {
    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    auto* manager = sub_710072BA90(actor);
    if (!enemy || !manager) {
        setFailed();
        return false;
    }
    const s32 kind = manager->getField54();
    if (kind == 34) {
        changeChild("消滅");
        return true;
    }
    auto* life = mActor->getLife();
    if ((kind >= 29 && kind <= 33) || (life && *life < 1)) {
        changeChild("死亡");
        return true;
    }
    if (enemy->m151(3)) {
        changeChild("凍結");
        return true;
    }
    if (enemy->m151(4)) {
        changeChild("痺れ");
        return true;
    }
    if (!isCurrentChild("気絶") && enemy->_e84.isOnBit(3)) {
        changeChild("気絶");
        return true;
    }
    switch (kind) {
    case 18:
        changeChild("炎上");
        return true;
    case 20:
        changeChild("突風");
        return true;
    case 21:
    case 22:
    case 23:
    case 27:
        changeChild("大ダメージ");
        return true;
    default:
        break;
    }
    if (!(kind >= 15 && kind <= 24) && !manager->_216.isOn(2))
        return false;
    const bool is_small_damage = isCurrentChild("小ダメージ");
    if (kind == 16 || is_small_damage || kind == 19)
        return false;
    changeChild("小ダメージ");
    return true;
}

bool WolfLinkReaction::isFinished() const {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

}  // namespace uking::ai
