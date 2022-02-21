# RedPoint-JS [![Cyber - Stuff](https://img.shields.io/badge/Cyber-Stuff-indianred)](https://13-05.github.io)
## Current Commands
1) Discord Webhook Spammer
2) Discord Webhook Deleter
3) Discord UserID Lookup Tool
4) Discord Token Checker
5) Paste.io generator
6) Generic Webpage Cloner
7) 2FA Account Recoverer (requires authentication ticket, see [Special Notes](https://github.com/13-05/redpoint/tree/redpoint-js#special-notes))

## TODOs
- [ ] Discord ANSI Codeblock Gen
- [ ] Reverse IPV4 Lookup tool (relies on [ip-api.com](https://ip-api.com))
- [ ] Image Search Tool
- [ ] Current Crypto Prices
- [ ] Discord Token Logger Generator
- [ ] Discord Commandline Client Mode
- [ ] Discord Token Lookup (gathers info on someone by their token)
- [ ] Discord Server Cloner

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
