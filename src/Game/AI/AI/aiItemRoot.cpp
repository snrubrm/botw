#include "Game/AI/AI/aiItemRoot.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

void sub_7100733E24(ksys::act::Actor* actor, const sead::Vector3f& impulse,
                   const sead::Vector3f& position,
                   ksys::act::ActorAtk::Unk_710079e64c::Unk1* attack_info);

namespace uking::ai {

ItemRoot::ItemRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemRoot::~ItemRoot() = default;

bool ItemRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!actor->getMapObject() || actor->hasPlacementLinkWithTypeFreeze()) {
        if (actor->getModel())
            Unk_710260af28::instance()->sub_7100F1EBF0(actor->getModel());
    } else if (body && *mInitMotionStatus_m == 0) {
        body->changeMotionType(ksys::phys::MotionType::Fixed);
    }
    if (body && actor->getConstraints().size() > 0) {
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        if (ksys::act::hasTag(actor, 0xf9c66decu) || ksys::act::hasTag(actor, 0xf321a28cu)) {
            body->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
            body->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        }
    }
    _48 = false;
    m34();
}

// NON_MATCHING: the contact-layer comparison omits the original temporary stack copy.
void ItemRoot::calc_() {
    auto* actor = mActor;
    auto* object = actor->m128();
    const bool state = object && object->m2();
    const bool attack_state = sub_71007A274C(actor);
    if (state || attack_state || actor->checkBasicSig())
        _48 = true;

    auto* body = actor->getMainBody();
    if (!body || body->getMotionType() == ksys::phys::MotionType::Dynamic || !_48 ||
        body->getContactLayer() == ksys::phys::ContactLayer::EntityNoHit) {
        return;
    }
    body->changeMotionType(ksys::phys::MotionType::Dynamic);
    auto* attack_info = sub_71007A255C(actor, 0);
    if (!attack_info)
        return;
    if (auto* map_object = actor->getMapObject()) {
        actor->setDeleteDistance(ksys::map::PlacementMgr::instance()->getDeleteDistance(map_object));
        map_object->setRevivalFlagValueIf(ksys::map::ActorData::Flag::RevivalEnable, true);
    }
    actor->emitBasicSigOn();
    if (sead::DynamicCast<ksys::act::DynamicActor>(actor))
        sub_7100733E24(actor, attack_info->_a0 * *mAtHitImpulseRate_s, attack_info->_0, attack_info);
}

void ItemRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ItemRoot::loadParams_() {
    getStaticParam(&mAtHitImpulseRate_s, "AtHitImpulseRate");
    getMapUnitParam(&mInitMotionStatus_m, "InitMotionStatus");
}

void ItemRoot::m34() {
    m35();
}

void ItemRoot::m35() {
    changeChild("通常");
}

}  // namespace uking::ai
