import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, nano_models,SPECULOS_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits} from "ethers/lib/utils";

const contractAddr = "0x1c27e1917dd883ef645f3bf563d1aadcd99d36b7";

const pluginName = "Kiln";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);

nano_models.forEach(function(model) {
    test('[Nano ' + model.letter + '] Stake Eth', zemu(model, async (sim, eth) => {
        const contract = new ethers.Contract(contractAddr, abi);

        const withdrawalAddress = "0x08DaD7a266694014815B619170E7548E0A138533"; parseUnits("28471151959593036279", 'wei');
        const deadline = Number(1632843280);

        const {data} = await contract.populateTransaction.deposit(withdrawalAddress);

        let unsignedTx = genericTx;

        unsignedTx.to = contractAddr;
        unsignedTx.data = data;
        unsignedTx.value = parseEther("32");

        const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);
        const right_clicks = model.letter === 'S' ? 7 : 5;

        await waitForAppScreen(sim);

        await sim.navigateAndCompareSnapshots('.', model.name + '_deposit', [right_clicks, 3]);
        
        await tx;
    }));
});

