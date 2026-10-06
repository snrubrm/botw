#include "Game/AI/Action/actionBombExplode.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

BombExplode::BombExplode(const InitArg& arg) : ActionEx(arg) {}

BombExplode::~BombExplode() = default;

void BombExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void BombExplode::leave_() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_20, false);
    if (_48) {
        sub_71007A2D34(_48);
        _48 = nullptr;
    }
}

void BombExplode::loadParams_() {
    if (mActor->getParam()) {
        getStaticParam(&mSizeUpTime_s, "SizeUpTime");
        getStaticParam(&mExplodeTime_s, "ExplodeTime");
        getStaticParam(&mShockPower_s, "ShockPower");
        getStaticParam(&mUseDefaultEffect_s, "UseDefaultEffect");
    }
}

void BombExplode::calc_() {
    if (!_48) {
        setFailed();
        return;
    }

    mActor->m107();
    if (_1c.value <= sead::Mathf::epsilon()) {
        if (_48)
            sub_71007A2D34(_48);
        auto* actor = mActor;
        if (actor) {
            setFinished();
            if (actor->getConnectedCalcParent())
                actor->resetConnectedCalcParent(false);
        }
        return;
    }

    _1c.update();
    ksys::VFR::chase(&_54, _50, _58);
    _48->setRadius(_54);
}

}  // namespace uking::action
