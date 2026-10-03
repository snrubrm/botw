#include "Game/AI/AI/aiAddBasicLinkOn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddBasicLinkOn::AddBasicLinkOn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddBasicLinkOn::~AddBasicLinkOn() = default;

bool AddBasicLinkOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddBasicLinkOn::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool only_one = *mOnlyOne_s;
    auto* actor = mActor;
    if (only_one) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
            if (!enemy->_e84.isOnBit(9)) {
                enemy->_e84.setBit(9);
                mActor->emitBasicSigOn();
                if (*mIsBroadCastOnlyOne_s) {
                    _48.x(mActor);
                    sub_71005E02E0(mActor, &_48, nullptr);
                }
            }
        }
    } else {
        actor->emitBasicSigOn();
    }
    changeChild("行動", params);
}

void AddBasicLinkOn::calc_() {}

bool AddBasicLinkOn::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddBasicLinkOn::isFinished() const {
    return getCurrentChild()->isFinished();
}

void AddBasicLinkOn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddBasicLinkOn::loadParams_() {
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
}

}  // namespace uking::ai
