#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class ChemicalMgr : public Job {
public:
    ChemicalMgr();

    JobType getType() const override { return JobType::Chemical; }

    void initBeforeStageGen();
    void unload2();
    bool x_4() const;

    u8 _20[0xb10 - 0x20];
    u8 _b10;
    u8 _b11[0xdc0 - 0xb11];
};
KSYS_CHECK_SIZE_NX150(ChemicalMgr, 0xdc0);

}  // namespace ksys::world
