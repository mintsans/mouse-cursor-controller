#include <windows.h>
#include <stdio.h>

#define MOVE_DISTANCE 5

void simulateMouseMove(int xOffset, int yOffset) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    SetCursorPos(cursorPos.x + xOffset, cursorPos.y + yOffset);
}

int main() {
    int isLeftButtonDown = 0;  // 좌클릭 상태 추적 변수

    printf("Press Ctrl+C to exit.\n");

    // 시작 위치 설정
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    while (1) {
        int xOffset = 0, yOffset = 0;

        // 화살표 키 입력에 따라 이동 거리 설정
        if (GetAsyncKeyState(VK_UP) & 0x8000) yOffset -= MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) yOffset += MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) xOffset -= MOVE_DISTANCE;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) xOffset += MOVE_DISTANCE;

        // 화살표 키가 눌린 경우에만 커서 이동
        if (xOffset != 0 || yOffset != 0) {
            simulateMouseMove(xOffset, yOffset);
        }
        else {
            // 화살표 키가 눌리지 않으면 커서를 마지막 위치로 고정
            SetCursorPos(cursorPos.x, cursorPos.y);
        }

        // Z 키로 좌클릭 유지
        if (GetAsyncKeyState('Z') & 0x8000) {
            if (!isLeftButtonDown) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                isLeftButtonDown = 1;
            }
        }
        else if (isLeftButtonDown) {  // Z 키를 떼면 좌클릭 해제
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            isLeftButtonDown = 0;
        }

        // X 키로 우클릭
        if (GetAsyncKeyState('X') & 0x8000) {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            Sleep(10);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }

        // 현재 커서 위치 저장
        GetCursorPos(&cursorPos);

        Sleep(1);  // 반복 속도 조절
    }

    return 0;
}
