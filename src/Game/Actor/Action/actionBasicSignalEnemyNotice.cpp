#include "Game/Actor/Action/actionBasicSignalEnemyNotice.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BasicSignalEnemyNotice::BasicSignalEnemyNotice(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BasicSignalEnemyNotice::~BasicSignalEnemyNotice() = default;

bool BasicSignalEnemyNotice::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BasicSignalEnemyNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = mActor->checkBasicSig();
}

void BasicSignalEnemyNotice::leave_() {
    ksys::act::ai::Action::leave_();
}

void BasicSignalEnemyNotice::loadParams_() {}

void BasicSignalEnemyNotice::calc_() {
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

void BasicSignalEnemyNotice::m32() {}

void BasicSignalEnemyNotice::m33() {}

void BasicSignalEnemyNotice::m34() {}

void BasicSignalEnemyNotice::m35() {}

}  // namespace uking::action
