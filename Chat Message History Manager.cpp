#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

// Struct for a chat message
struct Message {
    string text;
    string timestamp;

    Message(string t = "") {
        text = t;
        timestamp = getTimestamp();
    }

    static string getTimestamp() {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        string ts = ctime(&now_time);
        ts.pop_back(); // remove newline
        return ts;
    }
};

// Chat Manager
class ChatManager {
private:
    queue<Message> inbox;           // incoming messages
    stack<Message> sentMessages;    // sent messages (for undo)
    stack<Message> undoneMessages;  // undone messages (for redo)

public:
    // Send message
    void sendMessage(const string& text) {
        Message msg(text);
        sentMessages.push(msg);
        while(!undoneMessages.empty()) undoneMessages.pop(); // clear redo history
        cout << "Message sent: \"" << msg.text << "\" at " << msg.timestamp << "\n";
    }

    // Receive message
    void receiveMessage(const string& text) {
        Message msg(text);
        inbox.push(msg);
        cout << "Message received: \"" << msg.text << "\" at " << msg.timestamp << "\n";
    }

    // Show inbox messages
    void showInbox() {
        if(inbox.empty()) {
            cout << "Inbox is empty.\n";
            return;
        }
        cout << "\n--- Inbox Messages ---\n";
        queue<Message> temp = inbox;
        while(!temp.empty()) {
            cout << temp.front().timestamp << " | " << temp.front().text << "\n";
            temp.pop();
        }
    }

    // Show sent messages
    void showSent() {
        if(sentMessages.empty()) {
            cout << "No sent messages.\n";
            return;
        }
        cout << "\n--- Sent Messages ---\n";
        stack<Message> temp = sentMessages;
        while(!temp.empty()) {
            cout << temp.top().timestamp << " | " << temp.top().text << "\n";
            temp.pop();
        }
    }

    // Undo last sent message
    void undoMessage() {
        if(sentMessages.empty()) {
            cout << "No messages to undo.\n";
            return;
        }
        Message undone = sentMessages.top();
        sentMessages.pop();
        undoneMessages.push(undone);
        cout << "Undo: \"" << undone.text << "\" removed from sent messages.\n";
    }

    // Redo last undone message
    void redoMessage() {
        if(undoneMessages.empty()) {
            cout << "No messages to redo.\n";
            return;
        }
        Message redone = undoneMessages.top();
        undoneMessages.pop();
        sentMessages.push(redone);
        cout << "Redo: \"" << redone.text << "\" re-sent.\n";
    }
};

// ------------------ Main ------------------
int main() {
    ChatManager chat;
    int choice;
    string text;

    do {
        cout << "\n=== Chat Message History Manager ===\n";
        cout << "1. Send Message\n";
        cout << "2. Receive Message\n";
        cout << "3. Show Inbox\n";
        cout << "4. Show Sent Messages\n";
        cout << "5. Undo Last Sent\n";
        cout << "6. Redo Last Undone\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        if(!(cin >> choice)) break;

        cin.ignore(); // clear newline from buffer

        switch(choice) {
            case 1:
                cout << "Enter message to send: ";
                getline(cin, text);
                chat.sendMessage(text);
                break;
            case 2:
                cout << "Enter message to receive: ";
                getline(cin, text);
                chat.receiveMessage(text);
                break;
            case 3:
                chat.showInbox();
                break;
            case 4:
                chat.showSent();
                break;
            case 5:
                chat.undoMessage();
                break;
            case 6:
                chat.redoMessage();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 7);

    return 0;
}
