#pragma once

#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"

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
    void sub_710056BD78(ksys::act::ActorConstDataAccess* acc);
    // 0x710056be7c (declared only, 528 bytes): the next candidate map object from `*index` on (nullptr at the end)
    ksys::map::Object* sub_710056BE7C(ksys::act::Actor* actor, s32* index, void* a3);

    // map_unit_param at offset 0x38
    const float* mMagneStickMaxSearchDistance_m{};
};

}  // namespace uking::ai
