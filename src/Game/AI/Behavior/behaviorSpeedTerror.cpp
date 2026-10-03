#include "Game/AI/Behavior/behaviorSpeedTerror.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

// NON_MATCHING: the original tail-calls memset for the parameters (known clang difference)
SpeedTerror::SpeedTerror(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool SpeedTerror::m6(sead::Heap* heap) {
    _28.sub_7100D78564(heap);
    return true;
}

void SpeedTerror::m7() {
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    sead::Vector3f velocity;
    body->getLinearVelocity(&velocity);
    const bool active = _28.sub_7100D78960();
    const f32 speed = velocity.length();
    if (active) {
        if (speed <= *mRemoveSpTh_s * 30.0f) {
            if (auto* owner = actor->get548())
                owner->sub_7100D78444(&_28);
        }
    } else {
        if (speed >= *mSpeedTh_s * 30.0f) {
            auto* owner = actor->get548();
            if (!owner)
                return;
            owner->sub_7100D783E4(&_28);
            const f32 level = *mLevel_s;
            u32 flags = *mIsPlayerLayer_s;
            if (*mIsNpcLayer_s)
                flags |= 0x2;
            if (*mIsEnemyLayer_s)
                flags |= 0x4;
            if (*mIsGuardianLayer_s)
                flags |= 0x8;
            if (*mIsImpulseLayer_s)
                flags |= 0x10;
            if (*mIsFireLayer_s)
                flags |= 0x20;
            if (*mIsInsectLayer_s)
                flags |= 0x40;
            if (*mIsHorseLayer_s)
                flags |= 0x80;
            if (*mIsAnimalLayer_s)
                flags |= 0x100;
            if (*mIsWolfLinkLayer_s)
                flags |= 0x200;
            if (*mIsIceLayer_s)
                flags |= 0x400;
            if (*mIsElectricLayer_s)
                flags |= 0x800;
            auto* entry = &actor->get548()->_18;
            entry->m9(2, level);
            entry->_3c |= flags;
        }
    }
}

// NON_MATCHING: the original loads and converts *mLevel_s before building the layer mask (same as
// TerrorBehavior::m8; the mask code is duplicated in m7, probably one inline helper)
void SpeedTerror::m8() {
    u32 flags = *mIsPlayerLayer_s;
    if (*mIsNpcLayer_s)
        flags |= 0x2;
    if (*mIsEnemyLayer_s)
        flags |= 0x4;
    if (*mIsGuardianLayer_s)
        flags |= 0x8;
    if (*mIsImpulseLayer_s)
        flags |= 0x10;
    if (*mIsFireLayer_s)
        flags |= 0x20;
    if (*mIsInsectLayer_s)
        flags |= 0x40;
    if (*mIsHorseLayer_s)
        flags |= 0x80;
    if (*mIsAnimalLayer_s)
        flags |= 0x100;
    if (*mIsWolfLinkLayer_s)
        flags |= 0x200;
    if (*mIsIceLayer_s)
        flags |= 0x400;
    if (*mIsElectricLayer_s)
        flags |= 0x800;
    _28.x(2, flags, f32(*mLevel_s));
    _28.setRadius(*mRadius_s);
}

void SpeedTerror::m9() {
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_28);
}

void SpeedTerror::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeedTh_s, "SpeedTh");
    getStaticParam(&mRemoveSpTh_s, "RemoveSpTh");
    getStaticParam(&mIsPlayerLayer_s, "IsPlayerLayer");
    getStaticParam(&mIsNpcLayer_s, "IsNpcLayer");
    getStaticParam(&mIsEnemyLayer_s, "IsEnemyLayer");
    getStaticParam(&mIsGuardianLayer_s, "IsGuardianLayer");
    getStaticParam(&mIsImpulseLayer_s, "IsImpulseLayer");
    getStaticParam(&mIsFireLayer_s, "IsFireLayer");
    getStaticParam(&mIsInsectLayer_s, "IsInsectLayer");
    getStaticParam(&mIsHorseLayer_s, "IsHorseLayer");
    getStaticParam(&mIsAnimalLayer_s, "IsAnimalLayer");
    getStaticParam(&mIsWolfLinkLayer_s, "IsWolfLinkLayer");
    getStaticParam(&mIsIceLayer_s, "IsIceLayer");
    getStaticParam(&mIsElectricLayer_s, "IsElectricLayer");
}

SpeedTerror::~SpeedTerror() {
    _28.sub_7100D786EC();
}

}  // namespace uking::behavior
