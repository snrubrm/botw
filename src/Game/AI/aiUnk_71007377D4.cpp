#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

void sub_7100737708(ksys::phys::CharacterController* controller, f32 value) {
    ksys::act::sub_7100EE60A0(controller, value);
}

void sub_710073770C(ksys::phys::CharacterController* controller, f32 value, const sead::Vector3f& up) {
    ksys::act::sub_7100EE61B4(controller, value, up);
}

void sub_7100737710(ksys::phys::CharacterController* controller, const sead::Vector3f& vel) {
    ksys::act::sub_7100EE61E8(controller, vel);
}

void sub_7100737714(ksys::phys::CharacterController* controller, const sead::Vector3f& ang_vel) {
    ksys::act::sub_7100EE6228(controller, ang_vel);
}

void sub_7100737718(ksys::phys::RigidBody* body, const sead::Vector3f& vel) {
    ksys::act::sub_7100EE6268(body, vel);
}

void sub_710073771C(ksys::phys::RigidBody* body, const sead::Vector3f& ang_vel) {
    ksys::act::sub_7100EE62B0(body, ang_vel);
}
