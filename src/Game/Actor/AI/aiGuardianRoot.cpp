#include "Game/Actor/AI/aiGuardianRoot.h"
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "Game/Actor/actGuardian.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/Actor/Damage/dmgStruct20.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// 0x710003955c (declared only; same declaration as in actionGuardianActionBase.cpp): reads the actor's parameters.
struct Unk_710003955c {
    u8 _0[0x70];
    s32 _70;
};
const Unk_710003955c* sub_710003955C(ksys::act::Actor* actor);

namespace uking::ai {

GuardianRoot::GuardianRoot(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoot::~GuardianRoot() = default;

bool GuardianRoot::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    _50.x();
    auto* guardian = sub_710040DA6C();
    if (guardian && guardian->_14c8.isOnBit(0) && sub_710003955C(guardian)->_70 != 2) {
        changeToFeignDeath();
        return;
    }
    changeChild("待機", nullptr);
    sub_710040DDB0(0);
    sub_710040DE48(false);
}

void GuardianRoot::leave_() {
    GuardianAI::leave_();
}

bool GuardianRoot::handleMessage_(const ksys::Message* message) {
    auto* guardian = sub_710040DA6C();
    if (!message || !guardian)
        return true;
    if (_50.sub_710070AFFC(message, guardian))
        return true;
    if (message->getType() == 0x800004b) {
        _48 |= 1;
        return true;
    } else if (message->getType() == 0x800004c) {
        _48 |= 2;
        return true;
    } else if (message->getType() == 0x3000003) {
        auto* life = guardian->getLife();
        if (life && *life < 1)
            return true;
        changeChild("待機", nullptr);
        sub_710040DDB0(0);
        sub_710040DE48(false);
        return false;
    }
    return true;
}

void GuardianRoot::loadParams_() {
    GuardianAI::loadParams_();
    getMapUnitParam(&mIsSuspended_m, "IsSuspended");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
}

void GuardianRoot::changeToFeignDeath() {
    auto* guardian = sub_710040DA6C();
    if (guardian && sub_710003955C(guardian)->_70 == 1) {
        if (auto* body = guardian->getMainBody()) {
            body->setFixed(ksys::phys::Fixed(true), ksys::phys::PreserveVelocities(true));
            body->enableGroundCollision(false);
            body->enableWaterCollision(false);
        }
    }
    sub_710040DDB0(12);
    sub_710040DE48(false);
    changeChild("仮死", nullptr);
}

// NON_MATCHING: stack slots of the SafeString temporaries in the isCurrentChild chains, one b.le / b.lt
void GuardianRoot::calc_() {
    GuardianAI::calc_();
    auto* guardian = sub_710040DA6C();
    act::Guardian::Unk15a8* info;
    if (!guardian || !(info = sub_710040DC50())) {
        changeChild("待機", nullptr);
        sub_710040DDB0(0);
        sub_710040DE48(false);
        return;
    }

    sub_7100734270(guardian, mForceSetDropPos_a, info->_0);

    const auto isDead = [guardian] {
        auto* life = guardian->getLife();
        return life && *life <= 0;
    };

    if (!isDead()) {
        if (guardian->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
            changeChild("待機", nullptr);
            sub_710040DDB0(0);
            sub_710040DE48(false);
            return;
        }
        if (!isCurrentChild("仮死") && !isCurrentChild("落雷スタン") && _50._30) {
            ksys::eft::searchAndEmitELink(guardian, "Lightning");
            _50.x();
            sub_710040DE48(false);
            sub_710040DDB0(0);
            changeChild("落雷スタン", nullptr);
            return;
        }
        if (!isCurrentChild("仮死") && (_48 & 2)) {
            changeToFeignDeath();
            _48 &= ~2u;
            return;
        }
        if (isCurrentChild("仮死") && (guardian->checkBasicSig() || (_48 & 1))) {
            changeToWakeUp();
            return;
        }
    }

    _48 &= ~3u;

    const auto sendDamage = [](act::DamageManagerBase* manager, bool flag) {
        act::Struct20_2 damage;
        damage.mField_8 = 100;
        damage.mField_14 = -1;
        damage.mField_18 = 22;
        if (flag)
            damage.mField_1C |= 0x80;
        if (manager->mStruct20_a) {
            manager->mField_30.lock();
            manager->mStruct20_a->combineMaybe(&damage);
            manager->mField_30.unlock();
        }
    };

    bool react = false;
    bool send_damage = false;
    if (isCurrentChild("リアクション")) {
        send_damage = guardian->_14c8.isOnBit(13);
    } else {
        const bool stunned = isCurrentChild("落雷スタン");
        const bool hit_flag = guardian->_14c8.isOnBit(13);
        if (stunned) {
            send_damage = hit_flag;
        } else if (const bool sensed = sub_71005D6E28(guardian); hit_flag || sensed) {
            if (isDead()) {
                react = true;
            } else if (isCurrentChild("仮死")) {
                changeToWakeUp();
                return;
            } else if (isCurrentChild("待機") || isCurrentChild("見失い") || isCurrentChild("見回す")) {
                react = true;
            } else {
                auto* manager = guardian->getDamageMgr();
                const bool damaged = manager->checkDamageFlags(0) || manager->checkDamageFlags(7) ||
                                     manager->checkDamageFlags(11);
                if (hit_flag) {
                    sendDamage(manager, true);
                    react = true;
                } else {
                    react = damaged;
                }
            }
        }
    }
    if (send_damage)
        sendDamage(guardian->getDamageMgr(), false);

    if (react) {
        sub_710040DE48(false);
        changeChild("リアクション", nullptr);
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("起動")) {
            if (info->_48 || info->_4a[0]) {
                changeToChase();
                return;
            }
            changeChild("待機", nullptr);
            sub_710040DDB0(0);
            sub_710040DE48(false);
            return;
        }
        if (isCurrentChild("落雷スタン") || isCurrentChild("リアクション")) {
            changeToReactToSound();
            return;
        }
        if (isCurrentChild("追跡") || isCurrentChild("視覚反応")) {
            if (info->_48 || info->_4a[0]) {
                changeToChase();
                return;
            }
            changeChild("見失い", nullptr);
            sub_710040DDB0(6);
            sub_710040DE48(false);
            return;
        }
        if (info->_48 || info->_4a[0]) {
            changeToChase();
            return;
        }
        if (info->_49) {
            changeToReactToSound();
            return;
        }
        changeChild("待機", nullptr);
        sub_710040DDB0(0);
        sub_710040DE48(false);
        return;
    }

    if (isCurrentChild("追跡")) {
        if (!info->_48) {
            changeChild("見失い", nullptr);
            sub_710040DDB0(6);
            sub_710040DE48(false);
            return;
        }
    } else if (isCurrentChild("見失い")) {
        if (info->_48) {
            changeToChase();
            return;
        }
    } else if (isCurrentChild("待機") || isCurrentChild("見回す")) {
        if (info->_4a[0]) {
            changeToChase();
            return;
        }
        if (info->_48) {
            changeToReactToSight();
            return;
        }
        if (info->_49) {
            changeToReactToSound();
            return;
        }
    } else if (isCurrentChild("音反応") && info->_48) {
        changeToReactToSight();
        return;
    }
    guardian->getASList()->sub_710115F444(0, 0, &ksys::as::ASList::Unk2::sub_710042BBEC);
}

void GuardianRoot::changeToWakeUp() {
    if (auto* guardian = sub_710040DA6C()) {
        if (sub_710003955C(guardian)->_70 == 1) {
            if (auto* body = guardian->getMainBody()) {
                body->setFixed(ksys::phys::Fixed(false), ksys::phys::PreserveVelocities(true));
                body->enableGroundCollision(true);
                body->enableWaterCollision(true);
            }
        }
        _48 &= ~1u;
        guardian->emitBasicSigOn();
    } else {
        _48 &= ~1u;
    }
    sub_710040DDB0(13);
    sub_710040DE48(false);
    changeChild("起動", nullptr);
}

// NON_MATCHING: register allocation (the original keeps the rail pointer in x20 from the call on and the string-temp
// vtable pointer in x22).
void GuardianRoot::changeToChase() {
    sead::Vector3f pos;
    if (sub_710040E008(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        sead::Vector3f stop_pos;
        if (auto* rail = sub_7100EEF034(mActor, 0)) {
            mActor->getMtx().getTranslation(stop_pos);
            const f32 progress = sub_7100EEF7AC(rail, stop_pos, false, 0.2f, -0.0f);
            rail->calcTranslate(&stop_pos, progress);
        } else {
            mActor->getMtx().getTranslation(stop_pos);
        }
        pack.addFloat(180.0f, "DynStopTime", -1);
        pack.addVec3(stop_pos, "DynStopPos", -1);
        changeChild("追跡", &pack);
        sub_710040DDB0(5);
        sub_710040DE48(true);
    }
}

void GuardianRoot::changeToReactToSight() {
    sead::Vector3f pos;
    if (sub_710040E008(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("視覚反応", &pack);
        sub_710040DDB0(4);
        sub_710040DE48(false);
    }
}

void GuardianRoot::changeToReactToSound() {
    sead::Vector3f pos;
    if (sub_710040E048(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("音反応", nullptr);
        sub_710040DDB0(2);
        sub_710040DE48(false);
    }
}

}  // namespace uking::ai
