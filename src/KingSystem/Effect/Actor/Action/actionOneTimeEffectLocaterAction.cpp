#include "KingSystem/Effect/Actor/Action/actionOneTimeEffectLocaterAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <prim/seadScopedLock.h>

namespace ksys::eft {

void Unk_EffectActorTable::sub_7100DA2118() {
    // NON_MATCHING: SDK range iteration uses a different counter instead of the native paired loop.
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mCount = 0;
    for (auto& entry : _0) {
        entry.actor = nullptr;
        entry._28 = false;
    }
}

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

}  // namespace ksys::eft
