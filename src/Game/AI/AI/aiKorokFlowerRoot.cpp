#include "Game/AI/AI/aiKorokFlowerRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KorokFlowerRoot::KorokFlowerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokFlowerRoot::~KorokFlowerRoot() = default;

bool KorokFlowerRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokFlowerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("コログ花出現");
    if (!*mIsNoAppearEffect_m)
        xlinkSearchAndEmit(mActor, "Appear", 2, &_48);
    if (*mIsLastKorokFlower_m) {
        if (auto* as_list = mActor->getASList()) {
            as_list->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
            as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 1.0f);
        }
    }
}

void KorokFlowerRoot::calc_() {
    if (isCurrentChild("コログ花消滅") || !isChangeable())
        return;

    if (isCurrentChild("コログ花出現")) {
        changeChild("コログ花待機");
    } else if (isCurrentChild("コログ花待機")) {
        xlinkSearchAndEmit(mActor, "Vanish", 2, &_48);
        changeChild("コログ花消滅");
    }
}

void KorokFlowerRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokFlowerRoot::loadParams_() {
    getMapUnitParam(&mIsNoAppearEffect_m, "IsNoAppearEffect");
    getMapUnitParam(&mIsLastKorokFlower_m, "IsLastKorokFlower");
}

}  // namespace uking::ai
