#include "Game/AI/AI/aiSimpleLiftableDLC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

SimpleLiftableDLC::SimpleLiftableDLC(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftableDLC::~SimpleLiftableDLC() = default;

bool SimpleLiftableDLC::init_(sead::Heap* heap) {
    _40.x();
    _80.x();
    return true;
}

void SimpleLiftableDLC::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::disableAttClient(mActor, "Grab");
    _d0 = false;
    _80.x();
    sub_710056EA38();
}

void SimpleLiftableDLC::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLiftableDLC::loadParams_() {
    getStaticParam(&mScaleToLiftUp_s, "ScaleToLiftUp");
}

inline void SimpleLiftableDLC::x() {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
    ksys::act::disableAllAttClients(actor);
    _40.x();
    changeChild("所持");
}

void SimpleLiftableDLC::sub_710056EA38() {
    auto* actor = mActor;
    bool has_parent = false;
    if (sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent())) {
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000)) {
            x();
            return;
        }
        has_parent = true;
    }

    const u32 type = actor->getRootAi()->getI();
    if (type == 2) {
        changeChild("投擲生成");
        return;
    }

    if (has_parent && type != 5 && sub_71005DC444(actor)) {
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        x();
        return;
    }

    if (!actor->getMapObject()) {
        if (auto* body = actor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
    changeChild("通常");
}

void SimpleLiftableDLC::calc_() {
    sub_710056EC90();

    if (_d0) {
        auto* actor = mActor;
        if (isCurrentChild("通常") &&
            (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _40._30)) {
            x();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("通常");
}

bool SimpleLiftableDLC::handleMessage_(const ksys::Message* message) {
    auto* actor = mActor;
    if (_d0 && isCurrentChild("通常")) {
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _40._30)
            return false;
        if (_40.m2(*message)) {
            _40.sub_710070B5A0(actor);
            return true;
        }
    }

    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _40._30 ||
        _80._30) {
        return false;
    }
    if (actor->getConnectedCalcParent())
        return false;
    return _80.m2(*message);
}

}  // namespace uking::ai
