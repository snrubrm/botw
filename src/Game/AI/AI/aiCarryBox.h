#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/gameActorContextStuff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

// Contact callback installed on the carried box's rigid body (vtable 0x71023dcd70, invoke 0x7100344920; placeholder
// name): contacts with bodies whose name starts with "Motorcycle" are disabled.
class Unk_71023dcd70 : public ksys::phys::ContactPointInfo::ContactCallback {
public:
    bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                const ksys::phys::ContactPointInfo::Event& event) override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023dcd70, 0x8);

namespace uking::ai {

class CarryBox : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CarryBox, ksys::act::ai::Ai)
public:
    explicit CarryBox(const InitArg& arg);
    ~CarryBox() override;

    bool hasUpdateForPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    bool updateForPreDelete() override;

    // 0x7100343fd0 / 0x71003440a8 (declaration only): the per-frame body of the carried box while it is
    // (343fd0) / is not (3440a8) held; `has_contacts`: the first contact point info has contacts.
    void sub_7100343FD0(ksys::phys::RigidBody* body, ksys::phys::ContactPointInfo* info, bool has_contacts);
    void sub_71003440A8(ksys::phys::RigidBody* body, ksys::phys::ContactPointInfo* info, bool has_contacts);

    /* 0x38 */ Unk_71024507c8 _38{0x1800004};
    /* 0x78 */ u8 _78{};
    /* 0x79 */ bool _79{};
    /* 0x7a */ u8 _7a{};
    /* 0x7c */ u32 _7c{};
    /* 0x80 */ ActorContextStuff _80{mActor};
    /* 0x7e0 */ Unk_71023dcd70 _7e0;
};
KSYS_CHECK_SIZE_NX150(CarryBox, 0x7e8);

}  // namespace uking::ai
