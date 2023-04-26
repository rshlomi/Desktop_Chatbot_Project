#include <iostream>
#include <array>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

int main() {
    array<char, 128> buffer{};
    string output;

    string api_key = "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";
    string prompt;
    cout << "What would you like to ask?\n";

    while (prompt != "quit")
    {
//        cin >> prompt;
        getline(cin, prompt);
//        cout << prompt;

    // Transfer data from openai server
        string command11 =
                R"(curl -s https://api.openai.com/v1/chat/completions -H "Content-Type: application/json" -H "Authorization: Bearer )";
        string command12 = R"(" -d '{"model": "gpt-3.5-turbo", "messages": [{"role": "user", "content": ")";
        string command2 = R"("}]}')";
        string joined = command11 + api_key + command12 + prompt + command2;

        //    cout << joined;

        // Open a pipe to read the output of the command
        FILE* pipe = popen(joined.c_str(), "r");
        if (!pipe) {
            cerr << "Error: Failed to open pipe for command: " << joined << std::endl;
            return 1;
        }

        // Read the output of the command into a string variable
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            output += buffer.data();
        }
        // Print the output


        json json_data = json::parse(output);

        string content = json_data["choices"][0]["message"]["content"];

        cout << "" << content << endl;

        // Close the pipe
        pclose(pipe);

        // alternative to pipe:
//        std::system(joined.c_str());
    }
}
