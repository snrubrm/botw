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

// NON_MATCHING: only the tail: the original keeps the call result as `and w19, w0, #1` and branches on w19 after
// the accessor destructor (returning true / false through two blocks); ours returns `and w0, w19, #1`
bool AssassinMagicTgtSelect::m34() {
    auto* link = sub_71005D9050(mActor);
    if (!link)
        return false;
    bool result = false;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.isBgGroundHit()) {
            result = true;
        } else {
            sead::Vector3f pos;
            accessor.getActorMtx().getTranslation(pos);
            if (accessor.getVelocity().y <= 0.0f) {
                const sead::Vector3f down = -sead::Vector3f::ey;
                result = somePositionCalc(&pos, pos, down, *mHeight_s);
            }
        }
    }
    return result;
}

}  // namespace uking::ai
