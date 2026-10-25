#include "Game/Actor/actRideable.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

// Shared rate defaults of the rider state (0x7101ec1934-0x7101ec193c; the movement action TUs use
// them as well, through these global-scope names).
extern const f32 sUnk_7101EC1934 = 0.0f;
extern const f32 sUnk_7101EC1938 = 0.0f;
extern const f32 sUnk_7101EC193C = 1.0f;

namespace uking::act {

const f32 sUnk_7101EC1904 = 1.0f;

// The S2 rate defaults (the block at 0x7101ec1920; the ctor takes their addresses).
static const f32 sUnk_7101EC1920 = 6.0f;
static const f32 sUnk_7101EC1924 = 0.0f;
static const f32 sUnk_7101EC1928 = 0.0f;
static const f32 sUnk_7101EC192c = 1.0f;
static const f32 sUnk_7101EC1930 = 0.4f;
// Start value of a gear request, loaded through the GOT by sub_7100E63224.
const f32 sUnk_7101EC1960 = 6.0f;

// 0x7100e6fa10: the S2 sub-object's defaults: the rate pointers, the movement state and the flags.
RideableBase::S2::S2() {
    _0 = &sUnk_7101EC1920;
    _8 = &sUnk_7101EC1924;
    _10 = &sUnk_7101EC1928;
    _18 = &sUnk_7101EC1934;
    _20 = &sUnk_7101EC1938;
    _28 = &sUnk_7101EC193C;
    _30.set(0.0f, 0.0f, 0.0f);
    _40 = &sUnk_7101EC192c;
    _48 = &sUnk_7101EC1904;
    _50 = 0;
    _54 = 0.0872665f;  // 5 degrees in radians
    _58 = &sUnk_7101EC1930;
    _68 = 1.0f;
    _6c = 0.0f;
    _60 = 0.0f;
    _78 = 0.0f;
    _7c = 0;
    _7e = 0;
    _70 = 0.0f;
    _74 = sead::Mathf::infinity();
    _80.set(sead::Vector2f::zero);
    _88 = 0;
}

// In its own file: the original's RideableBase destructor calls this out-of-line (it is in another
// translation unit).
RideableBase::S2::~S2() {}

// 0x7100e6fdd4: the gear request without a direction. Reads the navmesh character's velocity and current
// direction (each under its lock), normalises the direction (the zero vector below Mathf::epsilon()) and
// forwards both to sub_7100E6FF38 with the already clamped gear values.
bool RideableBase::S2::sub_7100E6FDD4(RideableBase* owner, ksys::as::ASList* as_list,
                                      ksys::phys::NavMeshCharacter* nav,
                                      ksys::phys::CharacterController* cc, S1::UnkGear gear_type,
                                      S1::UnkGear gear, S1::UnkGear min_gear_at_auto_down,
                                      AutoStopAndTurnMode mode) {
    nav->_1e0.lock();
    const sead::Vector3f velocity = nav->_248;
    nav->_1e0.unlock();
    nav->_1e0.lock();
    sead::Vector3f dir = nav->_23c;
    nav->_1e0.unlock();

    if (dir.normalize() < sead::Mathf::epsilon())
        dir.set(0.0f, 0.0f, 0.0f);

    return sub_7100E6FF38(owner, as_list, nav, velocity, dir, cc, gear_type, gear, min_gear_at_auto_down,
                          mode);
}

}  // namespace uking::act
