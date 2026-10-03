#pragma once

#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::ai {

class BossBattleRoomRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BossBattleRoomRoot, ksys::act::ai::Ai)
public:
    explicit BossBattleRoomRoot(const InitArg& arg);
    ~BossBattleRoomRoot() override;

    bool handleMessage_(const ksys::Message& message) override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // The command of the 0x80000d7 message payload (a SEAD_ENUM in the original: the value goes through
    // a stack round trip); names and the number of values are guesses.
    SEAD_ENUM(Command, _0, _1, _2)

    // Bit indices of _1b4 (a SEAD_ENUM in the original: the index goes through a stack round trip);
    // names and the number of values are guesses.
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7)

    // static_param at offset 0x38
    const int* mFramesRollKeepSecond_s{};
    // static_param at offset 0x40
    const int* mNumTimesRoll_s{};
    // static_param at offset 0x48
    const float* mTitleAngle_s{};
    // static_param at offset 0x50
    const float* mRollAngle_s{};
    // static_param at offset 0x58
    const float* mFramesRotate_s{};
    // static_param at offset 0x60
    const float* mFramesReset_s{};
    // static_param at offset 0x68
    const float* mFramesRoll_s{};
    // static_param at offset 0x70
    const float* mFramesDelayRoll_s{};
    // static_param at offset 0x78
    const float* mFramesRollKeepFirst_s{};
    sead::Matrix34f _80 = sead::Matrix34f::ident;
    sead::Matrix34f _b0 = sead::Matrix34f::ident;
    sead::Matrix34f _e0 = sead::Matrix34f::ident;
    Unk_71023dbd40 _110{mActor, 0x80000d7};
    Unk_71024509a8 _140;
    void* _188 = nullptr;
    f32 _190 = 0;
    f32 _194 = 0;
    f32 _198 = 0;
    ksys::Timer _19c{0, 0};
    ksys::Timer _1a8{0, 0};
    sead::BitFlag32 _1b4;
    ksys::MesTransceiverId _1b8;
    f32 _1d0 = 0;
    u32 _1d4 = 0;
    u32 _1d8 = 0;
    ksys::phys::RigidBody* _1e0 = nullptr;
    ksys::phys::RigidBody* _1e8 = nullptr;
    // aal::Shape* (destroyed by the destructor; aal is not in the repo)
    void* _1f0 = nullptr;
    // xlink2 handle (event pointer + create id; leave_ fades the event)
    void* _1f8 = nullptr;
    u32 _200 = 0;
    u32 _204;
    bool _208 = true;
};
KSYS_CHECK_SIZE_NX150(BossBattleRoomRoot, 0x210);

}  // namespace uking::ai
