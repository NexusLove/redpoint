import fs from "fs"
const tokens = fs.readFileSync('./tokens.txt', 'utf-8').replace(/\r/gi, '').split("\n");
import { Bot as Bot } from "./tokenbot.mjs"
export async function tok(){
await fs.writeFileSync('invalid.txt', '');
await fs.writeFileSync('verified.txt', '');
await fs.writeFileSync('unverified.txt', '');

function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}

var i = 0;
return await new Promise(resolve => {
const tokenint = setInterval(() => {
    if (i >= tokens.length) {
      resolve(`Done checking tokens!`)
    }
    if (tokens[i]){
    Bot.check(tokens[i]);
  }
    i++;
}, 250);
})}
