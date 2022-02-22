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
let obj = `{
  "token": "your bot token here",
  "webhook": "your webhook URL here"
}`
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
let webhook = config.webhook
const response = await fetch(webhook)
const data = await response.json()
console.log(data)

const client = new Client({ intents: [Intents.FLAGS.GUILDS, Intents.FLAGS.GUILD_MESSAGES, Intents.FLAGS.GUILD_BANS, Intents.FLAGS.GUILD_MEMBERS], });
client.on('message', async message => {
if (data.channel_id == message.channelId) return;
console.log(message.channelId)
console.log(`${message.member.nickname}`)
})
client.login(token);
}
