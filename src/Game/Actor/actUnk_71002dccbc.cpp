#include "Game/Actor/actUnk_71002dccbc.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::act {

void Unk_71002dccbc::sub_71002DC32C() {
    for (auto& entry : mEntries) {
        entry.link.reset();
        entry.flags = 0;
        entry._12 = 0;
    }
}

void Unk_71002dccbc::sub_71002DCBDC(u16 flags) {
    for (auto& entry : mEntries) {
        entry.flags &= ~flags;
        if (entry.flags == 0) {
            entry.link.reset();
            entry._12 = 0;
        }
    }
}

// NON_MATCHING: the original keeps a redundant `and w8, w8, #0xffff` after each flag test
bool Unk_71002dccbc::sub_71002DCCBC(s32 flags) {
    for (auto& entry : mEntries) {
        if (entry.link.hasProcInCalcState() && (entry.flags & flags))
            return false;
    }
    return true;
}

// NON_MATCHING: the original keeps the found index in a register and recomputes the entry address in the shared tail
bool Unk_71002dccbc::sub_71002DC8A0(const ksys::act::BaseProcLink& link, u16 flags) {
    for (auto& entry : mEntries) {
        if (entry.link == link && (entry.flags & flags)) {
            entry.flags &= ~flags;
            if (entry.flags == 0) {
                entry.link.reset();
                entry._12 = 0;
            }
            return true;
        }
    }
    return false;
}

// NON_MATCHING: the original loads the entry's x / z before the position's (load order only)
ksys::act::BaseProcLink* Unk_71002dccbc::sub_71002DCEDC(u16 flags, const sead::Vector3f& pos) {
    f32 min_distance = std::numeric_limits<f32>::max();
    ksys::act::BaseProcLink* nearest = nullptr;
    for (auto& entry : mEntries) {
        if (entry.link.hasProcInCalcState() && static_cast<u16>(entry.flags & flags)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry.link, &accessor);
            const auto& mtx = accessor.getActorMtx();
            const f32 dx = pos.x - mtx(0, 3);
            const f32 dz = pos.z - mtx(2, 3);
            const f32 distance = dx * dx + dz * dz;
            if (distance < min_distance) {
                min_distance = distance;
                nearest = &entry.link;
            }
        }
    }
    if (!nearest)
        nearest = &ksys::act::getDummyBaseProcLink();
    return nearest;
}

}  // namespace uking::act
