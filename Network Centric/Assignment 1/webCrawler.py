from bs4 import BeautifulSoup
import requests
from urllib.parse import urlparse
from urllib.parse import urlsplit

def webCrawler(url, webpagename):
	# print ("in for site", url)
	global count, main_page, searched
	r = requests.get(url)
	data = r.text
	soup = BeautifulSoup(data, "html5lib")

	for link in soup.find_all('a'):
		raw = link.get('href')
		if raw is None or str(raw) =="/" or str(raw) == "" or "#" in str(raw) or "@" in str(raw):
			continue
		elif "http" in str(raw) and main_page in str(raw): # embedded site
			if (webpagename in str(raw) and str(raw) not in searched):
				print (raw,"1\n")
				searched.append(str(raw))
				count = count + 1
				webCrawler(raw, webpagename)
		elif "http" in str(raw) and webpagename in str(raw):
			searched.append(str(raw))			
			if str(raw) not in searched:
				count = count + 1
				print(raw,"2\n")
		elif "http" not in str(raw) and "www" not in str(raw) and raw[0]!="/": # /loops
			raw = "/" + raw
			raw = "http://" + main_page + str(raw)
			raw2= "https://" + main_page + str(raw)
			if raw not in searched and raw2 not in searched:
				count = count + 1
				searched.append(str(raw))
				print(raw,"3\n")
				if (webpagename in str(raw)):
					webCrawler(raw, webpagename)
		

searched = []
count = 1
first_link = "http://" + input("Enter website: ")
main_page = str(urlparse(first_link).netloc)
main_page1 = main_page[4: len(main_page) - 4]
#print (main_page1)
webCrawler(first_link, main_page1)
print(count)