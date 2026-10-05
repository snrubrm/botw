#include "Game/AI/Action/actionPulleyChainASControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

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
        const f32 px = pos.x;
        const f32 py = pos.y;
        const f32 pz = pos.z;
        const sead::Vector3f diff(_40 - px, _44 - py, _48 - pz);
        const f32 dist = diff.length();
        const f32 value = sead::Mathf::clamp(length - dist, 0.0f, length);
        as_list->x_3(*mTargetIdx_s, *mSeqBankIdx_s, &ksys::as::ASList::Unk2::sub_7101163298, value);
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

void PulleyChainASControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
