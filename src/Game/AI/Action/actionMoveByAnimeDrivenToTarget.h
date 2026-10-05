#pragma once

#include "Game/AI/Action/actionMoveByAnimeDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::as {
class ASList;
}
namespace ksys::phys {
class CharacterController;
class NavMeshCharacter;
}

// The embedded object is constructed and destroyed out of line; its source name is unknown.
class Unk_7100000fd0 {
public:
    Unk_7100000fd0();
    ~Unk_7100000fd0();
    void sub_710000102C(f32 value);
    void sub_710000103C(const Unk_7100000fd0& other);
    bool sub_7100001050(ksys::as::ASList* as_list, ksys::phys::NavMeshCharacter* nav,
                       ksys::phys::CharacterController* controller, f32 max_rotate);
    bool sub_71000010E0(ksys::as::ASList* as_list, const sead::Vector3f& direction,
                       const sead::Vector3f& forward, f32 max_rotate);

private:
    const f32* _0;
    const f32* _8;
    const f32* _10;
    const f32* _18;
    const f32* _20;
    const f32* _28;
    sead::Vector3f _30;
    const f32* _40;
    f32 _48;
};
KSYS_CHECK_SIZE_NX150(Unk_7100000fd0, 0x50);

namespace uking::action {

class MoveByAnimeDrivenToTarget : public MoveByAnimeDriven {
    SEAD_RTTI_OVERRIDE(MoveByAnimeDrivenToTarget, MoveByAnimeDriven)
public:
    explicit MoveByAnimeDrivenToTarget(const InitArg& arg);
    ~MoveByAnimeDrivenToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x58
    const float* mAnimRotateMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    Unk_7100000fd0 _68;
};
KSYS_CHECK_SIZE_NX150(MoveByAnimeDrivenToTarget, 0xb8);

}  // namespace uking::action
