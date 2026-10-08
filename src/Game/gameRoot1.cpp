#include "Game/gameRoot1.h"
#include "Game/gameRoot4.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root1)

Root1::Root1() {
    _28[0] = 2;
    _28[1] = 2;
}

Root1::~Root1() = default;

void Root1::sub_7100899CA4(FlagIdx idx, s32 value) {
    _28[idx] = value;
}

bool Root1::sub_7100899CC8() {
    if (_28[0] != 2)
        _30 = _28[0] == 0;
    else if (_28[1] != 2)
        _30 = _28[1] == 0;
    else
        _30 = _31;
    if (Root4::instance())
        Root4::instance()->sub_71008BCE5C(Root4::FlagIdx::_3, _30, 9);
    return _30;
}

}  // namespace uking
