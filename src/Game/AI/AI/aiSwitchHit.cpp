#include "Game/AI/AI/aiSwitchHit.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SwitchHit::SwitchHit(const InitArg& arg) : SwitchAI(arg) {}

SwitchHit::~SwitchHit() = default;

bool SwitchHit::init_(sead::Heap* heap) {
    if (!SwitchAI::init_(heap))
        return false;
    if (auto* body = mActor->getMainBody()) {
        if (mActor->getConstraints().size() > 0) {
            body->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        }
        body->clearEntityMotionFlag10(false);
    }
    return true;
}

void SwitchHit::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
    _40 = *mWaitTime_s;
    _44 = false;
    _45 = false;
}

void SwitchHit::leave_() {
    SwitchAI::leave_();
}

void SwitchHit::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

bool SwitchHit::m35() {
    return isCurrentChild("オフ待機") && _44 && _45;
}

bool SwitchHit::m36() {
    return isCurrentChild("オン待機") && _44 && _45;
}

bool SwitchHit::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isChangeable();
}

bool SwitchHit::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isChangeable();
}

void SwitchHit::m40() {
    _40 = 0;
    changeChild("オフ待機");
}

void SwitchHit::m41() {
    _40 = 0;
    changeChild("オン待機");
}

void SwitchHit::m42() {
    changeChild("オフ");
}

void SwitchHit::m43() {
    changeChild("オン");
}

void SwitchHit::calc_() {
    SwitchAI::calc_();
    auto* actor = mActor;
    _44 = false;
    _45 = false;
    const bool hit = sub_71007A274C(actor);
    auto* link = actor->getImpulseBaseProcLink();
    const bool impulse = link && link->_10._c > 0;
    _44 = hit || impulse;
    _45 = ksys::VFR::chase(&_40, *mWaitTime_s);
    SwitchAI::calc_();
    if (actor->hasPlacementLinkForBasicSig() && isCurrentChild("オン待機") && _45 &&
        !actor->checkBasicSig()) {
        m42();
    }
}

}  // namespace uking::ai
