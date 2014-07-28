// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 84 Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

	// Cinnamon has released another updated client with checkpoints JUST FOR YOU 
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (  0,    uint256("0x4eca3cfb295cb8f84c6dfb52de099c508f18ac5233a95cc10324999fa1898843"))			
                        ( 1400, uint256("0x94e143c76ec283b39b080645dbe7b48b1895b5864c64073f2044189e83794f78"))
                        ( 2000, uint256("0xe96e34b5f100389944f8bdad1c6acd8f5756babd2ea97a57bf743b6a1308b3ff"))
						( 8200, uint256("0x916141e77e69798ba3fe40c3958cba7726d89840daa7526c97d7791499a74e1c"))
						( 31550, uint256("0x113a3aa864c82450d18c21946b9f02bf1b2e8495857b47e7af6261c30eefcc45"))
						( 47118, uint256("0x3ad0a0434e3e4d6326bc74f357c4a248384c7f5dda72b16891c7515e12069719"))
						( 56229, uint256("0x0055a40785f3c1e72282fec3ee20ad3562738219781a930cf4a6935d24e2f7cc"))
						( 71005, uint256("0x07c8f83ea8a2f452fd46241dd99986fc62b08a02994faa3b9c5921c76d5ef586"))
						( 99022, uint256("0x0b70ed3423484eafcb7b0c06056ef87a53b1b6969c6e09d29c03ad6918d42fdf"))
						( 115142, uint256("0x0682d1c451a7411730df7a8849b07b4c04128e28fab528abb1968247747ea52b"))
						
						;		

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
