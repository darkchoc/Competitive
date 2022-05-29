import sys
import pandas as pd
from selenium import webdriver
from bs4 import BeautifulSoup
import time 

from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def open_browser():
	driver = webdriver.Chrome("/usr/local/bin/chromedriver")
	driver.get("https://www.mastersindia.co/gst-number-search-and-gstin-verification/")
	return driver

def getinfo(driver, gstnum):	
	gstbox = driver.find_element_by_class_name('inputbox')
	gstbox.clear()
	gstbox.send_keys(gstnum)

	submit = WebDriverWait(driver, 3).until(EC.presence_of_element_located((By.NAME, "Submit")))
	submit.click()

	time.sleep(2)
	soup = BeautifulSoup(driver.page_source)
	list_of_items = []
	try:
		table = soup.select('table')[0]
		items = table.select('tr')[1]
		for i, item in enumerate(items.select('td')):
			if i>0 and i<6:	
				list_of_items.append(item.text)
	except:
		list_of_items.append("Not Found")
	return list_of_items

if __name__=="__main__":
	list_of_gst = []
	file_pointer = open("/Users/raghav.ma/Codes/Utsav/Book1.csv","r")
	
	for cnt, line in enumerate(file_pointer):
		if cnt < 2 or cnt > 5:
			continue
		gst_number = line.split(",")[2].strip()
		list_of_gst.append(gst_number)
 
	file_pointer.close()
	
	driver = open_browser()
	with open("/Users/raghav.ma/Codes/Utsav/CompanyList.csv", "w") as fw:
		for gstnums in list_of_gst:
			details = getinfo(driver, gstnums)
			row = gstnums
			for tokens in details:
				row += '\t' + str(tokens.replace("\n"," "))
			fw.write("%s\n"%(row))
