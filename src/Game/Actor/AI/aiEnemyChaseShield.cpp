#include "Game/Actor/AI/aiEnemyChaseShield.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

EnemyChaseShield::EnemyChaseShield(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChaseShield::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyChaseShield::sub_71003835C0() {
    setFailed();
    const s32 index = *mEquipItemSearchIdx_s;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->_c38[index].reset();
        enemy->_e80.resetBit(index);
    }
}

// NON_MATCHING: the original has no null test of the proc before the RTTI virtual call (clang keeps one for
// sead::DynamicCast) and dereferences the possibly null cast result.
bool EnemyChaseShield::sub_7100383680() {
    if (!mTargetWeapon_d || !mTargetWeapon_d->hasProc())
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mTargetWeapon_d->getProc(nullptr, nullptr));
    const sead::Vector3f position = actor->getMtx().getTranslation();
    return !sub_710072DDB8(position, mActor->getMtx(), *mTurnAng_s);
}

void EnemyChaseShield::sub_71003843E4() {
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        sead::Vector3f position;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(position);
        if (_58) {
            _58->_8 = -1;
            if (auto* nav = _58->_0) {
                nav->inlineReset();
                auto* unk = _58;
                if (auto* nav2 = unk->_0) {
                    nav2->sub_7100F75F8C(position);
                    unk->_8 = 0;
                }
            }
        }
    }
}

void EnemyChaseShield::sub_7100383768() {
    bool reachable = false;
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        sead::Vector3f position;
        accessor.getActorMtx().getTranslation(position);
        reachable = sub_710072F8E4(mActor, position, nullptr, 3.0f);
    }
    if (!reachable)
        sub_71003843E4();

    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    auto* link2 = mTargetWeapon_d;
    if (link2 && link2->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link2, &accessor);
        accessor.getActorMtx().getTranslation(target);
    } else {
        target = sub_71005D9330(mActor);
    }
    pack.addVec3(target, "TargetPos", -1);
    changeChild("追跡", &pack);
}

void EnemyChaseShield::enter_(ksys::act::ai::InlineParamPack*) {
    _58 = sub_71005E2BCC(mActor);
    if (!_58) {
        changeToRotate();
        setFailed();
        return;
    }
    if (_58->_0)
        _58->_0->sub_7100F7604C(0.2f);
    act::Weapon* weapon = nullptr;
    if (mTargetWeapon_d) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(mTargetWeapon_d->getProc(nullptr, nullptr));
        weapon = sead::DynamicCast<act::Weapon>(actor);
    }
    if (!weapon || weapon->hasParentActor()) {
        changeToRotate();
        sub_71003835C0();
        return;
    }
    if (sub_7100383680())
        changeToRotate();
    else
        sub_7100383768();
}

// NON_MATCHING: stack layout of the SafeString temporaries and the accessor, block layout of the shared exits.
void EnemyChaseShield::calc_() {
    // Acquires the shield when it is in reach, gives up otherwise.
    const auto acquireOrFail = [this](act::Weapon* weapon) {
        auto* actor = mActor;
        const f32 reach = *mShieldReachDist_s;
        if (sub_7100738FA8(actor, weapon) ||
            (weapon->getMtx().getTranslation() - actor->getMtx().getTranslation()).length() < reach) {
            changeToAcquire();
        } else {
            sub_71003835C0();
        }
    };
    const auto getWeapon = [this]() -> act::Weapon* {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(mTargetWeapon_d->getProc(nullptr, nullptr));
        return sead::DynamicCast<act::Weapon>(actor);
    };
    const auto updateTargetPos = [this] {
        auto* link = mTargetWeapon_d;
        if (!link || !link->hasProc())
            return;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転")) {
            sub_7100383768();
            return;
        }
        if (isCurrentChild("追跡") || isCurrentChild("ナビ追跡")) {
            if (!mTargetWeapon_d) {
                sub_71003835C0();
                return;
            }
            auto* weapon = getWeapon();
            if (!weapon) {
                sub_71003835C0();
                return;
            }
            acquireOrFail(weapon);
            return;
        }
        if (isCurrentChild("取得")) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                sub_71003835C0();
            return;
        }
    }

    if (!isCurrentChild("追跡") && !isCurrentChild("ナビ追跡") && !isCurrentChild("回転"))
        return;

    if (!getCurrentChild()->isChangeable()) {
        updateTargetPos();
        return;
    }

    auto* link = mTargetWeapon_d;
    if (!link || !link->hasProc()) {
        sub_71003835C0();
        return;
    }
    auto* weapon = getWeapon();
    if (!weapon || weapon->hasParentActor() || weapon->sub_71002E9A50() ||
        weapon->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
        sub_71003835C0();
        return;
    }
    {
        auto* actor = mActor;
        const f32 reach = *mShieldReachDist_s;
        if (sub_7100738FA8(actor, weapon) ||
            (weapon->getMtx().getTranslation() - actor->getMtx().getTranslation()).length() < reach) {
            changeToAcquire();
            return;
        }
    }

    if (isCurrentChild("追跡")) {
        if (auto* unk = _58) {
            if (unk->_8 == 2) {
                sub_71003835C0();
                return;
            }
            if (unk->_8 == 1) {
                if (auto* nav = unk->_0) {
                    sead::Vector3f end;
                    {
                        auto lock = sead::makeScopedLock(nav->_1e0);
                        end = nav->_194;
                    }
                    auto* nav2 = _58->_0;
                    if (nav2 && (_58->_8 == 1 || _58->_8 == 3)) {
                        sead::Vector3f goal;
                        {
                            auto lock = sead::makeScopedLock(nav2->_1e0);
                            goal = nav2->_1a0;
                        }
                        if (sead::Vector2f(end.x - goal.x, end.z - goal.z).length() >= *mShieldReachDist_s) {
                            sub_71003835C0();
                            return;
                        }
                    }
                }
                sub_7100384290();
                return;
            }
        }
        updateTargetPos();
        return;
    }

    if (isCurrentChild("ナビ追跡")) {
        auto* nav = mActor->m45();
        if (nav && _58) {
            if (_58->_8 != 3) {
                sead::Vector3f pos;
                {
                    auto lock = sead::makeScopedLock(nav->_1e0);
                    pos = nav->_1ac;
                }
                if ((pos - mActor->getMtx().getTranslation()).length() > *mShieldReachDist_s) {
                    updateTargetPos();
                    return;
                }
            }
            auto* weapon2 = getWeapon();
            if (!weapon2) {
                updateTargetPos();
                return;
            }
            acquireOrFail(weapon2);
            return;
        }
    }
    updateTargetPos();
}

void EnemyChaseShield::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mTurnAng_s, "TurnAng");
    getStaticParam(&mShieldReachDist_s, "ShieldReachDist");
}

void EnemyChaseShield::changeToRotate() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    } else {
        pos = sub_71005D9330(mActor);
    }

    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

void EnemyChaseShield::sub_7100384290() {
    if (_58)
        _58->_8 = -1;

    auto* link = mTargetWeapon_d;
    sead::Vector3f pos;
    if (link && link->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    } else {
        pos = sub_71005D9330(mActor);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ナビ追跡", &pack);
}

void EnemyChaseShield::changeToAcquire() {
    ksys::act::ai::InlineParamPack pack;
    auto* link = mTargetWeapon_d;
    if (link && link->hasProc()) {
        sead::Vector3f pos;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
        pack.addVec3(pos, "TargetPos", -1);
        pack.addActor(*mTargetWeapon_d, "TargetWeapon", -1);
    } else {
        pack.addVec3(sead::Vector3f::zero, "TargetPos", -1);
        pack.addActor(ksys::act::getDummyBaseProcLink(), "TargetWeapon", -1);
    }
    changeChild("取得", &pack);
}

}  // namespace uking::ai
