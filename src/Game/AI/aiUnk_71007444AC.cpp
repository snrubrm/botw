#include "Game/AI/aiUnk_71007444AC.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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
