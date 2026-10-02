#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

class KeeseNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(KeeseNormal, EnemyNormal)
public:
    explicit KeeseNormal(const InitArg& arg);
    ~KeeseNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // static_param at offset 0x3d0
    const float* mRoamHeightFromGlowObj_s{};
    // map_unit_param at offset 0x3d8
    const bool* mIsCreateOnFace_m{};
    Unk_7102450558 _3e0;
    sead::Vector3f _430;
    sead::Vector3f _43c;
    bool _448 = false;
    ksys::Timer _44c;
    ksys::phys::RayCastForRequest* _458 = nullptr;
    Unk_7102451938 _460;
    ksys::act::BaseProcLink _488;
};
KSYS_CHECK_SIZE_NX150(KeeseNormal, 0x498);

}  // namespace uking::ai
