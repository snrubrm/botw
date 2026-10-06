#include "Game/AI/Action/actionOneTimeEffectLocaterAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

OneTimeEffectLocaterAction::OneTimeEffectLocaterAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OneTimeEffectLocaterAction::~OneTimeEffectLocaterAction() = default;

bool OneTimeEffectLocaterAction::init_(sead::Heap* heap) {
    _1c = false;
    return true;
}

void OneTimeEffectLocaterAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OneTimeEffectLocaterAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void OneTimeEffectLocaterAction::loadParams_() {}

void OneTimeEffectLocaterAction::calc_() {
    if (!_1c) {
        _1c = true;
        auto* actor = mActor;
        if (actor) {
            if (auto* xlink = actor->getXLink()) {
                sub_71012410C8(xlink, "_OneTime", 2, &_20);
                sead::Matrix34f scale;
                scale.makeS(actor->getScale());
                sead::Matrix34f mtx;
                mtx.setMul(actor->getMtx(), scale);
                _20.sub_7101241A44(mtx);
            }
        }
    }
    if (auto* actor = mActor) {
        auto* xlink = actor->getXLink();
        if (!xlink || xlink->x_2())
            actor->deleteAndEmit(0);
    }
}

}  // namespace uking::action
