#include "Game/Actor/actGelEnemy.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
GelEnemy::~GelEnemy() = default;

bool GelEnemy::startPreparingForPreDelete_() {
    sub_71011DA868(&_14c8);
    return Enemy::startPreparingForPreDelete_();
}

}  // namespace uking::act
