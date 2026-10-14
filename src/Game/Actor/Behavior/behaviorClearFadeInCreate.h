#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ClearFadeInCreate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ClearFadeInCreate, ksys::act::ai::Behavior)
public:
    explicit ClearFadeInCreate(const InitArg& arg);
    ~ClearFadeInCreate() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;
    void m9() override;

};
KSYS_CHECK_SIZE_NX150(ClearFadeInCreate, 0x28);

}  // namespace uking::behavior
