#include <iostream>
#include <windows.h>
using namespace std;

void sendKeyInput(WORD vk, bool up) {
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vk & 0xFF;
	input.ki.dwFlags = up ? KEYEVENTF_KEYUP: 0;
	UINT result = SendInput(1, &input, sizeof(input));
	if(result != 1) {
		cerr << "Error sending key (" << int(vk) << ")!" << endl;
		cerr << "GetLastError() = " << GetLastError() << endl;
	}
}

void sendKeyModifers(WORD vk, bool up) {
	const static int SHIFT = 1 << 8;
	const static int CTRL = 1 << 9;
	const static int ALT = 1 << 10;
	if(vk & SHIFT) {
		sendKeyInput(VK_SHIFT, up);
	}
	if(vk & CTRL) {
		sendKeyInput(VK_CONTROL, up);
	}
	if(vk & ALT) {
		sendKeyInput(VK_MENU, up);
	}
}

WORD charToVk(char ch) {
	SHORT vk = VkKeyScanEx(ch, nullptr);
	return vk;
}

void typeChar(char ch) {
	const static int KEYS_PER_SEC = 25;
	WORD vk = charToVk(ch);
	sendKeyModifers(vk, false);
	sendKeyInput(vk, false);
	Sleep(1000 / KEYS_PER_SEC);
	sendKeyInput(vk, true);
	sendKeyModifers(vk, true);
}

int main() {
	const static int DELAY = 2;
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
