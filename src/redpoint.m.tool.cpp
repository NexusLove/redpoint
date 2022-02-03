#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cpr/cpr.h>
#include <string>
#include <nlohmann/json.hpp> // it should always be json.hpp, NOT just json
#include <regex>
#include <ctime>
#include <iomanip>
#include <algorithm>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <random>
#include <ctime>
using namespace std;
using json = nlohmann::json;
using namespace cpr;

/* globals yea */
string BLACK = "\x1b[1;30m";
string RED = "\x1b[1;31m";
string GREEN = "\x1b[1;32m";
string YELLOW = "\x1b[1;33m";
string BLUE = "\x1b[1;34m";
string MAGENTA = "\x1b[1;35m";
string CYAN = "\x1b[1;36m";
string WHITE = "\x1b[1;37m";
string RESET = "\x1b[1;0m";
string REDPOINT_VERSION = "1.7";


void clearscr() {
#ifdef _WIN32 // Includes both 32 bit and 64 bit
    system("cls");
#else
    system("clear"); // os is probs a linux distro, so call "clear"
#endif
}

void enable_color_on_WIN(){
  #ifdef _WIN32 // includes all windows architectures
    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
    system("title redpoint") // sets the console window's title on windows ;)
  #else
    // do nothing lmao, we cant do and dont have to do anything similar on unix systems
  #endif
}

void help() {
    cout << "\n\n";
    cout << MAGENTA << "USABLE COMMANDS: \n\n";
    cout << MAGENTA << "1)" << WHITE << " exit " << BLUE << " | " << GREEN << " exits the program" << endl;
    cout << MAGENTA << "2)" << WHITE << " clear " << BLUE << " | " << GREEN << " clears the screen" << endl;


    cout << MAGENTA << "3)" << BLUE << " spam webhook " << BLUE << " | " << GREEN << " spams a discord webhook" << endl;
    cout << MAGENTA << "4)" << BLUE << " delete webhook " << BLUE << " | " << GREEN << " deletes a discord webhook" << endl;
    cout << MAGENTA << "5)" << BLUE << " userid lookup " << BLUE << " | " << GREEN << " gets info on a discord userid" << endl;
    cout << MAGENTA << "6)" << BLUE << " disable token " << BLUE << " | " << GREEN << " deletes a discord account by token" << endl;
    cout << MAGENTA << "7)" << BLUE << " token checker " << BLUE << " | " << GREEN << " looks for working tokens in a file" << endl;
    cout << MAGENTA << "8)" << BLUE << " nitro gen " << BLUE << " | " << GREEN << " generates random nitro codes and checks them" << endl;
    cout << MAGENTA << "9)" << BLUE << " colored codeblock " << BLUE << " | " << GREEN << " generates a discord codeblock; with color!" << endl;

    cout << MAGENTA << "10)" << RED << " clone webpage " << BLUE << " | " << GREEN << " command-line \"view source\"" << endl;
    cout << MAGENTA << "11)" << RED << " ip lookup " << BLUE << " | " << GREEN << " gets information for an Ipv4 address" << endl;
    cout << MAGENTA << "12)" << RED << " image search " << BLUE << " | " << GREEN << " finds similar images based on a url" << endl;
    cout << MAGENTA << "13)" << RED << " cryptos" << BLUE << " | " << GREEN << " fetches current XMR, BTC, & ETH prices" << endl;
    cout << MAGENTA << "14)" << RED << " make paste " << BLUE << " | " << GREEN << " makes a https://pastie.io/ paste";

    cout << "\n\n";
}

void welcome() {
    const char* welcomestr =
        " \n"
        " R   E   D   P   O   I   N   T\n"
        " ";
    clearscr();
    cout << RED << welcomestr << MAGENTA << "\n\n[run \"help\" for a list of commands.]" << RED;
    cout << "\n\n\n";
}

void spam_webhook(string URL, int times, string message) {
    cout << RED << "attempting to spam..." << RED << endl;
    for (int i = 0; i < times; i++) {
        cpr::Response spam = cpr::Post(cpr::Url{ URL },
            cpr::Payload{ {"content", message} });

    }
    cout << BLUE << "done spamming!" << RED << endl;
}

void userid_lookup(string USERID) {
    /* GETTING THE DATA FROM THE USERID AND API */
    cpr::Response r = cpr::Get(cpr::Url{ "https://discordid.13-05.repl.co/api/" + USERID });
    json id = json::parse(r.text);

    /* STORING THE DATA AS VARIABLES */
    string uname = to_string(id["user"]["username"]);
    string discrim = to_string(id["user"]["discriminator"]);
    string uname_and_discrim = to_string(id["user"]["tag"]);
    string av_url = to_string(id["user"]["avatarURL"]);
    string bot_bool = to_string(id["user"]["bot"]);

    string unixtimestr = to_string(id["user"]["createdTimestamp"]);


    cout << BLUE << "username: " << uname << endl << "discrim: " << discrim << endl << "bot?: " << bot_bool << endl << "(unix) creation date: " << unixtimestr << endl;
}

void disable_token(string token) {
    cout << BLUE << "attempting to disable token " << token << RESET << endl;
    cpr::Response r = cpr::Patch(cpr::Url{ "https://discord.com/api/v9/users/@me" },
        cpr::Header{ {"user-agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)"} },
        cpr::Payload{ {"date_of_birth", "2022-1-1"} });
}

void clone_page(string exac_page_url) {
    cpr::Response r = cpr::Get(cpr::Url{ exac_page_url },
        cpr::Header{ {"user-agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)"} });
    if (r.status_code != 200) {
        cout << YELLOW << "there was an error cloning the page." << endl;
    }
    else {
        cpr::Response paste = cpr::Post(cpr::Url{ "https://pastie.io/documents" },
            cpr::Header{ {"content-type", "text/plain"} },
            cpr::Body{ {r.text} });

        json pastie_response = json::parse(paste.text);
        string key = to_string(pastie_response["key"]);
        string key1 = key.erase(0, 1);
        string key2 = key1.erase(key1.size() - 1);
        cout << BLUE << "view the source code at https://pastie.io/" << key2 << RESET << endl;
    }
}

void lookup_ip(string ip) {
    cpr::Response r = cpr::Get(cpr::Url{ "http://ip-api.com/json/" + ip });

    json ip_response = json::parse(r.text);
    cout << BLUE << "country: " << ip_response["country"] << endl << "state/region: " << ip_response["regionName"] << endl << "city: " << ip_response["city"] << endl << "isp: " << ip_response["isp"] << endl << "zip code: " << ip_response["zip"] << endl << "timezone: " << ip_response["timezone"] << endl;
}

void delete_webhook(string HOOK) {
    cpr::Response r = cpr::Delete(cpr::Url{ HOOK });
    cout << BLUE << "attempted to delete the webhook." << RESET << endl;
}

void yand_image_search(string ImgURL) {
    cout << BLUE << "find similar images at https://yandex.com/images/search?source=collections&&url=" << ImgURL << "&rpt=imageview" << endl;
}

string check_token_validity(string token) {
    string url = "https://discord.com/api/v9/users/@me";
    Response r =
        Get(Url{ url },
            Header{ {"Content-Type", "application/json"} },
            Header{ {"User-Agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)','Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)"} },
            Header{ {"Authorization", token} });
    if (r.status_code == 200) {
        string returnval = GREEN + token + " VALID " + to_string(r.status_code) + "\n" + RESET;
        return returnval;
    }
    else if (r.status_code == 401) {
        string returnval = RED + token + " INVALID " + to_string(r.status_code) + "\n" + RESET;
        return returnval;
    }
    else if (r.status_code == 429) {
        string returnval = YELLOW + token + " RATELIMITED " + to_string(r.status_code) + "\n" + RESET;
        return returnval;
    }
    else {
        return token + CYAN + " ERROR " + to_string(r.status_code) + "\n";
    }
}

void check_crypto_prices() {
    cpr::Response a = cpr::Get(cpr::Url{ "https://min-api.cryptocompare.com/data/price?fsym=XMR&tsyms=USD" });
    json jsonA = json::parse(a.text);
    cpr::Response b = cpr::Get(cpr::Url{ "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD" });
    json jsonB = json::parse(b.text);
    cpr::Response c = cpr::Get(cpr::Url{ "https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD" });
    json jsonC = json::parse(c.text);

    cout << BLUE << "CURRENT CRYPTO PRICES:\n\n" << "Monero: $" << jsonA["USD"] << "USD\n" << "Bitcoin: $" << jsonB["USD"] << "USD\n" << "Ethereum: $" << jsonC["USD"] << "USD\n";
}

int randu(int min, int max) {
    int RANDNUM = min + (rand() % static_cast<int>(max - min + 1));
    return RANDNUM;
}

void paste(string input){
    cpr::Response paste = cpr::Post(cpr::Url{ "https://pastie.io/documents" },
            cpr::Header{ {"content-type", "text/plain"} },
            cpr::Body{ {input} });

        json pastie_response = json::parse(paste.text);
        string key = to_string(pastie_response["key"]);
        string key1 = key.erase(0, 1);
        string key2 = key1.erase(key1.size() - 1);
        cout << BLUE << "view your paste at  https://pastie.io/" << key2 << RESET << endl;
}

/* thanks https://stackoverflow.com/a/3418285/17055513 :> */
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

string colorize_str(string str) {
    if (str.find("{BLACK}") != string::npos) {
        replaceAll(str, "{BLACK}", "\x1b[0;30m");
    }
    if (str.find("{RED}") != string::npos) {
        replaceAll(str, "{RED}", "\x1b[0;31m");
    }
    if (str.find("{GREEN}") != string::npos) {
        replaceAll(str, "{GREEN}", "\x1b[0;32m");
    }
    if (str.find("{YELLOW}") != string::npos) {
        replaceAll(str, "{YELLOW}", "\x1b[0;33m");
    }
    if (str.find("{BLUE}") != string::npos) {
        replaceAll(str, "{BLUE}", "\x1b[0;34m");
    }
    if (str.find("{MAGENTA}") != string::npos) {
        replaceAll(str, "{MAGENTA}", "\x1b[0;35m");
    }
    if (str.find("{CYAN}") != string::npos) {
        replaceAll(str, "{CYAN}", "\x1b[0;36m");
    }
    if (str.find("{WHITE}") != string::npos) {
        replaceAll(str, "{WHITE}", "\x1b[0;37m");
    }
    if (str.find("{RESET}") != string::npos) {
        replaceAll(str, "{RESET}", "\x1b[0;0m");
    }
    string str2 = "```ansi\n" + str + "\n```";
    return str2;
}

void bf_nitro_codes() {
    /* globals */
    int ncodelen = 16;
    string code;

    /* char-choices */
    char valid_nitro_chars[62] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5',
  '6', '7', '8', '9' };

    /* generating the code */
    for (int i = 0; i < ncodelen; i++) {
        int randint = randu(0, 62);
        code += valid_nitro_chars[randint];
    }

    /* testing the validity of the code */
    string URL = "https://discordapp.com/api/v9/entitlements/gift-codes/" + code + "?with_application=false&with_subscription_plan=true";
    cpr::Response r = cpr::Get(cpr::Url{ URL });

    if (r.status_code == 200) {
        cout << GREEN << "https://discord.gift/" + code + " VALID" << endl;
    }
    else {
        cout << YELLOW << "https://discord.gift/" + code + " INVALID" << endl;
    }

}

void makepaste(string TEXT){
  cpr::Response paste = cpr::Post(cpr::Url{ "https://pastie.io/documents" },
            cpr::Header{ {"content-type", "text/plain"} },
            cpr::Body{ { TEXT } });

        json pastie_response = json::parse(paste.text);
        string key = to_string(pastie_response["key"]);
        string key1 = key.erase(0, 1);
        string key2 = key1.erase(key1.size() - 1);
        cout << BLUE << "paste is up at https://pastie.io/" << key2 << RESET << endl;
}


void interpret(string inter) {
    /* thanks https://stackoverflow.com/a/2340309/17055513 :> */
    if (inter.find("help") != string::npos) {
        help();
    }
    else if (inter.find("exit") != string::npos) {
        exit(0);
    }
    else if (inter.find("clear") != string::npos) {
        clearscr();
    }
    else if (inter.find("spam webhook") != string::npos) {
        /* MINI-GLOBALS */
        string hook_url;
        string timesstr;
        int times;
        string message;

        /* USER INPUT */
        cout << BLUE << "webhook url to spam: " << RESET;
        getline(cin, hook_url);

        cout << BLUE << "amount of times to spam: " << RESET;
        getline(cin, timesstr);
        times = stoi(timesstr);

        cout << BLUE << "message to spam: " << RESET;
        getline(cin, message);

        /* SPAM IT! */
        spam_webhook(hook_url, times, message);
    }
    else if (inter.find("userid lookup") != string::npos) {
        /* GLOBALS */
        string userid;

        /* USER INPUT*/
        cout << RED << "input a userid: " << RESET;
        getline(cin, userid);

        userid_lookup(userid);
    }
    else if (inter.find("disable token") != string::npos) {
        /* mini global things */
        string token;
        string choice;

        /* user input */
        cout << RED << "input a token to disable: " << RESET;
        getline(cin, token);

        cout << YELLOW << "WARNING: THIS WILL PERMANENTLY DISABLE THE ACCOUNT. ARE YOU SURE?: y/n >> ";
        getline(cin, choice);

        if (choice == "y") {
            disable_token(token);
        }
        else if (choice == "n") {
            cout << BLUE << "alright, aborting the token disable." << endl;
        }
    }
    else if (inter.find("delete webhook") != string::npos) {
        /* mini globals jej */
        string hook;

        /* user input yea */
        cout << RED << "input a webhook to delete: " << RESET;
        getline(cin, hook);

        /* the fun part: actually deleting it lol */
        delete_webhook(hook);
    }
    else if (inter.find("clone webpage") != string::npos) {
        /* globals */
        string URL;

        /* user input */
        cout << RED << "input the exact url to the html webpage you'd like to clone: " << RESET;
        getline(cin, URL);

        /* pageclone call */
        clone_page(URL);
    }
    else if (inter.find("ip lookup") != string::npos) {
        /* globals yea */
        string IP;

        /* user input */
        cout << RED << "ip to lookup: " << RESET;
        getline(cin, IP);

        /* calling the function ofc :> */
        lookup_ip(IP);
    }
    else if (inter.find("image search") != string::npos) {
        /* globals ez */
        string IMG_URL;

        /* ez user input */
        cout << RED << "image url: " << RESET;
        getline(cin, IMG_URL);

        /* searching it */
        yand_image_search(IMG_URL);
    }
    else if (inter.find("token checker") != string::npos) {
        /* globals :AYAYA: */
        string inputtedtokenfile;
        string line;
        ifstream tokenfile;

        /* user input momen */
        cout << RED << "file containing token list: " << RESET;
        getline(cin, inputtedtokenfile);

        /* checking input validity */
        if (inputtedtokenfile.find(".txt") == string::npos) {
            inputtedtokenfile = inputtedtokenfile + ".txt";
        }
        cout << RED << "reading from file \"" << inputtedtokenfile << "\"" << endl;
        tokenfile.open(inputtedtokenfile);

        if (!tokenfile.is_open()) {
            cout << YELLOW <<
"there was an error opening " << inputtedtokenfile << endl;
        }
        else {
            while (getline(tokenfile, line)) {
                cout << check_token_validity(line);
            }
        }
    }
    else if (inter.find("cryptos") != string::npos) {
        /* just running the function, no user input is necessary */
        check_crypto_prices();
    }
    else if (inter.find("nitro gen") != string::npos) {
        int times;
        string timesstr;
        cout << RED << "times to bruteforce (int): ";
        getline(cin, timesstr);
        times = stoi(timesstr);
        for (int i = 0; i < times; i++) {
            bf_nitro_codes();
        }
    }
    else if (inter.find("colored codeblock") != string::npos) {
    /* globals :> */
    string preformatted;

    /* lemme tell them how to use it first lol */
    cout << RED << "open https://github.com/13-05/redpoint/blob/main/etc/autoANSIinstructions.md in a browser for instructions on how to format your input correctly!" << endl;

    /* user input!! */
    cout << RED << "input the text: " << RESET;
    getline(cin, preformatted);

    /* let's send it to a paste so the escape char doesnt make the text */
    /* colored right in the terminal... */
    string formatted = colorize_str(preformatted);
    cpr::Response paste = cpr::Post(cpr::Url{ "https://pastie.io/documents" },
        cpr::Header{ {"content-type", "text/plain"} },
        cpr::Body{ {formatted} });

    json pastie_response = json::parse(paste.text);
    string key = to_string(pastie_response["key"]);
    string key1 = key.erase(0, 1);
    string key2 = key1.erase(key1.size() - 1);

    cout << BLUE << "now, copy the text at https://pastie.io/" << key2 << " and paste it in discord!" << endl;

    }
    else if (inter.find("make paste") != string::npos){
      /* mini globals hehe */
      string inp;

      /* user input */
      cout << RED << "text to paste: ";
      getline(cin, inp);

      /* making da paste :D */
      makepaste(inp);
    }
}

int main()
{
    /* ENABLE COLORS */
    enable_color_on_WIN();

    /* GLOBALS */
    int constant = 1;
    string input;
    string username;

    /* WELCOME AND GET USERNAME*/
    cout << RED << ""; // set screen to red by default
    welcome();

    /* INPUT INTERPRETATION */
    while (constant == 1) {
        cout << RED << "red@redpoint:" << BLUE << "~" << WHITE << "$ ";
        getline(cin, input);
        interpret(input);
    }
    return 0;
}
