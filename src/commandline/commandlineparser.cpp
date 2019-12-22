#include "commandlineparser.h"

CommandLineParser::CommandLineParser(int argc, char *argv[])
    : QCommandLineParser()
{
    setApplicationDescription("Hot reload for nested qml files.");
    addVersionOption();

    for (const auto optionStruct : _optionsStruct) {
        addOption(optionStruct.option);
    }

    QStringList arguments;
    for(int i{0}; i < argc; i++) {
        arguments.append(argv[i]);
    }
    process(arguments);

    for (const auto optionStruct : _optionsStruct) {
        if(!isSet(optionStruct.option)) {
            continue;
        }

        // Check if there is a result and if the option accepts it
        if (!optionStruct.option.valueName().isEmpty()) {
            QString result = value(optionStruct.option);
            if (!result.isEmpty()) {
                qDebug().noquote() << QStringLiteral("%1 [%2]: %3")
                                                .arg(optionStruct.option.names().first(),
                                                    optionStruct.option.description(), result);
                optionStruct.function(result);
            } else {
                qDebug().noquote() << QStringLiteral("%1 [%2]: %3")
                                                .arg(optionStruct.option.names().first(),
                                                    optionStruct.option.description(), "No valid parameter.");
            }
        } else {
            qDebug().noquote() << QStringLiteral("%1 [%2]: ON")
                                              .arg(optionStruct.option.names().first(),
                                                  optionStruct.option.description());
            optionStruct.function({});
        }
    }
};

void CommandLineParser::printHelp()
{
    for (const auto& optionStruct : _optionsStruct) {
        auto names = optionStruct.option.names();
        for(auto& name: names) {
            name.prepend(name.length() > 1 ? "--" : "-");
        }

        qDebug().noquote() << names.join(", ") << "\t\t\t" << optionStruct.option.description();
    }
}
