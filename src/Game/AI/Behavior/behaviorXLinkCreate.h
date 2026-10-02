#pragma once

#include <math/seadVector.h>
#include "Game/AI/Behavior/behaviorOnStateXLinkCreate.h"

namespace uking::behavior {

class XLinkCreate : public OnStateXLinkCreate {
    SEAD_RTTI_OVERRIDE(XLinkCreate, OnStateXLinkCreate)
public:
    explicit XLinkCreate(const InitArg& arg);
    ~XLinkCreate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual void m15(sead::Vector3f* out) {}
    virtual void m16(sead::Vector3f* out) {}
    // 0x7100647608
    void sub_7100647608();

};

}  // namespace uking::behavior
