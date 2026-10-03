#include "Game/Actor/actSwarm.h"

namespace uking::act {

void Swarm::Unit::sub_71002DAA98() {
    if (!(_b8 & 2))
        _b8 = (_b8 & ~0xc) | 8;
}

void Swarm::Unit::sub_71002DAA78() {
    if (_b8 & 2) {
        _b8 = (_b8 & ~0xe) | 4;
        _bc = 0;
    }
}

}  // namespace uking::act
