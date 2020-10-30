import time
import cv2
import mss
import numpy as np
import pyautogui

COUNTDOWN_FROM = 5
NUM_PIXELS = 2000
DO_BEEP = True
MOVE_STEPS = 10
PAUSE_AFTER_EVENT = 5

for i in range(COUNTDOWN_FROM, 0, -1):
    print('Capture starts in %d...' % i)
    time.sleep(1)

img_prev = None
with mss.mss() as sct:
    while True:
        img = cv2.cvtColor(np.array(sct.grab(sct.monitors[1])), cv2.COLOR_BGRA2GRAY)
        if img_prev is not None:
            diff = cv2.absdiff(img, img_prev)
            _, thresh = cv2.threshold(diff, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
            if (thresh == 0).sum() > NUM_PIXELS:
                if DO_BEEP:
                    print('\a')
                contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
                centerX = np.mean([c[0][0] for c in contours[1]])
                centerY = np.mean([c[0][1] for c in contours[1]])
                #print(centerX, centerY); cv2.imshow("thresh", 255 - thresh); cv2.waitKey(10000); exit();  # debug
                currentX, currentY = pyautogui.position()
                targetX, targetY = 100, 100
                stepX, stepY = (centerX - currentX) / MOVE_STEPS, (centerY - currentY) / MOVE_STEPS
                for _ in range(MOVE_STEPS):
                    pyautogui.move(stepX, stepY)
                time.sleep(0.5);
                pyautogui.click()
                time.sleep(PAUSE_AFTER_EVENT)
                img_prev = None
                continue
        img_prev = img
