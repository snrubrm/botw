#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace uking::action {

// Callback stored in Unk_7102459df8::Unk::_588 by BeltConveyor::enter_ (declared only).
void sub_71000C4560(ksys::act::Actor* actor, const ksys::act::ActorConstDataAccess* other, void* unused,
                    ksys::phys::RigidBody* body);

class BeltConveyor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeltConveyor, ksys::act::ai::Action)
public:
    explicit BeltConveyor(const InitArg& arg);
    ~BeltConveyor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71000c48c0 (declared only): the body of calc_ is out of line in the original.
    void sub_71000C48C0();
    void calc_() override;

    sead::Vector3f _1c{0, 0, 0};
    sead::Vector3f _28{0, 0, 0};
    sead::Vector3f _34{0, 0, 0};
    f32 _40 = 0;
    // static_param at offset 0x48
    const float* mASRate_s{};
    // static_param at offset 0x50
    const bool* mIsReverse_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x68
    const float* mRotateSpeed_m{};
};

}  // namespace uking::action
