#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GanonBeastFirstMessage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GanonBeastFirstMessage, ksys::act::ai::Behavior)
public:
    explicit GanonBeastFirstMessage(const InitArg& arg);
    ~GanonBeastFirstMessage() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x7100623ef4)
    void m7() override;  // not decompiled yet (0x7100624204)
    void m8() override;  // not decompiled yet (0x7100623ff4)
    void m9() override;  // not decompiled yet (0x71006243cc)

    /* 0x28 */ const int* mCloseOption_s{};
    /* 0x30 */ const int* mDelayTimer_s{};
    /* 0x38 */ const int* mType_s{};
    /* 0x40 */ const int* mInterval_s{};
    /* 0x48 */ const bool* mOnce_s{};
    /* 0x50 */ sead::SafeString mmstxtName_s{};
    /* 0x60 */ sead::SafeString mlabelName_s{};
    /* 0x70 */ sead::SafeString mlabelName2_s{};
    /* 0x80 */ sead::SafeString mlabelName3_s{};
    /* 0x90 */ int* mGanonBeastVoiceSequenceCount_a{};
    /* 0x98 */ void* mSimpleDialogUnit_a{};
    /* 0xa0 */ Unk_71025afb58** _a0 = nullptr;
    /* 0xa8 */ u32 _a8 = 0;
    /* 0xac */ u8 _ac = 0;
    /* 0xad */ u8 _ad = 0;
    /* 0xae */ u16 _ae = 0;
    /* 0xb0 */ u32 _b0 = 0;
    /* 0xb4 */ u8 _b4 = 0;
};
KSYS_CHECK_SIZE_NX150(GanonBeastFirstMessage, 0xb8);

}  // namespace uking::behavior
