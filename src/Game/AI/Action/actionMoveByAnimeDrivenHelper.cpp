#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <prim/seadScopedLock.h>

extern const f32 sUnk_7101EC1934;
extern const f32 sUnk_7101EC1938;
extern const f32 sUnk_7101EC193C;

static const f32 sUnk_7101DA350C = 0.6f;
static const f32 sUnk_7101DA3510 = 0.15f;
static const f32 sUnk_7101DA3514 = 0.002f;
static const f32 sUnk_7101DA3518 = 0.4f;

Unk_7100000fd0::Unk_7100000fd0()
    : _0(&sUnk_7101DA350C), _8(&sUnk_7101DA3510), _10(&sUnk_7101DA3514),
      _18(&sUnk_7101EC1934), _20(&sUnk_7101EC1938), _28(&sUnk_7101EC193C),
      _30(0, 0, 0), _40{&sUnk_7101DA3518, 0} {}

// NON_MATCHING: vector copy uses three scalar stores; original uses a z store and an xy pair.
bool Unk_7100000fd0::sub_7100001050(ksys::as::ASList* as_list,
                                  ksys::phys::NavMeshCharacter* nav,
                                  ksys::phys::CharacterController* controller, f32 max_rotate) {
    sead::Vector3f direction;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        direction = nav->_23c;
    }
    sub_71000010E0(as_list, direction, controller->get64(), max_rotate);
    return false;
}


// The embedded helper object of MoveByAnimeDrivenToTarget (its TU starts at 0x7100000fd0).
Unk_7100000fd0::~Unk_7100000fd0() = default;

// NON_MATCHING: the original stores the z component (wzr) before the 8-byte xy store (ours: xy first)
void Unk_7100000fd0::sub_710000102C(f32 value) {
    _30.set(0.0f, 0.0f, 0.0f);
    _40._8 = value;
}

// NON_MATCHING: store order of the zeroed vector (original: z, then xy) and the load of other._48 first
void Unk_7100000fd0::sub_710000103C(const Unk_7100000fd0& other) {
    _30.set(0.0f, 0.0f, 0.0f);
    _40._8 = other._40._8;
}
