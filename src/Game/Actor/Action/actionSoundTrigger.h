#pragma once

#include <prim/seadSafeString.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundTrigger : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundTrigger, ksys::act::ai::Action)
public:
    explicit SoundTrigger(const InitArg& arg);
    ~SoundTrigger() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x7100e16614 (placeholder name): emits the SLink asset `mSound_d` into `_50` (event, actor or fallback user
    // instance); plays a UI sound and returns false if none has it.
    bool sub_7100E16614();

    u8 _1c[0x4];
    // dynamic_param at offset 0x20 (loaded in enter_)
    int* mSoundDelay_d{};
    // dynamic_param at offset 0x28 (loaded in enter_)
    sead::SafeString mSound_d{};
    // dynamic_param at offset 0x38 (loaded in enter_)
    sead::SafeString mSLinkInst_d{};
    s32 _48 = -1;
    u8 _4c[0x4];
    xlink2::HandleSLink _50;
    bool _60 = false;
    u8 _61[0x7];
};
KSYS_CHECK_SIZE_NX150(SoundTrigger, 0x68);

}  // namespace uking::action
