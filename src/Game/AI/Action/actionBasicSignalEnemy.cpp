#include "Game/AI/Action/actionBasicSignalEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BasicSignalEnemy::BasicSignalEnemy(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BasicSignalEnemy::~BasicSignalEnemy() = default;

bool BasicSignalEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = mActor->checkBasicSig();
}

void BasicSignalEnemy::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalEnemy::loadParams_() {}

void BasicSignalEnemy::calc_() {
    if (mActor->checkBasicSig()) {
        if (!_1c) {
            m32();
            _1c = true;
        }
        m34();
    } else {
        if (_1c) {
            m33();
            _1c = false;
        }
        m35();
    }
}

void BasicSignalEnemy::m32() {}

void BasicSignalEnemy::m33() {}

void BasicSignalEnemy::m34() {}

void BasicSignalEnemy::m35() {}

}  // namespace uking::action
