#pragma once

#include "Game/AI/Behavior/behaviorOnTrgGuardOffTargetXLinkCreateBase.h"

namespace uking::behavior {

class OnTrgGuardOffTargetXLinkCreate : public OnTrgGuardOffTargetXLinkCreateBase {
    SEAD_RTTI_OVERRIDE(OnTrgGuardOffTargetXLinkCreate, OnTrgGuardOffTargetXLinkCreateBase)
public:
    explicit OnTrgGuardOffTargetXLinkCreate(const InitArg& arg);
    ~OnTrgGuardOffTargetXLinkCreate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14(Unk_71012419b4* handle) override;  // TODO 0x7100632148

};
KSYS_CHECK_SIZE_NX150(OnTrgGuardOffTargetXLinkCreate, 0x38);

}  // namespace uking::behavior
