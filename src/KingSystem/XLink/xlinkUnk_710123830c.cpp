#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::xlink {

void Unk_710123830c::sub_71012372EC() {
    _1c.reset(1);
}

void Unk_710123830c::sub_710123827C(bool value) {
    if (_16.isOn(0x100))
        _1c.change(0x100, value);
}

}  // namespace ksys::xlink
