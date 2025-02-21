
/**
  * @name SovereigntyDataMgr.h
  *   memory object caching system for managing and saving ingame static and dynamic sovereignty data
  *
  * @Author:         James
  * @date:           21Apr13
  *
  */

#ifndef _EVE_SERVER_SOVEREIGNTY_DATAMANAGER_H__
#define _EVE_SERVER_SOVEREIGNTY_DATAMANAGER_H__

#include "../../eve-server.h"

#include "system/sov/SovereigntyDB.h"

//Shiny multi-index containers
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

class SovereigntyDataMgr
    : public Singleton<SovereigntyDataMgr>
{
public:
    SovereigntyDataMgr();
    ~SovereigntyDataMgr();

    int Initialize();

    void Clear();
    void Close();
    void GetInfo();

    PyRep *GetSystemSovereignty(uint32 systemID);
    PyRep *GetAllianceSystems();
    PyRep *GetCurrentSovData(uint32 locationID);
    PyRep *GetAllianceBeacons(uint32 allianceID);
    uint32 GetSystemAllianceID(uint32 systemID);
    void AddSovClaim(SovereigntyData data);
    void RemoveSovClaim(uint32 systemID);
    void MarkContested(uint32 systemID, bool contested);
    SovereigntyData GetSovereigntyData(uint32 systemID);
    void UpdateSystemHubID(uint32 systemID, uint32 hubID);
    void UpdateSystemJammerID(uint32 systemID, uint32 jammerID);
    void UpdateSystemBeaconID(uint32 systemID, uint32 beaconID);
    void UpdateClaim(uint32 systemID);

protected:
    void Populate();

private:
    //Multi-index container for sov data
    typedef boost::multi_index_container<
        SovereigntyData,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<SovDataBySolarSystem>,
                boost::multi_index::member<SovereigntyData, uint32, &SovereigntyData::solarSystemID>
                >,
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<SovDataByConstellation>,
                boost::multi_index::member<SovereigntyData, uint32, &SovereigntyData::constellationID>
                >,
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<SovDataByRegion>,
                boost::multi_index::member<SovereigntyData, uint32, &SovereigntyData::regionID>
                >,
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<SovDataByClaim>,
                boost::multi_index::member<SovereigntyData, uint32, &SovereigntyData::claimID>
                >,
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<SovDataByAlliance>,
                boost::multi_index::member<SovereigntyData, uint32, &SovereigntyData::allianceID>
                >>> SovDataContainer;

    SovDataContainer m_sovData;
};

//Singleton
#define svDataMgr \
    (SovereigntyDataMgr::get())

#endif // _EVE_SERVER_SOVEREIGNTY_DATAMANAGER_H__
