Beyondcoin Core integration/staging tree [BYND, Ƀ]
==================================================

![bynd_banner](https://beyondcoin.io/assets/images/banners/bynd_banner.png)

[![Build Status](https://travis-ci.org/beyondcoin-project/beyondcoin.svg?branch=master)](https://travis-ci.org/beyondcoin-project/beyondcoin)
[![Build status](https://ci.appveyor.com/api/projects/status/qxam58ebbuw42my0?svg=true)](https://ci.appveyor.com/project/beyondcoin-project/beyondcoin-i7gkc)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Genesis](https://img.shields.io/badge/Genesis%20Block-September%2015'th%2C%202019-lightgrey)

What is Beyondcoin?
----------------

Beyondcoin is an open source peer-to-peer network-based digital currency. Employing the fundamentals of Bitcoin, although it does not use SHA256 as its proof of work algorithm. Instead, Beyondcoin currently employs a simplified variant of Scrypt as its proof of work (POW). Taking development cues from Tenebrix, Litecoin, and Dogecoin. Peer-to-peer (P2P) means that there is no central authority to issue new money or keep track of transactions. Instead, these tasks are managed collectively by the nodes of the network.

[https://beyondcoin.io](https://beyondcoin.io)

Table of Contents
-----------------

<!--ts--->
- [Beyondcoin Core integration/staging tree [BYND, Ƀ]](#beyondcoin-core-integrationstaging-tree-bynd-%c9%83)
  - [What is Beyondcoin?](#what-is-beyondcoin)
  - [Table of Contents](#table-of-contents)
  - [Specifications](#specifications)
  - [Block Rewards](#block-rewards)
  - [License](#license)
  - [Development Process](#development-process)
  - [Testing](#testing)
    - [Automated Testing](#automated-testing)
    - [Manual Quality Assurance (QA) Testing](#manual-quality-assurance-qa-testing)
  - [Translations](#translations)
<!--te-->

Specifications
--------------
Specification | Descriptor
------------- | ----------
Ticker Symbol                  | BYND
Algorithm                      | SCRYPT
Maxiumum Supply                | 84000000
SegWit                         | Activated
Mainnet RPC Port               | 10332
Mainnet P2P Port               | 10333
Testnet RPC Port               | 14332
Testnet P2P Port               | 14333
Block Time                     | 150 Seconds
Coinbase Transaction Maturity  | 100 Blocks
Confirmation                   | 6 Blocks
Difficulty Adjustment Interval | 2016 Blocks
Protocol Support               | IPV4, IPV6, TOR, I2P

Block Rewards
-------------
Year | Block | Reward
---- | ----- | ------
2019-2023 | 1-840000        | 50 BYND
2023-2027 | 840001-1680000  | 25 BYND
2027-2031 | 1680001-2520000 | 12.5 BYND
2031-2035 | 2520001-3360000 | 6.25 BYND
2035-2039 | 3360001-4200000 | 3.125 BYND
...       | ...             | ...

License
-------

Beyondcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/beyondcoin-project/beyondcoin/tags) are created
regularly to indicate new official, stable release versions of Beyondcoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://groups.google.com/forum/#!forum/beyondcoin-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #beyondcoin-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Beyondcoin periodically.

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.
