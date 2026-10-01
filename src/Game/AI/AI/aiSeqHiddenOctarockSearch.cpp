#include "Game/AI/AI/aiSeqHiddenOctarockSearch.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SeqHiddenOctarockSearch::SeqHiddenOctarockSearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqHiddenOctarockSearch::~SeqHiddenOctarockSearch() = default;

bool SeqHiddenOctarockSearch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqHiddenOctarockSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = ksys::act::isAttClientEnabled(mActor, "AutoAim");
    _39 = ksys::act::isAttClientEnabled(mActor, "AutoAimHidden");
    ksys::act::disableAttClient(mActor, "AutoAimHidden");
    ksys::act::enableAttClient(mActor, "AutoAim");
    changeChild("サーチ", params);
}

void SeqHiddenOctarockSearch::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        child->isChangeable();
        return;
    }

    if (!isCurrentChild("サーチ")) {
        setFinished();
        return;
    }

    if (child->isFinished())
        changeChild("発見");
    else
        changeChild("未発見");
}

void SeqHiddenOctarockSearch::leave_() {
    if (_38)
        ksys::act::enableAttClient(mActor, "AutoAimHidden");
    if (!_39)
        ksys::act::disableAttClient(mActor, "AutoAim");
}

void SeqHiddenOctarockSearch::loadParams_() {}

}  // namespace uking::ai
