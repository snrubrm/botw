#include "Game/AI/AI/aiNushiEscapeSelector.h"
#include "Game/Actor/actHorse.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

static const sead::SafeString sUnk_710240D298 = "AnimalMaster_Appearance";

NushiEscapeSelector::NushiEscapeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NushiEscapeSelector::~NushiEscapeSelector() = default;

bool NushiEscapeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NushiEscapeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* horse = sead::DynamicCast<act::Horse>(mActor);
    if (!horse) {
        setFailed();
        return;
    }

    if (!mActor->getMapObject()) {
        changeChild("消滅");
        return;
    }

    bool appeared = false;
    ksys::gdt::Manager::instance()->getParam().get().getBool(&appeared, sUnk_710240D298);
    ++horse->_11a9;
    if (appeared && horse->_11a9 < *mNumOfAllowedEscapes_s)
        changeChild("ワープ");
    else
        changeChild("消滅");
}

void NushiEscapeSelector::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void NushiEscapeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NushiEscapeSelector::loadParams_() {
    getStaticParam(&mNumOfAllowedEscapes_s, "NumOfAllowedEscapes");
}

}  // namespace uking::ai
