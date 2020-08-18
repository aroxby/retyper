#include <iostream>
#include <windows.h>
using namespace std;

void sendKeyInput(WORD vk, bool up) {
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vk;
	input.ki.dwFlags = up ? KEYEVENTF_KEYUP: 0;
	UINT result = SendInput(1, &input, sizeof(input));
	if(result != 1) {
		cerr << "Error sending key (" << int(vk) << ")!" << endl;
		cerr << "GetLastError() = " << GetLastError() << endl;
	}
}

WORD charToVk(char ch) {
	// TODO: Does this work with modifers like ctrl?
	SHORT vk = VkKeyScanEx(ch, nullptr);
	return vk;
}

void typeChar(char ch) {
	int KEYS_PER_SEC = 10;
	sendKeyInput(charToVk(ch), false);
	Sleep(1000 / KEYS_PER_SEC);
	sendKeyInput(charToVk(ch), true);
}

int main() {
	int DELAY = 2;
	Sleep(DELAY * 1000);

	for(;;) {
		char ch = cin.get();
		if(ch == EOF) {
			break;
		}
		typeChar(ch);
	}
	return 0;
}
