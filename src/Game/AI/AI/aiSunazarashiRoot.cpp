#include "Game/AI/AI/aiSunazarashiRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include <cmath>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SunazarashiRoot::SunazarashiRoot(const InitArg& arg) : PreyRoot(arg) {}

SunazarashiRoot::~SunazarashiRoot() = default;

bool SunazarashiRoot::init_(sead::Heap* heap) {
    if (!PreyRoot::init_(heap))
        return false;

    if (auto* physics = mActor->getPhysics()) {
        if (auto* cloth = physics->getClothSet())
            cloth->_70 |= 0x10000;
    }
    if (*mForbidSystemDeleteDistance_m)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void SunazarashiRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (*mEnableHangAlways_s)
        ksys::act::enableAttClient(actor, "Hang");
    else
        ksys::act::disableAttClient(actor, "Hang");

    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(0x10);

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    *mSunazarashiReturnPos_a = pos;
    _290 = 0.0f;
    _294 = 0.0f;
    _298 = 1.0f;
    _29c = 150.0f;
    _2a0 = 10.0f;
    PreyRoot::enter_(params);
}

void SunazarashiRoot::leave_() {
    PreyRoot::leave_();
}

void SunazarashiRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mStunNoiseLevel_s, "StunNoiseLevel");
    getStaticParam(&mClashSpeed_s, "ClashSpeed");
    getStaticParam(&mClashAngle_s, "ClashAngle");
    getStaticParam(&mEnableHangAlways_s, "EnableHangAlways");
    getMapUnitParam(&mForbidSystemDeleteDistance_m, "ForbidSystemDeleteDistance");
    getAITreeVariable(&mSunazarashiReturnPos_a, "SunazarashiReturnPos");
}

bool SunazarashiRoot::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("牽引")) {
        if (_238._30)
            return false;
        if (_238.m2(*message))
            return true;
    }
    return PreyRoot::handleMessage_(message);
}

// NON_MATCHING: the original materialises a dead bool (w23 = 0 for "衝突", 1 for "びっくり") that is never used
bool SunazarashiRoot::m39() {
    auto* actor = mActor;
    if (isCurrentChild("砂地復帰") && actor->m139() < 1.0f)
        return false;

    if (isCurrentChild("衝突") || isCurrentChild("びっくり")) {
        if (getCurrentChild()->isFinishedOrFailed()) {
            sub_7100504A9C(8, true);
            if (mActor->getASList()->sub_710115ED5C(66, 10))
                ksys::act::enableAttClient(actor, "Hang");
            return true;
        }
    }
    return PreyRoot::m39();
}

// NON_MATCHING: identical except the operand order of one fmul in the cross product (n.x * dir.z vs dir.z * n.x)
bool SunazarashiRoot::sub_71005AF91C() {
    if (isCurrentChild("牽引")) {
        if (auto* controller = mActor->getCharacterController()) {
            const s32 count = sub_71007A47C4(mActor);
            f32 min_angle = sead::Mathf::pi();
            for (s32 i = 0; i < count; ++i) {
                auto* contact = sub_71007A471C(mActor, i);
                if (!contact)
                    continue;
                sead::Vector3f target = contact->_0;
                sead::Vector3f pos;
                mActor->getMtx().getTranslation(pos);
                target.y = pos.y;
                const sead::Vector3f dir = target - pos;
                const f32 dot = dir.dot(controller->_64);
                sead::Vector3f cross;
                cross.setCross(dir, controller->_64);
                const f32 angle = std::atan2(cross.length(), dot);
                if (min_angle > angle)
                    min_angle = angle;
            }

            if (min_angle < *mClashAngle_s) {
                if (_280 - min_angle >= sead::Mathf::deg2rad(3.0f)) {
                    if (controller->sub_7100F5EF00() > *mClashSpeed_s * 30.0f && !_279)
                        return true;
                }
                _279 = true;
                _27c = 30.0f;
                return false;
            }
            _280 = min_angle;
        }

        if (_27c > 0.0f) {
            ksys::Timer::update(&_27c, -1.0f);
            if (_27c <= 0.0f) {
                _279 = false;
                _280 = sead::Mathf::pi();
            }
        }
    }
    return false;
}

void SunazarashiRoot::m41() {
    if (!isCurrentChild("牽引")) {
        if (auto* info = ksys::act::PlayerInfo::instance()) {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&info->getPlayerLink(), &player);
            if (player.hasProc() && player.isRidingSandSeal() &&
                player.isRidingThisSandSeal(mActor)) {
                ksys::act::disableAttClient(mActor, "Hang");
                mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
                _29c = 150.0f;
                _298 = 1.0f;
                _290 = 0.0f;
                _294 = 0.0f;
                _279 = false;
                _280 = sead::Mathf::pi();
                changeChild("牽引");
                return;
            }
        }
    }

    if (isCurrentChild("通常行動") && _29c <= 0.0f) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
        _29c = 150.0f;
        changeChild("砂地復帰");
        return;
    }

    if (sub_71005AF91C()) {
        changeChild("衝突");
        return;
    }

    auto* actor = mActor;
    if (!(isCurrentChild("砂地復帰") && actor->m139() < 1.0f) && _278) {
        const s32* life = mActor->getLife();
        if (!life || *life >= 1) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
            changeChild("びっくり");
            return;
        }
    }
    PreyRoot::m41();
}

void SunazarashiRoot::m42() {
    if ((isCurrentChild("水中行動") && !m34()) || isCurrentChild("牽引")) {
        if (mActor->getASList()->sub_710115ED5C(66, 10)) {
            sub_71005047A8();
        } else {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
            _29c = 150.0f;
            changeChild("砂地復帰");
        }
    } else if (m38()) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
        changeChild("びっくり");
    }
}

void SunazarashiRoot::m43() {
    if (!isCurrentChild("牽引"))
        PreyRoot::m43();
}

void SunazarashiRoot::m44() {
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&info->getPlayerLink(), &player);
        if (player.hasProc() && player.isRidingSandSeal() && player.isRidingThisSandSeal(mActor)) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
            _29c = 150.0f;
            _298 = 1.0f;
            _290 = 0.0f;
            _294 = 0.0f;
            _279 = false;
            _280 = sead::Mathf::pi();
            changeChild("牽引");
            return;
        }
    }
    sub_71005047A8();
}

}  // namespace uking::ai
