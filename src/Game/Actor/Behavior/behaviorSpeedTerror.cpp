#include "Game/Actor/Behavior/behaviorSpeedTerror.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

SpeedTerror::SpeedTerror(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool SpeedTerror::init_(sead::Heap* heap) {
    _28.sub_7100D78564(heap);
    return true;
}

void SpeedTerror::calc() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    const bool active = _28.sub_7100D78960();
    const f32 speed = velocity.length();
    if (active) {
        if (speed <= *mParams.mRemoveSpTh_s * 30.0f) {
            if (auto* owner = actor->get548())
                owner->sub_7100D78444(&_28);
        }
    } else {
        if (speed >= *mParams.mSpeedTh_s * 30.0f) {
            auto* owner = actor->get548();
            if (!owner)
                return;
            owner->sub_7100D783E4(&_28);
            const f32 level = *mParams.mLevel_s;
            u32 flags = *mParams.mIsPlayerLayer_s;
            if (*mParams.mIsNpcLayer_s)
                flags |= 0x2;
            if (*mParams.mIsEnemyLayer_s)
                flags |= 0x4;
            if (*mParams.mIsGuardianLayer_s)
                flags |= 0x8;
            if (*mParams.mIsImpulseLayer_s)
                flags |= 0x10;
            if (*mParams.mIsFireLayer_s)
                flags |= 0x20;
            if (*mParams.mIsInsectLayer_s)
                flags |= 0x40;
            if (*mParams.mIsHorseLayer_s)
                flags |= 0x80;
            if (*mParams.mIsAnimalLayer_s)
                flags |= 0x100;
            if (*mParams.mIsWolfLinkLayer_s)
                flags |= 0x200;
            if (*mParams.mIsIceLayer_s)
                flags |= 0x400;
            if (*mParams.mIsElectricLayer_s)
                flags |= 0x800;
            auto* entry = &actor->get548()->_18;
            entry->m9(2, level);
            entry->_3c |= flags;
        }
    }
}

// NON_MATCHING: the original loads and converts *mParams.mLevel_s before building the layer mask (same as
// TerrorBehavior::enter; the mask code is duplicated in calc, probably one inline helper)
void SpeedTerror::enter() {
    u32 flags = *mParams.mIsPlayerLayer_s;
    if (*mParams.mIsNpcLayer_s)
        flags |= 0x2;
    if (*mParams.mIsEnemyLayer_s)
        flags |= 0x4;
    if (*mParams.mIsGuardianLayer_s)
        flags |= 0x8;
    if (*mParams.mIsImpulseLayer_s)
        flags |= 0x10;
    if (*mParams.mIsFireLayer_s)
        flags |= 0x20;
    if (*mParams.mIsInsectLayer_s)
        flags |= 0x40;
    if (*mParams.mIsHorseLayer_s)
        flags |= 0x80;
    if (*mParams.mIsAnimalLayer_s)
        flags |= 0x100;
    if (*mParams.mIsWolfLinkLayer_s)
        flags |= 0x200;
    if (*mParams.mIsIceLayer_s)
        flags |= 0x400;
    if (*mParams.mIsElectricLayer_s)
        flags |= 0x800;
    _28.x(2, flags, f32(*mParams.mLevel_s));
    _28.setRadius(*mParams.mRadius_s);
}

void SpeedTerror::leave() {
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_28);
}

void SpeedTerror::loadParams() {
    getStaticParam(&mParams.mLevel_s, "Level");
    getStaticParam(&mParams.mRadius_s, "Radius");
    getStaticParam(&mParams.mSpeedTh_s, "SpeedTh");
    getStaticParam(&mParams.mRemoveSpTh_s, "RemoveSpTh");
    getStaticParam(&mParams.mIsPlayerLayer_s, "IsPlayerLayer");
    getStaticParam(&mParams.mIsNpcLayer_s, "IsNpcLayer");
    getStaticParam(&mParams.mIsEnemyLayer_s, "IsEnemyLayer");
    getStaticParam(&mParams.mIsGuardianLayer_s, "IsGuardianLayer");
    getStaticParam(&mParams.mIsImpulseLayer_s, "IsImpulseLayer");
    getStaticParam(&mParams.mIsFireLayer_s, "IsFireLayer");
    getStaticParam(&mParams.mIsInsectLayer_s, "IsInsectLayer");
    getStaticParam(&mParams.mIsHorseLayer_s, "IsHorseLayer");
    getStaticParam(&mParams.mIsAnimalLayer_s, "IsAnimalLayer");
    getStaticParam(&mParams.mIsWolfLinkLayer_s, "IsWolfLinkLayer");
    getStaticParam(&mParams.mIsIceLayer_s, "IsIceLayer");
    getStaticParam(&mParams.mIsElectricLayer_s, "IsElectricLayer");
}

SpeedTerror::~SpeedTerror() {
    _28.sub_7100D786EC();
}

}  // namespace uking::behavior
