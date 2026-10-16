#include "Game/Actor/Action/actionStopCliffTongueAttack.h"
#include <algorithm>
#include <cmath>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::action {

StopCliffTongueAttack::StopCliffTongueAttack(const InitArg& arg) : OnCliffWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
StopCliffTongueAttack::~StopCliffTongueAttack() {
    ;
}

bool StopCliffTongueAttack::init_(sead::Heap* heap) {
    return OnCliffWait::init_(heap);
}

void StopCliffTongueAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnCliffWait::enter_(params);
    _68 = sub_71005DB4DC(mActor);
    _6c = sub_71005DB4FC(mActor);
    _64 = 0;
}

void StopCliffTongueAttack::leave_() {
    OnCliffWait::leave_();
    sub_71007A2D7C(mActor, mRigidName_s);
    sub_71005DB3EC(mActor);
}

// NON_MATCHING: the original computes both member addresses (this + 0x48 / 0x58) and the SafeString vtable
// into callee-saved registers up front (one more spilled register than ours).
void StopCliffTongueAttack::loadParams_() {
    OnCliffWait::loadParams_();
    getStaticParam(&mRigidName_s, "RigidName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void StopCliffTongueAttack::calc_() {
    auto* actor = mActor;
    OnCliffWait::calc_();
    switch (_64) {
    case 0: {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(actor, 0x29, &query, 0, 0))
            _64 = 1;
        break;
    }
    case 1: {
        auto* self = mActor;
        sead::Vector3f dir = self->getMtx().getTranslation() - *mTargetPos_d;
        dir.normalize();
        sead::Vector3f local = -dir;
        sead::Matrix34f inv;
        inv.setInverse(self->getMtx());
        local.rotate(inv);
        f32 yaw = ksys::util::sub_71011EF0CC(-std::atan2(local.x, local.z));
        f32 pitch = ksys::util::sub_71011EF0CC(
            std::atan2(local.y, sead::Vector2f(local.x, local.z).length()));
        ksys::VFR::lerp(&_68, yaw, 0.15f, sead::Mathf::deg2rad(12), sead::Mathf::deg2rad(1));
        ksys::VFR::lerp(&_6c, pitch, 0.15f, sead::Mathf::deg2rad(12), sead::Mathf::deg2rad(1));
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(self, 3, &query, 0, 0)) {
            auto* sensor = getActorAttackSensor(self);
            const s32 power =
                std::max(static_cast<ksys::act::PlayerOrEnemy*>(self)->getEnemyAtkPower(), 1);
            const auto* attack = self->getParam()->getRes().mGParamList->getAttack();
            sensor->activateAttackSensor(0x2000, 1, power, attack->mImpulse.ref(), 0.0f,
                                         attack->mGuardBreakPower.ref(), 1, -1, false, 1, -1);
            sub_71007A2C30(self, mRigidName_s, nullptr);
            _64 = 2;
        }
        break;
    }
    case 2: {
        ksys::as::ASList::Unk4 query;
        if (sub_71005DD734(actor, 3, &query, 0, 0)) {
            sub_71007A2D7C(actor, mRigidName_s);
            _64 = 3;
        }
        break;
    }
    case 3:
        ksys::VFR::lerp(&_68, 0.0f, 0.12f, sead::Mathf::deg2rad(12), sead::Mathf::deg2rad(1));
        ksys::VFR::lerp(&_6c, 0.0f, 0.12f, sead::Mathf::deg2rad(12), sead::Mathf::deg2rad(1));
        break;
    }
    sub_71005DB44C(actor, _68, _6c);
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
