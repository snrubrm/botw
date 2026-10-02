#include "Game/AI/Behavior/behaviorEnemyKeepAnimeDriven.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

EnemyKeepAnimeDriven::EnemyKeepAnimeDriven(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
EnemyKeepAnimeDriven::~EnemyKeepAnimeDriven() {
    ;
}

bool EnemyKeepAnimeDriven::m6(sead::Heap* heap) {
    return true;
}

void EnemyKeepAnimeDriven::m7() {}

void EnemyKeepAnimeDriven::loadParams() {
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

void EnemyKeepAnimeDriven::m8() {
    auto* actor = mActor;
    _38 = false;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    if (!enemy || !enemy->_e84.isOnBit(20))
        return;
    if (!as_list->_14.isValid()) {
        as_list->sub_710115BAF8(mTransBoneName_s);
        _38 = true;
    }
}

}  // namespace uking::behavior
