#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorXLinkCreate.h"

namespace uking::behavior {

class XLinkCreateToParts : public XLinkCreate {
    SEAD_RTTI_OVERRIDE(XLinkCreateToParts, XLinkCreate)
public:
    explicit XLinkCreateToParts(const InitArg& arg);
    ~XLinkCreateToParts() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;  // TODO 0x710064826c
    void m16(sead::Vector3f* out) override;  // TODO 0x7100648178

    /* 0x78 */ sead::SafeString mPartsName_s{};
    /* 0x88 */ const sead::Vector3f* mOffset_s{};
};
KSYS_CHECK_SIZE_NX150(XLinkCreateToParts, 0x90);

}  // namespace uking::behavior
