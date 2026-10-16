#include "Game/Actor/AI/aiSunazarashiRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include <cmath>
#include "Game/Actor/aiUnk_71005E0AAC.h"
#include "Game/Actor/aiUnk_71006F1DF0.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

bool Unk_7102426418::m2(ksys::act::Unk_71024dc978* entry) {
    return entry->m5(1);
}

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
    _290.value = 0.0f;
    _290.previous_value = 0.0f;
    _290.rate = 1.0f;
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
// NON_MATCHING: stack slots only (the original shares one slot between the velocity and the position copy, and
// another between the string temporaries and the hit position)
// Updates the stun state (_278: damage type 4 or a noise above StunNoiseLevel), the sand flag of the AS
// parameters, the return position while towed on sand ("牽引") and the "Hang" attention client.
void SunazarashiRoot::calc_() {
    bool stunned;
    auto* damage = mActor->getDamageMgr();
    if (damage && damage->getField50() == 4) {
        stunned = true;
    } else {
        stunned = false;
        if (auto* awareness = mActor->getAwareness()) {
            Unk_7102426418 filter;
            while (auto* sensor = awareness->_260[1]) {
                auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
                if (!entry) {
                    stunned = false;
                    break;
                }
                if (entry->_a4 > *mStunNoiseLevel_s) {
                    stunned = true;
                    break;
                }
            }
        }
    }
    _278 = stunned;

    auto* controller = mActor->getCharacterController();
    if (controller) {
        const ksys::phys::MaterialMask mask = controller->sub_7100F609CC();
        if (sub_71006F1E70(mask)) {
            mActor->getASList()->x_2(0x42, 10, true, false);
            _2a0 = 10.0f;
        } else {
            ksys::Timer::update(&_2a0, -1.0f);
            if (_2a0 < 0.0f)
                mActor->getASList()->x_2(0x42, 10, false, false);
        }
    }

    if (isCurrentChild("牽引") && controller) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.x != 0.0f || velocity.z != 0.0f) {
            sead::Vector3f hit{0, 0, 0};
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            bool far = false;
            if (sub_71005E0788(pos, &hit)) {
                const sead::Vector2f diff{hit.x - mSunazarashiReturnPos_a->x, hit.z - mSunazarashiReturnPos_a->z};
                far = diff.length() >= 3.0f;
            }
            if (!far) {
                _290.reset(0.0f, 1.0f);
            } else {
                _290.update();
                if (_290.hasEnded(10.0f)) {
                    _284 = hit;
                } else if (_290.hasEnded(20.0f)) {
                    *mSunazarashiReturnPos_a = _284;
                    _290.reset(0.0f, 1.0f);
                }
            }
        }
    }

    const bool flag = mActor->getASList()->sub_710115ED5C(0x42, 10);
    if (isCurrentChild("砂地復帰")) {
        if (*mEnableHangAlways_s && flag && isCurrentAction("移動"))
            ksys::act::enableAttClient(mActor, "Hang");
        else
            ksys::act::disableAttClient(mActor, "Hang");
    } else if (isCurrentChild("通常行動")) {
        if (*mEnableHangAlways_s && flag)
            ksys::act::enableAttClient(mActor, "Hang");
        else
            ksys::act::disableAttClient(mActor, "Hang");
        if (flag)
            _29c = 150.0f;
        else
            ksys::Timer::update(&_29c, -1.0f);
    }

    PreyRoot::calc_();
}

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
        if (auto* info = uking::act::PlayerInfo::instance()) {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&info->getPlayerLink(), &player);
            if (player.hasProc() && player.isRidingSandSeal() &&
                player.isRidingThisSandSeal(mActor)) {
                ksys::act::disableAttClient(mActor, "Hang");
                mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
                _29c = 150.0f;
                _290.rate = 1.0f;
                _290.value = 0.0f;
                _290.previous_value = 0.0f;
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
    if (auto* info = uking::act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&info->getPlayerLink(), &player);
        if (player.hasProc() && player.isRidingSandSeal() && player.isRidingThisSandSeal(mActor)) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_8000000);
            _29c = 150.0f;
            _290.rate = 1.0f;
            _290.value = 0.0f;
            _290.previous_value = 0.0f;
            _279 = false;
            _280 = sead::Mathf::pi();
            changeChild("牽引");
            return;
        }
    }
    sub_71005047A8();
}

}  // namespace uking::ai
