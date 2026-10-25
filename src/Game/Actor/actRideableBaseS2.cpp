#include "Game/Actor/actRideable.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::act {

const f32 sUnk_7101EC1904 = 1.0f;
// Start value of a gear request, loaded through the GOT by sub_7100E63224.
const f32 sUnk_7101EC1960 = 6.0f;

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
