#pragma once

#include <prim/seadBitFlag.h>

namespace ksys::phys {
class CharacterController;
};

namespace ksys::act {

class Actor;

// todo: move?
enum class MotionType {
    _0 = 0,
    Hover = 3,
};

class CCAccessor {
public:
    CCAccessor();
    ~CCAccessor();

    phys::CharacterController* sub_710072ACF8(Actor* actor);
    bool sub_710072AD1C(phys::CharacterController* cc);
    bool changeMotionType(phys::CharacterController* cc, MotionType motion_type);
    void resetMotionType(phys::CharacterController* cc);
    void resetRigidBodyMotion(Actor* actor);
    void sub_710072AE20(phys::CharacterController* cc);
    void sub_710072AEEC(phys::CharacterController* cc);

private:
    MotionType mMotionType{};
    sead::BitFlag8 _4;
    sead::BitFlag8 _5;
};

// Unnamed CCAccessor extension (its functions follow CCAccessor's in the same TU): puts the actor into
// hover mode (character controller motion type Hover, else zero gravity on the main rigid body) and
// restores the previous state.
class Unk_710072AFD0 : public CCAccessor {
public:
    Unk_710072AFD0();
    ~Unk_710072AFD0();

    bool sub_710072AFFC(Actor* actor);
    void sub_710072B078(Actor* actor);

private:
    f32 _8 = 1.0f;
    int _c = 0;
};

}  // namespace ksys::act
