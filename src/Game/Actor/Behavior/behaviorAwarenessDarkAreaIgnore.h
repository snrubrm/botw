#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AwarenessDarkAreaIgnore : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwarenessDarkAreaIgnore, ksys::act::ai::Behavior)
public:
    explicit AwarenessDarkAreaIgnore(const InitArg& arg);
    ~AwarenessDarkAreaIgnore() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(AwarenessDarkAreaIgnore, 0x28);

}  // namespace uking::behavior
