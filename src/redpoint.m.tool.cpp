// #define _CRT_SECURE_NO_WARNINGS
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
using namespace std;
using json = nlohmann::json;

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


void check_for_updates() {

    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);

    cpr::Response ver = cpr::Get(cpr::Url{"https://raw.githubusercontent.com/13-05/redpoint/main/etc/VERSION.txt"});

    string version = ver.text;
    string new_version;

    if (!version.empty() && version[version.length() - 1] == '\n') {
        new_version = version.erase(version.length() - 1);
    }
    else {
        version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
        new_version = version;
    }

    if (new_version.find(REDPOINT_VERSION) == string::npos && new_version.find("404") == string::npos) {
        string ex;
        cout << RED << "A new RedPoint version is available!" << endl;
        cout << BLUE << "Download it here: https://github.com/13-05/redpoint/blob/main/redpoint/VERSION_" << new_version << ".txt" << endl;
        cout << MAGENTA << "Press ENTER to close the program..." << endl;
        getline(cin, ex);
        exit(0);
    }
    else {
        cout << RED << "RedPoint is up to date!" << endl;
        Sleep(5000);
    }
}

void clearscr() {
#ifdef _WIN32 // Includes both 32 bit and 64 bit
    system("cls");
#else
    system("clear"); // os is probs a linux distro, so call "clear"
#endif
}

void help() {
    cout << "\n\n";
    cout << MAGENTA << "USABLE COMMANDS: \n\n";
    cout << MAGENTA << "1)" << WHITE << " exit " << BLUE << " | " << GREEN << " exits the program" << endl;
    cout << MAGENTA << "2)" << WHITE << " clear " << BLUE << " | " << GREEN << " clears the screen" << endl;


    cout << MAGENTA << "3)" << BLUE << " spam webhook " << BLUE << " | " << GREEN << " spams a discord webhook" << endl;
    cout << MAGENTA << "4)" << BLUE << " delete webhook " << BLUE << " | " << GREEN << " deletes a provided discord webhook" << endl;
    cout << MAGENTA << "5)" << BLUE << " userid lookup " << BLUE << " | " << GREEN << " gets info on a discord user by their id" << endl;
    cout << MAGENTA << "6)" << BLUE << " disable token " << BLUE << " | " << GREEN << " disables the account associated with a provided token " << endl;

    cout << MAGENTA << "7)" << RED << " clone webpage " << BLUE << " | " << GREEN << " gets the source code of a specified html webpage; command-line \"view source\"" << endl;
    cout << MAGENTA << "8)" << RED << " ip lookup " << BLUE << " | " << GREEN << " gets information about the specified Ipv4 address" << endl;
    cout << MAGENTA << "9)" << RED << " image search " << BLUE << " | " << GREEN << " uses the yandex image search api to find similar images to the inputted url" << endl;

    cout << "\n\n";
}

void welcome() {
    const char* welcomestr =
        "  ______ _______ ______   _____   _____  _____ __   _ _______\n"
        " |_____/ |______ |     \\ |_____] |     |   |   | \\  |    |   \n"
        " |    \\_ |______ |_____/ |       |_____| __|__ |  \\_|    |   ";
    DWORD dwMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
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
    

    cout << "username: " << uname << endl << "discrim: " << discrim << endl << "bot?: " << bot_bool << endl << "(unix) creation date: " << unixtimestr << endl;
}

void disable_token(string token) {
    cout << BLUE << "attempting to disable token " << token << RESET << endl;
    cpr::Response r = cpr::Patch(cpr::Url{ "https://discord.com/api/v9/users/@me" },
        cpr::Header{ {"user-agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)"}},
        cpr::Payload{ {"date_of_birth", "2022-1-1"} });
}

void clone_page(string exac_page_url) {
    cpr::Response r = cpr::Get(cpr::Url{ exac_page_url },
        cpr::Header{ {"user-agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)"}});
    if (r.status_code != 200) {
        cout << YELLOW << "there was an error cloning the page." << endl;
    }
    else {
        cpr::Response paste = cpr::Post(cpr::Url{ "https://pastie.io/documents" },
            cpr::Header{ {"content-type", "text/plain"}},
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
    cout << YELLOW << "attempted to delete the webhook." << RESET << endl;
}

void yand_image_search(string url) {
    cpr::Response r = cpr::Get(cpr::Url{"https://n.mnfd.link/new"},
        cpr::Header{ {"host", "n.mnfd.link"}},
        cpr::Header{ {"user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:93.0) Gecko/20100101 Firefox/93.0"}});
    cout << r.status_code << endl;
    json shortened_res_url = json::parse(r.text);
    cout << RED << "find image search results at " << GREEN << "https://n.mnfd.link/" << shortened_res_url["id"] << endl;
}

void interpret(string inter) {
    /* thanks https://stackoverflow.com/a/2340309/17055513 :> for da string::npos and str.find ykyk */
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
        cout << RED << "input the ip you'd like to gather information on: " << RESET;
        getline(cin, IP);

        /* calling the function ofc :> */
        lookup_ip(IP);
    }
    else if (inter.find("image search") != string::npos) {
        /* globals jej */
        string URL;
        string URLTOSEARCH;

        /* user input */
        cout << RED << "input image url to reverse search: " << RESET;
        getline(cin, URL);

        URLTOSEARCH = "https://yandex.com/images/search?source=collections&&url=" + URL + "&rpt=imageview";

        yand_image_search(URLTOSEARCH);
    }
}

int main()
{
    check_for_updates();

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
