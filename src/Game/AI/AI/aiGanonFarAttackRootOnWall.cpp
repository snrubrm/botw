#include "Game/AI/AI/aiGanonFarAttackRootOnWall.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actLastBoss.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

GanonFarAttackRootOnWall::GanonFarAttackRootOnWall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonFarAttackRootOnWall::~GanonFarAttackRootOnWall() = default;

bool GanonFarAttackRootOnWall::sub_71003E8F1C() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const s32 pillar_max = *mPillarMax_s;
        if (pillar_max >= 0) {
            s32 i = -1;
            do {
                ++i;
                sead::FormatFixedSafeString<64> name("IronPile%d", i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    if (accessor.sub_7100D13BB8())
                        return true;
                }
            } while (i < pillar_max);
        }
    }
    return false;
}

// NON_MATCHING: the original schedules the per-state weights after the Random::getU32 call
// (one fewer callee-saved register).
void GanonFarAttackRootOnWall::sub_71003E8884() {
    const int state = _54;
    auto* boss = mActor;
    u32 can_lightning = state != 5;
    u32 can_tornado = state != 4;
    u32 can_ice = state != 6;
    u32 can_gust = state != 7;
    u32 can_beam = state != 8;
    if (auto* last_boss = sead::DynamicCast<act::LastBoss>(boss); last_boss && last_boss->_14e8.isOnBit(1)) {
        can_gust = 0;
        can_ice = 0;
        can_tornado = 0;
        can_lightning = 0;
    } else {
        can_beam = 0;
    }

    const u32 count = (state != 1) + (state != 2) + (state != 3) + can_beam + can_gust + can_ice +
                      can_tornado + can_lightning;
    const int r = int( sead::GlobalRandom::instance()->getU32(count * 10));
    const int arrow = state == 1 ? 0 : 10;
    const int spear = state == 2 ? 0 : 10;
    const int fireball = state == 3 ? 0 : 10;

    int limit = arrow;
    if (r < limit) {
        _54 = 1;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("弓矢攻撃", &pack);
        return;
    }
    if (r < (limit += spear)) {
        changeToThrowSpear();
        return;
    }
    if (r < (limit += fireball)) {
        changeToFireball();
        return;
    }
    if (r < (limit += can_lightning ? 10 : 0)) {
        changeToLightning();
        return;
    }
    if (r < (limit += can_tornado ? 10 : 0)) {
        changeToTornado();
        return;
    }
    if (r < (limit += can_ice ? 10 : 0)) {
        changeToIcePillar();
        return;
    }
    if (r < limit + (can_gust ? 10 : 0)) {
        _54 = 7;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("疾風弾", &pack);
    } else {
        _54 = 8;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("ビーム攻撃", &pack);
    }
}

bool GanonFarAttackRootOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonFarAttackRootOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0;
    sub_71003E8884();
}

// NON_MATCHING: Target pointer selection and saved-register allocation differ.
void GanonFarAttackRootOnWall::calc_() {
    const bool wait = isCurrentChild("落雷後待機");
    auto* child = getCurrentChild();
    child->setDynamicParam(wait ? *mViewPos_d : *mTargetPos_d, "TargetPos");
    if (sub_71003E8F1C() && getCurrentChild()) {
        child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("落雷")) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mViewPos_d, "TargetPos", -1);
                changeChild("落雷後待機", &pack);
                return;
            }
            if (isCurrentChild("落雷後待機") && _50 <= 2) {
                changeToLightning();
                return;
            }
        }
    }
    if (getCurrentChild()) {
        child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            setFinished();
    }
}

void GanonFarAttackRootOnWall::leave_() {
    sub_71003E9150();
}

void GanonFarAttackRootOnWall::loadParams_() {
    getStaticParam(&mPillarMax_s, "PillarMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

bool GanonFarAttackRootOnWall::isFinished() const {
    if (getCurrentChild()) {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && !isCurrentChild("落雷") &&
            !isCurrentChild("落雷後待機")) {
            return true;
        }
    }
    return ActionBase::isFinished();
}

void GanonFarAttackRootOnWall::sub_71003E9150() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    const int max = *mPillarMax_s;
    for (int i = 0; i <= max; ++i) {
        sead::FormatFixedSafeString<64> name("IronPile%d", i);
        if (enemy->getActorPartsActor(name).hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                                nullptr, true);
        }
    }
}

void GanonFarAttackRootOnWall::changeToThrowSpear() {
    _54 = 2;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("槍投げ", &pack);
}

void GanonFarAttackRootOnWall::changeToFireball() {
    _54 = 3;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("火球", &pack);
}

void GanonFarAttackRootOnWall::changeToTornado() {
    _54 = 4;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("竜巻", &pack);
}

void GanonFarAttackRootOnWall::changeToIcePillar() {
    _54 = 6;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("氷柱", &pack);
}

void GanonFarAttackRootOnWall::changeToLightning() {
    _54 = 5;
    ++_50;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mViewPos_d, "ViewPos", -1);
    changeChild("落雷", &pack);
}

}  // namespace uking::ai
