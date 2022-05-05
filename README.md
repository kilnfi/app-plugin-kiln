# app-plugin-kiln

![Kiln Logo](https://uploads-ssl.webflow.com/625db3caa8abd6c22d5f0ce3/6260572336892a801afd71e3_Kiln_Logo-Transparent-Dark.svg)

This plug-in is compatible with Nano S / X devices, it enables to interact in a
secure with the Kiln deposit smart contract to stake Ethereum. It is based on
the [boilerplate example](https://github.com/LedgerHQ/app-plugin-boilerplate)
from Ledger.

Current implementation targets the Goërli network and is limited to the
`deposit` call.

## Unit Tests

The plug-in is currently unit tested using
[Speculos](https://github.com/LedgerHQ/speculos), to run tests:

```
cd tests
./build_local_test_elfs.sh
yarn test
```

## Existing Flows

### Nano S Deposit

![step 0](./tests/snapshots/nanos_deposit/00000.png)
![step 1](./tests/snapshots/nanos_deposit/00001.png)
![step 2](./tests/snapshots/nanos_deposit/00002.png)
![step 3](./tests/snapshots/nanos_deposit/00003.png)
![step 4](./tests/snapshots/nanos_deposit/00004.png)
![step 5](./tests/snapshots/nanos_deposit/00005.png)
![step 6](./tests/snapshots/nanos_deposit/00006.png)
![step 7](./tests/snapshots/nanos_deposit/00007.png)
![step 8](./tests/snapshots/nanos_deposit/00008.png)

### Nano X Deposit

![step 0](./tests/snapshots/nanox_deposit/00000.png)
![step 1](./tests/snapshots/nanox_deposit/00001.png)
![step 2](./tests/snapshots/nanox_deposit/00002.png)
![step 3](./tests/snapshots/nanox_deposit/00003.png)
![step 4](./tests/snapshots/nanox_deposit/00004.png)
![step 5](./tests/snapshots/nanox_deposit/00005.png)
![step 6](./tests/snapshots/nanox_deposit/00006.png)
