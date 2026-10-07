#include "Game/AI/aiUnk_710070F974.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

Unk_710070f974::Unk_710070f974() = default;

Unk_710070f974::~Unk_710070f974() = default;

void Unk_710070f974::sub_710070F984(ksys::act::ai::ActionBase* action) {
    action->getAITreeVariable(&_10, "LynelMoveParam");
}

void Unk_710070f974::sub_710070F9CC(ksys::act::Actor* actor) {
    _0 = 0;
    if (auto* as_list = actor->getASList())
        as_list->x_6(9, 0, 0.0f);
    if (_10)
        _8 = sead::DynamicCast<Unk_71025c89e8>(*static_cast<Unk_71025afb58**>(_10));
    else
        _8 = nullptr;
}

void Unk_71025c89e8::sub_710070F83C(ksys::act::ai::ActionBase* action) {
    action->getStaticParam(&mStartRotBoostAngle_s, "StartRotBoostAngle");
    action->getStaticParam(&mMaxRotBoostAngle_s, "MaxRotBoostAngle");
    action->getStaticParam(&mRotBoostScale_s, "RotBoostScale");
    action->getStaticParam(&mRotBoostScaleGearTop_s, "RotBoostScaleGearTop");
    action->getStaticParam(&mMoveStraightAngle_s, "MoveStraightAngle");
    action->getStaticParam(&mFrontCheckStartOffset_s, "FrontCheckStartOffset");
    action->getStaticParam(&mSideCheckAngle_s, "SideCheckAngle");
    action->getStaticParam(&mFrontCheckNavRadius_s, "FrontCheckNavRadius");
    action->getStaticParam(&mFrontCheckDist_s, "FrontCheckDist");
}
