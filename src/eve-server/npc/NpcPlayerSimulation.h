/*
    EVEmu NPC Player Simulation System - Header
    This header file declares the NPCPlayerManager class and its methods.
*/

#ifndef NPC_PLAYER_SIMULATION_H
#define NPC_PLAYER_SIMULATION_H

#include "eve-server.h"
#include "npc/NPC.h"
#include "npc/NPCAI.h"
#include "market/MarketMgr.h"
#include "corporation/CorpMgr.h"
#include "sovereignty/SovereigntyMgr.h"
#include "industry/IndustryMgr.h"
#include "mining/MiningMgr.h"
#include "system/SystemManager.h"
#include "system/SpawnMgr.h"

class NPCPlayerManager {
public:
    void Process();

private:
    void ProcessSovereignty();
    void ProcessMining();
    void ProcessIndustry();
    void ProcessMarketOrders();
    void ProcessCorpApplications();
    void ProcessSkillTraining();
    void ProcessSpawning();
    void ProcessNPCGangs();
    void ProcessNPCCorporations();
    void ProcessNPCAlliances();

    bool ShouldApplyToCorp(Corporation& corp);
    void SubmitApplication(Corporation& corp);
    std::string GenerateUniqueCorpName();
    std::string GenerateUniqueAllianceName();
};

void StartNPCPlayerSimulation();

#endif // NPC_PLAYER_SIMULATION_H
