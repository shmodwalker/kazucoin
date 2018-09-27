// Copyright (c) 2009-2012 The Bitcoin developers
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

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x758f3d45d6b5d2b08b3715c4fc1a75b6dc46ee5c08f059ccd2ea14e1c50f6349"))
        (  500, uint256("0x7876e7e613a19bb670f6703ee0e03cb2caaa04a21de3d508fd03839e1f3a82ec"))
        (  1000, uint256("0x9134c8f6b69fdfcb46ffab9d832afb23abc8781fec6b8244c62333cf06a58cbe"))
        (  1500, uint256("0x1e07669c6c0bd09f2256448cf8fd916dbc3807cd3ddd69041805bc9b5bac2e1d"))
        (  2000, uint256("0x95ea40ab2952c2e06bcd7e9c7fe05e7d70e7cd777af98a2a3613eb7d772ef743"))
        (  2500, uint256("0x12fc08b76fa4d57afc3154196c9236d1f47d4b23b321770c3043f7b9f1053528"))
        (  3000, uint256("0xf33fb205f78772d657e926a3c14f96144b9e14d80a486d12375e3216dc1d3be1"))
        (  3500, uint256("0x32bff3fa5efb48d31d44385e03690076c37acd20fd027be69191203178481a04"))
        (  4000, uint256("0xa5655eb531a0ace4fd5da522d85e690ce74940175ddfe837b62137f6fb056788"))
        (  4500, uint256("0xab28005bb361c8eb32eb477a09f35e638a41b8f0193ae6f034e979f52604d3e5"))
        (  5000, uint256("0x40b8e8f8b091e8ea3bbc401deb23f1bc41256eb285f021130a1725982bdb7098"))
        (  5500, uint256("0x1eac6ec14da8e179565a079265f706b2462f8ec5ab6c196a88248b60661579dd"))
        (  6000, uint256("0x70ed993df59f0288e6acbf0d93c2e06905e62066f0bb1c0e34f63028cbc86c6f"))
        (  6400, uint256("0xe4434ddc8aa47774863447b575aab6ebc2d7617ec26e0cb93f114e26351438d3"))
        (  7000, uint256("0x10384b6fd8ea6478e5e10752abc48469359a294e577b2566148acdae05f685ee"))
        (  8000, uint256("0x3609d76f672b8e200575d5372f7b0c0491104d1b4faa198956718b9e5f815888"))
        (  9000, uint256("0xe4b2ed06ab55688163daf4c8c9847ad7922655c3eefbc09133390cf1d777488b"))
        (  10000, uint256("0x0430181a50ecf8c3816bdec6af03c1e70846cd1d490eebac5b5904bf61a87bc9"))
        (  11000, uint256("0x46568f47a151fcdea3f367850d4ac72bb154d2d8b5e3936076d2398656c22cc8"))
        (  12000, uint256("0x52ac2a1a4bcefa8a2b18a368b477614f9878e3a75ce373043ce91806a13f61cc"))
        (  13000, uint256("0x55d4c7607eb4cb503a21db5a034ecfe6e49a6097e15d11c2784dc011c5cc609e"))
        (  14000, uint256("0x9d821de657cafc5bbaf982f0a229e6286264b657aefd5599cd2e38afe7245a1d"))
        (  15000, uint256("0x0fdd49fce80337b94d4480f7d536858049eb2402f624333ff949b39e30330abf"))
        (  16000, uint256("0x6f403e14636acce66aaf6ed767a13907b63402e30f67589fbc5231a9e6a1535c"))
        (  17000, uint256("0xb8e1d81d110e09755a12b3d2104788582e4bc74c59a72219cb27001c352560ae"))
        (  18000, uint256("0x186b13a33d945309f8bb5da2b223fa2e2ed00be4898742cedaafaed2e51e2880"))
        (  19000, uint256("0xcbc10d199d8b3f87af2d6895200cb64bfd927e05ac288eed5799bfd72a7b9dc9"))
        (  20000, uint256("0xe799b883a499690ab0db26e3f357e3b1f2a6a5669e4b561bf302a95e7d220dda"))
        (  21000, uint256("0xff9ab6ac6fcd15715e3a71a2753114c697193e4f599d9858a3d702aa5184010d"))
        (  22000, uint256("0xd7b25a89c72aff4b4d5980d30cd861ceefed36af46509e223376dd33be41a0b3"))
        (  23000, uint256("0xc7cf938ca8ac400cb09fb707d52557d166c94ddea6ea72e08b5360afd3bd8bec"))
        (  24000, uint256("0xbdd7eab619f85c573b264b6f800bda87b0887e47db987f451ed4424157ace687"))
        (  25000, uint256("0x293a663d100c76502b2787618d132ec9f1c516c6133b97047963c8f7e2b2879e"))
        (  26000, uint256("0x9dd6d19a6f127c9cb8657928754517e3b4c266f34bd558961bc8020125edbf0a"))
        (  27000, uint256("0x441046977d79b8d276b0dd9eea4e428e98236eac90dd3bc3f294f17906dab73d"))
        (  28000, uint256("0x7f2874cc04d9c9e2af9448e7879d13b70cf27e50714febe6c7597e3afaa1d5ef"))
        (  29000, uint256("0x17e86a115b59b9228c251c083e87bccc742f962e8b94537ff47e6ec8149e4cb5"))
        (  30000, uint256("0xea816ab2564f6211830f0156c057488e6bd0b29fe2301b64a7734faa41de705f"))
        (  31000, uint256("0x1159f498c06e7d95448a4b28ea5675c5ef9bff46c692602202a02e5dbd88ab62"))
        (  32000, uint256("0x24aba7f552b32f72b40a27ea95d5017d54ea3a7fe9a5a474bb6818d61dc60a94"))
        (  33000, uint256("0xdc5a3e1c894b95f1068b867f99ffa7387025dd1a134adf7699c2cbf4ef0e4d86"))
        (  34000, uint256("0xf056ba230e00f5dc01f2961e9db153715bbd04713ba3255fc86f7881cda8601c"))
        (  35000, uint256("0xcebcff3d89d2353caa2c214c995946591776b04a0799a77c4c0433f0bd520c01"))
        (  36000, uint256("0x4d477e533d669ce560e52e4333267904e20afeccadc1978ab4233e4cdc59705a"))
        (  37000, uint256("0x17c63e3b4f08d0fded5801c6842da542f1cacfcb00397b74934817a5fa1105bb"))
        (  38000, uint256("0x4c210dcb5c1b6fc7f75fa87aa43229d1512e223fbf969f96fbb4297db78ef277"))
        (  39000, uint256("0xdead65d5bf2665f2f706bd2f130977a330e4499b0ed29132cf1fd775003494f9"))
        (  40000, uint256("0xf37afccfd681a8f329bf3c6e87974bbfc1582a7e5ed7f4d4efda64943c9407c3"))
        (  41000, uint256("0x1c27fa4f8a8dde65ebbf6f4c99185b7d1a164aa65b6e4fd9fbc740af40700ba2"))
        (  42000, uint256("0xb11debd6e4ca7a4c3122d27a3ebe4ded8c9b3fa98523bf6cc176b4db31346730"))
        (  43000, uint256("0x8b63a4976e77462bd86a07eadb43261749d75d6cd564bc9cae82ce838df278fe"))
        (  44000, uint256("0x9ddcc78fa88356090fb8aef2173d2a26e6860df9bcf0588669879362a7480fee"))
        (  45000, uint256("0x096286ce5fa56c35ec6234fba0af2ef1af180510f3c86cc7bf2edabab29fc0b1"))
        (  46000, uint256("0x58d22204e8624670bd47154c3f6a47a591185061d000c4111ffb10904d7d6867"))
        (  47000, uint256("0xdda1eddf59350ecdd9be2ad50bfcb5ee1814a9074f1350890b573af53625e1f3"))
        (  48000, uint256("0xcec3a82a249e79ddf845cc94c0d8bc1f52a8fa040f38f8be42baff658dbed367"))
        (  49000, uint256("0x5f6becc46b5ad7446f805ac2e80e319d218878cfebc2ea4a0833def5fc52ab6c"))
        (  50000, uint256("0x0d59cd3994c4d4b164d7f6b36c3753490df86111f029ba83f7641d0101eb831c"))
        (  51000, uint256("0xb9f8c5bcea5f82281329941122e52f5039d7bf2790e31958a2c1b50611ecc550"))
        (  52000, uint256("0x109d41a7eef99a09311bf74e5059180691a6adb5e2ee069f33f239818610c63a"))
        (  53000, uint256("0x252ffbb011d17d328ba679a01ffac43ace3b2c8161c0ec88828e77074729f842"))
        (  54000, uint256("0xe937be2b7827fe7440a1d23ff36ff67b01ea85127b322a42c8217aef90c33c62"))






        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1526880792, // * UNIX timestamp of last checkpoint block
        0,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        1.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   0, uint256("0x002a7836ad62cfc71666fc678674e07af906d4dfce9679865ca7a29dd0a16ecc"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1526880772,
        0,
        1.0
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
