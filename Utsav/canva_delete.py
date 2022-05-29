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
	driver.get("https://www.canva.com/folder/trash")
	return driver

def startdeleting(driver, gstnum):	
	lol = driver.find_element_by_xpath("//button[text()='Images']")
	l.click()
	time.sleep(40)
	"""
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
	"""

if __name__=="__main__":
	driver = open_browser()
	startdeleting(driver)
