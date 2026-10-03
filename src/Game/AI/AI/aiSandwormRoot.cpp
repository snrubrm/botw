#include "Game/AI/AI/aiSandwormRoot.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

SandwormRoot::SandwormRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRoot::~SandwormRoot() = default;

bool SandwormRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_1650 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Spine_1");
    return true;
}

void SandwormRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SandwormRoot::leave_() {
    sub_71005DA114(mActor, &_250);
    if (_288 != 0) {
        auto* actor = mActor;
        sub_7100720140(actor);
        sub_7100720A70(actor);
    }
    _288 = 0;
    EnemyRoot::leave_();
}

void SandwormRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
}

}  // namespace uking::ai
