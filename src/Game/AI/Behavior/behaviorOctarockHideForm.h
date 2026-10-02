#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OctarockHideForm : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OctarockHideForm, ksys::act::ai::Behavior)
public:
    explicit OctarockHideForm(const InitArg& arg);
    ~OctarockHideForm() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ void* mOctarockFormChangeUnit_a{};
};
KSYS_CHECK_SIZE_NX150(OctarockHideForm, 0x30);

}  // namespace uking::behavior
