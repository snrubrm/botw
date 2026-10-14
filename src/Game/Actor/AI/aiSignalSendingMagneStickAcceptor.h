#pragma once

#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include <prim/seadDelegate.h>

namespace ksys::map {
class Object;
}

namespace uking::ai {

class SignalSendingMagneStickAcceptor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SignalSendingMagneStickAcceptor, ksys::act::ai::Ai)
public:
    explicit SignalSendingMagneStickAcceptor(const InitArg& arg);
    ~SignalSendingMagneStickAcceptor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710056bd78: acquires the closest placed actor within MagneStickMaxSearchDistance into `acc`
    void sub_710056BD78(ksys::act::ActorLinkConstDataAccess* acc);
    // 0x710056be7c: the first linked map object from `*index` on whose actor exists and passes `filter`
    // (nullptr at the end); stores its index in `*index`. `this` is unused (callers never set x0).
    ksys::map::Object*
    sub_710056BE7C(ksys::act::Actor* actor, s32* index,
                   sead::IDelegate1R<const ksys::act::ActorLinkConstDataAccess&, bool>* filter);

    // map_unit_param at offset 0x38
    const float* mMagneStickMaxSearchDistance_m{};
};

}  // namespace uking::ai
