#include <windows.h>
#include <stdio.h>

#define MOVE_DISTANCE_FAST 5   // �⺻ �̵� �ӵ� (�� ������)
#define MOVE_DISTANCE_SLOW 1    // ���� �̵� �ӵ�

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
        int moveDistance = MOVE_DISTANCE_FAST;  // �⺻ �̵� �ӵ��� ����

        // Shift Ű�� ���� ��� �̵� �ӵ� ����
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
            moveDistance = MOVE_DISTANCE_SLOW;
        }

        // ȭ��ǥ Ű �Է¿� ���� �̵� �Ÿ� ����
        if (GetAsyncKeyState(VK_UP) & 0x8000) yOffset -= moveDistance;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) yOffset += moveDistance;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) xOffset -= moveDistance;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) xOffset += moveDistance;

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

        Sleep(5);  // �ſ� ª�� ���� �ð����� �̵� �ε巴��
    }

    return 0;
}
