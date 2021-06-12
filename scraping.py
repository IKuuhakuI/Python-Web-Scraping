from bs4 import BeautifulSoup
import requests
from urllib.request import urlopen as uReq
import time

def getUrl (searchTerm, loja):
	if (loja == 'amazon'):
		template = 'https://www.amazon.com.br/s?k={}'
		searchTerm = searchTerm.replace (' ', '+')

	elif (loja == 'americanas'):
		template = 'https://www.americanas.com.br/busca/{}'
		searchTerm = searchTerm.replace (' ', '-')

	elif (loja == 'submarino'):
		template = 'https://www.submarino.com.br/busca/{}'
		searchTerm = searchTerm.replace (' ', '-')

	return template.format(searchTerm)

def getSubmarinoItem (item):
	gotContent = False

	while (gotContent == False):
		url = getUrl(item, 'submarino')
		print (url)
		print ('Aguarde...')
		headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.76 Safari/537.36', "Upgrade-Insecure-Requests": "1","DNT": "1","Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","Accept-Language": "en-US,en;q=0.5","Accept-Encoding": "gzip, deflate"}

		html_text = requests.get(url, headers=headers).text
		soup = BeautifulSoup (html_text ,'lxml')
		products = soup.find_all ('div', class_ = 'src__Wrapper-r60f4z-0 jRHnRS')
		if (products != []):
			gotContent = True

	productList = []

	for product in products:
		name = product.find('span', class_ = 'src__Text-sc-154pg0p-0 src__Name-r60f4z-1 keKVYT').text

		productLink = ""

		price = True
		for a in product.find_all('a', href=True):
			productLink = a['href']
			break

		try:		
			currentPrice = product.find ('span', class_ = 'src__Text-sc-154pg0p-0 src__PromotionalPrice-r60f4z-6 kTMqhz').text

			if currentPrice[0] != 'R' and currentPrice[1] != '$':
				price = False
				break

			else:
				currentPrice = currentPrice [3:]
		except:
			price = False

		if price == True:	
			currentProduct = (name, currentPrice, productLink, "submarino")
			productList.append (currentProduct)

	return tuple(productList)

def getAmericanasItem (item):
	gotContent = False

	while (gotContent == False):
		url = getUrl(item, 'americanas')
		print (url)
		print ('Aguarde...')
		headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.76 Safari/537.36', "Upgrade-Insecure-Requests": "1","DNT": "1","Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8","Accept-Language": "en-US,en;q=0.5","Accept-Encoding": "gzip, deflate"}

		html_text = requests.get(url, headers=headers).text
		soup = BeautifulSoup (html_text ,'lxml')
		products = soup.find_all ('div', class_ = 'src__Wrapper-sc-1k0ejj6-2 dGIFSc')
		if (products != []):
			gotContent = True

	productList = []

	for product in products:
		name = product.find('span', class_ = 'src__Text-sc-154pg0p-0 src__Name-sc-1k0ejj6-3 dSRUrl').text

		productLink = ""

		price = True
		for a in product.find_all('a', href=True):
			productLink = a['href']
			break
		
		currentPrice = product.find ('span', class_ = 'src__Text-sc-154pg0p-0 src__PromotionalPrice-sc-1k0ejj6-7 iIPzUu').text

		if currentPrice[0] != 'R' and currentPrice[1] != '$':
			price = False
			break

		else:
			currentPrice = currentPrice [3:]
			if currentPrice[-1] == 'e':
				currentPrice = currentPrice[:-14]
		if price == True:	
			currentProduct = (name, currentPrice, productLink, "americanas")
			productList.append (currentProduct)

	return tuple(productList)


def getAmazonItem (item):
	gotContent = False

	while (gotContent == False):
		url = getUrl(item, 'amazon')

		print ('Aguarde...')
		html_text = requests.get(url).text
		soup = BeautifulSoup (html_text, 'lxml')
		products = soup.find_all ('div', class_ = 'sg-col-4-of-12 s-result-item s-asin sg-col-4-of-16 sg-col sg-col-4-of-20')
		if (products != []):
			gotContent = True

	productList = []

	for product in products:
		name = product.find('span', class_ = 'a-size-base-plus a-color-base a-text-normal').text
		price = True

		productLink = ""

		for a in product.find_all('a', href=True):
			productLink = a['href']
			break

		try:
			priceWhole = product.find ('span', class_ = 'a-price-whole').text
			priceFraction = product.find ('span', class_ = 'a-price-fraction').text
		except:
			price = False

		if price == True:
			completePrice = priceWhole + priceFraction
			currentProduct = (name, completePrice, productLink, "amazon")
			productList.append (currentProduct)

	return tuple(productList)

#print(getSubmarinoItem ('Iphone X'))
