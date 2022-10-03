import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models,SPECULOS_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits} from "ethers/lib/utils";
import { ledgerService } from '@ledgerhq/hw-app-eth';

const contractAddr = "0x393216dfc16b9115936ffb78c87888817e63f291";

const pluginName = "kiln";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);
  
nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] Stake Eth', zemu(model, async (sim, eth) => {
        const contract = new ethers.Contract(contractAddr, abi);

        const {data} = await contract.populateTransaction.deposit();

        let unsignedTx = genericTx;

        unsignedTx.to = contractAddr;
        unsignedTx.data = '0xd0e30db0';
        unsignedTx.value = parseEther("32");

        const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
        const right_clicks = 4;

        await waitForAppScreen(sim);
        await sim.navigateAndCompareSnapshots('.', model.name + '_deposit', [right_clicks, 0]);
        await tx;
    }));
});
