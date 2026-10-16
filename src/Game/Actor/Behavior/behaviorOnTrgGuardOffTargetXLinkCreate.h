#pragma once

#include "Game/Actor/Behavior/behaviorOnTrgGuardOffTargetXLinkCreateBase.h"

namespace uking::behavior {

class OnTrgGuardOffTargetXLinkCreate : public OnTrgGuardOffTargetXLinkCreateBase {
    SEAD_RTTI_OVERRIDE(OnTrgGuardOffTargetXLinkCreate, OnTrgGuardOffTargetXLinkCreateBase)
public:
    explicit OnTrgGuardOffTargetXLinkCreate(const InitArg& arg);
    ~OnTrgGuardOffTargetXLinkCreate() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m14(Unk_71012419b4* handle) override;

};
KSYS_CHECK_SIZE_NX150(OnTrgGuardOffTargetXLinkCreate, 0x38);

}  // namespace uking::behavior
