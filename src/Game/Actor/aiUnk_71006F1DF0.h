#pragma once

#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

namespace ksys::phys {
class RigidBody;
class MaterialMask;
}

namespace sead {
template <typename T>
class SafeStringBase;
}

// Placeholder name = address (lane2 s21; 0x71006f1df0): whether `pos` is in a non-auto-placement zone, for an
// actor that has a rideable part (Actor slot 132) and is not a domestic animal. Used by PreyNormal::m39.
bool sub_71006F1DF0(ksys::act::Actor* actor, const sead::Vector3f& pos);

// 0x71006f1408 (declared only; placeholder name, 624 B): finds the rigid body `body_name` of the actor's physics
// for the bone `bone_name` (HorseFreeze / HorseElectricParalysis pass the ThrowOffAttackRigidBodyName param and
// "Saddle_Root").
ksys::phys::RigidBody* sub_71006F1408(ksys::act::Actor* actor, const sead::SafeStringBase<char>& body_name,
                                      const sead::SafeStringBase<char>& bone_name);

// 0x71006f1e70: Soil, Sand or HeavySand membership of the material mask.
bool sub_71006F1E70(const ksys::phys::MaterialMask& mask);
