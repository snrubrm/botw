#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OctarockHideForm : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OctarockHideForm, ksys::act::ai::Behavior)
public:
    explicit OctarockHideForm(const InitArg& arg);
    ~OctarockHideForm() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ void* mOctarockFormChangeUnit_a{};
};
KSYS_CHECK_SIZE_NX150(OctarockHideForm, 0x30);

}  // namespace uking::behavior
