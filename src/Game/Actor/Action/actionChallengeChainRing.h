#pragma once

#include "Game/Actor/Action/actionAppearFollowChallenge.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include <math/seadVector.h>

class Unk_71024f15c0;
namespace ksys::map { class Rail; }

namespace uking::action {

class ChallengeChainRing : public AppearFollowChallenge {
    SEAD_RTTI_OVERRIDE(ChallengeChainRing, AppearFollowChallenge)
public:
    explicit ChallengeChainRing(const InitArg& arg);
    ~ChallengeChainRing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m33();
    virtual void m34(const sead::Vector3f& pos, const sead::Vector3f& dir);

    // map_unit_param at offset 0xab0
    const float* mChainRingOrbitSpeed_m{};
    // map_unit_param at offset 0xab8
    const bool* mIsFirstNode_m{};
    // Four 0x10-byte records (an 8-byte field and a 4-byte field each), cleared by the constructor.
    struct Record {
        u64 _0 = 0;
        u32 _8 = 0;
    };
    Record _ac0;
    Record _ad0;
    Record _ae0;
    Record _af0;
    sead::Vector3f _b00 = sead::Vector3f::zero;
    sead::Vector3f _b0c = sead::Vector3f::zero;
    sead::Matrix34f _b18 = sead::Matrix34f::ident;
    f32 _b48 = 0;
    f32 _b4c = 0;
    f32 _b50 = 0;
    f32 _b54 = 0;
    f32 _b58 = 0;
    f32 _b5c = 0;
    f32 _b60 = 0;
    f32 _b64 = 0;
    f32 _b68 = 45.0f;
    u8 _b6c = 0;
    u8 _b6d = 1;
    u8 _b6e = 0;
    u8 _b6f = 0;
    bool _b70 = false;
    u8 _b71 = 0;
    u16 _b72 = 0;
    u8 _b74 = 0;
    Unk_71024f15c0* _b78 = nullptr;
    // Not initialised by the constructor.
    sead::Vector3f _b80;
    ksys::Timer _b8c;

    virtual void m35(sead::Vector3f* pos);
    // Complete enter_ passes the rail, position output, direction output and progress.
    bool sub_7100051DF4(ksys::map::Rail* rail, sead::Vector3f* pos,
                       sead::Vector3f* direction, f32 progress);
};

}  // namespace uking::action
