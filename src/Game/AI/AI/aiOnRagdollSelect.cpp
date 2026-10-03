#include "Game/AI/AI/aiOnRagdollSelect.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

namespace uking::ai {

OnRagdollSelect::OnRagdollSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnRagdollSelect::~OnRagdollSelect() = default;

bool OnRagdollSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnRagdollSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && actor->_868) {
        if (actor->_868->sub_71006ED9EC())
            changeChild("ラグドール中", params);
        else
            changeChild("通常", params);
    } else if (mActor->sub_71011CEA90()) {
        changeChild("ラグドール中", params);
    } else {
        changeChild("通常", params);
    }
}

void OnRagdollSelect::calc_() {}

void OnRagdollSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnRagdollSelect::loadParams_() {}

}  // namespace uking::ai
