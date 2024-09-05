import process from 'process';
import { pathToFileURL } from 'url';
import { headerData } from "./inputdata.js";
import { generateBlob, generateCArray, generateDsHexLiteral } from "./main.js";

if (import.meta.url === pathToFileURL(process.argv[1]).href) {
    const headerBlob = generateBlob(headerData);
    console.log('Blob:', headerBlob);
    console.log(`\nC code:\n${generateCArray(headerBlob)}`);
    console.log(`DeviceScript:\n${generateDsHexLiteral(headerBlob)}`);
}
