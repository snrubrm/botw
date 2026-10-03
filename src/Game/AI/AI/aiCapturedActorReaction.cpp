#include "Game/AI/AI/aiCapturedActorReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CapturedActorReaction::CapturedActorReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CapturedActorReaction::~CapturedActorReaction() = default;

bool CapturedActorReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActorReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = true;
    auto* manager = sub_710072BA90(mActor);
    if (!manager) {
        setFailed();
        return;
    }
    if (manager->getField54() == 34) {
        if (!isCurrentChild("消滅")) {
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
            changeChild("消滅");
        }
    } else if (manager->getField50() == 17) {
        if (!isCurrentChild("怨念")) {
            mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
            changeChild("怨念");
        }
    } else {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e84.setBit(3);
        changeChild("死亡");
    }
}

void CapturedActorReaction::calc_() {
    if (_38) {
        _38 = false;
        return;
    }

    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr)
        return;

    const s32 damage_type = damage_mgr->getField54();
    const s32 field_50 = damage_mgr->getField50();
    if (damage_type == 0x22) {
        if (isCurrentChild("消滅"))
            return;
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("消滅");
    } else if (field_50 == 0x11) {
        if (isCurrentChild("怨念"))
            return;
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("怨念");
    } else {
        if (damage_type == -1)
            return;
        if (!isCurrentChild("死亡"))
            return;
        changeChild("死亡後ダメージ");
    }
}

void CapturedActorReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorReaction::loadParams_() {}

}  // namespace uking::ai
