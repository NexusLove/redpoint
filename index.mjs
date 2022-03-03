/* imports & stuff */
import fs from "fs";
import https from "https";
import { Webhook } from "discord-webhook-node";
import fetch from "node-fetch";
import { main1 , welcome, rl } from "./src/main.mjs";
import { newClient, webhook } from "./src/client.mjs";
import { rl as newrl } from "./src/client.mjs";
import request from "request";
let main = main1;
/* globals & funcs */
let BLACK = "\x1b[1;30m";
let RED = "\x1b[1;31m";
let GREEN = "\x1b[1;32m";
let YELLOW = "\x1b[1;33m";
let BLUE = "\x1b[1;34m";
let MAGENTA = "\x1b[1;35m";
let CYAN = "\x1b[1;36m";
let WHITE = "\x1b[1;37m";
let RESET = "\x1b[1;0m";
let client;
let $log;
console.oldLog = console.log;
console.log = async function(value){
    console.oldLog(value);
    $log = value;
};
function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}
async function message(){
rl.question('', async (answer) => {
if (answer == `$exit`){process.exit()}
else if (answer !== ``){
const hook = new Webhook(webhook);
hook.send(answer);}
rl.pause()
})
}
welcome()
console.log(`Please type the redpoint app you want to use.\nIf you do not type in a correct answer, it will default to main\nIf you choose main then run "help" for a list of commands`)
console.log(`${RED}MAIN \n${CYAN}WEBHOOK CLIENT${RESET}`)
rl.question('', async (answer) => {
if (answer == `webhook client`){
client = await newClient()
main = message;
}
rl.pause()
})
rl.on('pause', () => {
rl.resume()
main().then().catch(console.err)
});
