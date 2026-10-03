#include "Game/AI/AI/aiStalHeadPartRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

StalHeadPartRoot::StalHeadPartRoot(const InitArg& arg) : EnemyRoot(arg) {}

StalHeadPartRoot::~StalHeadPartRoot() = default;

bool StalHeadPartRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void StalHeadPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->sub_7100EE1E94() && !m35()) {
        changeChild("朝が来た");
        return;
    }
    if (auto* body = mActor->getMainBody())
        body->clearFlag2000000(false);
    EnemyRoot::enter_(params);
}

void StalHeadPartRoot::leave_() {
    EnemyRoot::leave_();
}

void StalHeadPartRoot::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
