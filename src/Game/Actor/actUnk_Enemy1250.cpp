#include "Game/Actor/actEnemy.h"

namespace uking::act {

// 0x71006f81f0 (in the ClothReactionUnit TU: make 0x71006f78a4, init 0x71006f7928)
void Unk_Enemy1250::sub_71006F81F0() {
    if (_10 && _10->_8)
        _10->_8->sub_71011DA868(&_10->_38);
    if (_18 && _18->_8)
        _18->_8->sub_71011DA868(&_18->_38);
    if (_20 && _20->_8)
        _20->_8->sub_71011DA868(&_20->_38);
    if (_28 && _28->_8)
        _28->_8->sub_71011DA868(&_28->_38);
}

}  // namespace uking::act
