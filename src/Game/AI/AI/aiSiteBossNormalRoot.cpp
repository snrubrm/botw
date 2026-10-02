#include "Game/AI/AI/aiSiteBossNormalRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SiteBossNormalRoot::SiteBossNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossNormalRoot::~SiteBossNormalRoot() = default;

bool SiteBossNormalRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    changeChild("攻撃");
}

void SiteBossNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossNormalRoot::loadParams_() {}

bool SiteBossNormalRoot::isChangeable() const {
    auto* life = mActor->getLife();
    if (life && *life < 1)
        return true;

    auto* child = getCurrentChild();
    if (!child)
        return false;
    return child->isChangeable();
}

}  // namespace uking::ai
