#include "Game/Actor/AI/aiPreyReaction.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PreyReaction::PreyReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyReaction::~PreyReaction() = default;

bool PreyReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    _38 = true;
}

// NON_MATCHING: child selection joins and SafeString/pack stack slots differ.
void PreyReaction::calc_() {
    if (isCurrentChild("ダメージ") || isCurrentChild("炎上") || isCurrentChild("凍結") ||
        isCurrentChild("痺れ"))
        setRootAiFlag(ksys::act::ai::RootAiFlag::_0);
    if (_38) {
        _38 = false;
        return;
    }
    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    auto* manager = sub_710072BA90(actor);
    if (!enemy || !manager)
        return;
    const s32 kind = manager->getField54();
    if (kind == 34 && !isCurrentChild("消滅")) {
        if (auto* life = mActor->getLife())
            *life = 0;
        changeChild("消滅", nullptr);
        return;
    }
    if (kind == 33 || enemy->m151(10)) {
        if (!isCurrentChild("溶岩"))
            changeChild("溶岩", nullptr);
        return;
    }
    if (enemy->m151(11)) {
        if (!isCurrentChild("怨念"))
            changeChild("怨念", nullptr);
        return;
    }
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive))
        return;
    auto* life = mActor->getLife();
    if (u32(kind - 29) < 5 || (life && *life < 1)) {
        if (auto* current_life = mActor->getLife())
            *current_life = 0;
        changeChild("死亡", nullptr);
        return;
    }
    if (isCurrentChild("凍結")) {
        if (kind == 23)
            changeChild("ダメージ", nullptr);
    } else if (isCurrentChild("痺れ")) {
        if (enemy->m151(3)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "IsEnableThrowOffAttack", -1);
            changeChild("凍結", &pack);
        }
    } else if (!m35()) {
        _38 = false;
    }
}

// NON_MATCHING: child selection joins and pack cleanup scheduling differ.
bool PreyReaction::m35() {
    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    auto* manager = sub_710072BA90(actor);
    if (!enemy || !manager) {
        setFailed();
        return false;
    }
    const s32 kind = manager->getField54();
    if (kind == 34) {
        if (auto* life = mActor->getLife())
            *life = 0;
        changeChild("消滅", nullptr);
        return true;
    }
    if (kind == 33 || enemy->m151(10)) {
        changeChild("溶岩", nullptr);
        return true;
    }
    if (enemy->m151(11)) {
        changeChild("怨念", nullptr);
        return true;
    }
    auto* life = mActor->getLife();
    if (u32(kind - 29) < 5 || (life && *life < 1)) {
        if (auto* current_life = mActor->getLife())
            *current_life = 0;
        changeChild("死亡", nullptr);
        return true;
    }
    if (enemy->m151(3)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "IsEnableThrowOffAttack", -1);
        changeChild("凍結", &pack);
        return true;
    }
    if (enemy->m151(4)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "IsEnableThrowOffAttack", -1);
        changeChild("痺れ", &pack);
        return true;
    }
    if (!isCurrentChild("気絶") && enemy->_e84.isOnBit(3)) {
        changeChild("気絶", nullptr);
        return true;
    }
    if (kind == 18) {
        changeChild("炎上", nullptr);
        return true;
    }
    if (u32(kind - 15) >= 12 && !manager->_216.isOn(2))
        return false;
    const bool already_damage = isCurrentChild("ダメージ");
    if (kind == 16 || already_damage || kind == 19)
        return false;
    changeChild("ダメージ", nullptr);
    return true;
}

void PreyReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyReaction::loadParams_() {}

void PreyReaction::m34() {
    if (m35())
        return;

    if (auto* manager = sub_710072BA90(mActor)) {
        manager->getField50();
        manager->getField54();
    }

    sead::FixedSafeString<128> message;
    message.format("%s：分岐条件が設定されていないリアクションです。", mActor->getName().cstr());
    setFailed();
    changeChild("ダメージ");
}

bool PreyReaction::isFinished() const {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

}  // namespace uking::ai
