#include "Game/AI/aiUnk_7100704914.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

Unk_7100704914::Unk_7100704914(ksys::act::Actor* actor) : _30(actor) {}

Unk_7100704914::~Unk_7100704914() = default;

void Unk_7100704914::sub_7100704944() {
    _38 = false;
}

// NON_MATCHING: the original loads *cNullChar before the first name byte (isEmpty() loads them the other way round)
void Unk_7100704914::sub_710070507C() {
    if (!_0.isEmpty())
        sub_71007A2D7C(_30, _0);
    if (!_10.isEmpty())
        sub_71007A2D7C(_30, _10);
}
