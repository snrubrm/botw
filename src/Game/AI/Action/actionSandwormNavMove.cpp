#include "Game/AI/Action/actionSandwormNavMove.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SandwormNavMove::SandwormNavMove(const InitArg& arg) : NavMeshMoveWithAS(arg) {}

SandwormNavMove::~SandwormNavMove() = default;

bool SandwormNavMove::init_(sead::Heap* heap) {
    if (!NavMeshMoveWithAS::init_(heap))
        return false;
    return _f0.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void SandwormNavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveWithAS::enter_(params);
    auto* actor = mActor;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = true;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = true;
    }
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0)) {
            if (*mVibrateMemoryStep_s > 0.0f)
                checker->_84 = *mVibrateMemoryStep_s;
            if (*mVibrateCheckFrame_s > 0.0f)
                checker->_88 = *mVibrateCheckFrame_s;
            checker->_78 = checker->_88;
            checker->_7c = 0;
            checker->_80 = 0;
            checker->_90.setUndef();
            checker->_8c = false;
        }
    }
}

void SandwormNavMove::leave_() {
    NavMeshMoveWithAS::leave_();
}

void SandwormNavMove::loadParams_() {
    NavMeshMoveWithAS::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void SandwormNavMove::calc_() {
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0))
            checker->sub_7100716408(mActor->getMtx().getTranslation());
    }

    NavMeshMoveWithAS::calc_();
    if (isFinished() || isFailed())
        return;

    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0)) {
            if (checker->_78 <= 0.0f ||
                (*mVibrateStopCheck_s > 0.0f && checker->sub_71007169CC(*mVibrateStopCheck_s)))
                setFailed();
        }
    }
}

}  // namespace uking::action
