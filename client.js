import fs from "fs";
import https from "https";
import { Webhook } from "discord-webhook-node";
import fetch from "node-fetch";
import readline from "readline";
import { stdin as input, stdout as output } from 'node:process';
import request from "request";
import { Client as Client, Intents as Intents } from 'discord.js';
const rl = readline.createInterface({ input, output });
console.clear();
let client;
let webhook;
let obj = `{
  "token": "your bot token here",
  "webhook": "your webhook URL here"
}`
async function newClient(){
console.log(`starting webhook client, use "$exit" to exit`)
if (!fs.existsSync(`config.json`)) {
fs.writeFile('config.json', obj, (err) => {
  if (err) throw err;
});
console.log(`no config.json file was found, so we created one.\nPlease fill it out for the code to work`)
process.exit()
} else {
let rawdata = fs.readFileSync('config.json');
let config = JSON.parse(rawdata);
let token = config.token
webhook = config.webhook
const response = await fetch(webhook)
const data = await response.json()
console.log(data)
console.log(`preparing your webhook, please wait for the ready message`)
client = new Client({ intents: [Intents.FLAGS.GUILDS, Intents.FLAGS.GUILD_MESSAGES, Intents.FLAGS.GUILD_BANS, Intents.FLAGS.GUILD_MEMBERS], });
client.on('messageCreate', async message => {
if (data.channel_id == message.channelId){
if (message.member) console.log(`${message.member.nickname}: \n${message.content}`);
}})
client.on("ready", async (client) => {
console.log(`ready`)
})
client.login(token);
} return client;}
export { newClient, rl, webhook };
