#include "Game/AI/AI/aiMagneGearRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

MagneGearRoot::MagneGearRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneGearRoot::~MagneGearRoot() = default;

bool MagneGearRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneGearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
    changeChild("通常");
}

void MagneGearRoot::calc_() {
    const bool grabbed = mActor->m128()->m2();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("マグネ捕まり中")) {
            changeChild("はめ込まれた");
            ksys::eft::searchAndEmitSLink(mActor, "Put", false);
        }
    } else if (child->isChangeable()) {
        bool to_grabbed = false;
        bool to_normal = false;
        if (isCurrentChild("通常"))
            to_grabbed = true;
        else if (isCurrentChild("マグネ捕まり中"))
            to_normal = true;
        else if (isCurrentChild("はめ込まれた") && _38 >= 6)
            to_grabbed = true;

        if (to_grabbed) {
            if (mActor->m128()->m2())
                changeChild("マグネ捕まり中");
        } else if (to_normal) {
            if (!mActor->m128()->m2())
                changeChild("通常");
        }
    }

    s32 counter = 0;
    if (!grabbed)
        counter = sead::Mathi::min(++_38, 100);
    _38 = counter;
}

void MagneGearRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneGearRoot::loadParams_() {}

}  // namespace uking::ai
