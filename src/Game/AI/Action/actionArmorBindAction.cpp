#include "Game/AI/Action/actionArmorBindAction.h"
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

ArmorBindAction::ArmorBindAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ArmorBindAction::~ArmorBindAction() {
    delete[] _28;
}

bool ArmorBindAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ArmorBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ArmorBindAction::leave_() {
    mActor->sub_71011DA834(_20);
    _20 = nullptr;
    if (_28) {
        if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
            if (auto* owner = armor->getOwner()) {
                owner->sub_71011DA868(&_28[0]);
                owner->sub_71011DA868(&_28[1]);
            }
        }
    }
}

void ArmorBindAction::loadParams_() {}

// NON_MATCHING: only the order of the two `is_armor = false` blocks (null actor / not an armor) differs.
void ArmorBindAction::calc_() {
    bool is_armor = false;
    auto* armor = sead::DynamicCast<act::ArmorBase>(mActor);
    if (armor) {
        auto* owner = armor->getOwner();
        if (owner && _20)
            _20->x(owner);
        is_armor = true;
    }
    mActor->setScale({1.0f, 1.0f, 1.0f});
    if (_28 && (is_armor & !_28->_8)) {
        if (auto* owner = armor->getOwner()) {
            owner->boneHandleStuff(&_28[0], false);
            owner->boneHandleStuff(&_28[1], false);
        }
    }
}

}  // namespace uking::action
