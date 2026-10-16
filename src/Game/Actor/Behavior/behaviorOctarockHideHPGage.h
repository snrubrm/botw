#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OctarockHideHPGage : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OctarockHideHPGage, ksys::act::ai::Behavior)
public:
    explicit OctarockHideHPGage(const InitArg& arg);
    ~OctarockHideHPGage() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ void* mOctarockFormChangeUnit_a{};
};
KSYS_CHECK_SIZE_NX150(OctarockHideHPGage, 0x30);

}  // namespace uking::behavior
