#pragma once

#include "Game/AI/Action/actionPriestBossWarpOrVanish.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>

namespace uking::action {

class PriestBossFastWarpMove : public PriestBossWarpOrVanish {
    SEAD_RTTI_OVERRIDE(PriestBossFastWarpMove, PriestBossWarpOrVanish)
public:
    explicit PriestBossFastWarpMove(const InitArg& arg);
    ~PriestBossFastWarpMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override {
        if (_204.value >= *mAppearFrame_s)
            return true;
        return mFlags.isOn(Flag::Finished);
    }

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mAfterImage0AppearFrame_s{};
    // static_param at offset 0x30
    const float* mAfterImage1AppearFrame_s{};
    // static_param at offset 0x38
    const float* mAppearFrame_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x50
    float* mCurrentFrame_d{};
    // dynamic_param at offset 0x58
    bool* mIsCloseMove_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mMoveDstPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mAfterImage0Pos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mAfterImage1Pos_d{};
    // Whole 222070 copies getMessageTransceiverId() into each destination;
    // whole 2224ec passes that destination and the +20 payload to Actor::sendMessage.
    struct Entry {
        struct Payload {
            ksys::act::Actor* actor = nullptr;
            sead::Vector3f position{0.0f, 0.0f, 0.0f};
            f32 time = 0.0f;
            bool _18 = false;
            bool _19 = false;
            u16 _1a = 0;
        };
        ksys::MesTransceiverId destination;
        bool pending = false;
        Payload payload{};
    };
    static_assert(sizeof(Entry) == 0x40);
    sead::SafeArray<Entry, 6> _80{};
    s32 _200 = 0;
    ksys::Timer _204;
    ksys::Timer _210;
    ksys::Timer _21c;
    u8 _228 = 0;
    sead::Vector3f _22c{0.0f, 0.0f, 0.0f};
    sead::Matrix33f _238;
};
KSYS_CHECK_SIZE_NX150(PriestBossFastWarpMove, 0x260);

}  // namespace uking::action
