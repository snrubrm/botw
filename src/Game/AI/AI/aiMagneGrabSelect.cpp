#include "Game/AI/AI/aiMagneGrabSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::ai {

MagneGrabSelect::MagneGrabSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneGrabSelect::~MagneGrabSelect() = default;

bool MagneGrabSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool MagneGrabSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool MagneGrabSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneGrabSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* grab = mActor->m128();
    if (grab && grab->m2())
        changeChild("掴まれ", params);
    else
        changeChild("離れ", params);
}

void MagneGrabSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;
    auto* grab = mActor->m128();
    if (grab && grab->m2())
        changeChild("掴まれ");
    else
        changeChild("離れ");
}

void MagneGrabSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneGrabSelect::loadParams_() {}

}  // namespace uking::ai
