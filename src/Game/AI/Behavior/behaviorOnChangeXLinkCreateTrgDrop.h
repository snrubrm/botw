#pragma once

#include "Game/AI/Behavior/behaviorOnChangeXLinkCreate.h"

namespace uking::behavior {

class OnChangeXLinkCreateTrgDrop : public OnChangeXLinkCreate {
    SEAD_RTTI_OVERRIDE(OnChangeXLinkCreateTrgDrop, OnChangeXLinkCreate)
public:
    explicit OnChangeXLinkCreateTrgDrop(const InitArg& arg);
    ~OnChangeXLinkCreateTrgDrop() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m14() override;

    /* 0x40 */ bool* mIsDrop_a{};
};
KSYS_CHECK_SIZE_NX150(OnChangeXLinkCreateTrgDrop, 0x48);

}  // namespace uking::behavior
