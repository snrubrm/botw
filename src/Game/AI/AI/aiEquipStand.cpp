#include "Game/AI/AI/aiEquipStand.h"
#include <cstdarg>
#include <gfx/seadColor.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005E0420.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/Thread/Message.h"

// The original helper's source namespace is unknown.
bool sub_7100700A78(s32 slot);

namespace uking::ai {

EquipStand::EquipStand(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipStand::~EquipStand() {
    if (_b0.mLink.hasProc()) {
        ksys::act::ActorConstDataAccess acc;
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
void sub_71003C7AD8(const char* name, const sead::Vector3f* pos, const sead::Color4f* color, s32 a4,
                    const char* format, f32 scale, ...) {
    std::va_list args;
    va_start(args, scale);
    va_end(args);
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
