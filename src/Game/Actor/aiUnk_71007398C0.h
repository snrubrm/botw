#pragma once

namespace ksys::act {
class Actor;
class Unk_7100d860d8;
}  // namespace ksys::act

// 0x71007398c0 (CSV Actor::x_50; declared only; placeholder name): &BoneControl::_0->_10 or nullptr, like
// sub_71005DB0EC (a second copy in the AI utility code next to sub_71007398A8).
ksys::act::Unk_7100d860d8* sub_71007398C0(ksys::act::Actor* actor);
