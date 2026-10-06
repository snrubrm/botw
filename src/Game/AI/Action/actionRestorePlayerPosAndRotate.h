#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RestorePlayerPosAndRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RestorePlayerPosAndRotate, ksys::act::ai::Action)
public:
    explicit RestorePlayerPosAndRotate(const InitArg& arg);
    ~RestorePlayerPosAndRotate() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataVec3fPlayerPos_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataFloatPlayerDirectionY_d{};
    sead::Matrix34f _40 = sead::Matrix34f::ident;
    sead::Vector3f _70 = sead::Vector3f::ones;
};

}  // namespace uking::action
