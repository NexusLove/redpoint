import fs from "fs"
import chalk from "chalk"
import request from "request"
import EventEmitter from "events"
var invalid = [];
var verified = [];
var unverified = [];
const handler = new EventEmitter();
class Checker {
    constructor(token) {
        this.token = token;
    }
    check() {
      handler.once('invalid', async (token) => {
        invalid.push(this.token);
        fs.appendFile('invalid.txt', this.token + "\n", (err) => {
            if (err) throw err;
        });
      });
      handler.on('unverified', async (token) => {
        unverified.push(this.token);
        fs.appendFile('unverified.txt', this.token + "\n", (err) => {
          if (err) throw err;
        });
      });
      handler.on('verified', async (token) => {
        verified.push(this.token);
        fs.appendFile('verified.txt', this.token + "\n", (err) => {
            if (err) throw err;
        });
      });
      let token = this.token;
        request({
            method: "GET",
            url: "https://discordapp.com/api/v9/users/@me",
            headers: {
                authorization: this.token
            }
        }, (error, response, body) => {
            if (!body) return;
            var json = JSON.parse(body);
            if (!json.id) {
                handler.emit(`invalid`, token)
            } else if (!json.verified) {
                handler.emit(`unverified`, token)
            } else {
                handler.emit(`valid`, token)
            }
            console.clear();
            var text = "";
            text += chalk.green(`Verified: ${verified.length}`);
            text += chalk.blue(" | ");
            text += chalk.yellow(`Unverified: ${unverified.length}`);
            text += chalk.blue(" | ");
            text += chalk.red(`Invalid: ${invalid.length}`);
            var title = `Verified: ${verified.length} | Unverified: ${unverified.length} | Invalid: ${invalid.length}`;
            log(text, title);
        });
    }
}

function log(text, title) {
    if (process.platform == 'win32') {
        process.title = title;
    } else {
        process.stdout.write('\x1b]2;' + title + '\x1b\x5c');
    }
    console.log(text);
}

export const Bot = {
    check: function(token) {
        new Checker(token).check();
    }
};
