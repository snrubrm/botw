#include "Game/AI/Behavior/behaviorShortRangeBattleAlignment.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

ShortRangeBattleAlignment::ShortRangeBattleAlignment(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// NON_MATCHING: midpoint float registers, arithmetic scheduling and vector stores differ.
void ShortRangeBattleAlignment::m7() {
    const sead::Vector3f first = sub_71005D9330(mActor);
    const sead::Vector3f second = sub_71005D960C(mActor);
    const f32 offset_y = *mOffsetY_s;
    if (auto* controller = mActor->sub_71011D8A10()) {
        controller->_8 = (first + second) * 0.5f;
        controller->_8.y += offset_y;
    }
}

void ShortRangeBattleAlignment::m8() {
    if (auto* controller = mActor->sub_71011D8A10()) {
        controller->_d4 |= 2;
        controller->_8c |= 0x10;
        switch (*mMode_s) {
        case 1:
            controller->_d4 |= 0x80;
            break;
        case 2:
            controller->_d4 = (controller->_d4 & ~0xc40u) | 0x40;
            break;
        }
    }
}

void ShortRangeBattleAlignment::m9() {
    if (auto* controller = mActor->sub_71011D8A10()) {
        controller->_8c &= ~0x10;
        controller->_d4 &= ~0xc0u;
    }
}

void ShortRangeBattleAlignment::loadParams() {
    getStaticParam(&mMode_s, "Mode");
    getStaticParam(&mOffsetY_s, "OffsetY");
}

}  // namespace uking::behavior
