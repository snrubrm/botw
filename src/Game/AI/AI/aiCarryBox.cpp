#include "Game/AI/AI/aiCarryBox.h"
#include "Game/gameSceneSubsys12.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Utils/Thread/Message.h"

bool Unk_71023dcd70::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body && event.body->getHkBodyName().startsWith("Motorcycle")) {
        if (!disable)
            return false;
        *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
        return false;
    }
    return true;
}

namespace uking::ai {

CarryBox::CarryBox(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CarryBox::~CarryBox() = default;

bool CarryBox::init_(sead::Heap* heap) {
    _80.sub_710065D8E4(heap, false);
    if (auto* scene = GameSceneSubsys12::instance())
        scene->sub_710066323C(mActor, &_80);
    return true;
}

void CarryBox::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent());
    const char* child;
    if (parent && actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000)) {
        auto* held = mActor;
        if (auto* physics = held->getPhysics())
            physics->sub_7100FBADDC();
        ksys::act::disableAllAttClients(held);
        _38.x();
        child = "所持";
    } else {
        child = "通常";
    }
    changeChild(child, nullptr);
    _7c = 0;
    if (auto* body = actor->getMainBody()) {
        if (auto* info = body->getContactPointInfo()) {
            info->setContactCallback(&_7e0);
            info->unsubscribeAllLayers();
            info->subscribeLayer(ksys::phys::ContactLayer::EntityGround);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundRough);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityGroundObject);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityObject);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityTree);
            info->subscribeLayer(ksys::phys::ContactLayer::EntityAirWall);
        }
    }
}

bool CarryBox::hasUpdateForPreDeleteCb() {
    return true;
}

void CarryBox::sub_7100343FD0(ksys::phys::RigidBody* body, ksys::phys::ContactPointInfo* info,
                              bool has_contacts) {
    auto* scene = GameSceneSubsys12::instance();
    if (!scene) {
        callDeleteAndCreateDropAndEmit(mActor, 0);
        return;
    }
    if (has_contacts) {
        if (body) {
            auto it = info->begin();
            const sead::Vector3f position =
                it.getPointPosition(ksys::phys::ContactPointInfo::Iterator::Point::BodyB) -
                (*it)->separating_normal * 0.5f;
            body->setPosition(position, ksys::phys::PropagateToLinkedMotions{true});
        }
        scene->sub_7100664484(2, &_80);
    }
}

// NON_MATCHING: the original calls sub_71003440A8 without loading its second argument (x2 is left as it was), so the
// source passed an uninitialised value there; passing `info` adds one `mov x2, x21`.
void CarryBox::calc_() {
    auto* actor = mActor;
    if (!GameSceneSubsys12::instance()) {
        callDeleteAndCreateDropAndEmit(actor, 0);
        return;
    }
    ksys::phys::ContactPointInfo* info = nullptr;
    if (auto* physics = actor->getPhysics())
        info = physics->getContactPointInfo(0);
    if (info) {
        bool has_contacts = false;
        if (info->getNumContactPoints().load() != 0)
            has_contacts = !info->begin().isEnd();
        if (auto* body = actor->getMainBody()) {
            if (_80.sub_710065F954() || _80.sub_710065E834()) {
                if (actor->getConnectedCalcParent())
                    actor->resetConnectedCalcParent(false);
                return;
            }
            if (_79)
                sub_7100343FD0(body, info, has_contacts);
            else
                sub_71003440A8(body, info, has_contacts);
            return;
        }
    } else {
        actor->getMainBody();
    }
    callDeleteAndCreateDropAndEmit(actor, 0);
}

bool CarryBox::updateForPreDelete() {
    return _80.sub_710065E710();
}

bool CarryBox::handleMessage_(const ksys::Message* message) {
    auto* actor = mActor;
    if (isCurrentChild("通常") && !actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) &&
        !_38._30) {
        if (_38.m2(*message)) {
            _38.sub_710070B5A0(actor);
            return true;
        }
    }
    return false;
}

void CarryBox::leave_() {
    if (auto* scene = GameSceneSubsys12::instance())
        scene->sub_7100664484(5, &_80);
}

void CarryBox::loadParams_() {}

}  // namespace uking::ai
