#include "Game/AI/AI/aiSoundTriggerTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SoundTriggerTag::SoundTriggerTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SoundTriggerTag::~SoundTriggerTag() = default;

bool SoundTriggerTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SoundTriggerTag::enter_(ksys::act::ai::InlineParamPack* params) {
    getStaticParam(&mAlways_s, "Always");
    if (*mAlways_s)
        sub_7100E1BB90();
    else
        changeChild("待機");
}

void SoundTriggerTag::sub_7100E1BB90() {
    ksys::act::ai::InlineParamPack params;
    params.addInt(*mSoundDelay_m, "SoundDelay", -1);
    params.addString(mSound_m, "Sound", -1);
    params.addString(mSLinkInst_m, "SLinkInst", -1);
    changeChild("再生", &params);
}

void SoundTriggerTag::calc_() {
    if (*mAlways_s)
        return;

    const bool signal = mActor->checkBasicSig();
    if (isCurrentChild("待機")) {
        if (!_68 && signal)
            sub_7100E1BB90();
    } else {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            changeChild("待機");
    }
    _68 = signal;
}

void SoundTriggerTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SoundTriggerTag::loadParams_() {
    getMapUnitParam(&mSoundDelay_m, "SoundDelay");
    getMapUnitParam(&mSound_m, "Sound");
    getMapUnitParam(&mSLinkInst_m, "SLinkInst");
}

}  // namespace uking::ai
