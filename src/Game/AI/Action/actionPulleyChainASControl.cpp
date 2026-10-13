#include "Game/AI/Action/actionPulleyChainASControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"

namespace uking::action {

PulleyChainASControl::PulleyChainASControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PulleyChainASControl::~PulleyChainASControl() = default;

bool PulleyChainASControl::init_(sead::Heap* heap) {
    sub_7100223114();
    return true;
}

void PulleyChainASControl::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);

    if (auto* as_list = mActor->getASList()) {
        const f32 length = as_list->x_5(*mTargetIdx_s, *mSeqBankIdx_s,
                                        &ksys::as::ASList::Unk2::sub_710116323C);
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        const sead::Vector3f diff = mStartPosition - pos;
        const f32 dist = diff.length();
        const f32 value = sead::Mathf::clamp(length - dist, 0.0f, length);
        as_list->x_3(*mTargetIdx_s, *mSeqBankIdx_s, &ksys::as::ASList::Unk2::sub_7101163298, value);
    }
}

// NON_MATCHING: matrix/vector evaluation and the constraint loop use different scheduling.
void PulleyChainASControl::sub_7100223114() {
    const auto& constraints = mActor->getConstraints().mConstraints;
    const s32 count = constraints.size();
    for (s32 i = 0; i < count; ++i) {
        auto* slider = sead::DynamicCast<ksys::phys::SliderCs>(constraints[i]);
        if (!slider)
            continue;
        sead::Matrix34f home;
        mActor->getHomeMtx(&home);
        mStartPosition.set(0.0f, slider->sub_7100F71034(), 0.0f);
        const f32 height = slider->sub_7100F71040();
        mStartPosition *= home;
        mEndPosition = home * sead::Vector3f(0.0f, height, 0.0f);
        return;
    }
}

void PulleyChainASControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void PulleyChainASControl::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: Parameter loads and vector evaluation scheduling differ.
void PulleyChainASControl::calc_() {
    if (auto* as_list = mActor->getASList()) {
        const f32 length = as_list->x_5(*mTargetIdx_s, *mSeqBankIdx_s,
                                      &ksys::as::ASList::Unk2::sub_710116323C);
        as_list->x_3(*mTargetIdx_s, *mSeqBankIdx_s,
                     &ksys::as::ASList::Unk2::sub_7101163298,
                     sead::Mathf::clamp(
                         length - (mStartPosition -
                                   mActor->getMtx().getTranslation()).length(),
                         0.0f, length));
    }
}

}  // namespace uking::action
