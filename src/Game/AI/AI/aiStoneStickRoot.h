#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class Constraint;
class ContactPointInfo;
class RigidBody;
}  // namespace ksys::phys

namespace uking::ai {

class StoneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneStickRoot, ksys::act::ai::Ai)
public:
    explicit StoneStickRoot(const InitArg& arg);
    ~StoneStickRoot() override;
    bool hasUpdateForPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool updateForPreDelete() override;

protected:
    // static_param at offset 0x38
    const sead::Vector3f* mFixPoint_s{};
    bool _40 = false;
    void* _48 = nullptr;
    void* _50 = nullptr;
    ksys::phys::Constraint* _58 = nullptr;
    ksys::phys::RigidBody* _60 = nullptr;
    ksys::phys::RigidBody* _68 = nullptr;
    ksys::phys::ContactPointInfo* _70 = nullptr;
    u32 _78 = 0;
};
KSYS_CHECK_SIZE_NX150(StoneStickRoot, 0x80);

}  // namespace uking::ai
