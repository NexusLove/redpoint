# RedPoint [![Cyber - Stuff](https://img.shields.io/badge/Cyber-Stuff-indianred)](https://13-05.github.io)
Have you ever wanted a tool to exploit multiple services? A single program to perform all the cool programming stuff you need? Well, that's what RedPoint aims to be.

## About
RedPoint rose from my need of a better, more stable, and more powerful version of [dsc.red](https://github.com/13-05/discord.RED). So, I archived *dsc.red*, and started from scratch. One command at a time.

## What's With the Name, Anyway?
- `redpoint`: a cooler name alternative for `dsc.red` I had lying around.
- `.m`: mobile; it works on multiple platforms, and is optimized for mobile!
- `.tool`: it's a multitool!

## Current Commands
1) Discord Webhook Spammer
2) Discord Webhook Deleter
3) Discord UserID Lookup Tool
4) Discord Account Disabler
5) Discord Token Checker
6) Discord Nitro Bruteforcer
7) Paste.io generator
8) Website source code generator
9) 2fa account recovery (requires authentication ticket, see [Special Notes](https://github.com/13-05/redpoint/tree/redpoint-js#special-notes))

## TODOs
1) Discord Token Logger Generator
2) Discord Commandline Client Mode
3) Discord Token Lookup (gathers info on someone by their token)
4) Discord Server Cloner

## Community
Join us on the matrix [here](https://matrix.to/#/!mgpMhaBWHrPHIuRdRC:matrix.org?via=matrix.org)!

Or, join our [Discord](https://dsc.gg/unwelcome)!

## Use
```sh
> git clone -b redpoint-js https://github.com/13-05/redpoint
> cd redpoint
> node index.js
```
If the `node index.js` fails, run `sudo apt install npm`.

## Special Notes
To get an authentication ticket, you need to go to the discord login page, then enter your password & email. When it shows the 2fa screen, open the network tab of the inspect element page (`Ctrl` + `Shift` + `I` or `Fn` + `Shift` + `I` on most browsers). Then enter anything into the text box and hit enter. As shown below, click on the payload for totp and copy the ticket. Then you can use that in redpoint! 
![image](https://user-images.githubusercontent.com/45636528/154579650-e7e27dbc-83d8-493c-bcc5-3dd1c7ecc33c.png)


## The Future
I'll add as many features as I can to this thing, so stay tuned!
