#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OffOcculutionCulling : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OffOcculutionCulling, ksys::act::ai::Behavior)
public:
    explicit OffOcculutionCulling(const InitArg& arg);
    ~OffOcculutionCulling() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(OffOcculutionCulling, 0x28);

}  // namespace uking::behavior
