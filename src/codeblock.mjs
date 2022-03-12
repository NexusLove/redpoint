let BLACK = "\x1b[1;30m";
let RED = "\x1b[1;31m";
let GREEN = "\x1b[1;32m";
let YELLOW = "\x1b[1;33m";
let BLUE = "\x1b[1;34m";
let MAGENTA = "\x1b[1;35m";
let CYAN = "\x1b[1;36m";
let WHITE = "\x1b[1;37m";
let RESET = "\x1b[1;0m";
let content;
let args;
export async function codeBlock(text){
content = text;
if (content.includes(`{BLACK}`)){
args = content.split('{BLACK}');
content = `${args[0]}${BLACK}${args[1]}`
}
if (content.includes(`{RED}`)){
args = content.split('{RED}');
content = `${args[0]}${RED}${args[1]}`
}
if (content.includes(`{GREEN}`)){
args = content.split('{GREEN}');
content = `${args[0]}${GREEN}${args[1]}`
}
if (content.includes(`{YELLOW}`)){
args = content.split('{YELLOW}');
content = `${args[0]}${YELLOW}${args[1]}`
}
if (content.includes(`{BLUE}`)){
args = content.split('{BLUE}');
content = `${args[0]}${BLUE}${args[1]}`
}
if (content.includes(`{MAGENTA}`)){
args = content.split('{MAGENTA}');
content = `${args[0]}${MAGENTA}${args[1]}`
}
if (content.includes(`{CYAN}`)){
args = content.split('{CYAN}');
content = `${args[0]}${CYAN}${args[1]}`
}
if (content.includes(`{WHITE}`)){
args = content.split('{WHITE}');
content = `${args[0]}${WHITE}${args[1]}`
}
if (content.includes(`{RESET}`)){
args = content.split('{RESET}');
content = `${args[0]}${RESET}${args[1]}`
}
return content;
}
//codeBlock(`{RED}hello {CYAN}there {BLACK}I {BLUE}am {YELLOW}turtle{RESET}`).then(console.log)
