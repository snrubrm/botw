#pragma once

#include <prim/seadSafeString.h>
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
    u8 _1c[0x4];
    u64 _20 = 0;
    sead::SafeString _28{};
    sead::SafeString _38{};
    s32 _48 = -1;
    u8 _4c[0x4];
    u64 _50 = 0;
    s32 _58 = 0;
    u8 _5c[0x4];
    bool _60 = false;
    u8 _61[0x7];
};
KSYS_CHECK_SIZE_NX150(SoundTrigger, 0x68);

}  // namespace uking::action
