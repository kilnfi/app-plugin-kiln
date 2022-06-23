import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models,SPECULOS_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits} from "ethers/lib/utils";

const contractAddr = "0x393216dfc16b9115936ffb78c87888817e63f291";

const pluginName = "kiln";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);

nano_models.forEach(function(model) {
    test('[Nano ' + model.letter + '] Withdraw', zemu(model, async (sim, eth) => {
        const contract = new ethers.Contract(contractAddr, abi);

        const validatorAddress = "0x8905410ae09a0b89d6af7296e2d0ae19adb672744f600d8da9b6293259641aa6e316bee60936cc1459b3f8697343d0f0";
        const deadline = Number(1632843280);

        const {data} = await contract.populateTransaction.withdraw(validatorAddress);

        let unsignedTx = genericTx;

        unsignedTx.value = 0;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

        const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
        const right_clicks = 5;

        await waitForAppScreen(sim);

        await sim.navigateAndCompareSnapshots('.', model.name + '_withdraw', [right_clicks, 0]);

        await tx;
    }));
});
