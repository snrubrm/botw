#include "Game/Actor/AI/aiEquipStand.h"
#include <cstdarg>
#include <gfx/seadColor.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_71005E0420.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/Utils/Thread/Message.h"

// The original helper's source namespace is unknown.
bool sub_7100700A78(s32 slot);
// 0x7100701774 (placeholder name; declared only): whether `weapon` can be put on the stand slot `slot`.
bool sub_7100701774(ksys::act::Actor* weapon, s32 slot);

namespace uking::ai {

EquipStand::EquipStand(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipStand::~EquipStand() {
    if (_b0.mLink.hasProc()) {
        ksys::act::ActorLinkConstDataAccess acc;
        if (ksys::act::acquireActor(&_b0.mLink, &acc))
            acc.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool EquipStand::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: display attention-key address lifetime and register allocation differ.
void EquipStand::enter_(ksys::act::ai::InlineParamPack* params) {
    *static_cast<Unk_71025afb58**>(mEquipDisplayChild_a) = &_b0;
    ksys::act::disableAllAttClients(mActor);
    _a8 = false;
    const bool occupied = sub_7100700A78(*mEquipStandSlot_m);
    _a8 = false;
    _38.x();
    auto* actor = mActor;
    ksys::act::disableAttClient(actor, mTakeOutAttKey_s);
    if (occupied) {
        ksys::act::disableAttClient(actor, mDisplayAttKey_s);
        changeChild("飾り生成");
    } else {
        ksys::act::enableAttClient(actor, mDisplayAttKey_s);
        changeChild("待機");
    }
    _38._34 = 0x1800020;
}

// 0x71003c7ad8 (placeholder name): a debug text function whose body is compiled out (only the
// variadic register save remains). EquipStand::calc_ calls it with "なにを飾ろうとしているのだ".
// inline: the original keeps the calls to this empty function, which happens only for an inline (weak) definition;
// a strong definition in this file lets the compiler drop the calls.
inline void sub_71003C7AD8(const char* name, const sead::Vector3f* pos, const sead::Color4f* color, s32 a4,
                    const char* format, f32 scale, ...) {
    std::va_list args;
    va_start(args, scale);
    va_end(args);
}

// NON_MATCHING: the attention key addresses and the _38 address are kept in different registers, and the debug text
// position copy is scheduled differently.
void EquipStand::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();

    if (isCurrentChild("待機")) {
        if (!_a8)
            return;

        ksys::act::Actor* weapon;
        {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            weapon = player.x_43();
        }

        if (!weapon) {
            const sead::Vector3f pos = actor->getMtx().getTranslation();
            const sead::Color4f color(1, 1, 1, 1);
            sub_71003C7AD8("", &pos, &color, 90, "かざる装備を持っていません", 2.0f);
        } else if (sub_7100701774(weapon, *mEquipStandSlot_m)) {
            _a8 = false;
            _38.x();
            auto* self = mActor;
            ksys::act::disableAttClient(self, mTakeOutAttKey_s);
            ksys::act::disableAttClient(self, mDisplayAttKey_s);
            changeChild("飾る");
            return;
        } else {
            const sead::Vector3f pos = actor->getMtx().getTranslation();
            const sead::Color4f color(1, 1, 1, 1);
            sub_71003C7AD8("", &pos, &color, 90, "なにを飾ろうとしているのだ", 2.0f);
        }
        _a8 = false;
        _38.x();
        return;
    }

    const char* next;
    if (isCurrentChild("飾る")) {
        if (child->isFinished()) {
            _a8 = false;
            _38.x();
            auto* self = mActor;
            ksys::act::enableAttClient(self, mTakeOutAttKey_s);
            ksys::act::disableAttClient(self, mDisplayAttKey_s);
            next = "飾り待機";
        } else if (child->isFailed()) {
            _a8 = false;
            _38.x();
            auto* self = mActor;
            ksys::act::disableAttClient(self, mTakeOutAttKey_s);
            ksys::act::enableAttClient(self, mDisplayAttKey_s);
            next = "待機";
        } else {
            return;
        }
    } else if (isCurrentChild("飾り待機")) {
        if (!_38._30 || _38._39 || _38._3a)
            return;
        _a8 = false;
        _38.x();
        auto* self = mActor;
        ksys::act::disableAttClient(self, mTakeOutAttKey_s);
        ksys::act::disableAttClient(self, mDisplayAttKey_s);
        next = "飾りゲット";
    } else if (isCurrentChild("飾り生成")) {
        if (!child->isFinished() && !child->isFailed())
            return;
        _a8 = false;
        _38.x();
        auto* self = mActor;
        ksys::act::enableAttClient(self, mTakeOutAttKey_s);
        ksys::act::disableAttClient(self, mDisplayAttKey_s);
        next = "飾り待機";
    } else if (isCurrentChild("飾りゲット")) {
        if (!child->isFinished() && !child->isFailed())
            return;
        _a8 = false;
        _38.x();
        auto* self = mActor;
        ksys::act::disableAttClient(self, mTakeOutAttKey_s);
        ksys::act::enableAttClient(self, mDisplayAttKey_s);
        next = "待機";
    } else {
        return;
    }
    changeChild(next);
}

void EquipStand::leave_() {
    *static_cast<void**>(mEquipDisplayChild_a) = nullptr;
}

void EquipStand::loadParams_() {
    getStaticParam(&mDisplayAttKey_s, "DisplayAttKey");
    getStaticParam(&mTakeOutAttKey_s, "TakeOutAttKey");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

// NON_MATCHING: only the address of mDisplayAttKey_s is computed one instruction earlier in the original.
bool EquipStand::handleMessage_(const ksys::Message* message) {
    auto* actor = mActor;
    if (!isCurrentChild("待機")) {
        if (isCurrentChild("飾り待機") && message->getType() == 0x1800020) {
            if (!sub_7100700A78(*mEquipStandSlot_m)) {
                _b0.mLink.reset();
                _a8 = false;
                _38.x();
                actor = mActor;
                ksys::act::disableAttClient(actor, mTakeOutAttKey_s);
                ksys::act::disableAttClient(actor, mDisplayAttKey_s);
                changeChild("飾りゲット");
                return true;
            }
            auto* other = sead::DynamicCast<ksys::act::Actor>(_b0.mLink.getProc(nullptr, nullptr));
            if (sead::IsDerivedFrom<ksys::act::Actor>(other))
                return handleItemPickedMessageMaybe(*message, &_38, actor, other);
        }
    } else if (message->getType() == 0x180001d || message->getType() == 0x180001e ||
               message->getType() == 0x180001f) {
        _a8 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
