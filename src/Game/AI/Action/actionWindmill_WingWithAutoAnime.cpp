#include "Game/AI/Action/actionWindmill_WingWithAutoAnime.h"
#include <gsys/gsysModel.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

Windmill_WingWithAutoAnime::Windmill_WingWithAutoAnime(const InitArg& arg) : Windmill_Wing(arg) {}

Windmill_WingWithAutoAnime::~Windmill_WingWithAutoAnime() = default;

bool Windmill_WingWithAutoAnime::init_(sead::Heap* heap) {
    return Windmill_Wing::init_(heap);
}

void Windmill_WingWithAutoAnime::enter_(ksys::act::ai::InlineParamPack* params) {
    Windmill_Wing::enter_(params);
}

void Windmill_WingWithAutoAnime::leave_() {
    Windmill_Wing::leave_();
}

void Windmill_WingWithAutoAnime::loadParams_() {
    Windmill_Wing::loadParams_();
}

void Windmill_WingWithAutoAnime::calc_() {
    Windmill_Wing::calc_();
}

void Windmill_WingWithAutoAnime::m32(bool a1) {
    if (auto* model = mActor->getModel()) {
        if (auto* manager = ksys::world::Manager::instance()) {
            manager->getWindSpeed();  // discarded in the original
            const f32 rate = sub_71002BDA28();
            model->setAutoAnimationFrameRate(rate);
            sub_71012412E4(mActor, 3, rate, false);
        }
    }
}

void Windmill_WingWithAutoAnime::m33() {
    if (auto* model = mActor->getModel())
        model->forceAutoAnimationFrame(*mStartFrameRange_s * sead::GlobalRandom::instance()->getF32() *
                                       31.0f);
}

}  // namespace uking::action
