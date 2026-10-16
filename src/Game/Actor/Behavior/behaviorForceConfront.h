#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceConfront : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceConfront, ksys::act::ai::Behavior)
public:
    explicit ForceConfront(const InitArg& arg);
    ~ForceConfront() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(ForceConfront, 0x28);

}  // namespace uking::behavior
