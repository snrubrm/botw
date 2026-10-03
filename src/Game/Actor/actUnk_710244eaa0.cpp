#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

Unk_710244eaa0::~Unk_710244eaa0() = default;

void Unk_710244eaa0::m4() {
    if (!_1e8)
        return;
    if (_40._8)
        _38->sub_71011DA868(&_40);
    if (_118._8)
        _110->sub_71011DA868(&_118);
}

void Unk_710244eaa0::m6() {
    if (_1e8) {
        _10c = 1;
        _1e4 = 1;
    }
}

void Unk_710244eaa0::m8() {
    if (!_1e8)
        return;
    _100 = 0;
    if (_40._8)
        _38->sub_71011DA868(&_40);
    _1d8 = 0;
    if (_118._8)
        _110->sub_71011DA868(&_118);
}

}  // namespace uking::act
