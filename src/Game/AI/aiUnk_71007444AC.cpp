#include "Game/AI/aiUnk_71007444AC.h"
#include <new>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/System/Timer.h"

void Unk_71007444acElem::sub_710074424C() {
    switch (_44) {
    case 1: {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_0, &accessor);
        if (accessor.isStateSleep()) {
            accessor.setProperties(_14, nullptr, nullptr, nullptr, false, 0, -1);
            _44 = 2;
        }
        break;
    }
    case 2:
        if (_10 > 0) {
            ksys::Timer::update(&_10, -1);
            if (_10 <= 0) {
                _10 = 0;
                _44 = 0;
            }
        }
        break;
    }
}

void Unk_71007444acElem::sub_7100744310() {
    _10 = 0;
    _44 = 0;
}

void Unk_71007444ac::sub_710074456C() {
    auto* elem = _8;
    for (s32 i = 0; i != _0; ++i, ++elem)
        elem->sub_710074424C();
}

bool Unk_71007444ac::sub_710074431C(sead::Heap* heap, const char* name, s32 count) {
    if (count > 0) {
        auto* elems = new (heap, 8, std::nothrow) Unk_71007444acElem[count];
        if (elems) {
            _0 = count;
            _8 = elems;
        }
    }
    if (!_8)
        return false;

    bool success = true;
    auto* elem = _8;
    for (s32 i = 0; i != _0; ++i, ++elem) {
        if (success) {
            ksys::act::InstParamPack params;
            auto* actor = ksys::act::ActorCreator::instance()->createActor(
                name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params,
                true, false);
            if (actor) {
                elem->_0.acquire(actor, false);
                elem->_44 = 0;
                success = true;
            } else {
                success = false;
            }
        }
    }
    return success;
}

void Unk_71007444ac::sub_71007444AC() {
    if (_8) {
        delete[] _8;
        _8 = nullptr;
        _0 = 0;
    } else {
        auto* elem = _8;
        for (s32 i = 0; i != _0; ++i, ++elem) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&elem->_0, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
    }
}

s32 Unk_71007444ac::sub_71007445BC(const sead::Matrix34f& mtx, s32 duration) {
    if (_0 == 0)
        return -1;

    const f32 time = duration;
    const f32 x = mtx(0, 3);
    const f32 z = mtx(2, 3);
    auto* elem = _8;
    Unk_71007444acElem* oldest = nullptr;
    s32 oldest_index = -1;
    s32 selected = -1;
    for (s32 i = 0; i != _0; ++i, ++elem) {
        if (elem->_44 != 0) {
            f32 distance;
            {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&elem->_0, &accessor);
                const auto& actor_mtx = accessor.getActorMtx();
                const f32 dx = actor_mtx(0, 3) - x;
                const f32 dz = actor_mtx(2, 3) - z;
                distance = sead::Mathf::sqrt(dx * dx + dz * dz);
            }
            if (distance < 5.0f) {
                elem->_10 = time;
                return i;
            }
        }
        if (selected < 0) {
            if (elem->_44 == 0) {
                elem->_44 = 1;
                if (elem->_0.hasProcInCalcState()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&elem->_0, &accessor);
                    accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                }
                elem->_14 = mtx;
                elem->_10 = time;
                selected = i;
            } else if (!oldest || oldest->_10 > elem->_10) {
                oldest = elem;
                oldest_index = i;
            }
        }
    }
    if (selected < 0 && oldest) {
        oldest->_10 = 0;
        oldest->_44 = 1;
        if (oldest->_0.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&oldest->_0, &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        oldest->_14 = mtx;
        oldest->_10 = time;
        return oldest_index;
    }
    return selected;
}
