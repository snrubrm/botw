#pragma once

#include <prim/seadBitFlag.h>

namespace ksys::phys {
class CharacterController;
};

namespace ksys::act {

class Actor;

// todo: move?
enum class MotionType {
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

}  // namespace ksys::act
