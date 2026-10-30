#include "Game/Actor/aiUnk_7100700620.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"

Unk_7100700620::Unk_7100700620() = default;

Unk_7100700620::~Unk_7100700620() = default;

void Unk_7100700620::sub_7100700634(ksys::act::Actor* actor) {
    _0 = actor->get6f4();
}

// NON_MATCHING: the threshold-crossing branches are combined and laid out differently.
bool Unk_7100700620::sub_7100700640(ksys::act::Actor* actor) {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD780(actor, 59, &query, 0, 0) && query.name == "WaterExit") {
        _0 = -1.0f;
        if (actor->get6e0() <= 0.0f) {
            ksys::act::Reaction::instance()->sub_7100EC27FC(actor);
            return true;
        }
        return false;
    }

    if (!(_0 > 0.0f && _0 < 1.0f))
        return false;

    const f32 current = actor->get6f4();
    if ((_0 < _4 && current >= _4) || (_0 >= _4 && current < _4)) {
        _0 = -1.0f;
        if (actor->get6e0() <= 0.0f) {
            ksys::act::Reaction::instance()->sub_7100EC27FC(actor);
            return true;
        }
        return false;
    }
    if (current <= 0.0f || current >= 1.0f)
        _0 = -1.0f;
    return false;
}
