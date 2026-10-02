#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiMessage3DText.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ShowMessage3D : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ShowMessage3D, ksys::act::ai::Behavior)
public:
    explicit ShowMessage3D(const InitArg& arg);
    ~ShowMessage3D() override;
    void m7() override;
    void loadParams() override;
    virtual void m14(sead::BufferedSafeString* out);
    void m8() override;

    /* 0x28 */ const int* mDelayFrame_s{};
    /* 0x30 */ const bool* mIsCloseOtherMessage_s{};
    /* 0x38 */ const bool* mUseVoiceFolder_s{};
    /* 0x40 */ sead::SafeString mLabelName_s{};
    /* 0x50 */ Message3DText _50;
};
KSYS_CHECK_SIZE_NX150(ShowMessage3D, 0x128);

}  // namespace uking::behavior
