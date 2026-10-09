#include "Game/AI/Behavior/behaviorSyncBodyASAndAnimalUnitAS.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

SyncBodyASAndAnimalUnitAS::SyncBodyASAndAnimalUnitAS(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// NON_MATCHING: member destruction calls its own D1 instead of inlining the unregister body.
SyncBodyASAndAnimalUnitAS::~SyncBodyASAndAnimalUnitAS() = default;

// NON_MATCHING: the root callback's original own D1 remains a real out-of-line call.
SyncBodyASAndAnimalUnitAS::Callback::~Callback() = default;

void SyncBodyASAndAnimalUnitAS::Callback::call(ksys::act::Actor* actor) {
    sub_71006459BC(actor);
}

void SyncBodyASAndAnimalUnitAS::m8() {
    _68 = -1;
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (enemy && enemy->_1170)
        enemy->_1170->append(&_28);
}

void SyncBodyASAndAnimalUnitAS::m9() {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (enemy && enemy->_1170)
        enemy->_1170->erase(&_28);
}

bool SyncBodyASAndAnimalUnitAS::m6(sead::Heap* heap) {
    return true;
}

void SyncBodyASAndAnimalUnitAS::m7() {}

void SyncBodyASAndAnimalUnitAS::loadParams() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mPreFix_s, "PreFix");
}

}  // namespace uking::behavior
