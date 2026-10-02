#include "Game/AI/Behavior/behaviorTerrorBehavior.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

TerrorBehavior::TerrorBehavior(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool TerrorBehavior::m6(sead::Heap* heap) {
    _a0.sub_7100D78564(heap);
    return true;
}

void TerrorBehavior::m7() {
    const f32 ratio = *mOffsetSpeedRatio_s;
    if (ratio > 0.0f)
        _a0._94 = mActor->getVelocity() * ratio;
}

// NON_MATCHING: the original converts *mLevel_s to float before building the layer mask
void TerrorBehavior::m8() {
    auto* owner = mActor->get548();
    if (!owner)
        return;
    _a0.setRadius(*mRadius_s);
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
    _a0.x(2, flags, f32(*mLevel_s));
    owner->sub_7100D783E4(&_a0);
}

void TerrorBehavior::m9() {
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_a0);
}

void TerrorBehavior::loadParams() {
    getStaticParam(&mLevel_s, "Level");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetSpeedRatio_s, "OffsetSpeedRatio");
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

TerrorBehavior::~TerrorBehavior() {
    _a0.sub_7100D786EC();
}

}  // namespace uking::behavior
