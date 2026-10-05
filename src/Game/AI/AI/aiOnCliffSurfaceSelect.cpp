#include "Game/AI/AI/aiOnCliffSurfaceSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

OnCliffSurfaceSelect::OnCliffSurfaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffSurfaceSelect::~OnCliffSurfaceSelect() = default;

bool OnCliffSurfaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffSurfaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mOnCliff_m && !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4) && mActor->getMtx()(1, 1) < 0.99f) {
        sead::Matrix34f home;
        mActor->getHomeMtx(&home);
        if (home(1, 1) < 0.99f) {
            sub_71004F277C(true);
            return;
        }
    }
    if (*mIsCliffFreeze_a) {
        sub_71004F296C();
    } else {
        auto* actor = mActor;
        sead::Matrix34f home;
        actor->getHomeMtx(&home);
        if (home(1, 1) < 0.99f) {
            ksys::util::sub_71011F00EC(&home, actor->getMtx().getBase(2), sead::Vector3f::ey,
                                     actor->getMtx().getTranslation(), false);
            actor->sub_71011C8B04(home);
        }
        changeChild("通常", nullptr);
    }
}

void OnCliffSurfaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffSurfaceSelect::loadParams_() {
    getMapUnitParam(&mOnCliff_m, "OnCliff");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
