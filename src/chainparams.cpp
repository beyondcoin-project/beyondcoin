// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2019-2020 Beyondtoshi
// Copyright (C) 2019-2020 The Beyondcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01043d4265796f6e64636f696e2c206120636f696e206372656174656420746f20676f206265796f6e64207768617420736f63696574792062656c6965766573)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Beyondcoin, a coin created to go beyond what society believes";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 1; // 5e3277b2f6d988288e2acda68d4894d3b62391dfd7f475c553592954c743f7a5
        consensus.BIP34Height = 1; // 5e3277b2f6d988288e2acda68d4894d3b62391dfd7f475c553592954c743f7a5
        consensus.BIP34Hash = uint256S("0x5e3277b2f6d988288e2acda68d4894d3b62391dfd7f475c553592954c743f7a5");
        consensus.BIP65Height = 100; // e36273167b0b9711be2ecddd761091aa5e716a19352df2e1aa91bf5b4f7f6d00
        consensus.BIP66Height = 100; // e36273167b0b9711be2ecddd761091aa5e716a19352df2e1aa91bf5b4f7f6d00
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1546300800; // January 1, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1577836800; // January 1, 2020

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1546300800; // January 1, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1577836800; // January 1, 2020

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000c0445ae8dc953c");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x210119fcd307909da3c034012c83ff258a89db262d2fa9adca0e63c054990d49"); // 92736

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x9c;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xa7;
        nDefaultPort = 10333;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1568521797, 314206, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0a9e3b5fce3aee6e04f06dfd6ad380a6c0f9d8420f53a4ca97845756ee5d56e7"));
        assert(genesis.hashMerkleRoot == uint256S("0x7f4191b0b1f7438204e2642ca18d7a2799da9e39733667a75afbf89c3a3dddc2"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        vSeeds.emplace_back("dnsseed.beyondcoin.io");
        vSeeds.emplace_back("bynd-main-dns1.beyondcoin.io");
        vSeeds.emplace_back("bynd-main-dns2.beyondcoin.io");
        vSeeds.emplace_back("bynd-main-dns3.beyondcoin.io");
        vSeeds.emplace_back("52.0.220.131:10333");
        vSeeds.emplace_back("52.11.0.47:10333");
        vSeeds.emplace_back("18.190.88.101:10333");
        vSeeds.emplace_back("185.244.150.234:10333");
        vSeeds.emplace_back("3.132.131.183:10333");
        vSeeds.emplace_back("3.133.28.194:10333");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,26);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176);
        base58Prefixes[EXT_PUBLIC_KEY] = {0xff, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0xff, 0x88, 0xAD, 0xE4};

        bech32_hrp = "bynd";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {     0, uint256S("0a9e3b5fce3aee6e04f06dfd6ad380a6c0f9d8420f53a4ca97845756ee5d56e7")},
                {  2016, uint256S("4634e6d5576aaeac9962aa71d4a14cbea593cbe2ee8dec3b35013c433a90e2e1")},
                {  4032, uint256S("069e7c1ee71176920f1dcf03d8d6b0d39c811873d8e0a912ffbf96db235307a1")},
                {  6048, uint256S("6690d77629136b546eace011747986e3f8e5262ba0f880713b7a6f086e0b278b")},
                {  8064, uint256S("a74124dc8802f31a37d86777b6d972ab7b825d28f351ef3366d85aa48218b846")},
                { 10080, uint256S("8995e6b36b94eb3bcc6258d65fc13b95f03115fee10a3c0e1593e58130f38783")},
                { 12096, uint256S("161dd4ef5904c58c42b8ca1854bcc1ad7d26e346293b31d7f0bee706ee87394a")},
                { 14112, uint256S("0efac2da1f2aba9329dca6884898630c11a87010125b418983be7fef13601c58")},
                { 16128, uint256S("59d2bbf3ea2f0094dc1bd2924f82df18f4b04832c7b0c54182eb814ee0cae7c9")},
                { 18144, uint256S("97d3e636460acb36a5f65ef84c92b4fa1f0902026a98027253bfd9e80f06742c")},
                { 20160, uint256S("4ac036e3b7b06eb9c1598e95ca9894054c987d86635b0c00ea6386aebdbeff38")},
                { 28224, uint256S("f8a1baa91a81fbede774878982b540d56cee4bbbfa8e5d6ce7e03d030172dd09")},
                { 36288, uint256S("3c4891e8bda65bbd45e6f7ab63d257afaffd04fa341f7f6afd2d765b14486356")},
                { 44352, uint256S("a93d5e64828d81f398942528fa8117758586248d63c2601120373f3c60df4929")},
                { 52416, uint256S("48525f181fef67737ae4902b0602e412ff98c42521f9f2f0e96e2bc8d027abf2")},
                { 60480, uint256S("bd3e841ad2cbbd522e1e92d617dcae2e5c226457ef1330e82db1b06c04230e14")},
                { 68544, uint256S("9a68906949af97eceb4a2633f7699f3db6538a0d87c46bf1787297dacf723041")},
                { 76608, uint256S("912f4fcf66197b901a1b0b2e8b78f1de10087a1515e7e1403a77e1bf3094cfcd")},
                { 84672, uint256S("0811c06502983c62a0905b8a90f7524b5f2566951852df6f89dd928952a13e5d")},
                { 92736, uint256S("210119fcd307909da3c034012c83ff258a89db262d2fa9adca0e63c054990d49")},
                //{ 111864, uint256S("")},
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 92736 210119fcd307909da3c034012c83ff258a89db262d2fa9adca0e63c054990d49
            /* nTime    */ 1594933544,
            /* nTxCount */ 126371,
            /* dTxRate  */ 0.005
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 1;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 100;
        consensus.BIP66Height = 100;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1546300800; // January 1, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1577836800; // January 1, 2020

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1546300800; // January 1, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1577836800; // January 1, 2020

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // 0

        pchMessageStart[0] = 0xb7;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xd7;
        pchMessageStart[3] = 0x81;
        nDefaultPort = 14333;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1568522508, 1184622, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xe4c23a189582c0a7719569717bfeb59b478a20367c5b36dd6fb18b7df4ecab51"));
        assert(genesis.hashMerkleRoot == uint256S("0x7f4191b0b1f7438204e2642ca18d7a2799da9e39733667a75afbf89c3a3dddc2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-seed.beyondcoin.io", true);
        vSeeds.emplace_back("bynd-test-dns1.beyondcoin.io", true);
        vSeeds.emplace_back("bynd-test-dns2.beyondcoin.io", true);
        vSeeds.emplace_back("54.157.251.114:14333", true);
        vSeeds.emplace_back("52.13.212.231:14333", true);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,85);
        base58Prefixes[EXT_PUBLIC_KEY] = {0xff, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0xff, 0x35, 0x83, 0x94};

        bech32_hrp = "tbynd";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                { 0, uint256S("e4c23a189582c0a7719569717bfeb59b478a20367c5b36dd6fb18b7df4ecab51")},
                // { 2016, uint256S("")},
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 0 e4c23a189582c0a7719569717bfeb59b478a20367c5b36dd6fb18b7df4ecab51
            /* nTime    */ 0,
            /* nTxCount */ 0,
            /* dTxRate  */ 0
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // 0

        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0xb0;
        pchMessageStart[3] = 0xdb;
        nDefaultPort = 11333;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1568523445, 0, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xaf6448d165f850f94accc66e7d763a656da14413579f8cda8ee4176dddfd4bed"));
        assert(genesis.hashMerkleRoot == uint256S("0x7f4191b0b1f7438204e2642ca18d7a2799da9e39733667a75afbf89c3a3dddc2"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = {
            {
                { 0, uint256S("af6448d165f850f94accc66e7d763a656da14413579f8cda8ee4176dddfd4bed")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0xff, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0xff, 0x35, 0x83, 0x94};

        bech32_hrp = "rbynd";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
