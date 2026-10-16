#include "Game/Actor/AI/aiHiddenOctarockNormal.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

HiddenOctarockNormal::HiddenOctarockNormal(const InitArg& arg) : EnemyNormal(arg) {}

HiddenOctarockNormal::~HiddenOctarockNormal() = default;

bool HiddenOctarockNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HiddenOctarockNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
    _410 = false;
    const s32 delay = *mOptionHitReactionDelay_s;
    _418 = delay;
    _41c = delay;
    _414 = delay;
    if (!*mIsHitGround_s) {
        if (auto* controller = mActor->getCharacterController()) {
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
            controller->enableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        }
    }
    sead::DynamicCast<uking::act::Enemy>(mActor);
}

void HiddenOctarockNormal::leave_() {
    auto* controller = mActor->getCharacterController();
    if (controller && *mIsHitGround_s)
        controller->sub_7100F60604();
    if (!*mIsHitGround_s) {
        if (auto* controller2 = mActor->getCharacterController())
            controller2->sub_7100F60604();
    }
    sead::DynamicCast<uking::act::Enemy>(mActor);
    EnemyNormal::leave_();
}

void HiddenOctarockNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mOptionHitReactionDelay_s, "OptionHitReactionDelay");
    getStaticParam(&mIsSitDown_s, "IsSitDown");
    getStaticParam(&mIsHitGround_s, "IsHitGround");
    getStaticParam(&mIsReactionByWigHit_s, "IsReactionByWigHit");
    getStaticParam(&mIsHide_s, "IsHide");
    getStaticParam(&mIsIvalidateSight_s, "IsIvalidateSight");
    getStaticParam(&mIsSealHearing_s, "IsSealHearing");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
}

bool HiddenOctarockNormal::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() && !isCurrentChild("攻撃反応");
}

s32 HiddenOctarockNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 2};
    return sTable[idx];
}

void HiddenOctarockNormal::m37() {
    EnemyNormal::m37();
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7EAE4(0);
    }
}

void HiddenOctarockNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("カツラ反応") || isCurrentChild("攻撃反応") ||
        (m52(idx) == 2 && *mIsSealHearing_s)) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m49(out, idx);
}

ksys::act::Unk_7100d78e50* HiddenOctarockNormal::m47(ksys::act::AwarenessInstance* awareness,
                                                     ksys::act::Unk_71024dccf8* filter, s32 a3) {
    auto* entry = EnemyNormal::m47(awareness, filter, a3);
    if (entry && entry->_a0 != 0)
        return entry;

    filter->_8 = -1;
    while (awareness->_260[3]) {
        entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, filter);
        if (!entry)
            return nullptr;
        if (m46(entry->_88, entry->_0.mLink))
            return entry;
    }
    return nullptr;
}

void HiddenOctarockNormal::m60(Unk3* out) {
    if (!isCurrentChild("攻撃反応") || !sub_71005D9050(mActor))
        out->_0 = -1;
}

void HiddenOctarockNormal::m61(Unk3* out) {
    if (isCurrentChild("プレイヤー発見") && sub_710039DB34(true)) {
        auto* target = sub_71005D9050(mActor);
        if (target && ksys::act::isPlayerProfile(target))
            out->_4 |= 2;
        out->_0 = 2;
    }
}

void HiddenOctarockNormal::m69(Unk2* target) {
    EnemyNormal::m69(target);
    _410 = false;
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
    sub_71005D8E9C(mActor);
}

void HiddenOctarockNormal::m34() {
    if (*mIsHide_s && (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
                       testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
                       testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4))) {
        _3ac.reset(8);
        if (*mIsSitDown_s)
            sub_7100432294();
        changeChild("隠れる");
        return;
    }
    if (*mIsSitDown_s)
        sub_7100432294();
    EnemyNormal::m34();
}

// NON_MATCHING: only the placement of `add x21, sp, #0x18` (the pack address kept for the destructor loop), which the
// original emits after sub_71005D8E9C instead of before addVec3.
// NON_MATCHING: block layout and register allocation; the original tests the wig hit inside the condition (no
// flag) and keeps &_414 in a register.
void HiddenOctarockNormal::calc_() {
    bool wig_hit = false;
    if (*mIsReactionByWigHit_s) {
        if (_410) {
            wig_hit = true;
        } else {
            auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
            wig_hit = child && sub_71007A274C(child);
        }
    }

    if (wig_hit) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
        if (child && sub_71007A274C(child)) {
            auto* weapon = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                if (weapon) {
                    enemy->_e08.sub_71006E4478(&sub_71007A255C(weapon, 0)->_d8,
                                               sub_71007A255C(weapon, 0)->_58);
                    enemy->_e08._5c = true;
                }
            }
            _410 = true;
            ksys::Timer::update(&_414, -1.0f);
        } else if (_410) {
            ksys::Timer::update(&_414, -1.0f);
        } else {
            s32 delay = _418;
            if (_41c != _418)
                delay = sead::GlobalRandom::instance()->getS32Range(_418, _41c);
            _414 = delay;
        }

        if (getCurrentChild()->isChangeable() && !(_414 > 0.0f) && !isCurrentChild("カツラ反応")) {
            _410 = false;
            changeToWigReaction();
            return;
        }
    } else if (!mActor->getConnectedCalcChild() && getCurrentChild()->isChangeable() &&
               !isCurrentChild("リロード")) {
        ksys::Timer::update(&_414, -1.0f);
        if (!(_414 > 0.0f) && getCurrentChild()->isChangeable() &&
            !isCurrentChild("カツラ反応")) {
            _410 = false;
            changeToWigReaction();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (isCurrentChild("攻撃反応") || isCurrentChild("カツラ反応")) {
        u16 flags = 0;
        if (auto* entry = sub_71003A0114(false, 0, 0, &flags))
            sub_71005D8DE8(mActor, entry->_0.mLink, &entry->_58, nullptr);
        if (child->isFinished() || child->isFailed()) {
            if (_410) {
                changeToWigReaction();
                return;
            }
            if (!mActor->getConnectedCalcChild()) {
                _3ac.reset(8);
                changeChild("リロード");
                if (*mIsIvalidateSight_s) {
                    if (auto* awareness = mActor->getAwareness())
                        awareness->sub_7100D7EAE4(0);
                }
                return;
            }
            if (!sub_71005D8F28(mActor)) {
                m37();
                return;
            }
        } else {
            if (!child->isChangeable() || !sub_71005D8F28(mActor))
                return;
        }
    } else if (isCurrentChild("リロード")) {
        if (!child->isFinished() && !child->isFailed())
            return;
        if (!sub_71005D8F28(mActor)) {
            if (!sub_710039FFA8(false))
                m37();
            return;
        }
    } else if (isCurrentChild("隠れる")) {
        if (!child->isFinished() && !child->isFailed())
            return;
        if (mActor->getConnectedCalcChild() || sub_71005D8F28(mActor)) {
            m37();
            return;
        }
        _3ac.reset(8);
        changeChild("リロード");
        if (*mIsIvalidateSight_s) {
            if (auto* awareness = mActor->getAwareness())
                awareness->sub_7100D7EAE4(0);
        }
        return;
    } else if (isCurrentChild("飛び出す")) {
        if (child->isFinished() || child->isFailed()) {
            setFinished();
            return;
        }
        if (*mIsHitGround_s)
            return;
        auto* actor = mActor;
        if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false))
            return;
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F60604();
        return;
    } else {
        EnemyNormal::calc_();
        return;
    }

    Unk2 target;
    target.sub_710039E308(sub_71005D9050(mActor));
    sub_71003A02E0(&target);
}

void HiddenOctarockNormal::changeToWigReaction() {
    s32 delay = _418;
    _410 = false;
    if (_41c != _418)
        delay = sead::GlobalRandom::instance()->getS32Range(_418, _41c);
    _414 = delay;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D8F28(mActor) ? sub_71005D9330(mActor) : getPlayerPosition(), "TargetPos", -1);
    sub_71005D8E9C(mActor);
    changeChild("カツラ反応", &pack);
    if (*mIsIvalidateSight_s) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
}

void HiddenOctarockNormal::sub_7100432294() {
    auto* controller = mActor->getCharacterController();
    if (!controller || !*mIsHitGround_s)
        return;
    controller->sub_7100F605F0();
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGround);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundObject);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    controller->disableContactLayer(ksys::phys::ContactLayer::EntityTree);
}

}  // namespace uking::ai
