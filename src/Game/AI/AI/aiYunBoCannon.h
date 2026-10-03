#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/AI/aiGoronCannonBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// Message sent to the linked cannon ball by YunBoCannon (the type is set per send; the payload carries
// the cannon's target matrix). Placeholder names: vtable 0x7102433368 (D2 0x60f2e4, D0 0x61011c, m2
// 0x610150: inline, emitted in this TU).
struct Unk_7102433368_Payload {
    ksys::act::BaseProcLink _0;
    sead::Matrix34f _10 = sead::Matrix34f::ident;
    u32 _40 = 0x8000000;
    sead::JobQueueLock mLock;
};

class Unk_7102433368 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    Unk_7102433368_Payload _18;
};

namespace uking::ai {

class YunBoCannon : public GoronCannonBase {
    SEAD_RTTI_OVERRIDE(YunBoCannon, GoronCannonBase)
public:
    explicit YunBoCannon(const InitArg& arg);
    ~YunBoCannon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    void m35(ksys::act::Actor* actor, ksys::act::Actor* ball) override;
    void m36(ksys::act::Actor* ball) override;

    // Unnamed in the binary (0x710060f440): sends the "RegistedActorMessageBroadCastTag" message of _1f0
    // and keeps the receiver in _220; true while the receiver is in the calc state.
    bool sub_710060F440();
    // Unnamed in the binary (0x710060fae0): sends `mtx` with message `type` through _190 to _220.
    void sub_710060FAE0(const sead::Matrix34f& mtx, u32 type, bool a3);

protected:
    // inline-only in the original; name is a guess. Evidence: m35 / handleMessage_ / calc_ build the
    // SafeString of the anchor name before the "DestinationAnchor" one and load mActor after both.
    ksys::map::Object* findDestinationAnchor(const sead::SafeString& anchor_name) const {
        return ksys::act::findLinkReferenceObj(mActor, "DestinationAnchor", anchor_name, nullptr);
    }

    // static_param at offset 0x130
    sead::SafeString mReturnAnchorName_s{};
    // map_unit_param at offset 0x140
    const int* mCannonSpot_m{};
    // map_unit_param at offset 0x148
    sead::SafeString mActorName_m{};
    gsys::BoneAccessKeyEx _158;
    Unk_7102433368 _190{mActor, 0x8000000};
    Unk_710235aba0 _1f0{mActor, 0x8000040};
    ksys::act::BaseProcLink _220;
    u16 _230 = 0;
    u8 _232 = 0;
};
KSYS_CHECK_SIZE_NX150(YunBoCannon, 0x238);

}  // namespace uking::ai
