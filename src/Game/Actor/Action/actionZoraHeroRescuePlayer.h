#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ZoraHeroRescuePlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ZoraHeroRescuePlayer, ksys::act::ai::Action)
public:
    explicit ZoraHeroRescuePlayer(const InitArg& arg);
    ~ZoraHeroRescuePlayer() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    // 0x71002c071c
    bool sub_71002C071C(const sead::Vector3f& pos, sead::Vector3f* out);
    // 0x71002c09e8
    void sub_71002C09E8(const sead::Vector3f& pos, sead::Vector3f* out);

    // aitree_variable at offset 0x20
    void* mZoraHeroShowMsgUnit_a{};
};

}  // namespace uking::action
