#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AwarenessDarkAreaIgnore : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwarenessDarkAreaIgnore, ksys::act::ai::Behavior)
public:
    explicit AwarenessDarkAreaIgnore(const InitArg& arg);
    ~AwarenessDarkAreaIgnore() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(AwarenessDarkAreaIgnore, 0x28);

}  // namespace uking::behavior
