#include <iostream>
#include <array>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

class OpenAIChatbot {
public:
    OpenAIChatbot(const std::string& api_key): m_api_key(api_key) {}

    std::string generate_curl_command(const std::string& prompt) {
        string endpoint =
                R"(curl -s https://api.openai.com/v1/chat/completions)";
        string command11 =
                R"( -H "Content-Type: application/json" -H "Authorization: Bearer )";
        string command12 = R"(" -d '{"model": "gpt-3.5-turbo", )";
        string messages = R"( "messages": [{"role": "user", "content": ")";
        string command2 = R"("}]}')";
        string joined = endpoint + command11 + m_api_key + command12 + messages + prompt + command2;
        return joined;
    }

    void run() {
        array<char, 128> buffer{};
        string output;
        string prompt;

        cout << "What would you like to ask?\n";

        while (prompt != "quit")
        {
            getline(cin, prompt);

            string joined = generate_curl_command(prompt);

            // Open a pipe to read the output of the command
            FILE* pipe = popen(joined.c_str(), "r");
            if (!pipe) {
                cerr << "Error: Failed to open pipe for command: " << joined << std::endl;
                return;
            }

            // Read the output of the command into a string variable
            while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
                output += buffer.data();
            }
            // Parse and print the output
            json json_data = json::parse(output);
            string content = json_data["choices"][0]["message"]["content"];
            cout << "" << content << endl;

            // Close the pipe
            pclose(pipe);
        }
    }

private:
    std::string m_api_key;
};

int main() {
    string api_key = "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";
    OpenAIChatbot chatbot(api_key);
    chatbot.run();
    return 0;
}
