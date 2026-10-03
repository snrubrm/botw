#include "Game/AI/AI/aiFreezeInWaterSelect.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

FreezeInWaterSelect::FreezeInWaterSelect(const InitArg& arg) : InWaterSelect(arg) {}

FreezeInWaterSelect::~FreezeInWaterSelect() = default;

void FreezeInWaterSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    InWaterSelect::enter_(params);
    *mIsKeepFreeze_a = false;
}

void FreezeInWaterSelect::calc_() {
    if (isCurrentChild("凍結解除")) {
        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed()) {
            _68.update();
            if (!(_68.value <= sead::Mathf::epsilon()))
                return;
            if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor))
                actor->m149(3);
        }
        setFinished();
        return;
    }

    if (isCurrentChild("水上")) {
        f32 depth = 0.0f;
        if (mActor->get68f().load()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        }
        if (depth > *mInWaterDepth_s) {
            *mIsKeepFreeze_a = true;
            _68.reset(*mIceBreakTime_s);
            changeChild("凍結解除");
            return;
        }
    }
    InWaterSelect::calc_();
}

void FreezeInWaterSelect::leave_() {
    InWaterSelect::leave_();
    *mIsKeepFreeze_a = false;
}

void FreezeInWaterSelect::loadParams_() {
    InWaterSelect::loadParams_();
    getStaticParam(&mIceBreakTime_s, "IceBreakTime");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
}

bool FreezeInWaterSelect::isFinished() const {
    if (getCurrentChild()->isFinished())
        return true;
    return isCurrentChild("凍結解除") && ActionBase::isFinished();
}

}  // namespace uking::ai
