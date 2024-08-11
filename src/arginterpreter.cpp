#include <string>
#include <unistd.h>
#include <getopt.h>

#include "ArgInterpreter.h"
#include "Logger.h"

using namespace std;

argstruct ArgInterpreter::GetArgs(int argc, char* argv[])
{
    argstruct args = argstruct();
    
    static struct option long_options[] = 
    {
        {"help", no_argument, nullptr, 'n'},
        {0, 0, 0, 0}
    };

    int arg;
    int option_index = 0;
    bool config_specified = false;
    bool ascii_specified = false;
    bool verb_set = false;

    while ((arg = getopt_long(argc, argv, "x:y:v:i:c:h", long_options, &option_index)) != -1)
    {
        switch (arg)
        {
            case 'h':
                args.help_requested = true;
                Logger::PrintUsage();
                return args;

            case 'c':
                if (optarg)
                {
                    config_specified = true;
                    args.config_path = optarg;
                    Logger::PrintLog(string("Config file path set to: '") + optarg + string("'"));
                }

            case 'v':
                if (optarg)
                {
                    if (verb_set) break;
                    verb_set = true;
                    Logger::SetVerbosity(stoi(optarg));
                    Logger::PrintLog(string("Verbosity set to: ") + optarg);
                }
                break;

            case 'i':
                if (optarg)
                {
                    args.ascii_path = optarg;
                    ascii_specified = true;
                    Logger::PrintLog(string("Ascii file path set to: '") + args.ascii_path + string("'"));
                }
                break;

            case 'x':
                if (optarg)
                {
                    args.ox = stoi(optarg);
                    Logger::PrintLog(string("Offset X set to: ") + optarg);
                }
                break;

            case 'y':
                if (optarg)
                {
                    args.oy = stoi(optarg);
                    Logger::PrintLog(string("Offset Y set to: ") + optarg);
                }
                break;

            case 'n':
                args.help_requested = true;
                Logger::PrintUsage();
                return args;
        }
    }

    if (!config_specified)
    {
        Logger::PrintWarn("Config file was not specified!");
    }

    if (!ascii_specified)
    {
        Logger::PrintErr("Ascii file was not specified!");
        args.exit = true;
    }

    return args;
}