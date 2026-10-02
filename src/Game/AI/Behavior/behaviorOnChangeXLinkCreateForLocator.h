#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorOnChangeXLinkCreate.h"

namespace uking::behavior {

class OnChangeXLinkCreateForLocator : public OnChangeXLinkCreate {
    SEAD_RTTI_OVERRIDE(OnChangeXLinkCreateForLocator, OnChangeXLinkCreate)
public:
    explicit OnChangeXLinkCreateForLocator(const InitArg& arg);
    ~OnChangeXLinkCreateForLocator() override;
    bool m6(sead::Heap* heap) override;  // TODO 0x7100630bf0
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14() override;  // TODO 0x7100631144
    
    // 0x40-byte elements allocated by m6 (type unknown).
    struct Unk58 {
        u8 _0[0x40];
    };

    /* 0x40 */ const int* mEmitSourceType_s{};
    /* 0x48 */ sead::SafeString mTargetLocaterName_s{};
    /* 0x58 */ sead::Buffer<Unk58> _58;
    /* 0x68 */ bool _68 = false;
};
KSYS_CHECK_SIZE_NX150(OnChangeXLinkCreateForLocator, 0x70);

}  // namespace uking::behavior
