#include "Game/AI/Behavior/behaviorSandwormBgmControl.h"
#include "Game/Actor/actSandworm.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SandwormBgmControl::SandwormBgmControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SandwormBgmControl::~SandwormBgmControl() = default;

bool SandwormBgmControl::m6(sead::Heap* heap) {
    return true;
}

void SandwormBgmControl::m8() {
    auto* actor = mActor;
    if (sead::DynamicCast<uking::act::Sandworm>(actor)) {
        if (auto* bgm = sub_7100FFDEA8()) {
            if (*mType_s == 1)
                bgm->sub_710102292C(*mIsEnable_s, actor->getId());
        }
    }
}

void SandwormBgmControl::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mIsEnable_s, "IsEnable");
}

}  // namespace uking::behavior
