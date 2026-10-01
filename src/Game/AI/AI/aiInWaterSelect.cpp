#include "Game/AI/AI/aiInWaterSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

InWaterSelect::InWaterSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InWaterSelect::~InWaterSelect() = default;

bool InWaterSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool InWaterSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool InWaterSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InWaterSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710044DC94(params);
}

void InWaterSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InWaterSelect::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutWaterDepth_s, "OutWaterDepth");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mIsForceChange_s, "IsForceChange");
}

void InWaterSelect::calc_() {
    if (!*mIsCheckEveryFrame_s)
        return;
    if (getCurrentChild()->isChangeable() || *mIsForceChange_s)
        sub_710044DC94(nullptr);
}

void InWaterSelect::sub_710044DC94(ksys::act::ai::InlineParamPack* params) {
    if (isCurrentChild("水中")) {
        f32 depth = 0.0f;
        if (mActor->get68f().load()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        }
        if (depth <= *mOutWaterDepth_s)
            changeChild("水上", params);
    } else {
        const bool is_out = isCurrentChild("水上");
        f32 depth = 0.0f;
        if (mActor->get68f().load()) {
            const f32 y = mActor->getMtx().m[1][3];
            depth = mActor->get6f0() - y;
        }
        if (is_out) {
            if (depth > *mInWaterDepth_s)
                changeChild("水中", params);
        } else if (depth > *mInWaterDepth_s) {
            changeChild("水中", params);
        } else {
            changeChild("水上", params);
        }
    }
}

}  // namespace uking::ai
