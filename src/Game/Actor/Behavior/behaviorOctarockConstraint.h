#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OctarockConstraint : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OctarockConstraint, ksys::act::ai::Behavior)
public:
    explicit OctarockConstraint(const InitArg& arg);
    ~OctarockConstraint() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OctarockConstraint, 0x28);

}  // namespace uking::behavior
