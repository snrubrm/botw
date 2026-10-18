#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/System/physClosestPointQueryWithInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"

namespace ksys::snd {

// TU 0x71010349dc..0x71010366e4 (static initialiser) in the original.

void Unk_SoundMgr38_48::sub_7101035A50() {
    _1e08.set(1);
    if (_1e08.isOff(2)) {
        sub_7101035888();
        _1dc0 = 1;
    }
}

// NON_MATCHING: query and contact iterator stack layout and status loads differ.
bool Unk_SoundMgr38_48::sub_7101036530(bool* indoor, const sead::Vector3f& position) {
    static_assert(offsetof(Unk_SoundMgr38_48, mSphere) == 0x1e00);
    static_assert(offsetof(phys::ClosestPointQuery, _18) == 0x18);
    static_assert(offsetof(phys::ContactPoint, material_mask_b) == 0x48);
    phys::SphereBasedClosestPointQuery query(mSphere, position, 1, "GrudgeBaseSound InDoor", 1,
                                             phys::LowPriority::Yes);
    if (auto* info = query.getContactPointInfo()) {
        info->subscribeLayer(phys::ContactLayer::SensorInDoor);
        const bool result = query.execute(false);
        if (query._18 == 1) {
            *indoor = result;
            if (result) {
                for (auto it = info->begin(), end = info->end(); it != end; ++it) {
                    const u32 type = (it.getPoint()->material_mask_b.getRawData() >> 20) & 7;
                    if (type == 3 || type == 4) {
                        *indoor = false;
                        break;
                    }
                }
            }
        }
    }
    return query._18 == 1;
}

}  // namespace ksys::snd
