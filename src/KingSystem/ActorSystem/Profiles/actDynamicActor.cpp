#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace ksys::act {

// NON_MATCHING: most member types are still unknown (placeholders)
DynamicActor::~DynamicActor() = default;

void DynamicActor::onPreDeleteStart_(PrepareArg&) {}

int DynamicActor::getExtraHeapSize() {
    return hasTag(this, tags::TreasureBox) ? 0xa90 : 0;
}

void DynamicActor::onEnterDelete_() {
    Actor::onEnterDelete_();
}

s32* DynamicActor::getLife() {
    return &mLife;
}

uking::dmg::DamageManagerBase* DynamicActor::getDamageMgr() {
    return mDamageMgr;
}

Unk_71025ae640* DynamicActor::getAtk() {
    return _850;
}

Unk_7100e4e084* DynamicActor::m100() {
    return &_870;
}

Actor::Unk3* DynamicActor::m135() {
    return &_a78;
}

Unk_71006e45c4* DynamicActor::m128() {
    return _a50;
}

Unk_71025b08f8* DynamicActor::m126() {
    return _858;
}

Unk_71025ae620* DynamicActor::getDropData() {
    return _a60;
}

}  // namespace ksys::act
