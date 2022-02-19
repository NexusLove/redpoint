/* imports */
use std::io;
use std::io::Write;
use std::io::Read;
use std::process::Command;
use std::collections::HashMap; // hashmaps for json go brrrrr
use reqwest;
use std::error::Error; // oops an error!!
use std::fs::File;
use http::StatusCode;
use serde::{Serialize, Deserialize};
use std::io::{BufRead, BufReader};

/* globals */
static BLACK: &str = "\x1b[1;30m";
static RED: &str = "\x1b[1;31m";
static GREEN: &str = "\x1b[1;32m";
static YELLOW: &str = "\x1b[1;33m";
static BLUE: &str = "\x1b[1;34m";
static MAGENTA: &str = "\x1b[1;35m";
static CYAN: &str = "\x1b[1;36m";
static WHITE: &str = "\x1b[1;37m";
static RESET: &str = "\x1b[1;0m";


/* funcs */
fn clearscr() {
  if cfg!(windows) {
    Command::new("cmd")
    .args(&["/c", "cls"])
    .spawn()
    .expect("cls command failed to start")
    .wait()
    .expect("failed to wait");
  }
  else {
    Command::new("clear")
     .spawn()
     .expect("failed to clear the screen!")
     .wait()
     .expect("failed to wait");
  }
}

fn getline<S: AsRef<str>>(print: S) -> String {
    let reffed = print.as_ref();
    print!("{}", String::from(reffed));
    io::stdout().flush().unwrap();
    let mut val = String::new();
    io::stdin().read_line(&mut val).expect("error reading input!");

    return val.to_string();
}

fn colored(inp: &str) -> String {
  let mut to_pr: &str = inp; // `to_pr` meaning `to print`; i just didnt wanna make the compiler think it was a token

  // simple find & replace stuff
  let to_pr = to_pr.replace("{BLACK}", BLACK);
  let to_pr = to_pr.replace("{RED}", RED);
  let to_pr = to_pr.replace("{GREEN}", GREEN);
  let to_pr = to_pr.replace("{YELLOW}", YELLOW);
  let to_pr = to_pr.replace("{BLUE}", BLUE);
  let to_pr = to_pr.replace("{MAGENTA}", MAGENTA);
  let to_pr = to_pr.replace("{CYAN}", CYAN);
  let to_pr = to_pr.replace("{WHITE}", WHITE);
  let to_pr = to_pr.replace("{RESET}", RESET);

  return to_pr; // brrrrrr
}

fn setcolor(inp: &str) {
  let mut to_pr: &str = inp;

  // simple find & replace stuffs
  let to_pr = to_pr.replace("BLACK", BLACK);
  let to_pr = to_pr.replace("RED", RED);
  let to_pr = to_pr.replace("GREEN", GREEN);
  let to_pr = to_pr.replace("YELLOW", YELLOW);
  let to_pr = to_pr.replace("BLUE", BLUE);
  let to_pr = to_pr.replace("MAGENTA", MAGENTA);
  let to_pr = to_pr.replace("CYAN", CYAN);
  let to_pr = to_pr.replace("WHITE", WHITE);
  let to_pr = to_pr.replace("RESET", RESET);

  print!("{}", to_pr); // prints the color brrr
}

fn launch_initial_startup() -> String {
  clearscr();
  let mut usernameGLOB = String::new();
  let doesitexist = std::path::Path::new("config.redpoint").exists();
  if doesitexist == false {
    let mut f = File::create("config.redpoint").expect("couldn't configure startup file!");
    let mut usernameGLOB = getline(colored("{CYAN}what'd you like to be called?: "));
    let usernameGLOB = usernameGLOB.trim_end().replace(" ", "_");
    f.write_all(usernameGLOB.as_bytes()).expect("failed to write username to config.redpoint!");
  }
  else if doesitexist == true {
    let mut f = File::open("config.redpoint").expect("couldn't access the startup file. aborting!");
    f.read_to_string(& mut usernameGLOB).unwrap();
  }
  clearscr();
  if cfg!(windows) {
    Command::new("cmd")
    .args(&["/c", "title redpoint.m.tool"])
    .spawn()
    .expect("cls command failed to start")
    .wait()
    .expect("failed to wait");
  }
  let welcomestr: &str = "\n R   E   D   P   O   I   N   T\n\n";
  setcolor(RED);
  println!("{}", welcomestr);
  setcolor(MAGENTA);
  print!("[run \"help\" for a list of commands.]\n\n\n");

  if doesitexist == false {
    let mut f = File::open("config.redpoint").expect("couldn't access the startup file. aborting!");
    f.read_to_string(& mut usernameGLOB).unwrap();
  }
  return usernameGLOB;
}

fn help() {
  print!("\n\n");
  print!("{}", colored("{MAGENTA}USABLE COMMANDS: \n\n"));
  print!("{}", colored("{MAGENTA}1){WHITE} exit {BLUE} | {GREEN} exits the program\n"));
  print!("{}", colored("{MAGENTA}2){WHITE} clear {BLUE} | {GREEN} clears the screen\n"));

  print!("{}", colored("{MAGENTA}3){BLUE} spam webhook {BLUE} | {GREEN} spams a discord webhook\n"));
  print!("{}", colored("{MAGENTA}4){BLUE} delete webhook {BLUE} | {GREEN} deletes a discord webhook\n"));
  print!("{}", colored("{MAGENTA}5){BLUE} userid lookup {BLUE} | {GREEN} gets info on a discord userid\n"));
  print!("{}", colored("{YELLOW}6) token checker | looks for working tokens in a file{RED} CURRENTLY BROKEN\n"));
  print!("{}", colored("{YELLOW}7) colored codeblock | generates a colored codeblock{RED} CURRENTLY BROKEN{YELLOW}, CANT MAKE A PASTIE.IO PASTE, ON TODOS LIST TO FINISH!"));

  print!("\n\n");
}

fn exit() {
  println!("{}", colored("{WHITE}goodbye!{RESET}"));
  std::process::exit(0);
}

async fn hook_spammer(url: &str, times: i32, message: &str) {
  let mut i: i32 = 0;
  let mut hashm = HashMap::new();
  hashm.insert("content", message);
  let client = reqwest::Client::new();
  while i < times {
    let res = client.post(url).json(&hashm).send().await;
    i = i+1;
  }
}

async fn delete_hook(url: &str) {
  let client = reqwest::Client::new();
  let res = client.delete(url).send().await;
}


async fn userid_lookup(userid: &str) -> Result<(), Box<dyn Error>> { // TODO: MAKE THIS WORK
  let mut url: String = "https://discordid.13-05.repl.co/api/".to_owned();
  url.push_str(&userid);
  //let client = reqwest::Client::new();

  #[derive(Deserialize)]
  struct Info {
      user: UserInfo,
  }
  #[derive(Deserialize)]
  struct UserInfo {
      username: String,
      discriminator: String,
      bot: bool,
      createdTimestamp: i64,
  }

  let r = reqwest::get(url)
          .await?
          .json::<Info>()
          .await?;

  setcolor(BLUE); // pretty output color
  /* bot variable checking (annoying lmao) */
  let botval: i32 = r.user.bot.into();
  let mut botthing = String::new();
  if botval == 1 {
    botthing = "true".to_string();
  }
  else if botval == 0 {
    botthing = "false".to_string();
  }
  /* YAY END OF BOT VAR CHECKING IT WORKED EZZZZZ */
  /* timestamp var checking :rage: */
  let mut createddate = String::new();
  let createdval: i64 = r.user.createdTimestamp;
  let createddate = createdval.to_string();
  /* nevermind that was pretty easy lol */
  println!("username: {}\ndiscrim: {}\nbot?: {}\n(unix) creation date: {}", r.user.username, r.user.discriminator, botthing, createddate);
  Ok(())
}


async fn check_token_validity(token: &str) { // TODO: TOKEN CHECKER DOESNT WORK... OUTPUT: `ERR, unknown status code: 400 Bad Request!!` (added this to the help command as info)
  let url: String = String::from("https://discord.com/api/v9/users/@me");

  let client = reqwest::Client::new();
  let mut headers = HashMap::new();
  //headers.insert("Content-Type", "application/json");
  //headers.insert("User-Agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)");
  headers.insert("authorization", token);

  let resp = client.get(url).json(&headers).send().await;

  if resp.as_ref().unwrap().status() == StatusCode::OK {
    println!("{}{} VALID {}", token, GREEN, resp.unwrap().status());
  }
  else if resp.as_ref().unwrap().status() == StatusCode::UNAUTHORIZED {
    println!("{}{} INVALID {}", token, RED, resp.unwrap().status());
  }
  else if resp.as_ref().unwrap().status() == StatusCode::TOO_MANY_REQUESTS {
    println!("{}{:#?} RATELIMITED {}", token, CYAN, resp.unwrap().status());
  }
  else {
    print!("{}", colored("{YELLOW}ERR, unknown status code: "));
    print!("{}!!\n", resp.unwrap().status());
    //println!("{}", resp);
  }

  /*
  match resp {
    StatusCode::OK => println!("{}{} VALID {}", token, GREEN, resp),
    StatusCode::UNAUTHORIZED => println!("{}{} INVALID {}", token, RED, resp),
    StatusCode::TOO_MANY_REQUESTS => println!("{}{} RATELIMITED {}", token, CYAN, resp),
    //_ => unreachable!(),
  };
                                                                                         */
}

fn make_colored_codeblock(text: &str) -> String {
  let mut to_pr: &str = text; // `to_pr` meaning `to print`; i just didnt wanna make the compiler think it was a token

  // simple find & replace stuff
  let to_pr = to_pr.replace("{BLACK}", BLACK);
  let to_pr = to_pr.replace("{RED}", RED);
  let to_pr = to_pr.replace("{GREEN}", GREEN);
  let to_pr = to_pr.replace("{YELLOW}", YELLOW);
  let to_pr = to_pr.replace("{BLUE}", BLUE);
  let to_pr = to_pr.replace("{MAGENTA}", MAGENTA);
  let to_pr = to_pr.replace("{CYAN}", CYAN);
  let to_pr = to_pr.replace("{WHITE}", WHITE);
  let to_pr = to_pr.replace("{RESET}", RESET);
  let to_pr = "```ansi\n".to_owned() + &to_pr + "\n```";

  return to_pr; // ez
}

fn catch_invalid_command(inp: &str) {
  println!("{}command {}\"{}\"{} not found\n", YELLOW, CYAN, inp, YELLOW);
  let mut x = getline(colored("{YELLOW}would you like to run {BLUE}\"help\"{YELLOW} for a list of {GREEN}usable commands{YELLOW}? {CYAN}[y/n]{WHITE} "));
  let x = x.trim_end();
  if x == "y" {
    clearscr();
    launch_initial_startup();
    help();
  }
  else if x == "n" {
    // do_nothing(); // ez
  }
}


async fn process(inp: &str) {
  if inp == "exit" {
    exit();
  }
  else if inp == "clear" {
    clearscr();
    launch_initial_startup();
  }
  else if inp == "help" {
    help();
  }
  else if inp == "spam webhook" {
    let urll = getline(colored("{RED}hook url: "));
    let ttimes = getline(colored("{RED}times to spam: "));
    let msgg = getline(colored("{RED}message to spam: "));
    let url = urll.trim_end();
    let ttimes2: &str = ttimes.trim_end();
    let times: i32 = ttimes2.parse().unwrap();
    let message: &str = msgg.trim_end();
    println!("{}", colored("{RED}attempting to spam..."));
    hook_spammer(url, times, message).await;
    println!("{}", colored("{GREEN}done spamming."));
  }
  else if inp == "delete webhook" {
    let hhook = getline(colored("{RED}hook url: "));
    let hookurl = hhook.trim_end();
    delete_hook(hookurl).await;
    println!("{}", colored("{BLUE}attempted to delete the hook."));
  }
  else if inp == "userid lookup" {
    let userid = getline(colored("{RED}userid to lookup: "));
    let useridtrimmed = userid.trim_end();
    userid_lookup(useridtrimmed).await;
  }
  else if inp == "token checker" {
    check_token_validity("owo.token69.124-jkl124").await;
  }
  else if inp == "colored codeblock" { // TODO: make this paste on pastie.io plz
    println!("{}", colored("{YELLOW}CURRENTLY UNFUNCTIONAL AND{RED} BROKEN{YELLOW}, PASTIE.IO PASTER LINES ARE COMMENTED OUT BECAUSE THEY CRASH THE COMPILER"));
    println!("{}", colored("{RED}open https://github.com/13-05/redpoint/blob/main/etc/autoANSIinstructions.md in a browser for instructions on how to format your input correctly!"));
    let mut textt: String = getline(colored("{RED}input text: {RESET}"));
    let txt: &str = textt.trim_end();
    println!("{}", make_colored_codeblock(txt));

   /* commented out so you cant run it; it's broken anyway, just fix!

    let client = reqwest::Client::new();
    let mut headers = HashMap::new();
    headers.insert("content-type", "text/plain");

    client.post("https://pastie.io/documents").header("content-type", "text/plain").body(txt).send().await;
                                                                                                             */
  }
  else {
    catch_invalid_command(inp);
  }
}


/* main process */
#[tokio::main]
async fn main() {
    // initial setup
    let mut usernameGLOB = launch_initial_startup();
    let usernameGLOB = usernameGLOB.trim_end();
    let mut testinp = String::new();
    let runtimevar: i32 = 0;


    // constant input grabber and processor func
    while runtimevar == 0 {
      let mut inp: String = getline(format!("{RED}{usernameGLOB}@redpoint:{BLUE}~{WHITE}$ "));
      let inp = inp.trim_end(); // returns &str type

      process(inp).await;
   }
}
