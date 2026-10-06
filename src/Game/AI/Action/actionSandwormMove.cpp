#include "Game/AI/Action/actionSandwormMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SandwormMove::SandwormMove(const InitArg& arg) : MoveWithAS(arg) {}

SandwormMove::~SandwormMove() = default;

bool SandwormMove::init_(sead::Heap* heap) {
    if (!MoveWithAS::init_(heap))
        return false;
    return _128.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void SandwormMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveWithAS::enter_(params);
    auto* actor = mActor;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = true;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = true;
    }
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_128._0)) {
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

void SandwormMove::leave_() {
    MoveWithAS::leave_();
}

void SandwormMove::loadParams_() {
    MoveWithAS::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mIsCheckAnmSeqCancel_s, "IsCheckAnmSeqCancel");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void SandwormMove::calc_() {
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_128._0))
            checker->sub_7100716408(mActor->getMtx().getTranslation());
    }

    MoveWithAS::calc_();
    if (isFinished() || isFailed())
        return;

    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_128._0)) {
            if (checker->_78 <= 0.0f ||
                (*mVibrateStopCheck_s > 0.0f && checker->sub_71007169CC(*mVibrateStopCheck_s)))
                setFailed();
        }
    }
}

bool SandwormMove::isChangeable() const {
    if (*mIsCheckAnmSeqCancel_s)
        return sub_71005DD798(mActor, 2, nullptr, 0, 0);
    return ActionBase::isChangeable();
}

}  // namespace uking::action
