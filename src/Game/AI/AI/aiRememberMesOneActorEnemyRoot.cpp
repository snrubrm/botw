#include "Game/AI/AI/aiRememberMesOneActorEnemyRoot.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

RememberMesOneActorEnemyRoot::RememberMesOneActorEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

RememberMesOneActorEnemyRoot::~RememberMesOneActorEnemyRoot() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mRememberKey_s);
}

bool RememberMesOneActorEnemyRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CED8(mRememberKey_s, heap);
    return true;
}

void RememberMesOneActorEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void RememberMesOneActorEnemyRoot::calc_() {
    EnemyRoot::calc_();
}

void RememberMesOneActorEnemyRoot::leave_() {
    EnemyRoot::leave_();
}

bool RememberMesOneActorEnemyRoot::handleMessage_(const ksys::Message& message) {
    if (EnemyRoot::handleMessage_(message))
        return true;
    if (_1e8.m2(message)) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->sub_7100D3D1E0(mRememberKey_s, _1e8._38.mLink);
        return true;
    }
    return false;
}

void RememberMesOneActorEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mRememberKey_s, "RememberKey");
}

}  // namespace uking::ai
