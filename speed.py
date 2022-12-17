from selenium import webdriver
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.common.by import By
import cv2
from gspread import service_account
from IPython.display import Image
import webbrowser
# import easyocr

class DemoFind():
    def locate(self):
        driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
        driver.get("http://192.168.1.17/")
        text = driver.find_element(By.XPATH, "/html/body/center/p/strong").text
        return text

def equalizeHistColor(frame):
    img = cv2.cvtColor(frame, cv2.COLOR_RGB2HSV)  
    img[:,:,2] = cv2.equalizeHist(img[:,:,2])  
    return cv2.cvtColor(img, cv2.COLOR_HSV2RGB)

# sa = service_account()
# sheet = sa.open('Speed_Detection')
# wks = sheet.sheet1

global i
i = 1
webcam = cv2.VideoCapture(0)
find=DemoFind()
l = []
while True:
    webcam = cv2.VideoCapture(0)
    var = find.locate()
    if float(var) >= 25 and float(var) not in l:
        check, frame = webcam.read()
        cv2.waitKey(1)
        cv2.imwrite(filename='saved_img'+str(i)+'.png', img=frame)
        
        img_new = equalizeHistColor(frame)
        gray = cv2.cvtColor(img_new, cv2.COLOR_BGR2GRAY)
        img_ = cv2.resize(gray,(256,256))
        img_resized = cv2.imwrite(filename='saved_img_'+str(i)+'_final'+'.png', img=img_)
        # reader=easyocr.Reader(['en'])
        # output=reader.readtext('saved_img_'+str(i)+'_final'+'.png')
        # print("Vehicle overspeeding license plate and speed : ",output, var)
        
        webcam.release()
        print("Image saved "+str(i)+" !")
        l.append(float(var))
        print(*l)
        # wks.append_row((i, 'saved_img'+str(i)+''+'.png',var))
        i += 1
    else:
        continue