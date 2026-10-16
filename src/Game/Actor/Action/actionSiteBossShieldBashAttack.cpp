#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/Action/actionSiteBossShieldBashAttack.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <algorithm>
#include <limits>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

SiteBossShieldBashAttack::SiteBossShieldBashAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShieldBashAttack::~SiteBossShieldBashAttack() = default;

bool SiteBossShieldBashAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShieldBashAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;
    sub_710073FA90(&_5c, mActor);
    playAS("ShieldBash", false, 0, 0, -1.0f);
    _80 = true;
    _81 = false;
    _50.value = *mInitSpeed_s;
    _50.prev_value = *mInitSpeed_s;
    m33();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.setBit(2);
}

void SiteBossShieldBashAttack::leave_() {
    m35();
    m32();
}

void SiteBossShieldBashAttack::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mKeepDist_s, "KeepDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the up vector is kept in registers until after the epsilon check in the original.
void SiteBossShieldBashAttack::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    const sead::Vector3f gravity = controller->get70();
    const f32 gravity_len = gravity.length();
    sead::Vector3f up = -gravity;
    if (gravity_len > 0.0f)
        up *= 1.0f / gravity_len;
    if (gravity_len < std::numeric_limits<f32>::epsilon())
        up = sead::Vector3f::ey;

    sub_710073FA94(&_5c, mActor);
    sead::Vector3f dir = *mTargetPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    const f32 distance = dir.length();
    if (distance > 0.0f)
        dir *= 1.0f / distance;
    ksys::util::sub_71011EFA00(&dir, dir, up);
    sub_710074006C(&_5c, dir, up, true, 0.16f, sead::Mathf::pi2(), 0.0f);

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD798(mActor, 0xe, &query, 0, 0)) {
        _50 *= 0.86f;
        const f32 keep_dist = *mKeepDist_s;
        if (keep_dist * 1.1f < distance) {
            const f32 speed = sead::Mathf::min(distance * 0.8f, *mMoveSpeed_s);
            _50.setToMax(speed);
        } else if (keep_dist * 0.9f > distance) {
            _50.setToMax(*mMoveSpeed_s);
        }
        _50.updateStats();
        pos += dir * _50.value;
    }
    controller->sub_7100F5F938(sead::Matrix34f(_5c, pos));

    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        m34(&query);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        m35();
    }
    if (_80 && sub_71005DD734(mActor, 0xe, &query, 0, 0)) {
        _80 = false;
        m32();
    }

    if (isFinishedAS(0, 0)) {
        setFailed();
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->_1558.resetBit(2);
        return;
    }

    _81 |= hasAttackInfo(mActor);
    if (_81 && sub_71005DD798(mActor, 2, &query, 0, 0)) {
        setFinished();
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->_1558.resetBit(2);
    }
}

void SiteBossShieldBashAttack::m32() {}

bool SiteBossShieldBashAttack::isChangeable() const {
    return _80;
}

void SiteBossShieldBashAttack::m33() {
    if (!_48) {
        _48 = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkShield");
        if (!_48)
            return;
    }
    sub_71007A2B64(_48, nullptr);
    sub_71007A3258(_48, nullptr);
}

void SiteBossShieldBashAttack::m34(ksys::as::ASList::Unk4* query) {
    if (!_48)
        return;
    sead::FixedSafeString<9> direction;
    sub_71005D7C94(&direction, &query->name);
    sub_71007A2EB0(_48, mActor, nullptr);
    auto* sensor = getActorAttackSensor(mActor);
    sensor->activateAttackSensor(1, 0x101, 0, 0, 0.0f, 3, 1,
                                 sub_71007A3A8C(&direction), false, *mAtMinDamage_s, -1);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_1558.isOnBit(5)) {
            if (auto* chemical = mActor->sub_71011D8A54("ShieldChemical")) {
                chemical->sub_7100D90D7C(false);
                chemical->sub_7100D91098(true);
                chemical->sub_7100D90AF4(true);
            }
        }
    }
}

void SiteBossShieldBashAttack::m35() {
    if (!_48)
        return;
    sub_71007A3258(_48, nullptr);
    if (auto* chemical = mActor->sub_71011D8A54("ShieldChemical")) {
        chemical->sub_7100D90D7C(true);
        chemical->sub_7100D91098(false);
        chemical->sub_7100D90AF4(false);
    }
}

}  // namespace uking::action
