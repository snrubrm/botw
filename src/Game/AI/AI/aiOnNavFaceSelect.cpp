#include "Game/AI/AI/aiOnNavFaceSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

OnNavFaceSelect::OnNavFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnNavFaceSelect::~OnNavFaceSelect() = default;

bool OnNavFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnNavFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    if (!nav || (nav->_2a4 & 0xffff) == 0x17)
        changeChild("ナビメッシュ無し", params);
    else
        changeChild("ナビメッシュ有り", params);
}

void OnNavFaceSelect::calc_() {}

void OnNavFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnNavFaceSelect::loadParams_() {}

bool OnNavFaceSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool OnNavFaceSelect::isFailed() const {
    return mFlags.isOn(Flag::Failed) || getCurrentChild()->isFailed();
}

}  // namespace uking::ai
