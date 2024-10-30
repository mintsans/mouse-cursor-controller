#include <windows.h>
#include <stdio.h>

#define MOVE_DISTANCE 5

void simulateMouseMove(int xOffset, int yOffset) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x + xOffset, cursorPos.y + yOffset);
}

int main() {
    int isLeftButtonDown = 0;  // ��Ŭ�� ���� ���� ����

    printf("Press Ctrl+C to exit.\n");

    // ���� ��ġ ����
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    while (1) {
        int xOffset = 0, yOffset = 0;

        // ȭ��ǥ Ű �Է¿� ���� �̵� �Ÿ� ����
        if (GetAsyncKeyState(VK_UP) & 0x8000) yOffset -= MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) yOffset += MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) xOffset -= MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) xOffset += MOVE_DISTANCE;

        // ȭ��ǥ Ű�� ���� ��쿡�� Ŀ�� �̵�
        if (xOffset != 0 || yOffset != 0) {
            simulateMouseMove(xOffset, yOffset);
        }
        else {
            // ȭ��ǥ Ű�� ������ ������ Ŀ���� ������ ��ġ�� ����
            SetCursorPos(cursorPos.x, cursorPos.y);
        }

        // Z Ű�� ��Ŭ�� ����
        if (GetAsyncKeyState('Z') & 0x8000) {
            if (!isLeftButtonDown) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                isLeftButtonDown = 1;
            }
        }
        else if (isLeftButtonDown) {  // Z Ű�� ���� ��Ŭ�� ����
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            isLeftButtonDown = 0;
        }

        // X Ű�� ��Ŭ��
        if (GetAsyncKeyState('X') & 0x8000) {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            Sleep(10);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }

        // ���� Ŀ�� ��ġ ����
        GetCursorPos(&cursorPos);

        Sleep(1);  // �ݺ� �ӵ� ����
    }

    return 0;
}
