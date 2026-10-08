#include "Game/UI/uiScreenControlCreators.h"

namespace uking::ui {
// The native tables all call these factories with (ControlSrc&, LayoutEx*).
ScreenChild* sub_71009D7198(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009D7294(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009DE3F4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009DE4F0(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E7F60(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E805C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8158(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8254(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E8350(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_71009E844C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17160(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A1725C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17358(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17454(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17550(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A1764C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17748(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A17844(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A233EC(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A2C3D8(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A2C4D4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A32F3C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A33038(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A33134(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A513A4(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A514A0(const nn::ui2d::ControlSrc&, eui::LayoutEx*);
ScreenChild* sub_7100A5159C(const nn::ui2d::ControlSrc&, eui::LayoutEx*);

static const ChildControlCreatorEntry sUnk_7102480388[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_SystemWindow_00", sub_71009D7294, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102480378(sUnk_7102480388);
// 0x71009d7168
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024803b8::getEntries() const {
    return &sUnk_7102480378;
}
// 0x71009d7174
Unk_71024803b8::~Unk_71024803b8() = default;

static const ChildControlCreatorEntry sUnk_7102480a98[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102480a88(sUnk_7102480a98);
// 0x71009dbe48
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102480ab0::getEntries() const {
    return &sUnk_7102480a88;
}
// 0x71009dbe54
Unk_7102480ab0::~Unk_7102480ab0() = default;

static const ChildControlCreatorEntry sUnk_7102481048[] = {
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481038(sUnk_7102481048);
// 0x71009de3c4
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481078::getEntries() const {
    return &sUnk_7102481038;
}
// 0x71009de3d0
Unk_7102481078::~Unk_7102481078() = default;

static const ChildControlCreatorEntry sUnk_7102481768[] = {
    {"Pa_Map_00", sub_71009E7F60, 0},
    {"Pa_MapIcon_00", sub_71009E805C, 0},
    {"Pa_PlayerNavi_00", sub_71009E8158, 0},
    {"Pa_StampBox_00", sub_71009E8254, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_Sensor_00", sub_71009E8350, 0},
    {"Pa_Comp_00", sub_71009E844C, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481758(sUnk_7102481768);
// 0x71009e7f30
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481828::getEntries() const {
    return &sUnk_7102481758;
}
// 0x71009e7f3c
Unk_7102481828::~Unk_7102481828() = default;

static const ChildControlCreatorEntry sUnk_710248d260[] = {
    {"Pa_NoticeZ_00", sub_71009D7198, 0},
    {"Pa_NoticeItem_00", sub_71009D7198, 0},
    {"Pa_NoticeItemShop_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_710248d250(sUnk_710248d260);
// 0x7100a10e9c
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248d2a8::getEntries() const {
    return &sUnk_710248d250;
}
// 0x7100a10ea8
Unk_710248d2a8::~Unk_710248d2a8() = default;

static const ChildControlCreatorEntry sUnk_710248e3c0[] = {
    {"Pa_ArrowPointer_00", sub_7100A17160, 0},
    {"Pa_CameraPointer_00", sub_7100A1725C, 0},
    {"Pa_Information_00", sub_7100A17358, 0},
    {"Pa_ThrowingPointer_00", sub_71009D7198, 0},
    {"Pa_PlayerStatusUp_00", sub_7100A17454, 0},
    {"Pa_ItemPointer_00", sub_7100A17550, 0},
    {"Pa_TempMeter_00", sub_7100A1764C, 0},
    {"Pa_Sensor_00", sub_71009E8350, 0},
    {"Pa_Weather_00", sub_7100A17748, 0},
    {"Pa_Time_00", sub_71009D7198, 0},
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_SinJu_", sub_7100A17844, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_710248e3b0(sUnk_710248e3c0);
// 0x7100a17130
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248e4e0::getEntries() const {
    return &sUnk_710248e3b0;
}
// 0x7100a1713c
Unk_710248e4e0::~Unk_710248e4e0() = default;

// 0x7100a1ec24
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248ea90::getEntries() const {
    return nullptr;
}
// 0x7100a1ec2c
Unk_710248ea90::~Unk_710248ea90() = default;

static const ChildControlCreatorEntry sUnk_710248f710[] = {
    {"Pa_Gear_00", sub_7100A233EC, 0},
    {"Pa_Gear_01", sub_7100A233EC, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_710248f700(sUnk_710248f710);
// 0x7100a233bc
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248f740::getEntries() const {
    return &sUnk_710248f700;
}
// 0x7100a233c8
Unk_710248f740::~Unk_710248f740() = default;

static const ChildControlCreatorEntry sUnk_7102492320[] = {
    {"Pa_Gear_00", sub_7100A233EC, 0},
    {"Pa_PlayerStatusUp_00", sub_7100A17454, 0},
    {"Pa_TempMeter_00", sub_7100A1764C, 0},
    {"Pa_HaveNum_00", sub_7100A2C3D8, 0},
    {"Pa_SetBonus_00", sub_71009D7198, 0},
    {"Pa_RotateGuide_00", sub_71009D7198, 0},
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_Sp_", sub_7100A2C4D4, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102492310(sUnk_7102492320);
// 0x7100a2c3a8
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024923e0::getEntries() const {
    return &sUnk_7102492310;
}
// 0x7100a2c3b4
Unk_71024923e0::~Unk_71024923e0() = default;

static const ChildControlCreatorEntry sUnk_71024934b0[] = {
    {"Pa_Save_00", sub_7100A32F3C, 0},
    {"Pa_Quest_00", sub_7100A33038, 0},
    {"Pa_PagePorch_", sub_7100A33134, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_71024934a0(sUnk_71024934b0);
// 0x7100a32f0c
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024934f8::getEntries() const {
    return &sUnk_71024934a0;
}
// 0x7100a32f18
Unk_71024934f8::~Unk_71024934f8() = default;

static const ChildControlCreatorEntry sUnk_7102496ed8[] = {
    {"Pa_GuideA_00", sub_71009D7198, 0},
    {"Pa_GuideB_00", sub_71009D7198, 0},
    {"Pa_GuideY_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102496ec8(sUnk_7102496ed8);
// 0x7100a4b67c
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102496f20::getEntries() const {
    return &sUnk_7102496ec8;
}
// 0x7100a4b688
Unk_7102496f20::~Unk_7102496f20() = default;

static const ChildControlCreatorEntry sUnk_71024981e8[] = {
    {"Pa_ItemName_00", sub_7100A513A4, 0},
    {"Pa_SubTextRupee_00", sub_7100A514A0, 0},
    {"Pa_SubTextMamo_00", sub_7100A514A0, 0},
    {"Pa_Material_", sub_7100A5159C, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_71024981d8(sUnk_71024981e8);
// 0x7100a51374
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498248::getEntries() const {
    return &sUnk_71024981d8;
}
// 0x7100a51380
Unk_7102498248::~Unk_7102498248() = default;

static const ChildControlCreatorEntry sUnk_7102498840[] = {
    {"Pa_Skip_00", sub_71009D7198, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102498830(sUnk_7102498840);
// 0x7100a53578
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498858::getEntries() const {
    return &sUnk_7102498830;
}
// 0x7100a53584
Unk_7102498858::~Unk_7102498858() = default;

static const ChildControlCreatorEntry sUnk_7102498e00[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102498df0(sUnk_7102498e00);
// 0x7100a53970
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102498e18::getEntries() const {
    return &sUnk_7102498df0;
}
// 0x7100a5397c
Unk_7102498e18::~Unk_7102498e18() = default;

}  // namespace uking::ui
