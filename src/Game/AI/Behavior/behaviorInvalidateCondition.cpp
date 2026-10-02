#include "Game/AI/Behavior/behaviorInvalidateCondition.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::behavior {

InvalidateCondition::InvalidateCondition(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InvalidateCondition::~InvalidateCondition() = default;

bool InvalidateCondition::m6(sead::Heap* heap) {
    return true;
}

void InvalidateCondition::m7() {}

void InvalidateCondition::loadParams() {
    getStaticParam(&mInvalidBurn_s, "InvalidBurn");
    getStaticParam(&mInvalidIce_s, "InvalidIce");
    getStaticParam(&mInvalidElectric_s, "InvalidElectric");
}

void InvalidateCondition::m8() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159());
    if (*mInvalidBurn_s)
        unit->_138 |= 1;
    if (*mInvalidIce_s)
        unit->_138 |= 2;
    if (*mInvalidElectric_s)
        unit->_138 |= 4;
}

void InvalidateCondition::m9() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159());
    if (*mInvalidBurn_s)
        unit->_138 &= ~1;
    if (*mInvalidIce_s)
        unit->_138 &= ~2;
    if (*mInvalidElectric_s)
        unit->_138 &= ~4;
}

}  // namespace uking::behavior
