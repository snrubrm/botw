#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ClearFadeInCreate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ClearFadeInCreate, ksys::act::ai::Behavior)
public:
    explicit ClearFadeInCreate(const InitArg& arg);
    ~ClearFadeInCreate() override;
    bool init_(sead::Heap* heap) override;
    void enter() override;
    void leave() override;

};
KSYS_CHECK_SIZE_NX150(ClearFadeInCreate, 0x28);

}  // namespace uking::behavior
