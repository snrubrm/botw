#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

// Placeholder for the 0x90-byte elements at CameraEventMultiTalk + 0xb0 (constructed by 0x71009241ac, three of them
// are cleared with one memset of 0x1b0 bytes); the destructor resets the link at +0x70.
struct Unk_CameraEventMultiTalkElem {
    u8 _0[0x70];
    ksys::act::BaseProcLink mLink;
    u8 _80[0x10];
};
static_assert(sizeof(Unk_CameraEventMultiTalkElem) == 0x90);

class CameraEventMultiTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventMultiTalk, CameraEvent)
public:
    explicit CameraEventMultiTalk(const InitArg& arg);
    ~CameraEventMultiTalk() override;

protected:
    void m45() override;

    // The members from 0x4c to 0x90 (Vector3f copies at 0x4c / 0x60 / 0x6c, zeroes at 0x58 / 0x78 / 0x80 / 0x88) and
    // from 0x260 to 0x328 (pointers and SafeStrings of the params) are not modelled yet (see the constructor
    // 0x7100765618).
    u8 _4c[0x90 - 0x4c];
    uking::act::Unk_7102459dd8 _90;
    Unk_CameraEventMultiTalkElem _b0[3];
    u8 _260[0x330 - 0x260];
};

}  // namespace uking::action
