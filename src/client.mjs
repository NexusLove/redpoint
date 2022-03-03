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
async function newClient(){
console.log(`\nstarting webhook client, use "$exit" to exit`)
let rawdata = fs.readFileSync('config.json');
let config = JSON.parse(rawdata);
if (config.token == "your bot token here" || config.webhook == "your webhook URL here") {
console.log(`Please fill "config.json" out for the code to work`)
process.exit()
} else {
let token = config.token
webhook = config.webhook
const response = await fetch(webhook)
const data = await response.json()
console.log(data)
console.log(`preparing your webhook, please wait for the ready message. \nAfter the ready message appears, you can type and send messages to your webhook.`)
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
