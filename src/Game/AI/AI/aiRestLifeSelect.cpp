#include "Game/AI/AI/aiRestLifeSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RestLifeSelect::RestLifeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RestLifeSelect::~RestLifeSelect() = default;

bool RestLifeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original shares one sub_7100550C44 call between the two paths (branch layout)
void RestLifeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mIsEnter_s && *mIsTrgOnly_s) {
        auto* life = mActor->getLife();
        const f32 current = life ? f32(*life) : 1.0f;
        if (f32(mActor->getMaxLife()) * *mLifeRatio_s > current ||
            (current <= 0.0f && *mLifeRatio_s < 0.0f))
            changeChild("元気", params);
        else
            sub_7100550C44(params);
    } else {
        sub_7100550C44(params);
    }

    _54 = false;
    auto* life = mActor->getLife();
    _50 = life ? *life : 1;
}

void RestLifeSelect::calc_() {
    if (*mIsTrgOnly_s) {
        auto* life = mActor->getLife();
        const s32 current = life ? *life : 1;
        const f32 previous = _50;
        if (!(f32(mActor->getMaxLife()) * *mLifeRatio_s > previous ||
              (previous <= 0.0f && *mLifeRatio_s < 0.0f))) {
            auto* new_life = mActor->getLife();
            const f32 now = new_life ? f32(*new_life) : 1.0f;
            if (f32(mActor->getMaxLife()) * *mLifeRatio_s > now ||
                (now <= 0.0f && *mLifeRatio_s < 0.0f)) {
                _54 = true;
            }
        }
        _50 = current;
    }

    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable() && !*mIsEnter_s) {
        if (!*mIsTrgOnly_s || _54)
            sub_7100550C44(nullptr);
    }
}

void RestLifeSelect::sub_7100550C44(ksys::act::ai::InlineParamPack* params) {
    auto* life = mActor->getLife();
    const f32 current = life ? f32(*life) : 1.0f;
    if (f32(mActor->getMaxLife()) * *mLifeRatio_s > current ||
        (current <= 0.0f && *mLifeRatio_s < 0.0f)) {
        if (!isCurrentChild("瀕死"))
            changeChild("瀕死", params);
    } else {
        if (!isCurrentChild("元気"))
            changeChild("元気", params);
    }
}

void RestLifeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RestLifeSelect::loadParams_() {
    getStaticParam(&mLifeRatio_s, "LifeRatio");
    getStaticParam(&mIsTrgOnly_s, "IsTrgOnly");
    getStaticParam(&mIsEnter_s, "IsEnter");
}

}  // namespace uking::ai
