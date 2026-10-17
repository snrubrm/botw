#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_7100736460.h"
#include "Game/gameStatisticsMgr.h"
#include <thread/seadDelegateThread.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(AutoPlacementMgr)

void AutoPlacementMgr::sub_7100659F94(ksys::act::Actor* actor) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : _5b118) {
        if (entry.actor == actor) {
            entry.actor = nullptr;
            _171e46 = true;
            break;
        }
    }
}

bool AutoPlacementMgr::auto0(const sead::Vector3f& pos, u32 placement_type) {
    return _171ef0.x(pos, true, 1 << placement_type, placement_type == 0 ? &_189df8 : nullptr);
}

bool AutoPlacementMgr::isNonAutoPlacement(const sead::Vector3f& pos, bool a2) {
    if (a2) {
        dlc::isPlayingOneHitObliteratorQuest();
        if (_171e68[6] > 0)
            return true;
    }
    return _171ef0.x(pos, true, 0x40, nullptr);
}

void AutoPlacementMgr::preCalc() {
    mNearWork.stepAllRaycasts();
    for (auto& entry : _5b118)
        entry.placement.stepAllRaycasts();
    for (auto& work : mWorks)
        work.stepAllRaycasts();
}

// NON_MATCHING: the original tests `arg == 2` first (cmp 2 / b.eq / cbnz); clang 4 always makes the
// `arg == 0` path the fall-through here, in every if/switch order tried.
// NON_MATCHING: the original uses a 0x70-byte frame and recomputes `i * 0x8b68` for every field
// access; ours keeps two entry pointers in registers and needs only 0x50 bytes.
void AutoPlacementMgr::cmd2_a() {
    auto lock = sead::makeScopedLock(mCS);
    if (!_171e46)
        return;

    for (s32 i = 0; i < 0x20; ++i) {
        if (auto9())
            return;
        Unk1& entry = _5b118[i];
        if (!entry.actor) {
            entry.placement.sub_710064DA54();
            entry.count = 0;
        } else if (!entry._8b63) {
            entry.placement.setSpawnInfo(entry.name, entry.count);
            entry._8b63 = true;
        }
    }
    _171e46 = false;
}

// NON_MATCHING: clang unrolls the nine-work loop here; the original keeps it rolled (madd /
// cmp 9). The guards, the near-work step and the 32-work loop match.
// NON_MATCHING: the original recomputes the work pointer with madd each iteration and keeps a few
// more values in registers; the random points, the group matrix transform and the calls match.
void AutoPlacementMgr::cmd2_b() {
    for (s32 i = 0; i < 9; ++i) {
        if (auto9())
            return;
        AutoPlacement& work = mWorks[i];
        if (work._8 == 0) {
            if (work.updateSpawnMaybe(nullptr))
                work.updateSpawnInfosMaybe();
        }
        if (auto9())
            return;
        sead::Thread::yield();
    }

    if (mNearWork._8 == 0) {
        if (mNearWork.updateSpawnMaybe(nullptr))
            mNearWork.updateSpawnInfosMaybe();
    }

    for (s32 i = 0; i < 0x20; ++i) {
        if (auto9())
            return;
        Unk1& entry = _5b118[i];
        if (entry._8b63 && entry.placement._8 == 0) {
            auto* rng = sead::GlobalRandom::instance();
            const f32 fx = entry.scale.x * rng->getF32() * (s32(rng->getU32() & 2) - 1);
            const f32 fz = entry.scale.z * rng->getF32() * (s32(rng->getU32() & 2) - 1);

            sead::Vector3f offset;
            offset.x = fx;
            offset.y = 0.0f;
            offset.z = fz;

            if (entry.is_box == 0) {
                const f32 radius = entry.scale.x;
                const f32 dist_sq = offset.x * offset.x + offset.y * offset.y + offset.z * offset.z;
                if (dist_sq > radius * radius) {
                    const f32 len = sead::Mathf::sqrt(dist_sq);
                    if (len > 0.0f) {
                        const f32 scale = radius * rng->getF32() / len;
                        offset.x *= scale;
                        offset.z *= scale;
                    }
                }
            }

            const auto& mtx = entry.mtx;
            sead::Vector3f pos;
            pos.x = mtx.m[0][3] + offset.x * mtx.m[0][0] + offset.y * mtx.m[0][1] +
                    offset.z * mtx.m[0][2];
            pos.y = mtx.m[1][3] + offset.x * mtx.m[1][0] + offset.y * mtx.m[1][1] +
                    offset.z * mtx.m[1][2];
            pos.z = mtx.m[2][3] + offset.x * mtx.m[2][0] + offset.y * mtx.m[2][1] +
                    offset.z * mtx.m[2][2];

            if (entry.placement.updateSpawnMaybe(&pos))
                entry.placement.updateSpawnInfosMaybe();
        }
        if (auto9())
            return;
        sead::Thread::yield();
    }
}

void AutoPlacementMgr::cmd2_c() {
    if (_5b058 || _5b060)
        return;
    if (_171e47)
        return;
    if (!_171e44)
        return;
    if (ksys::act::ActorSystem::instance()->get13b().isOnBit(0))
        return;

    if (_54 & 0x10) {
        if (prepareSpawn(&mNearWork))
            return;
    }

    for (s32 i = 0; i < 0x20; ++i) {
        if (auto9())
            return;
        Unk1& entry = _5b118[i];
        if (entry._8b62 && prepareSpawn(&entry.placement))
            return;
        if (auto9())
            return;
        sead::Thread::yield();
    }

    AutoPlacement* const works = mWorks.mBuffer;
    for (s32 i = 0; i < 9; ++i) {
        if (auto9())
            return;
        if (prepareSpawn(&works[i]))
            return;
        if (auto9())
            return;
        sead::Thread::yield();
    }
}

// NON_MATCHING: the original materialises `return true` in both branches after doSpawn (two orr/b
// blocks); clang merges them here, and it places the negative-index block inline.
bool AutoPlacementMgr::prepareSpawn(AutoPlacement* placement) {
    const u8 near_flag = placement->mNearFlag;
    if (!placement->sub_71006504FC())
        return false;

    const s32 group_idx = placement->sub_7100650908();
    if (group_idx < 0) {
        if (near_flag != 0xFF)
            return false;
        _nearCounts[group_idx] = 0;
        return false;
    }

    AutoPlacementFlowRes* res;
    if (near_flag == 0xFF)
        res = AutoPlacementFlowMgr::instance()->getResource2(group_idx);
    else
        res = AutoPlacementFlowMgr::instance()->getResource1(group_idx);
    const s32 placement_type = res->placement_type;

    if (near_flag == 0xFF)
        res = AutoPlacementFlowMgr::instance()->getResource2(group_idx);
    else
        res = AutoPlacementFlowMgr::instance()->getResource1(group_idx);

    const s32 group = placement->placeGroup(res);
    if (group < 0) {
        placement->incrementGroup();
        return false;
    }

    if (near_flag == 0xFF) {
        s16& count = _nearCounts[group_idx];
        if (count < placement->_6) {
            count = u16(count) + 1;
            return false;
        }
    }

    if (!doSpawn(placement, group, placement_type))
        placement->incrementGroup();
    return true;
}

bool AutoPlacementMgr::invoked3(int arg) {
    if (arg == 2) {
        const s32 old = _171e48--;
        if (old == 0)
            _171e48 = 0;
        return old == 1;
    } else if (arg != 0) {
        if (!mThread || _171e48 < 1)
            return true;
        return _50 == 3;
    } else {
        ++_171e48;
        preCalc();
        return true;
    }
}

bool AutoPlacementMgr::auto2(const sead::SafeString& name, const sead::Vector3f& pos) {
    f32 dist = -1.0f;
    for (auto& work : mWorks) {
        if (work.hasGroupNearMaybe(name, pos, &dist))
            return true;
    }
    return false;
}

bool AutoPlacementMgr::auto9() {
    return _171e48 > 0;
}

bool AutoPlacementInfo::x(const sead::Vector3f& pos, bool a2, u32 type_mask, const void* a4) {
    const int px = int(pos.x) + 5000;
    int cx = px / 1000;
    if (cx > 9)
        cx = 9;
    if (px < -999)
        cx = 0;

    const int pz = int(pos.z) + 4000;
    int cz = pz / 1000;
    if (cz > 7)
        cz = 7;
    if (pz < -999)
        cz = 0;

    if (x_0(1.0f, cx, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx + 1, cz - 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx + 1, cz, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx - 1, cz + 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    if (x_0(1.0f, cx, cz + 1, pos, a2, type_mask, nullptr, a4) != -1)
        return true;
    return x_0(1.0f, cx + 1, cz + 1, pos, a2, type_mask, nullptr, a4) != -1;
}

void AutoPlacementMgr::stopThread() {
    _50.load();
    if (mThread) {
        mThread->quitAndDestroySingleThread(false);
        ksys::phys::System::instance()->sub_71012157B4(mThread, false);
        delete mThread;
        mThread = nullptr;
    }
    ksys::act::ActorSystem::instance()->clearAutoPlacementMgrDelegates();
}

int AutoPlacementMgr::sub_7100659158(int idx, bool near_flow) {
    auto* mgr = AutoPlacementFlowMgr::instance();
    return (near_flow ? mgr->getResource2(idx) : mgr->getResource1(idx))->placement_type;
}

// NON_MATCHING: the original loads the placement type with `ldrsb x20` (sign-extended to 64 bits, tested with
// `cbnz x20` after the call); ours loads `ldrb w20` and sign-extends later (for `s8` / `int` / `long` locals alike).
bool AutoPlacementMgr::sub_71006591BC(int idx, bool near_flow) {
    auto* mgr = AutoPlacementFlowMgr::instance();
    const s8 type = (near_flow ? mgr->getResource2(idx) : mgr->getResource1(idx))->placement_type;
    if (dlc::isPlayingOneHitObliteratorQuest() && type == 0)
        return true;
    return _171e68[type] > 0;
}

f32 AutoPlacementMgr::sub_7100659230(const sead::Vector3f& pos) {
    f32 value = 0;
    if (uking::StatisticsMgr::instance()->query(&value, 1, _189db0, &pos))
        return value * 50.0f;
    return 0.0f;
}

f32 sub_7100659298(const sead::Vector3f& pos, void* const* stats) {
    f32 value = 0;
    if (uking::StatisticsMgr::instance()->query(&value, 1, *stats, &pos))
        return value;
    return 0.0f;
}

void sub_710065622C(s32* col, s32* row, const sead::Vector3f* pos) {
    *col = sead::Mathi::clamp(s32((pos->x + 5000.0f) / 200.0f), 0, 49);
    *row = sead::Mathi::clamp(s32((pos->z + 4000.0f) / 200.0f), 0, 39);
}

f32 AutoPlacementMgr::sub_71006592E8(const sead::Vector3f& pos) {
    f32 value = 0;
    if (uking::StatisticsMgr::instance()->query(&value, 1, _189dd0, &pos))
        return value * 200.0f;
    return 0.0f;
}

// NON_MATCHING: only the select polarity of the free-entry choice (`csel x25, x12, x25, eq` in the original, `csel
// x25, x25, x12, ne` here). `is_box` is a u32 (the original stores the raw argument register).
bool AutoPlacementMgr::sub_7100659E40(ksys::act::Actor* actor, const sead::SafeString& actor_name, int count,
                                      u32 is_box) {
    if (u32(count - 1) >= 0x7fff)
        return false;

    auto lock = sead::makeScopedLock(mCS);
    Unk1* free_entry = nullptr;
    for (auto& entry : _5b118) {
        if (entry.actor == actor)
            return false;
        if (!entry.actor && !entry._8b62 && !free_entry)
            free_entry = &entry;
    }
    if (!free_entry)
        return false;

    free_entry->actor = actor;
    free_entry->mtx = actor->getMtx();
    free_entry->scale = actor->getScale();
    free_entry->name = actor_name;
    free_entry->is_box = is_box;
    free_entry->count = count;
    free_entry->_8b62 = true;
    _171e46 = true;
    return true;
}

// NON_MATCHING: the original reads the counter once more (a discarded volatile load) after the decrement
void AutoPlacementMgr::sub_7100659DE0(int type, bool enable) {
    if (enable) {
        ++_171e4c[type];
        _171e68[type] = 5;
    } else {
        --_171e4c[type];
    }
}

}  // namespace uking
