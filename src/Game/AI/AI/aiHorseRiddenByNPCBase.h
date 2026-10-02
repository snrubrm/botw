#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act {
class BaseProcLink;
struct Unk_7100d78e50;
}  // namespace ksys::act

namespace uking::ai {

class HorseRiddenByNPCBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRiddenByNPCBase, ksys::act::ai::Ai)
public:
    explicit HorseRiddenByNPCBase(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Switches to 徘徊 / 逃走 (from `pos`) for the threat level `kind` found by calc_.
    virtual void m34(u32 kind, const sead::Vector3f& pos, ksys::act::BaseProcLink* link);
    // Whether an awareness entry of sensor `idx` is ignored.
    virtual bool m35(ksys::act::Unk_7100d78e50* entry, s32 idx);

protected:
    // static_param at offset 0x38
    const bool* mIsEscapeFromSameActorType_s{};
    bool _40 = false;
};

}  // namespace uking::ai
