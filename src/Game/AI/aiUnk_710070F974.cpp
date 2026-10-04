#include "Game/AI/aiUnk_710070F974.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

Unk_710070f974::Unk_710070f974() = default;

Unk_710070f974::~Unk_710070f974() = default;

void Unk_710070f974::sub_710070F9CC(ksys::act::Actor* actor) {
    _0 = 0;
    if (auto* as_list = actor->getASList())
        as_list->x_6(9, 0, 0.0f);
    if (_10)
        _8 = sead::DynamicCast<Unk_71025c89e8>(*static_cast<Unk_71025afb58**>(_10));
    else
        _8 = nullptr;
}
