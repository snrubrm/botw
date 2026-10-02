#include "Game/AI/AI/aiAssassinMagicTgtSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

AssassinMagicTgtSelect::AssassinMagicTgtSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

AssassinMagicTgtSelect::~AssassinMagicTgtSelect() = default;

bool AssassinMagicTgtSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void AssassinMagicTgtSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void AssassinMagicTgtSelect::calc_() {
    TargetInAreaSelect::calc_();
}

void AssassinMagicTgtSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void AssassinMagicTgtSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mHeight_s, "Height");
}

// NON_MATCHING: block layout of the false paths (the original computes the result before the
// accessor destructor and branches on it afterwards, as if through an inline helper)
bool AssassinMagicTgtSelect::m34() {
    if (auto* link = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.isBgGroundHit())
            return true;

        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        if (accessor.getVelocity().y <= 0.0f) {
            const sead::Vector3f down = -sead::Vector3f::ey;
            if (somePositionCalc(&pos, pos, down, *mHeight_s))
                return true;
        }
    }
    return false;
}

}  // namespace uking::ai
