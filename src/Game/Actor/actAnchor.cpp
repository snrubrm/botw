#include "Game/Actor/actAnchor.h"
#include <basis/seadNew.h>
#include <gfx/seadCamera.h>
#include <gfx/seadTextWriter.h>
#include "KingSystem/ActorSystem/actDebug.h"

namespace uking::act {

Anchor::Anchor(const CreateArg& arg) : Actor(arg) {
    bindCalc1ToJob1_2();
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
    _1c0 = 2;
}

ksys::act::BaseProc* Anchor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Anchor(arg);
}

bool Anchor::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void Anchor::calcMaybe() {
    auto* debug = ksys::act::ActorDebug::instance();
    if (debug && debug->hasFlag(ksys::act::ActorDebug::Flag::_100))
        mActorFlags2.reset(ActorFlag2::_1);
    else
        mActorFlags2.set(ActorFlag2::_1);
}

void Anchor::m148(DebugDrawArg* arg) {
    if (mActorFlags2.isOn(ActorFlag2::_1))
        return;
    sead::TextWriter::setupGraphics(arg->draw_context);
    sead::FixedSafeString<64> text;
    text.format("%s \n", mName.cstr());
    sead::Vector3f pos;
    mMtx.getTranslation(pos);
    sead::Vector2f screen_pos;
    arg->camera->projectByMatrix(&screen_pos, pos, *arg->projection, *arg->viewport);
}

}  // namespace uking::act
