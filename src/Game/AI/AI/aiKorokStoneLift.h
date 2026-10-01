#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokStoneLift : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(KorokStoneLift, SimpleLiftable)
public:
    explicit KorokStoneLift(const InitArg& arg);
    ~KorokStoneLift() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    sead::Vector3f _c8 = sead::Vector3f::zero;
    sead::Vector3f _d4;
    sead::Vector3f _e0;
    sead::Vector3f _ec;
    sead::Vector3f _f8 = sead::Vector3f::zero;
    sead::Vector3f _104;
    sead::Vector3f _110;
    sead::Vector3f _11c;
    f32 _128 = 0.0f;
    f32 _12c = 1.0f;
    f32 _130 = 1.5f;
    f32 _134 = 0.0f;
    bool _138 = false;
    f32 _13c = -1.0f;
    bool _140 = false;
    bool _141 = false;
    bool _142 = false;
};

}  // namespace uking::ai
