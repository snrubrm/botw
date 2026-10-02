#include "Game/AI/Action/actionFreeze.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

namespace uking::action {

Freeze::Freeze(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Freeze::~Freeze() = default;

bool Freeze::init_(sead::Heap* heap) {
    _68.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_68._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _68.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _68.x();
    return true;
}

void Freeze::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Freeze::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Freeze::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsChangeInAir_s, "IsChangeInAir");
    getStaticParam(&mTransBoneKey_s, "TransBoneKey");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Freeze::calc_() {
    ActionWithPosAngReduce::calc_();
    if (_30) {
        sub_7100738428(mActor, 0.0f);
        sub_7100738AA8(mActor, 0.0f);
        _30 = false;
    } else if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (dynamic_actor->_868)
            dynamic_actor->_868->sub_71006EDFBC();
    }
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(3))
        setFinished();
}

}  // namespace uking::action
